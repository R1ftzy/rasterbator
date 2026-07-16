# Rasterbator (ik very funny)

> [!IMPORTANT]
> This build is Windows only. For the standalone graphics library, use the main branch.

Very primitive software rasterizer in C from scratch.

can draw 3D shi onto a 2D screen in real time!

![render](assets/sonic_demo.gif)
![depth](assets/depth.png)

sonic.

2 python scripts included for converting `.ppm` outputs to a more human `.png` and to delete output images.

## Build

```sh
make
```

duh

## Usage

```sh
./bin/raster
```

Ts (this) opens a Win32 window with real-time rendering.
Also generates an `image.ppm` frame on startup.
Convert the PPM to PNG using the script provided.
