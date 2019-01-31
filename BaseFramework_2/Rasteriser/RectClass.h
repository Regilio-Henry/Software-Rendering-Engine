#pragma once
#include "Framework.h"


class RectClass
{

public:
	RectClass();
	RectClass(int left, int right, int top, int botom, COLORREF color);
	COLORREF GetColor();
	RECT GetRect();
	void SetColor(COLORREF color);
	void SetRect(RECT rect);
	


private:
	RECT rectStruct;
	COLORREF colour;
};

