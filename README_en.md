# GM Engine

**Other Language Versions:** [English](README_en.md) | [简体中文](README.md)

GM Engine is a 2D window application development framework focused on the gaming domain. Its core functionalities are similar to those of a 2D game engine, yet it offers significantly greater flexibility. If you wish to develop games freely while achieving higher efficiency than building everything from scratch using raw libraries, consider trying this project.

## Architecture

The overall architecture is implemented in C++ and LuaJIT. Users primarily execute logic by writing Lua scripts. With extensions, users can also write C/C++ code directly to assist the Lua layer in executing logic.

## Features

1. **Flexibility**
   - Users can directly manipulate fields within C-layer structures at the Lua layer for modifications.
   - Users can call Lua interfaces to dynamically load external dynamic libraries for functional extension.

2. **High Performance**
   - At the architectural level, C++ is compiled directly into machine code, and LuaJIT uses trace compilation to semi-bytecode, providing GM Engine with a substantial performance baseline.
   - With the `xclang` extension, users can write C++/C code locally, compile it directly into DLLs, and use them to assist the Lua layer in implementing high-performance logic (e.g., reducing memory consumption by using C structs, or rewriting complex Lua-layer logic natively in C/C++).

3. **Low Barrier to Entry**
   - To get started with GM Engine, you only need to understand Lua syntax and basic game concepts (such as main loops, scenes, cameras, etc.).

4. **High Scalability**
   - As your skills improve, you can progress from initially writing small games in Lua to learning C++ for high-performance implementations of larger-scale games. Eventually, after learning computer networking and databases, you can even bypass official implementations to manually implement database integration and online multiplayer features.

5. **Efficiency**
   - The engine provides implementations for common game concepts: events, entities, cameras, scenes, state machines, rendering, resource loading, etc., eliminating the need to reinvent basic wheels.
   - The engine also includes standard libraries, such as animation and video libraries, further enhancing your development efficiency.

## Usage

1. If you intend to use the engine directly, download the release package and refer to the API specifications in the Wiki to start your project.

2. If you want to reference the source code for purposes such as developing plugins, please download the corresponding third-party dependencies listed in `thirdparty.txt`, then download the GM Engine source code, configure the build options, and compile/run it.

## License

This project adopts a dual-license model:

- **Open Source Users:** GPLv3 license. See LICENSE-GPL for details.
- **Commercial Users:** Commercial license. Please contact 759792938@qq.com to obtain authorization.
