//==========================================================================
// ランチャー [Launcher.cpp]
// author : MasyoLab
//==========================================================================
#include "Launcher.h"
#include "resource.h"

namespace main_system
{
	//==========================================================================
	// 定数定義
	//==========================================================================
	constexpr DWORD WINDOW_STYLE = (WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX));
	constexpr DWORD ID_BUTTON000 = (10000);//ボタンの認識ID
	constexpr DWORD ID_BUTTON001 = (10001);//ボタンの認識ID
	constexpr DWORD ID_BUTTON002 = (10002);	//ボタンの認識ID
	constexpr int MainWidth = 500;
	constexpr int MainHeight = 500;

	//==========================================================================
	// 実体
	//==========================================================================
	HWND Launcher::m_hWnd = nullptr;
	HDC Launcher::m_BackBufferDC = nullptr;
	HBITMAP Launcher::m_BackBufferBMP = nullptr;
	HWND Launcher::m_hWndButton10000 = nullptr;
	HWND Launcher::m_hWndButton10001 = nullptr;
	HWND Launcher::m_combo = nullptr;
	HBITMAP Launcher::m_hBitmap = nullptr;
	HWND Launcher::m_check = nullptr;
	BITMAP Launcher::m_Bitmap;
	WindowData Launcher::m_data;
	mslib::aspect::AspectRatio Launcher::m_asp;

	Launcher::Launcher()
	{
		AddComponent(new mslib::window::WindowsAPI("Default", "Default"));
		SetComponentName("Launcher");
	}

	Launcher::Launcher(const std::string& class_name, const std::string& window_name)
	{
		AddComponent(new mslib::window::WindowsAPI(class_name, window_name));
		SetComponentName("Launcher");
	}

	Launcher::~Launcher()
	{
	}

	bool Launcher::Window(HINSTANCE hInstance, int nCmdShow)
	{
		RECT wr, dr; // 画面サイズ

		auto windows_api = GetComponent<mslib::window::WindowsAPI>();
		windows_api->SetWindowClass(CS_VREDRAW | CS_HREDRAW, WndProc, nullptr, nullptr, nullptr, hInstance);
		wr = windows_api->GetWindowRECT(WINDOW_STYLE, MainWidth, MainHeight, false);

		m_data = WindowData(-1, false);

		// マウスカーソル表示設定
		ShowCursor(true);

		//デスクトップサイズ習得
		GetWindowRect(GetDesktopWindow(), &dr);

		// 初期位置修正
		wr.left = dr.right / 2;
		wr.top = dr.bottom / 2;
		wr.left -= wr.right / 2;
		wr.top -= wr.bottom / 2;

		// ウィンドウの生成
		windows_api->Create(WINDOW_STYLE, wr, nullptr, nullptr, nullptr, nCmdShow);

		MSG& msg = windows_api->GetMSG(); // メッセージ構造体

		for (;;)
		{
			// メッセージ
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;

				//メッセージ処理
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		return m_data.m_key;
	}

	void Launcher::newtex()
	{
		for (int i = 0; i < m_asp.Size(); i++)
		{
			char ptex[MAX_PATH] = { 0 };
			sprintf(ptex, "%d×%d (%d:%d)", m_asp.Get(i).m_size.x, m_asp.Get(i).m_size.y, m_asp.Get(i).m_asp.x, m_asp.Get(i).m_asp.y);
			SendMessage(m_combo, CB_ADDSTRING, 0, (LPARAM)ptex);
		}
		SendMessage(m_combo, CB_ADDSTRING, 0, (LPARAM)TEXT("Full Screen"));
	}

	void Launcher::Button(HWND hWnd, LPARAM* lParam, int posx, int posy)
	{
		auto vpos = mslib::intTexvec(posx + 120, posy, 200, 10000);
		m_combo = CreateWindowEx(
			0,
			TEXT("COMBOBOX"),
			TEXT("menu"),
			(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST),
			vpos.x, vpos.y, vpos.w, vpos.h,
			hWnd, (HMENU)1,
			((LPCREATESTRUCT)(*lParam))->hInstance,
			nullptr
		);

		newtex();

		vpos = mslib::intTexvec(20, 450, 80, 20);
		vpos = mslib::intTexvec(vpos.x + vpos.w + 190, vpos.y, vpos.w, vpos.h);

		//ボタンを作る
		m_hWndButton10000 = CreateWindowEx
		(
			0,
			TEXT("BUTTON"),
			TEXT("PLAY!"),
			(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),
			vpos.x, vpos.y, vpos.w, vpos.h,
			hWnd,
			(HMENU)ID_BUTTON000,
			((LPCREATESTRUCT)(*lParam))->hInstance,
			nullptr
		);

		vpos = mslib::intTexvec(vpos.x + vpos.w + 10, vpos.y, vpos.w, vpos.h);
		m_hWndButton10001 = CreateWindowEx
		(
			0,
			TEXT("BUTTON"),
			TEXT("END"),
			(WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON),
			vpos.x, vpos.y, vpos.w, vpos.h,
			hWnd,
			(HMENU)ID_BUTTON001,
			((LPCREATESTRUCT)(*lParam))->hInstance,
			nullptr
		);
	}

	void Launcher::Config(HDC* hDC, mslib::intTexvec* vpos)
	{
		auto pos = mslib::intTexvec(vpos->x, (int)(MainHeight / 2), vpos->w, (int)(MainHeight - 80));
		HBRUSH Brush, OldBrush; // ブラシ
		HPEN Pen, OldPen; // ペン
		int nSize = 1; // 線の幅

		Brush = CreateSolidBrush(RGB(255, 255, 255));
		OldBrush = (HBRUSH)SelectObject(*hDC, Brush);

		Pen = CreatePen(PS_SOLID, nSize, RGB(200, 200, 200));
		OldPen = (HPEN)SelectObject(*hDC, Pen);

		// 長方形
		Rectangle(*hDC, pos.x, pos.y, pos.w, pos.h);

		SelectObject(*hDC, OldBrush);
		DeleteObject(Brush);
		SelectObject(*hDC, OldPen);
		DeleteObject(Pen);
	}

	void Launcher::Text(HWND hWnd, HDC* hDC, LPCTSTR lpszStr, int posx, int posy)
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		auto vpos = mslib::intTexvec(0, 0, MainWidth, MainHeight);

		BitBlt(hdc, vpos.x, vpos.y, vpos.w, vpos.h, *hDC, 0, 0, SRCCOPY);
		TextOut(hdc, posx, posy, lpszStr, lstrlen(lpszStr));
		EndPaint(hWnd, &ps);
	}

	void Launcher::ImgeData(HDC* hDC, mslib::intTexvec* vpos)
	{
		auto pos = mslib::intTexvec(vpos->x, vpos->y, vpos->w, vpos->h);
		HBRUSH Brush, OldBrush; // ブラシ
		HPEN Pen, OldPen; // ペン
		int nSize = 1; // 線の幅
		HDC bitmapDC = CreateCompatibleDC(*hDC);

		Brush = CreateSolidBrush(RGB(227, 227, 227));
		OldBrush = (HBRUSH)SelectObject(*hDC, Brush);

		Pen = CreatePen(PS_SOLID, nSize, RGB(200, 200, 200));
		OldPen = (HPEN)SelectObject(*hDC, Pen);

		// 長方形
		Rectangle(*hDC, pos.x, pos.y, pos.w, pos.h);

		SelectObject(*hDC, OldBrush);
		DeleteObject(Brush);
		SelectObject(*hDC, OldPen);
		DeleteObject(Pen);
		DeleteDC(bitmapDC);
	}

	void Launcher::LoadTex(LPARAM* lp)
	{
		// ファイル読み込み
		m_hBitmap = LoadBitmap(((LPCREATESTRUCT)(*lp))->hInstance, (LPCSTR)IDB_BITMAP1);

		//画像サイズ取得
		GetObject(m_hBitmap, sizeof(BITMAP), &m_Bitmap);
	}

	void Launcher::DrawTex(HWND hWnd, HDC* hDC, mslib::intTexvec* vpos)
	{
		PAINTSTRUCT ps = { 0 };

		HDC hBuffer = CreateCompatibleDC(*hDC);
		auto pos = mslib::intTexvec(vpos->x, vpos->y, vpos->w, vpos->h);
		pos += mslib::intTexvec(1, 1, -12, -12);

		SelectObject(hBuffer, m_hBitmap);

		BitBlt(*hDC, pos.x, pos.y, pos.w, pos.h, hBuffer, 0, 0, SRCCOPY);

		DeleteDC(hBuffer);
		EndPaint(hWnd, &ps);
	}

	LRESULT Launcher::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		RECT rect;
		auto vpos = mslib::intTexvec(0, 0, 0, 0);
		int nPosX = 70;
		int nPosY = 325;

		if (m_hWnd != nullptr)
		{
			hWnd = m_hWnd;
		}

		// メッセージの種類に応じて処理を分岐。
		switch (uMsg)
		{
		case WM_CREATE: // 初期化
			GetClientRect(hWnd, &rect); // 幅と高さ
			m_BackBufferDC = CreateCompatibleDC(GetDC(hWnd)); // デバイスの生成
			m_BackBufferBMP = CreateCompatibleBitmap(GetDC(hWnd), MainWidth, MainHeight);  // ビットマップの生成
			SelectObject(m_BackBufferDC, m_BackBufferBMP); // セット
			ReleaseDC(hWnd, GetDC(hWnd)); // 解放
			Button(hWnd, &lParam, nPosX, nPosY);
			LoadTex(&lParam);
			break;
		case WM_PAINT: // 描画
			vpos = mslib::intTexvec(10, 10, (int)(MainWidth - 10), (int)((MainHeight / 2) - 10));
			// 画面のクリア
			GetClientRect(hWnd, &rect); // クリアする場
			FillRect(m_BackBufferDC, &rect, (HBRUSH)(COLOR_INFOTEXT)); // 塗りつぶす
			ImgeData(&m_BackBufferDC, &vpos);
			Config(&m_BackBufferDC, &vpos);
			DrawTex(hWnd, &m_BackBufferDC, &vpos);
			Text(hWnd, &m_BackBufferDC, TEXT("Window Mode"), nPosX, nPosY);
			break;
		case WM_DESTROY: // 終了
			DeleteObject(m_BackBufferBMP);
			DeleteDC(m_BackBufferDC);

			//ビットマップハンドルを削除
			DeleteObject(m_hBitmap);
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
			{
				m_data.m_serect = (int)SendMessage(m_combo, CB_GETCURSEL, 0, 0);
				return 0;
			}
			break;
			default:
				break;
			}
			switch (LOWORD(wParam))
			{
			case ID_BUTTON000:
				if (m_data.m_serect == -1)
				{
					MessageBox(hWnd, TEXT("Window Modeを選択してください"), TEXT("error"), MB_OK);
				}
				else
				{
					DestroyWindow(hWnd);
					m_data.m_key = true;
				}
				break;
			case ID_BUTTON001:
				DestroyWindow(hWnd);
				m_data.m_key = false;
				break;
			case ID_BUTTON002:
				// チェック無し
				if (BST_CHECKED == SendMessage(m_check, BM_GETCHECK, 0, 0))
				{
					SendMessage(m_check, BM_SETCHECK, BST_UNCHECKED, 0);
				}
				// チェック在り
				else if (BST_UNCHECKED == SendMessage(m_check, BM_GETCHECK, 0, 0))
				{
					SendMessage(m_check, BM_SETCHECK, BST_CHECKED, 0);
				}
				break;
			default:
				break;
			}
			break;
		case WM_KEYDOWN: // キー入力
			switch (wParam)
			{
			case VK_ESCAPE: // [ESC]キーが押されたら
				DestroyWindow(hWnd);
				break;
			default:
				break;
			}
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		}
		return 0;
	}
}