# Compiling

Build Options :

- Debug : Program is compiled with Debug Flags
- Release : Program is compiled with Release Flags

OS :

- Windows : Windows macro is inserted
- Linux : Linux macro is inserted

Compilers :

- MSVC : For Visual Studio work
- g++ : For general purpose compiling

# Organization

This framework for OpenGL is organized based on the directory underneath underneath the `/OpenGL-Core/src/...`. Such that `OpenGL-Core/src/[dir]` corresponds to the `GLCore::[dir]` namespace.

Note that anything under `OpenGL-Core/src/` is accessible by default using `GLCore::[name]`

# OpenGL-Core

## Core (Default)

> All the methods & classes for using the basic framework.

- **Application** : Bundles all the other classes in `GLCore::[name]` together. Anything to do with getting information about the status of the running application can be done here.
- **Window** : The window class to display for different OS.
- **LayerList** : An ArrayList containing all the `Layer`
  - **Layer(Abstract)** : Every iteration / re-render of the window, the code in the layer is ran. Data in layers are **INDEPDENT** from eachother!

## Extension

> Simplification of opengl and also helpful utilities

- **AssetPool(Abstract)** : A hashmap that keeps track of certain instances of classes under extensions.

### Shaders

- **VertexPipelineShader** : Shader for rendering vertices to the window.
- **ComputeShder** : Shader for sending and recieving data computed in parallel from the GPU.

### Primitives

- **Texture** : a 2D buffer object for GPU computations.

#### GLObjects

- **VAO** : Vertex array object
- **VBO** : Vertex buffer object
- **EBO** : Element buffer object

### Utils

#### Cameras

- **PerspectiveCamera** - a perspective camera class

# Production CheckList

- [x] Release & Debug Configurations
- [x] MSVC Support
- [ ] g++ support

- [x] Windows Support
- [ ] Linux Support

- [ ] Importing Third Party Libraries
  - [x] glad
  - [x] glfw
  - [x] imgui
  - [x] spdlog
  - [ ] stb_image
- [x] Core
  - [x] Application
  - [x] Window
  - [x] Layer & LayerStack & ImGuiLayer
  - [x] OpenGLDebug
  - [x] Log
- [x] Extension

  - [ ] Primitives
    - [x] VertexPipeline
    - [ ] SSBO
    - [ ] Texture
  - [x] Shaders
    - [x] Shader (Base Class)
    - [x] VertexPipelineShader
    - [x] ComputeShader
  - [x] AssetPool

# TODO

- [ ] SSBO
- [ ] Test ComputeShaders
