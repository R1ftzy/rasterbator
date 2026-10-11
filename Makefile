# Thin wrapper around CMake, which is the source of truth (see CMakeLists.txt).
# Defaults to the MinGW/clang toolchain (the MSVC build currently hits a heap
# corruption). Override if you know what you're doing:
#   make GEN="Visual Studio 18 2026" CC=cl
# BACKEND selects the window backend: sdl (default) or win32.

CMAKE  ?= cmake
BUILD  ?= build
BACKEND ?= sdl
GEN    ?= MinGW Makefiles
CC     ?= gcc

all: release

release:
	$(CMAKE) -B $(BUILD) -G "$(GEN)" -DCMAKE_C_COMPILER=$(CC) -DCMAKE_BUILD_TYPE=Release -DRASTERBATOR_BACKEND=$(BACKEND)
	$(CMAKE) --build $(BUILD)

debug:
	$(CMAKE) -B $(BUILD) -G "$(GEN)" -DCMAKE_C_COMPILER=$(CC) -DCMAKE_BUILD_TYPE=Debug -DRASTERBATOR_BACKEND=$(BACKEND)
	$(CMAKE) --build $(BUILD)

win:
	$(CMAKE) -B build-win -G "$(GEN)" -DCMAKE_C_COMPILER=$(CC) -DCMAKE_BUILD_TYPE=Release -DRASTERBATOR_BACKEND=win32
	$(CMAKE) --build build-win

run: release
	./bin/cartest

clean:
	$(CMAKE) -E rm -rf $(BUILD) build-win
	$(CMAKE) -E rm -f bin/cartest bin/cartest.exe bin/SDL3.dll bin/rasterbator.lib bin/librasterbator.a

.PHONY: all release debug win run clean