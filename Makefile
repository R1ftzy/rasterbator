raster: src/display.c src/framebuffer.c src/draw.c src/color.c src/vecmath.c src/camera.c src/obj.c src/trans.c
	mkdir -p bin
	gcc -Iinclude $^ -mwindows -municode -lgdi32 -luser32 -o bin/$@