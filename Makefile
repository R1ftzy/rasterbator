raster: src/main.c src/framebuffer.c src/noise.c src/draw.c
	mkdir -p bin
	gcc -Iinclude $^ -o bin/$@