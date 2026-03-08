#### 🚧 Work in progress 🚧
# A 3D [Software Renderer](https://en.wikipedia.org/wiki/Software_rendering)
<img src='./preview.gif'>

### Features/standards so far
- Column major
- Translation, sacaling and roration transforms
- DDA line drawing
- Back-face culling
- Triangle filling
- Painter's algorithm for handling deep (No z-buffer yet, that's why some triangles filling looks strange)
- Left handed
- Direct3D projection matrix
- "Global" lighting flat shading

### Build dependencies

- [SDL2](http://libsdl.org) in order to create a window and draw pixels to to it (simply put, a [raster](https://en.wikipedia.org/wiki/Raster_graphics))
- [SDL2_image](https://wiki.libsdl.org/SDL2_image/FrontPage) in order to load image files
- gcc
- make

#### Debian

```bash
  sudo apt install libsdl2-dev libsdl2-image-dev
```

#### Fedora
```bash
  sudo dnf install SDL2-devel SDL2_image-devel
```
### Compiling

```bash
make
```
### Testing

```bash
make test
```

### Assets
Keep in mind this repository uses [Git LFS](https://git-lfs.com/), you need that to get the assets back, after cloning, run:
```bash
cd 3dsr
git lfs pull
```

### Render options
Press some of these buttons
- 1 for rendering only the point of vectors
- 2 for rendering only the wireframe
- 3 for rendering only the faces
- 4 for rendering the wireframe and faces
