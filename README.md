# Frisen (Friska Engine)
Graphic engine development. 

# References

This project will use CMake to configure/generate and build applications.

This project is based on these two books :
- Modern CMake for C++ - Rafal Świdziński (for the project configuration and build system) 
- Game Engine Architecture (Third edition) - Jason Gregory (for the architecture)

## Inspired by 
- [Hazel Engine](https://github.com/TheCherno/Hazel/tree/master)

# Architecture

- Frisen 
  - src
    - **Platform**
      - Platform Detection, Primitive Data Types, Collections and Iterators, File System, Hi-Res Timer, Threading Lib, Graphics Wrapper, Physics/Coll. Wrapper, ... 
    - **Core**
      - Assertions, Unit Testing, Memory Allocation, Math Lib, Debug Printing and Logging, Parsers (JSON, CSV, etc..), Engine Config, Random Num Generator, Curves and Surfaces Lib, ...
    - **Resources**
      - 3D Model Resource, Texture Resource, Material Resource, Font Resource, *Resource Manager*, ...
    - **Debug**
      - Memory & Performance Stats, In-Game Menus or Console, ...  
    - **Renderer**
      - Materials & Shaders, Static & Dynamic Lighting, Cameras, Test & Fonts, Primitive Submission, Viewport & Virtual Screens, Texture and Surface Managment, Debug Drawing, *Graphics Device Interface*, ...
    - **Scene**
      - Spatial Hash (BSP Tree, ...), Occlusion & PVS, LOD System, ...
    - **Physics**
      - Forces & Constraints, Ray/Shape Casting (Queries), Rigid Bodies, Phantoms, Shapes/Collidables, Physics/Collision World, ...
    - **UI**
      - Game-Specific Interface, Physical Device I/O, ...   
    - **VisualEffects**
      - Light Mapping & Dynamic Shadows, HDR Lighting, Particule & Decal Systems, Post Effects, Environment Mapping, PRT Lighting Subsurface Scatter, ...  
    - **Animation**
      - Animation State Tree & Layers, Inverse Kinematics (IK), LERP and Additive Blending, Sub-Skeleton Animation, ...    
  - vendor (3rd party SDKs) : see **Dependencies** below

# Dependencies

- OpenGL
  - GLFW (but I consider using SDL2 instead) 
  - GLAD
- ImGUI (GUI)
- Boost 
- Eigen (?) or GLM (?) for math



