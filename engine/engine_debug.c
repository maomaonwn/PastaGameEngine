#include "engine_api.h"
#include <stdio.h>
#include <windows.h>

/**
 * @brief   ���Է���
 * @param   �������Ϣ
 */
void DebugLog(const char* msg)
{ 
	printf("%s\n", msg);
	OutputDebugStringA(msg);
}

/**
 * @brief   �߼����Է���
 * @param   ��־����(INFO\WARN\ERROR)
 * @param   �������Ϣ
 */
void DebugLogEx(ExType type,const char* fmt,...)
{
	// =============================
	// ���ͱ�����ѡ��
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
	// �ɱ��������
	// =============================
	char buffer[1024];
	//����ɱ��������
	va_list args;
	//��ʼ���ɱ������fmtΪ���һ���̶�����
	va_start(args, fmt);

	//��ʽ���ַ��������buffer�ַ������������ַ����Ϳ�ѡ����ƴ������洢��
	vsnprintf(buffer, sizeof(buffer), fmt, args);

	//�ͷſɱ����
	va_end(args);

	// =============================
	// �ַ���ƴ��
	// =============================
	char finalBuffer[1080];
	//�� ��־���� �� ����ɿ�ѡ����ƴ�ӵ��ַ��� ƴ������
	snprintf(finalBuffer, sizeof(finalBuffer), "%s %s\n", typeStr, buffer);

	// =============================
	// �ַ������
	// =============================
	//���������̨
	printf("%s", finalBuffer);
	//�����������
	OutputDebugStringA(finalBuffer);
}