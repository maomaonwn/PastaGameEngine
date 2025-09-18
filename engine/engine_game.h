#pragma once

//����void (*)void���͵ĺ���ָ��
typedef void (*GameCallBack)(void);

extern GameCallBack ENTER;
extern GameCallBack UPDATE;
extern GameCallBack EXIT;

void SetEnter(GameCallBack func);
void SetUpdate(GameCallBack func);
void SetExit(GameCallBack func);
void InitGameLifeCycle();



