<h1 align="center">GM Engine</h1>
<p align="center">
轻量级跨平台 2D 游戏引擎，基于 SDL2 + C++20
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-20-blue" alt="C++20">
  <img src="https://img.shields.io/badge/SDL2-2.28+-green" alt="SDL2">
  <img src="https://img.shields.io/badge/CMake-3.20+-orange" alt="CMake">
  <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey" alt="Platform">
</p>

## ✨ 特性

- 🎮 基于 SDL2 渲染，支持硬件加速
- ⚡ 集成 mimalloc 高性能内存分配
- 🧩 模块化架构，组件化实体系统
- 🔧 CMake 一键构建，vcpkg 管理依赖
- 📦 零运行时依赖，静态链接

## 🚀 快速开始

### 环境要求

- C++20 编译器（MSVC 2022 / GCC 11+ / Clang 14+）
- CMake 3.20+
- vcpkg（依赖管理）

### 构建

```bash
git clone https://github.com/skyorange-dev/GM-Engine.git
cd GM-Engine
cmake -B build -DCMAKE_TOOLCHAIN_FILE=[vcpkg根目录]/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
