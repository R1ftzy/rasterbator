raster: src/main.c src/framebuffer.c src/noise.c src/draw.c src/color.c
	mkdir -p bin
	gcc -Iinclude $^ -o bin/$@