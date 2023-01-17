#pragma once
#include "../main.h"

typedef struct
{
	int AnimNo;
	int Priority;

	void Set(int no, int priority)
	{
		AnimNo = no;
		Priority = priority;
	};
} ANIM_DATA;
