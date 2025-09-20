#include "engine_api.h"
#include <stdio.h>
#include <windows.h>

/**
 * @brief   调试方法
 * @param   输出的信息
 */
void DebugLog(const char* msg)
{ 
	printf("%s\n", msg);
	OutputDebugStringA(msg);
}

/**
 * @brief   高级调试方法
 * @param   日志类型(INFO\WARN\ERROR)
 * @param   输出的信息
 */
void DebugLogEx(ExType type,const char* fmt,...)
{
	// =============================
	// 类型变量的选择
	// =============================
	const char* typeStr = "";
	switch (type)
	{
		case LOGWARN:
			typeStr = "[WARN]";
			break;
		case LOGERROR:
			typeStr = "[ERROR]";
			break;
		default:
			typeStr = "[INFO]";
			break;
	}

	// =============================
	// 可变参数处理
	// =============================
	char buffer[1024];
	//定义可变参数类型
	va_list args;
	//初始化可变参数，fmt为最后一个固定参数
	va_start(args, fmt);

	//格式化字符串输出到buffer字符串里（将传入的字符串和可选参数拼起来后存储）
	vsnprintf(buffer, sizeof(buffer), fmt, args);

	//释放可变参数
	va_end(args);

	// =============================
	// 字符串拼接
	// =============================
	char finalBuffer[1080];
	//将 日志类型 和 已完成可选参数拼接的字符串 拼接起来
	snprintf(finalBuffer, sizeof(finalBuffer), "%s %s\n", typeStr, buffer);

	// =============================
	// 字符串输出
	// =============================
	//输出到控制台
	printf("%s", finalBuffer);
	//输出到调试器
	OutputDebugStringA(finalBuffer);
}