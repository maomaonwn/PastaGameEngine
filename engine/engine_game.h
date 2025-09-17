#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

//定义void (*)void类型的函数指针
typedef void (*GameCallBack)(void);

extern GameCallBack ENTER;
extern GameCallBack UPDATE;
extern GameCallBack EXIT;

void SetEnter(GameCallBack func);
void SetUpdate(GameCallBack func);
void SetExit(GameCallBack func);
void InitGameLifeCycle();

#endif


