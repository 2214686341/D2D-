#include "framework.h"
#include "Draw.h"

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

HWND hwnd;

Direct2D D2D;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR    lpCmdLine, _In_ int nCmdShow)
{


	//---------------------------注册窗口类
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc,0L,0L, GetModuleHandle(NULL), NULL, NULL, (HBRUSH)RGB(0, 0, 0), NULL, L"D2D", NULL };
	::RegisterClassEx(&wc);
	//---------------------------创建窗口（本程序为展现效果使用的 CreateWindow函数此函数不可以设置透明窗口 需要设置透明 请使用 CreateWindowEX）
	hwnd = ::CreateWindow(wc.lpszClassName, wc.lpszClassName, WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, wc.hInstance, NULL);
	//----------------------设置窗口透明 对CreateWindow函数不支持
	//::SetLayeredWindowAttributes(hwnd, 0, RGB(0, 0, 0), LWA_COLORKEY);
	//----------------------显示窗口和更新窗口
	::ShowWindow(hwnd, SW_SHOW);
	::UpdateWindow(hwnd);
	//-----------------------初始化D2D

	D2D.InitDirect2D(hwnd);


    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {

		D2D.BeginDraw();

        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
			continue;
        }
    }

    return (int) msg.wParam;
}


//----------------------------窗口消息函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)	   //窗口消息 == 退出
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		D2D.Destroy2D();  //销毁D2D
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
	}
	return DefWindowProc(hWnd, Message, wParam, lParam);

}