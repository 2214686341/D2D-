#include "Draw.h"


#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}  //销毁D2D宏定义



Direct2D::Direct2D()
{

	ID2D1HwndRenderTarget* pRender = 0;
	ID2D1Factory* pFactory = 0;
	ID2D1SolidColorBrush* pBrush = 0;
	IDWriteFactory* pWriteFactory = 0;
	IDWriteTextFormat* pTextFormatMsyh = 0;
	ID2D1SolidColorBrush* DrawBrush = 0;
	IDWriteTextFormat* pTextFormatKaiTi = 0;
	RECT rect = { 0 };



}



VOID Direct2D::InitDirect2D(HWND  hnwd)  //初始化D2D
{
	if (!pRender)
	{
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
		GetWindowRect(hnwd, &rect);
		pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)), D2D1::HwndRenderTargetProperties(hnwd, D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top)), &pRender);
		pRender->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &pBrush);
		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pWriteFactory));
	}
	pRender->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &DrawBrush);
	pWriteFactory->CreateTextFormat(L"Calibri", NULL, DWRITE_FONT_WEIGHT_ULTRA_BLACK, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 11.0f, L"MyFont", &pTextFormatKaiTi);
}



VOID  Direct2D::BeginDraw()
{
	pRender->BeginDraw();	//开始绘图
	pRender->Clear(D2D1_COLOR_F{ 255, 255, 255, 255 });	 //清空
	DrawLine(100, 100, 200, 300, D2D1::ColorF::Blue, 1, 1.0F);		//画线
	DrawRect(30, 60, 60, 120, D2D1::ColorF::Blue, 1.0F);
	DrawWndText(80, 80, L"D2D测试", D2D1::ColorF::Red, pTextFormatKaiTi, 1.0F);
	pRender->EndDraw();	  //结束绘图

}




VOID Direct2D::Destroy2D()  //销毁D2D
{
	SAFE_RELEASE(pRender);
	SAFE_RELEASE(pBrush);
	SAFE_RELEASE(pFactory);
	SAFE_RELEASE(pWriteFactory);
	SAFE_RELEASE(pTextFormatMsyh);
	SAFE_RELEASE(DrawBrush);
	SAFE_RELEASE(pTextFormatKaiTi);
}

//画线
VOID Direct2D::DrawLine(int X, int Y, int XX, int YY, DWORD Color, float Width, float Alpha)
{
	DrawBrush->SetColor(D2D1::ColorF(Color, Alpha));
	pRender->DrawLine(D2D1::Point2F(X, Y), D2D1::Point2F(XX, YY), DrawBrush, Width);
}
//画横线
VOID Direct2D::DrawHorizontalLine(int X, int Y, int XX, int YY, DWORD Color, float Width, float Alpha)
{
	DrawBrush->SetColor(D2D1::ColorF(Color, Alpha));
	pRender->DrawLine(D2D1::Point2F(X, Y), D2D1::Point2F(X + XX, Y), DrawBrush, Width);
}
//画竖线
VOID Direct2D::DrawVerticalLine(int X, int Y, int XX, int YY, DWORD Color, float Width, float Alpha)
{
	DrawBrush->SetColor(D2D1::ColorF(Color, Alpha));
	pRender->DrawLine(D2D1::Point2F(X, Y), D2D1::Point2F(X, Y + YY), DrawBrush, Width);
}
//画字
VOID Direct2D::DrawWndText(int X, int Y, const WCHAR* text, DWORD Color, IDWriteTextFormat* TextFormat, float Alpha)//文字
{
	DrawBrush->SetColor(D2D1::ColorF(Color, Alpha));
	pRender->DrawText(text, wcslen(text), TextFormat,
		D2D1::RectF((float)X, (float)Y, (float)rect.right, (float)rect.bottom), DrawBrush);
}
//画框	   
VOID Direct2D::DrawRect(int left, int top, int w, int h, DWORD color, int LineWidth)
{
	DrawHorizontalLine(left, top, w, LineWidth, color, 2, 15);
	DrawHorizontalLine(left, top + h, w, LineWidth, color, 2, 15);
	DrawVerticalLine(left, top - 1, LineWidth, h + 2, color, 2, 15);
	DrawVerticalLine(left + w, top - 1, LineWidth, h + 2, color, 2, 15);
}
VOID Direct2D::DrawWndTextW(int X, int Y, const char* text, DWORD Color, IDWriteTextFormat* TextFormat, float Alpha)//文字
{
	WCHAR WStr[256] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, text, strlen(text), WStr, strlen(text) * 2);
	DrawBrush->SetColor(D2D1::ColorF(Color, Alpha));
	pRender->DrawText(WStr, wcslen(WStr), TextFormat, D2D1::RectF((float)X, (float)Y, (float)rect.right, (float)rect.bottom), DrawBrush);
}



