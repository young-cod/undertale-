
#include "stdafx.h"
#include "utils.h"

namespace UJN_UTIL
{
	float GetDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//�ޱ۰��� ������ �Լ� 3D���� ���Ͱ���� ���
	float GetAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);
		float angle = acosf(x / distance);

		if (y2 > y1)
		{
			angle = PI2 - angle;

			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}


	//�簢���� �簢���� �浹�ߴ�?
	bool IsCollision(const RECT& rc1, const ENEMYRECT& rc2)
	{
		if ((rc1.left <= rc2.right && rc1.right >= rc2.left) &&
			(rc1.top <= rc2.bottom && rc1.bottom >= rc2.top)) return true;
		return false;
	}

	bool IsCollision(const RECT& rc1, const RECT& rc2)
	{
		if ((rc1.left <= rc2.right && rc1.right >= rc2.left) &&
			(rc1.top <= rc2.bottom && rc1.bottom >= rc2.top)) return true;
		return false;
	}

	char * ConvertWCtoC(wchar_t * str)
	{
		//��ȯ�� char* ���� ����
		char* pStr;

		//�Է¹��� wchar_t ������ ���̸� ����
		int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		//char* �޸� �Ҵ�
		pStr = new char[strSize];

		//�� ��ȯ 
		WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
		return pStr;
	}

	const char * ConvertWCtoC(const wchar_t * str)
	{
		//��ȯ�� char* ���� ����
		char* pStr;

		//�Է¹��� wchar_t ������ ���̸� ����
		int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		//char* �޸� �Ҵ�
		pStr = new char[strSize];

		//�� ��ȯ 
		WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
		return pStr;
	}

	wchar_t *ConvertCtoWC(char * str)
	{
		//wchar_t�� ���� ����
		wchar_t* pStr;
		//��Ƽ ����Ʈ ũ�� ��� ���� ��ȯ
		int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
		//wchar_t �޸� �Ҵ�
		pStr = new WCHAR[strSize];
		//�� ��ȯ
		MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);
		return pStr;
	}
	
	const wchar_t *ConvertCtoWC(const char * str)
	{
		//wchar_t�� ���� ����
		wchar_t* pStr;
		//��Ƽ ����Ʈ ũ�� ��� ���� ��ȯ
		int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
		//wchar_t �޸� �Ҵ�
		pStr = new WCHAR[strSize];
		//�� ��ȯ
		MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);
		return pStr;
	}
}