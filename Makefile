CC       = gcc
TARGET   = raster

SRC      = src/main.c src/framebuffer.c src/draw.c src/color.c src/vecmath.c src/camera.c src/obj.c src/trans.c
DEBUG_FLAGS  = -O0 -g -Wall -Wextra -Iinclude
RELEASE_FLAGS = -O3 -march=native -Iinclude
WIN_SRC  = $(SRC) src/RB_windows.c
SDL_SRC  = $(SRC) src/RB_sdl.c
WIN_LDFLAGS = -mwindows -municode -lgdi32 -luser32

SDL_CFLAGS  = -Iinclude -Iexternal/SDL3/include
SDL_LDFLAGS = -Lexternal/SDL3/lib -lSDL3

all: release

debug:
	mkdir -p bin
	$(CC) $(DEBUG_FLAGS) $(WIN_SRC) $(WIN_LDFLAGS) -o bin/$(TARGET)

release:
	mkdir -p bin
	$(CC) $(RELEASE_FLAGS) $(WIN_SRC) $(WIN_LDFLAGS) -o bin/$(TARGET)

sdl:
	mkdir -p bin
	$(CC) $(RELEASE_FLAGS) $(SDL_CFLAGS) $(SDL_SRC) $(SDL_LDFLAGS) -o bin/$(TARGET)
	cp external/SDL3/bin/SDL3.dll bin/
