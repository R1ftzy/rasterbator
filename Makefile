# Thin wrapper around CMake, which is the source of truth (see CMakeLists.txt).
# BACKEND selects the window backend: sdl (default) or win32.

CMAKE   ?= cmake
BUILD   ?= build
BACKEND ?= sdl

all: release

release:
	$(CMAKE) -B $(BUILD) -DCMAKE_BUILD_TYPE=Release -DRASTERBATOR_BACKEND=$(BACKEND)
	$(CMAKE) --build $(BUILD) --config Release

debug:
	$(CMAKE) -B $(BUILD) -DCMAKE_BUILD_TYPE=Debug -DRASTERBATOR_BACKEND=$(BACKEND)
	$(CMAKE) --build $(BUILD) --config Debug

win:
	$(CMAKE) -B build-win -DRASTERBATOR_BACKEND=win32 -DCMAKE_BUILD_TYPE=Release
	$(CMAKE) --build build-win --config Release

run: release
	./bin/cartest

clean:
	$(CMAKE) -E rm -rf $(BUILD) build-win
	$(CMAKE) -E rm -f bin/cartest bin/cartest.exe bin/SDL3.dll

.PHONY: all release debug win run clean