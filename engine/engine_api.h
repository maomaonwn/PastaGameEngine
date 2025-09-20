#pragma once

#ifdef _cplusplus
extern "C" {
#endif

typedef enum {
		LOGWARN,
		LOGERROR,
		LOGINFO
}ExType;

void DebugLog(const char* msg);
void DebugLogEx(ExType type, const char* fmt);

#ifdef _cplusplus
}
#endif