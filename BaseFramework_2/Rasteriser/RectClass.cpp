#include "RectClass.h"



RectClass::RectClass()
{
	rectStruct.bottom = 0;
	rectStruct.top = 0;
	rectStruct.left= 0;
	rectStruct.right = 0;
	colour = RGB(0, 0, 0);
}

RectClass::RectClass(int left, int right, int top, int botom, COLORREF color)
{
	rectStruct.left = left;
	rectStruct.right = right;
	rectStruct.top = top;
	rectStruct.bottom = botom;
	colour = color;
}



COLORREF RectClass::GetColor()
{
	return colour;
}

RECT RectClass::GetRect()
{
	return rectStruct;
}

void RectClass::SetColor(COLORREF color)
{
	colour = color;
}

void RectClass::SetRect(RECT rect)
{
	rectStruct = rect;
}
