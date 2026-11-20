<h1 align="center">GM Engine</h1> <p align="center"> 轻量级跨平台 2D 游戏引擎 · C++20 + SDL2 · 内置 Lua 脚本层与 C 侧高性能通道 </p> <p align="center">     </p>
✨ 特性
🎮 SDL2 渲染管线：硬件加速 2D 渲染，Image 实体 + 场景（Scene）+ 窗口（Window）绑定模型
📜 内置 Lua 脚本层：引擎逻辑全部用脚本编写，提供 grmanager 全局表、SetUpdateData 帧回调、BindEntity 实体绑定等 API
⚡ C 侧高性能通道（FFI / ldll）：把高频热点逻辑（如敌人寻路追踪）下沉到 C，Lua 只持有句柄，避开解释器与 GC 开销
🧍 C 侧实体生命周期管理：InitEnemyNode 建立节点、DDeleteGRTable 即时回收，支撑同屏大量实体
⏱️ 帧率无关运动：基于 delta-time 的位移计算，物理表现与刷新率解耦
🎥 相机系统：默认跟随玩家中心，支持按住右键拖拽视野偏移（带距离钳制与平滑插值）
🔧 CMake + vcpkg 构建，依赖统一管理
🎯 示例：幸存者（Survivors）Demo
仓库附带一个用本引擎脚本层完整搭出的幸存者类游戏 Demo，作为引擎 API 的实战验证：

玩家 8 方向移动（九宫格方向编码 + 对角线归一化，斜向不超速）
角色 + 阴影双实体渲染
大量敌人持续追踪玩家，AI 下沉 C 端
右键拖拽视野的相机 QoL
这个 Demo 同时也是学习「如何用 GM Engine 写游戏」的参考代码。

🚀 快速开始
环境要求
C++20 编译器（MSVC 2022 / GCC 11+ / Clang 14+）
CMake 3.20+
vcpkg（依赖管理）
构建
git clone https://github.com/skyorange-dev/GM-Engine.git
cd GM-Engine
cmake -B build -DCMAKE_TOOLCHAIN_FILE=[vcpkg根目录]/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
运行
./build/Release/gm_engine_demo
📁 目录结构
GM-Engine/
|-- src/
|   |-- core/            # 引擎主循环、时间、日志
|   |-- renderer/        # SDL2 渲染封装、Image 实体、相机
|   |-- scene/           # 场景与实体绑定（Window / Scene / BindEntity）
|   |-- input/           # 输入处理
|   |-- scripting/       # Lua 绑定、grmanager 全局表、SetUpdateData 回调
|   `-- native/          # C 侧高性能通道（FFI / ldll）、实体节点管理
|-- include/gm/          # 公共头文件
|-- examples/survivors/  # 幸存者 Demo（main / game / player / enemy / camera）
|-- thirdparty/          # 第三方库许可证文本
`-- CMakeLists.txt
🧩 脚本 API 速览
-- 创建实体并绑定到场景
local enemy = NewEnemy(window, scene_t)
window.BindEntity("game", enemy.e)

-- 注册每帧回调（delta-time 帧率无关运动）
player.SetUpdateData(function(event, ptr)
    local dt = event.dptr._time - ptr.last_time
    ptr.last_time = event.dptr._time
    -- ... 按 dt 计算位移 ...
end)

-- 高频逻辑下沉 C 端，Lua 仅持有句柄
ld.EnemyUpdate(enemy_ptr.value, player_ptr.value, enemy_ptr.data_value)
🔗 第三方依赖
本项目使用以下开源库，许可证文本见 thirdparty/ 目录：

库	许可证	用途
SDL2	Zlib	窗口、渲染、输入
SDL2_image	Zlib	图片加载
SDL2_mixer	Zlib	音频混音
mimalloc	MIT	内存分配
LuaJIT	MIT	脚本引擎
nlohmann/json	MIT	JSON 解析
📄 许可证
本项目采用双许可模式：

开源用户：GPLv3 许可，详见 LICENSE-GPL
商业用户：商业许可，请联系 skyorange.dev@gmail.com 获取授权
🤝 贡献
欢迎提交 Issue 和 Pull Request！

Fork 本仓库
创建功能分支：git switch -c feature/xxx
提交更改：git commit -m "feat: 添加 xxx"
推送分支：git push origin feature/xxx
提交 Pull Request
