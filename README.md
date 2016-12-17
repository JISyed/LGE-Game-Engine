![Demo Screenshot](https://github.com/JISyed/LGE-Game-Engine/blob/master/Screenshots/demo2.png)

# LGE-Game-Engine
Game graphics and animation engine made at DePaul University over several months. Requires at least Visual Studios 2013 to open.

### Features

 - Advanced graphics engine with OpenGL 3 (Shaders, Textures, Materials, Uniform managemet, Meshes)
 - Basic animation system that performs mesh skinning in the GPU
 - Graphics materials that are serialized as YAML files to allow tweaking outside the engine code
 - Cameras that are serialized as 1 YAML file
 - Run-time format for art assets converted from FBX files (faster than having the engine load FBX files at start time) (See ConvertersDemo folder)
 - Scene graph with Parent-Child-Sibling tree structure
 - Fast custom-made math library that supports 4d vectors, 4x4 matrices, and quaternions
 - Fast file-loading library utilizing Windows' file API (instead of C's)
 - Simple GameObject system that supports object-oriented behaviors (called "Components" in Unity3D)
