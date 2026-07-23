CC       = gcc
TARGET   = raster

SRC      = src/main.c src/RB_windows.c src/framebuffer.c src/draw.c src/color.c src/vecmath.c src/camera.c src/obj.c src/trans.c
DEBUG_FLAGS  = -O0 -g -Wall -Wextra -Iinclude
RELEASE_FLAGS = -O3 -march=native -Iinclude

LDFLAGS = -mwindows -municode -lgdi32 -luser32

all: release

debug:
	mkdir -p bin
	$(CC) $(DEBUG_FLAGS) $(SRC) $(LDFLAGS) -o bin/$(TARGET)

release:
	mkdir -p bin
	$(CC) $(RELEASE_FLAGS) $(SRC) $(LDFLAGS) -o bin/$(TARGET)

