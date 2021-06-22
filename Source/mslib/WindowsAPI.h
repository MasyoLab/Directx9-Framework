//==========================================================================
// WindowsAPI [WindowsAPI.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <windows.h>
#include <string>
#include <memory> // c++ メモリ
#include <cstdio> // 

#include "mslib.hpp"
#include "Component.h"

_MSLIB_BEGIN

namespace window
{
	// Class styles
	enum class WindowStyles
	{
		VREDRAW = CS_VREDRAW,
		HREDRAW = CS_HREDRAW,
		DBLCLKS = CS_DBLCLKS,
		OWNDC = CS_OWNDC,
		CLASSDC = CS_CLASSDC,
		PARENTDC = CS_PARENTDC,
		NOCLOSE = CS_NOCLOSE,
		SAVEBITS = CS_SAVEBITS,
		BYTEALIGNCLIENT = CS_BYTEALIGNCLIENT,
		BYTEALIGNWINDOW = CS_BYTEALIGNWINDOW,
		GLOBALCLAS = CS_GLOBALCLASS,
		VREDRAW_HREDRAW = CS_VREDRAW | CS_HREDRAW,
	};

	//==========================================================================
	//
	// class : WindowsAPI
	// Content : WindowsAPI
	//
	//=========================================================================
	class WindowsAPI :
		public component::Component
	{
	private:
		WindowsAPI() = delete;
		WindowsAPI(const WindowsAPI&) = delete;
		WindowsAPI(WindowsAPI&&) = delete;
		WindowsAPI& operator=(const WindowsAPI&) = delete;
		WindowsAPI& operator=(WindowsAPI&&) = delete;
	public:
		WindowsAPI(const std::string& _class_name, const std::string& _window_name);
		virtual ~WindowsAPI();

		/**
		@brief ウィンドウクラスとセット
		@param style [in] ウィンドウのスタイル
		@param __WndProc [in] WndProc
		@param hIcon [in] アイコンのハンドル
		@param hIconSm [in] 16×16の小さいサイズのアイコンのハンドル
		@param lpszMenuName [in] デフォルトメニュー
		@param hInstance [in] インスタンスハンドル
		@return BUGBUG - might want to remove this from minwin
		*/
		ATOM SetWindowClass(UINT _style, WNDPROC _WndProc, LPCSTR _Icon, LPCSTR _IconSm, LPCSTR _lpszMenuName, HINSTANCE _Instance);

		/**
		@brief ウィンドウの生成
		@param dwStyle [in] ウィンドウスタイル
		@param rect [in] ウィンドウサイズ
		@param hWndParent [in] 親ウィンドウまたはオーナーウィンドウのハンドル
		@param hMenu [in] メニューハンドルまたは子ウィンドウ ID
		@param lpParam [in] ウィンドウ作成データ
		@param nCmdShow [in] ShowWindow
		@return 失敗時に true が返ります
		*/
		bool Create(DWORD _dwStyle, RECT _rect, HWND _WndParent, HMENU _Menu, LPVOID _lpParam, int _CmdShow);

		/**
		@brief メッセージのゲッター
		@return Message
		*/
		MSG& GetMSG();

		/**
		@brief ウィンドウハンドル
		@return hwnd
		*/
		HWND GetHWND();

		/**
		@brief ウィンドウRECT
		@param dwStyle [in] ウィンドウスタイル
		@param Width [in] Width
		@param Height [in] Height
		@param bMenu [in] メニューがあるかどうか
		@return ウィンドウRECT
		*/
		RECT GetWindowRECT(DWORD _dwStyle, int _Width, int _Height, bool _Menu);

		/**
		@brief エラーメッセージ
		*/
		template <typename ... Args>
		void ErrorMessage(const char* _text, const Args& ... _args);
	private:
		std::string m_class_name; // クラス名
		std::string m_window_name; // ウィンドウ名
		RECT m_rect; // ウィンドウRECT
		HWND m_hWnd; // ウィンドウハンドル
		MSG m_msg; // メッセージ
		WNDCLASSEX m_wcex; // ウィンドウクラス
	};

	/**
	@brief エラーメッセージ
	*/
	template<typename ...Args>
	inline void WindowsAPI::ErrorMessage(const char* _text, const Args& ... _args)
	{
		size_t size = snprintf(nullptr, 0, _text, _args ...) + 1; // Extra space for '\0'
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, _text, _args ...);

		MessageBox(m_hWnd, std::string(buf.get(), buf.get() + size - 1).c_str(), "ERROR", MB_OK | MB_ICONEXCLAMATION | MB_ICONWARNING);
	}

	using WindowsAPIReference = reference::IReference<WindowsAPI>;
}
_MSLIB_END