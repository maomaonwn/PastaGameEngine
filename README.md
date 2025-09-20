# 🍝 意面引擎 | Pasta Game Engine

![C](https://img.shields.io/badge/Language-C-blue) ![Windows](https://img.shields.io/badge/Platform-Windows-lightgrey) ![License](https://img.shields.io/badge/License-Apache%202.0-green)

轻量级、模块化的 **C语言游戏引擎**，基于 **Windows SDK** 开发，适合开发 2D 游戏，也适合想研究游戏引擎底层机制的开发者。

*A lightweight, modular **C Language** game engine developed using **Windows SDK**, suitable for 2D games and for developers interested in low-level engine mechanics.*

---

## 🚀 亮点 | Features

### 中文版
- **纯粹的 C 语言开发环境**  
  开发者可以使用 **C/C++ 标准库 API** 或 **引擎提供的 API**。引擎无第三方依赖，环境轻量、纯粹。

- **跨模块开发**  
  支持多文件结构，方便扩展和模块化开发。

- **高效轻量的引擎**  
  基于底层 **Windows SDK**，运行内存小，执行速度快（当前版本约 2MB~几百 MB）。

- **学习与扩展友好**  
  项目开源，代码注释良好，底层结构清晰，适合学习引擎内部机制和自定义扩展。

### English Version
- **Pure C Development Environment**  
  Developers can use standard **C/C++ library APIs** or engine-provided APIs. No third-party dependencies; lightweight and pure environment.

- **Modular Development**  
  Supports multi-file structure for modular and extensible development.

- **Efficient & Lightweight Engine**  
  Built on low-level **Windows SDK**, with small memory footprint and high execution speed (current version ~2MB to a few hundred MB).

- **Learning & Extensible**  
  Open-source with clear comments and structure, ideal for learning engine internals and extending functionality.

---

## 🛠️ 技术栈 | Tech Stack

- **语言 Language:** C、Windows SDK  
- **平台 Platform:** Windows  
- **底层系统实现 System Modules:** *(仍在开发中 / under development)* <br>
| 中文名称 | English Names | <br>
|-----------|----------------| <br>
| 消息循环 | MessageLoop | <br>
| 生命周期系统 | LifecycleSystem | <br>
| 窗口生成与设计 | Window Creation & Design | <br>
| 输入输出系统 | Input & OutputSystem | <br>
| 定时器系统 | TimerSystem | <br>
| 渲染系统 | RenderingSystem | <br>
| 资源管理系统 | Resource ManagementSystem | <br>

---

## 🖼️ 项目示意图 / Demo

---

## 📦 快速开始 | Quick Start

### 中文版
1. 在 **user.c** 文件中实现生命周期函数，这是用户书写代码的主要位置。  
2. 可以新建与 **user.c** 架构一致的文件，实现多文件开发。  
3. 更多 API 使用说明请参考 **意面引擎 API PDF 文件**（待更新）。

### English Version
1. Implement lifecycle functions in **user.c**, the main user code file.  
2. You can create additional files following the same structure for multi-file development.  
3. For more API usage, refer to the **Pasta Game Engine API PDF** (coming soon).

---

## 💻 示例代码 | Example Code

```c
#include "user.h"
#include "engine_api.h"

/********** 在此自定义添加 C 标准库头文件 / Add your C standard library headers **********/
#include <stdio.h>
/**************************************************************************************/

// 游戏进入时调用 / Called when the game starts
void OnEnter()
{
   DebugLog("Hello World!");
}

// 每帧更新时调用 / Called every frame
void OnUpdate()
{
   
}

// 游戏退出时调用 / Called when the game exits
void OnExit()
{

}
