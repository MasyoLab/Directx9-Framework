//==========================================================================
// ゲームウィンドウ [GameWindow.cpp]
// author : MasyoLab
//==========================================================================
#include "GameWindow.h"
#include "Screen.h"
#include "resource.h"

namespace main_system
{
	//==========================================================================
	// 定数定義
	//==========================================================================
	constexpr DWORD WINDOW_STYLE = (WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX));
	constexpr int __fps = 60;
	constexpr long long __time_per_frame = (long long)1000 / __fps;

	//==========================================================================
	// 関数
	//==========================================================================
	// FPS固定
	static const bool FpsFixed();

	GameWindow::GameWindow()
	{
		AddComponent(new mslib::window::WindowsAPI("Default", "Default"));
		SetComponentName("GameWindow");
	}

	GameWindow::GameWindow(const std::string& _class_name, const std::string& _window_name)
	{
		AddComponent(new mslib::window::WindowsAPI(_class_name, _window_name));
		SetComponentName("GameWindow");
	}

	GameWindow::~GameWindow()
	{
	}

	int GameWindow::Window(HINSTANCE _Instance, const mslib::int2& _data, bool _Mode, int _CmdShow)
	{
		RECT wr, dr;
		auto windows_api = GetComponent<mslib::window::WindowsAPI>();

		windows_api->SetWindowClass(CS_VREDRAW | CS_HREDRAW, WndProc, nullptr, nullptr, nullptr, _Instance);

		// マウスカーソル表示設定
		ShowCursor(true);

		// Direct3Dオブジェクトの作成 に失敗時終了 
		auto device = mslib::manager::Manager::GetDevice();
		device->Init();

		// ウィンドウRECT
		wr = windows_api->GetWindowRECT(WINDOW_STYLE, _data.x, _data.y, false);

		//デスクトップサイズ習得
		GetWindowRect(GetDesktopWindow(), &dr);

		// 初期位置修正
		wr.left = dr.right / 2;
		wr.top = dr.bottom / 2;
		wr.left -= wr.right / 2;
		wr.top -= wr.bottom / 2;

		// ウィンドウの生成
		windows_api->Create(WINDOW_STYLE, wr, nullptr, nullptr, nullptr, _CmdShow);

		// 色々失敗した時終了
		if (device->CreateWindowMode(_data, _Mode))
			return -1;

		// デバイスにウィンドウハンドルを教える
		device->SetHwnd(windows_api->GetHWND());

		// ゲームループ
		return GameLoop(_Instance, windows_api->GetHWND());
	}

	LRESULT CALLBACK GameWindow::WndProc(HWND _Wnd, UINT _Msg, WPARAM _wParam, LPARAM _lParam)
	{
		auto device = mslib::manager::Manager::GetDevice();
		device->GetWindowsSize();
		if (device->GetHwnd() != nullptr)
			_Wnd = device->GetHwnd();

		if (mslib::imgui::ImGui_WndProcHandler(_Wnd, _Msg, _wParam, _lParam))
			return true;

		// メッセージの種類に応じて処理を分岐します。
		switch (_Msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:	// キー入力
			switch (_wParam)
			{
			case VK_ESCAPE:
				// [ESC]キーが押されたら
				if (MessageBox(_Wnd, "終了しますか？", "終了メッセージ", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
					DestroyWindow(_Wnd);	// ウィンドウを破棄
				else
					return 0;	// いいえの時
			}
			break;
		case WM_LBUTTONDOWN:
			SetFocus(_Wnd);
			break;
		case WM_CLOSE:	// ×ボタン押した時
			if (MessageBox(_Wnd, "終了しますか？", "終了メッセージ", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) == IDYES)
				DestroyWindow(_Wnd);	// ウィンドウを破棄
			else
				return 0;	// いいえの時
			break;
		default:
			break;
		}

		//デフォルトの処理
		return mslib::imgui::SetMenu(_Wnd, _Msg, _wParam, _lParam, device->Getd3ddevice(), &device->Getd3dpp());
	}

	int GameWindow::GameLoop(HINSTANCE _Instance, HWND _hWnd)
	{
		auto windows_api = GetComponent<mslib::window::WindowsAPI>();
		auto screen = AddComponent(new Screen);
		MSG& msg = windows_api->GetMSG(); // メッセージ構造体

		if (screen->Init(_Instance, _hWnd))
		{
			windows_api->ErrorMessage("初期化に失敗しました");
			return-1;
		}

		// メッセージループ
		for (;;)
		{
			// 何があってもスルー
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					break;

				//メッセージ処理
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				continue;
			}

			if (!FpsFixed())
				continue;

			if (screen->Update())
			{
				windows_api->ErrorMessage("初期化に失敗しました");
				return-1;
			}

			//描画
			screen->Draw();
		}

		return (int)msg.wParam;
	}

	const bool FpsFixed()
	{
		static auto start = std::chrono::system_clock::now();

		while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() < __time_per_frame);

		start = std::chrono::system_clock::now();

		return true;
	}
}