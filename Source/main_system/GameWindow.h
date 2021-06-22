//==========================================================================
// ゲームウィンドウ [GameWindow.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string>
#include "dxlib.h"

namespace main_system
{
	//==========================================================================
	//
	// class : GameWindow
	// Content : ゲームウィンドウ
	//
	//==========================================================================
	class GameWindow :
		public mslib::component::Component
	{
	private:
		// コピー禁止 (C++11)
		GameWindow(const GameWindow&) = delete;
		GameWindow& operator=(const GameWindow&) = delete;
		GameWindow& operator=(GameWindow&&) = delete;
	public:
		GameWindow();
		GameWindow(const std::string& _class_name, const std::string& _window_name);
		~GameWindow();
		// ウィンドウ生成
		int Window(HINSTANCE _Instance, const mslib::int2& _data, bool _Mode, int _CmdShow);
	private:
		// ウィンドウプロシージャ
		static LRESULT CALLBACK WndProc(HWND _Wnd, UINT _Msg, WPARAM _wParam, LPARAM _lParam);
		// ゲームループ
		int GameLoop(HINSTANCE _Instance, HWND _hWnd);
	};

	using GameWindowReference = mslib::reference::IReference<GameWindow>;
}