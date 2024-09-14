#### 🚧 Work in progress 🚧
# A 3D [Software Renderer](https://en.wikipedia.org/wiki/Software_rendering)
<img src='./preview.gif'>

###### Rendered and recorded on a Thinkpad T400 (2 core no hyperthreading cpu)

### Dependencies

- [SDL2](http://libsdl.org) to make a [raster](https://en.wikipedia.org/wiki/Raster_graphics)
- gcc
- make

#### Debian

```bash
  sudo apt install libsdl2-2.0-0 libsdl2-dev
```

#### Fedora
```bash
  sudo dnf install SDL2 SDL2-devel
```
### Compiling

```bash
make
```
### Testing

```bash
make test
```

### Render options
Press some of these buttons
- 1 for rendering only the point of vectors
- 2 for rendering only the wireframe
- 3 for rendering only the faces
- 4 for rendering the wireframe and faces
