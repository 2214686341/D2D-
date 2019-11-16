#pragma once
#include <windows.h>
#include <iostream>
#include <d2d1.h>
#include <Dwrite.h>

//---------------定义画图接口

//-----------函数声明


//extern ID2D1HwndRenderTarget* pRender;
//extern ID2D1Factory* pFactory;
//extern ID2D1SolidColorBrush* pBrush;
//extern IDWriteFactory* pWriteFactory;
//extern IDWriteTextFormat* pTextFormatMsyh;
//extern IDWriteTextFormat* pTextFormatKaiTi;
//extern ID2D1SolidColorBrush* DrawBrush;
//extern RECT rect;


class Direct2D
{
public:
	 ID2D1HwndRenderTarget* pRender;
	 ID2D1Factory* pFactory;
	 ID2D1SolidColorBrush* pBrush;
	 IDWriteFactory* pWriteFactory;
	 IDWriteTextFormat* pTextFormatMsyh;
	 IDWriteTextFormat* pTextFormatKaiTi;
	 ID2D1SolidColorBrush* DrawBrush;
	 RECT rect;



	Direct2D();

	VOID InitDirect2D(HWND  hwnd);	 //初始化D2D

	VOID Destroy2D();    //销毁，释放D2D 

	VOID DrawLine(int X, int Y, int XX, int YY, DWORD Color, float Width, float Alpha);	 //画线

	VOID DrawRect(int left, int top, int w, int h, DWORD color, int LineWidth);		 //画框

	VOID DrawWndText(int X, int Y, const WCHAR* text, DWORD Color, IDWriteTextFormat* TextFormat, float Alpha); //画字

	VOID DrawWndTextW(int X, int Y, const char* text, DWORD Color, IDWriteTextFormat* TextFormat, float Alpha);

	VOID BeginDraw(); //开始绘制
private:
	VOID DrawHorizontalLine(int X, int Y, int XX, int YY, DWORD Color, float Width, float Alpha); //横线

	VOID DrawVerticalLine(int X, int Y, int XX, int YY, DWORD Color, float Width, float Alpha);//竖线
};








