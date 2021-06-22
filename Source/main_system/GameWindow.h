//==========================================================================
// �Q�[���E�B���h�E [GameWindow.h]
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
	// Content : �Q�[���E�B���h�E
	//
	//==========================================================================
	class GameWindow :
		public mslib::component::Component
	{
	private:
		// �R�s�[�֎~ (C++11)
		GameWindow(const GameWindow&) = delete;
		GameWindow& operator=(const GameWindow&) = delete;
		GameWindow& operator=(GameWindow&&) = delete;
	public:
		GameWindow();
		GameWindow(const std::string& _class_name, const std::string& _window_name);
		~GameWindow();
		// �E�B���h�E����
		int Window(HINSTANCE _Instance, const mslib::int2& _data, bool _Mode, int _CmdShow);
	private:
		// �E�B���h�E�v���V�[�W��
		static LRESULT CALLBACK WndProc(HWND _Wnd, UINT _Msg, WPARAM _wParam, LPARAM _lParam);
		// �Q�[�����[�v
		int GameLoop(HINSTANCE _Instance, HWND _hWnd);
	};

	using GameWindowReference = mslib::reference::IReference<GameWindow>;
}