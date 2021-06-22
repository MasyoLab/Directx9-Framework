//==========================================================================
// WindowsAPI [WindowsAPI.cpp]
// author : MasyoLab
//==========================================================================
#include "WindowsAPI.h"

_MSLIB_BEGIN
namespace window
{
	WindowsAPI::WindowsAPI(const std::string& class_name, const std::string& window_name)
		: Component("WindowsAPI"), m_class_name(class_name), m_window_name(window_name), m_hWnd(nullptr), 
		m_msg(), m_wcex(), m_rect()
	{
	}

	WindowsAPI::~WindowsAPI()
	{
		m_class_name.clear();
		m_window_name.clear();

		UnregisterClass(m_wcex.lpszClassName, m_wcex.hInstance);
	}

	ATOM WindowsAPI::SetWindowClass(UINT _style, WNDPROC _WndProc, LPCSTR _Icon, LPCSTR _IconSm, LPCSTR _lpszMenuName, HINSTANCE _Instance)
	{
		m_wcex.cbSize = sizeof(m_wcex);						// 構造体のサイズ
		m_wcex.style = _style;								// ウインドウスタイル
		m_wcex.lpfnWndProc = _WndProc;						// そのウインドウのメッセージを処理するコールバック関数へのポインタ
		m_wcex.cbClsExtra = 0L;								// ウインドウクラス構造体の後ろに割り当てる補足バイト数．普通0．
		m_wcex.cbWndExtra = 0L;								// ウインドウインスタンスの後ろに割り当てる補足バイト数．普通0．
		m_wcex.hInstance = _Instance;						// このクラスのためのウインドウプロシージャがあるインスタンスハンドル．
		m_wcex.hIcon = LoadIcon(_Instance, _Icon);			// アイコンのハンドル
		m_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);	// マウスカーソルのハンドル．LoadCursor(nullptr, IDC_ARROW )とか．
		m_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	// ウインドウ背景色(背景描画用ブラシのハンドル)．
		m_wcex.lpszMenuName = _lpszMenuName;				// デフォルトメニュー名(MAKEINTRESOURCE(メニューID))
		m_wcex.lpszClassName = m_class_name.c_str();		// このウインドウクラスにつける名前
		m_wcex.hIconSm = LoadIcon(_Instance, _IconSm);		// 16×16の小さいサイズのアイコン

		return RegisterClassEx(&m_wcex);
	}

	bool WindowsAPI::Create(DWORD _dwStyle, RECT _rect, HWND _WndParent, HMENU _Menu, LPVOID _lpParam, int _CmdShow)
	{
		m_rect = _rect;
		m_hWnd = CreateWindow(m_class_name.c_str(), m_window_name.c_str(), _dwStyle, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, _WndParent, _Menu, m_wcex.hInstance, _lpParam);

		if (m_hWnd == nullptr)
		{
			MessageBox(m_hWnd, "ウィンドウが生成されませんでした。", "ERROR", MB_OK | MB_ICONEXCLAMATION | MB_ICONWARNING);
			return true;
		}

		ShowWindow(m_hWnd, _CmdShow);
		UpdateWindow(m_hWnd);

		return false;
	}

	MSG& WindowsAPI::GetMSG()
	{
		return m_msg;
	}

	HWND WindowsAPI::GetHWND()
	{
		return m_hWnd;
	}

	RECT WindowsAPI::GetWindowRECT(DWORD _dwStyle, int _Width, int _Height, bool _Menu)
	{
		m_rect = { 0,0,_Width ,_Height };

		// ウィンドウの情報
		AdjustWindowRect(&m_rect, _dwStyle, _Menu);
		m_rect.right = (m_rect.right - m_rect.left);
		m_rect.bottom = (m_rect.bottom - m_rect.top);
		m_rect.left = 0;
		m_rect.top = 0;

		return m_rect;
	}
}
_MSLIB_END