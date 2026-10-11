cmake_minimum_required(VERSION 3.16)
project(rasterbator C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Keep binaries in bin/ so asset paths (resolved relative to the exe) still work.
set(_rb_outdir ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${_rb_outdir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${_rb_outdir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${_rb_outdir})
foreach(_cfg DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${_cfg} ${_rb_outdir})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${_cfg} ${_rb_outdir})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${_cfg} ${_rb_outdir})
endforeach()

option(RASTERBATOR_BUILD_EXAMPLES "Build example apps" ON)
option(BUILD_SHARED_LIBS "Build rasterbator as a shared library" OFF)
set(RASTERBATOR_BACKEND "sdl" CACHE STRING "Window backend: sdl or win32")
set_property(CACHE RASTERBATOR_BACKEND PROPERTY STRINGS sdl win32)
option(RASTERBATOR_WIN32_ENTRY "Compile the Win32 wWinMain entry into the backend" ON)

set(SDL3_ROOT "${CMAKE_SOURCE_DIR}/external/SDL3")

# ---------------------------------------------------------------------------
# SDL3 bootstrap: if external/SDL3 is missing, pull SDL3, build it, and install
# it into external/SDL3 (matching the include/SDL3 | lib | bin layout).
# ---------------------------------------------------------------------------
if(NOT EXISTS "${SDL3_ROOT}/include/SDL3/SDL.h")
  message(STATUS "SDL3 not found at ${SDL3_ROOT}; bootstrapping (needs git + network once)")
  set(_sdl_src "${CMAKE_BINARY_DIR}/_deps/sdl-src")
  set(_sdl_bld "${CMAKE_BINARY_DIR}/_deps/sdl-build")

  execute_process(COMMAND git clone --depth 1 --branch release-3.4.14
                          https://github.com/libsdl-org/SDL.git "${_sdl_src}"
                  RESULT_VARIABLE _rc)
  if(NOT _rc EQUAL 0)
    message(FATAL_ERROR "SDL3 git clone failed (${_rc})")
  endif()

  execute_process(COMMAND ${CMAKE_COMMAND} -S "${_sdl_src}" -B "${_sdl_bld}"
                          -DSDL_SHARED=ON -DSDL_STATIC=OFF
                          -DSDL_TEST=OFF -DSDL_EXAMPLES=OFF
                          -DCMAKE_BUILD_TYPE=Release
                  RESULT_VARIABLE _rc)
  if(NOT _rc EQUAL 0)
    message(FATAL_ERROR "SDL3 configure failed (${_rc})")
  endif()

  execute_process(COMMAND ${CMAKE_COMMAND} --build "${_sdl_bld}" --config Release
                  RESULT_VARIABLE _rc)
  if(NOT _rc EQUAL 0)
    message(FATAL_ERROR "SDL3 build failed (${_rc})")
  endif()

  execute_process(COMMAND ${CMAKE_COMMAND} --install "${_sdl_bld}" --config Release
                                  --prefix "${SDL3_ROOT}"
                  RESULT_VARIABLE _rc)
  if(NOT _rc EQUAL 0)
    message(FATAL_ERROR "SDL3 install failed (${_rc})")
  endif()
endif()

# Prefer SDL's config package if the tree has one, else define the target from
# the vendored layout.
find_package(SDL3 CONFIG QUIET PATHS "${SDL3_ROOT}/lib/cmake" NO_DEFAULT_PATH)
if(NOT SDL3_FOUND)
  add_library(SDL3::SDL3 SHARED IMPORTED)
  if(WIN32)
    if(MINGW)
      set(_sdl_implib "${SDL3_ROOT}/lib/libSDL3.dll.a")
      if(NOT EXISTS "${_sdl_implib}" AND EXISTS "${SDL3_ROOT}/bin/SDL3.dll")
        find_program(_rb_gendef NAMES gendef)
        find_program(_rb_dlltool NAMES dlltool llvm-dlltool)
        if(NOT _rb_gendef OR NOT _rb_dlltool)
          message(FATAL_ERROR
            "MinGW requires libSDL3.dll.a, or gendef and dlltool must be available "
            "to generate it from ${SDL3_ROOT}/bin/SDL3.dll")
        endif()

        set(_sdl_def "${CMAKE_BINARY_DIR}/_deps/SDL3.def")
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/_deps")
        execute_process(
          COMMAND "${_rb_gendef}" - "${SDL3_ROOT}/bin/SDL3.dll"
          OUTPUT_FILE "${_sdl_def}"
          RESULT_VARIABLE _rc)
        if(NOT _rc EQUAL 0)
          message(FATAL_ERROR "Failed to extract SDL3 exports (${_rc})")
        endif()

        execute_process(
          COMMAND "${_rb_dlltool}" -d "${_sdl_def}" -D SDL3.dll -l "${_sdl_implib}"
          RESULT_VARIABLE _rc)
        if(NOT _rc EQUAL 0)
          message(FATAL_ERROR "Failed to generate ${_sdl_implib} (${_rc})")
        endif()
        message(STATUS "Generated MinGW SDL3 import library: ${_sdl_implib}")
      endif()
    else()
      set(_sdl_implib "${SDL3_ROOT}/lib/SDL3.lib")
    endif()
    set_target_properties(SDL3::SDL3 PROPERTIES
      IMPORTED_LOCATION "${SDL3_ROOT}/bin/SDL3.dll"
      IMPORTED_IMPLIB    "${_sdl_implib}")
  else()
    set_target_properties(SDL3::SDL3 PROPERTIES
      IMPORTED_LOCATION "${SDL3_ROOT}/lib/libSDL3.so")
  endif()
  set_target_properties(SDL3::SDL3 PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${SDL3_ROOT}/include")
endif()

# ---------------------------------------------------------------------------
# rasterbator library
# ---------------------------------------------------------------------------
set(RB_SOURCES
  src/framebuffer.c
  src/draw.c
  src/color.c
  src/vecmath.c
  src/camera.c
  src/obj.c
  src/trans.c
  src/thread_pool.c
  src/render.c)

if(RASTERBATOR_BACKEND STREQUAL "sdl")
  list(APPEND RB_SOURCES src/RB_sdl.c)
elseif(RASTERBATOR_BACKEND STREQUAL "win32")
  list(APPEND RB_SOURCES src/RB_windows.c)
else()
  message(FATAL_ERROR "RASTERBATOR_BACKEND must be 'sdl' or 'win32' (got '${RASTERBATOR_BACKEND}')")
endif()

add_library(rasterbator ${RB_SOURCES})
add_library(rasterbator::rasterbator ALIAS rasterbator)

target_include_directories(rasterbator PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(rasterbator PUBLIC SDL3::SDL3)

if(RASTERBATOR_BACKEND STREQUAL "win32")
  target_link_libraries(rasterbator PUBLIC gdi32 user32)
  target_compile_definitions(rasterbator PUBLIC UNICODE _UNICODE)
  if(RASTERBATOR_WIN32_ENTRY)
    target_compile_definitions(rasterbator PUBLIC RASTERBATOR_WIN32_ENTRY)
  endif()
endif()

# ---------------------------------------------------------------------------
# Example
# ---------------------------------------------------------------------------
if(RASTERBATOR_BUILD_EXAMPLES)
  add_executable(cartest tests/cartest.c)
  target_link_libraries(cartest PRIVATE rasterbator)

  if(RASTERBATOR_BACKEND STREQUAL "win32")
    set_target_properties(cartest PROPERTIES WIN32_EXECUTABLE TRUE)
    if(MSVC)
      target_link_options(cartest PRIVATE /ENTRY:wWinMainCRTStartup)
    else()
      target_link_options(cartest PRIVATE -municode)
    endif()
  endif()

  if(WIN32)
    add_custom_command(TARGET cartest POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
              "$<TARGET_FILE:SDL3::SDL3>"
              "$<TARGET_FILE_DIR:cartest>")
  endif()
endif()