# 🍝 Pasta Game Engine

![C](https://img.shields.io/badge/Language-C-blue) ![Windows](https://img.shields.io/badge/Platform-Windows-lightgrey) ![License](https://img.shields.io/badge/License-Apache%202.0-green)

A lightweight, modular game engine or game engine framework. 

---
## 🚀 Features

- **C Development Environment**

  Developers can use std C/C++ APIs or engine-provided APIs to develop. No third-party dependecies, lightweight and pure environment.
  
- **Modular**

  Supports multi-file structure for development.
  
- **Efficient & Lightweight**

  Built on Windows SDK which is low-level, this engine will have small memory-need and high execution speed (a few MB~a few hundred MB).
  
---
## 🛠️ Systems
**The developed systems:**
- MessageLoop
- LifeCycle
- IO
- Timer
- Renderering
- Resource Management
- Basic Window's Creation
  
---
## 📦 Quick Start

You can develop in **user.c / user.h**, and extend the proj as needed;

```c
#include "user.h"
#include "engine_api.h"

/********** Add your C standard library headers **********/
#include <stdio.h>
/*********************************************************/

// Called when the game starts
void OnEnter()
{
   DebugLog("Hello World!");
}

// Called every frame
void OnUpdate()
{
   
}

//Called when the game exits
void OnExit()
{

}
```

---
## 📝 TODOs
- [ ] Add APIs
- [ ] Add API Document
- [ ] Improve Graphic UI
