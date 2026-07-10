raster: src/main.c src/framebuffer.c src/noise.c src/draw.c src/color.c src/tests.c src/vecmath.c src/camera.c
	mkdir -p bin
	gcc -Iinclude $^ -o bin/$@