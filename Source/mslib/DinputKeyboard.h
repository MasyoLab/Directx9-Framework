//==========================================================================
// キーボード入力処理 [DinputKeyboard.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "DirectInput.h"

_MSLIB_BEGIN

namespace dinput_keyboard
{
	class Button
	{
		static constexpr int __MaxKey = 256;
	public:
		static constexpr int
			KEY_SPACE = DIK_SPACE, // Spause
			KEY_A = DIK_A, // A～Z
			KEY_B = DIK_B, // A～Z
			KEY_C = DIK_C, // A～Z
			KEY_D = DIK_D, // A～Z
			KEY_E = DIK_E, // A～Z
			KEY_F = DIK_F, // A～Z
			KEY_G = DIK_G, // A～Z
			KEY_H = DIK_H, // A～Z
			KEY_I = DIK_I, // A～Z
			KEY_J = DIK_J, // A～Z
			KEY_K = DIK_K, // A～Z
			KEY_L = DIK_L, // A～Z
			KEY_N = DIK_N, // A～Z
			KEY_M = DIK_M, // A～Z
			KEY_O = DIK_O, // A～Z
			KEY_P = DIK_P, // A～Z
			KEY_Q = DIK_Q, // A～Z
			KEY_R = DIK_R, // A～Z
			KEY_S = DIK_S, // A～Z
			KEY_T = DIK_T, // A～Z
			KEY_U = DIK_U, // A～Z
			KEY_V = DIK_V, // A～Z
			KEY_W = DIK_W, // A～Z
			KEY_X = DIK_X, // A～Z
			KEY_Y = DIK_Y, // A～Z
			KEY_Z = DIK_Z, // A～Z
			KEY_1 = DIK_1, // 数字(メイン・キーボード)
			KEY_2 = DIK_2, // 数字(メイン・キーボード)
			KEY_3 = DIK_3, // 数字(メイン・キーボード)
			KEY_4 = DIK_4, // 数字(メイン・キーボード)
			KEY_5 = DIK_5, // 数字(メイン・キーボード)
			KEY_6 = DIK_6, // 数字(メイン・キーボード)
			KEY_7 = DIK_7, // 数字(メイン・キーボード)
			KEY_8 = DIK_8, // 数字(メイン・キーボード)
			KEY_9 = DIK_9, // 数字(メイン・キーボード)
			KEY_0 = DIK_0, // 数字(メイン・キーボード)
			KEY_MINUS = DIK_MINUS, // [-] (メイン・キーボード)
			KEY_EQUALS = DIK_EQUALS, // [＝] (メイン・キーボード)
			KEY_RETURN = DIK_RETURN, // Enter(メイン・キーボード)
			KEY_F1 = DIK_F1, // F1～F12
			KEY_F2 = DIK_F2, // F1～F12
			KEY_F3 = DIK_F3, // F1～F12
			KEY_F4 = DIK_F4, // F1～F12
			KEY_F5 = DIK_F5, // F1～F12
			KEY_F6 = DIK_F6, // F1～F12
			KEY_F7 = DIK_F7, // F1～F12
			KEY_F8 = DIK_F8, // F1～F12
			KEY_F9 = DIK_F9, // F1～F12
			KEY_F10 = DIK_F10, // F1～F12
			KEY_F11 = DIK_F11, // F1～F12
			KEY_F12 = DIK_F12, // F1～F12
			KEY_DOWN = DIK_DOWN, // [↓]
			KEY_LEFT = DIK_LEFT, // [←]
			KEY_RIGHT = DIK_RIGHT, // [→]
			KEY_UP = DIK_UP, // [↑]
			KEY_CAPITAL = DIK_CAPITAL, // Caps Lock
			KEY_TAB = DIK_TAB, // TAB
			KEY_ESCAPE = DIK_ESCAPE, // Esc
			KEY_BACK = DIK_BACK, // BackSpace
			KEY_INSERT = DIK_INSERT, // insert
			KEY_DELETE = DIK_DELETE, // Delete
			KEY_HOME = DIK_HOME, // Home
			KEY_END = DIK_END, // End
			KEY_PRIOR = DIK_PRIOR, // PageUp
			KEY_NEXT = DIK_NEXT, // PageDown
			KEY_SYSRQ = DIK_SYSRQ, // SysRq
			KEY_SCROLL = DIK_SCROLL, // ScrollLock
			KEY_PAUSE = DIK_PAUSE, // Pause
			KEY_LCONTROL = DIK_LCONTROL, // 左Ctrl
			KEY_RCONTROL = DIK_RCONTROL, // 右Ctrl
			KEY_LMENU = DIK_LMENU, // 左Alt
			KEY_RMENU = DIK_RMENU, // 右Alt
			KEY_LSHIFT = DIK_LSHIFT, // 左Shift
			KEY_RSHIFT = DIK_RSHIFT, // 右Shift
			KEY_LWIN = DIK_LWIN, // 左Windows
			KEY_RWIN = DIK_RWIN, // 右Windows
			KEY_LBRACKET = DIK_LBRACKET, // 左角カッコ {
			KEY_RBRACKET = DIK_RBRACKET, // 右角カッコ }
			KEY_PERIOD = DIK_PERIOD, // ピリオド(メイン・キーボード)
			KEY_APOSTROPHE = DIK_APOSTROPHE, // アポストロフィ
			KEY_APPS = DIK_APPS, // アプリケーション
			KEY_BACKSLASH = DIK_BACKSLASH, // バック・スラッシュ
			KEY_SLASH = DIK_SLASH, // スラッシュ(メイン・キーボード)
			KEY_COMMA = DIK_COMMA, // コンマ
			KEY_SEMICOLON = DIK_SEMICOLON, // セミコロン
			KEY_GRAVE = DIK_GRAVE, // アクサン・グラーヴ(`)
			KEY_NUMLOCK = DIK_NUMLOCK, // NumLock
			KEY_NUMPAD0 = DIK_NUMPAD0, // テンキーの 0～9
			KEY_NUMPAD1 = DIK_NUMPAD1, // テンキーの 0～9
			KEY_NUMPAD2 = DIK_NUMPAD2, // テンキーの 0～9
			KEY_NUMPAD3 = DIK_NUMPAD3, // テンキーの 0～9
			KEY_NUMPAD4 = DIK_NUMPAD4, // テンキーの 0～9
			KEY_NUMPAD5 = DIK_NUMPAD5, // テンキーの 0～9
			KEY_NUMPAD6 = DIK_NUMPAD6, // テンキーの 0～9
			KEY_NUMPAD7 = DIK_NUMPAD7, // テンキーの 0～9
			KEY_NUMPAD8 = DIK_NUMPAD8, // テンキーの 0～9
			KEY_NUMPAD9 = DIK_NUMPAD9, // テンキーの 0～9
			KEY_ADD = DIK_ADD, // テンキーの[+]
			KEY_SUBTRACT = DIK_SUBTRACT, // テンキーの[-]
			KEY_DECIMAL = DIK_DECIMAL, // テンキーの[.]
			KEY_DIVIDE = DIK_DIVIDE, // テンキーの[/]
			KEY_MULTIPLY = DIK_MULTIPLY, // テンキーの[*]
			KEY_DNUMPADENTER = DIK_NUMPADENTER, // テンキーのEnter
			KEY_F13 = DIK_F13, // NEC PC98 F13～F15
			KEY_F14 = DIK_F14, // NEC PC98 F13～F15
			KEY_F15 = DIK_F15, // NEC PC98 F13～F15
			KEY_YEN = DIK_YEN, // 日本語キーボードの￥
			KEY_NOCONVERT = DIK_NOCONVERT, // 日本語キーボードのキー
			KEY_UNLABELED = DIK_UNLABELED, // 日本語キーボードのキー
			KEY_KANA = DIK_KANA, // 日本語キーボードのキー
			KEY_KANJI = DIK_KANJI, // 日本語キーボードのキー
			KEY_AT = DIK_AT, // 日本語キーボードのキー
			KEY_AX = DIK_AX, // 日本語キーボードのキー
			KEY_COLON = DIK_COLON, // 日本語キーボードのキー
			KEY_CONVERT = DIK_CONVERT; // 日本語キーボードのキー
	public:
		static constexpr int size() { return __MaxKey; }
	};

	//==========================================================================
	//
	// class : DirectInputKeyboard
	// Content : キーボード
	//
	//==========================================================================
	class Keyboard :
		public direct_input::DirectInput
	{
	private:
		Keyboard(const Keyboard&) = delete;
		Keyboard(Keyboard&&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;
		Keyboard& operator=(Keyboard&&) = delete;
	public:
		Keyboard();
		~Keyboard();

		/**
		@brief 初期化
		@param _hInstance [in] インスタンスハンドル
		@param _hWnd [in] ウィンドウハンドル
		@return 失敗時に true が返ります
		*/
		bool Init(HINSTANCE _hInstance, HWND _hWnd);

		/**
		@brief 更新
		*/
		void Update()override;

		/**
		@brief プレス
		@param _id [in] 入力キー
		@return 押されている場合 true が返ります
		*/
		bool Press(int _id) override;

		/**
		@brief トリガー
		@param _id [in] 入力キー
		@return 押されている場合 true が返ります
		*/
		bool Trigger(int _id) override;

		/**
		@brief リピート
		@param _id [in] 入力キー
		@return 押されている場合 true が返ります
		*/
		bool Repeat(int _id) override;

		/**
		@brief リリース
		@param _id [in] 入力キー
		@return 押されている場合 true が返ります
		*/
		bool Release(int _id) override;
	private:
		BYTE m_state[Button::size()] = { 0 }; // キーボードの入力情報ワーク
		BYTE m_state_trigger[Button::size()] = { 0 }; // キーボードのトリガー情報ワーク
		BYTE m_state_release[Button::size()] = { 0 }; // キーボードのリリース情報ワーク
		BYTE m_state_repeat[Button::size()] = { 0 }; // キーボードのリピート情報ワーク
		int m_state_repeat_cnt[Button::size()] = { 0 }; // キーボードのリピートカウンタ
	};

	using KeyboardReference = reference::IReference<Keyboard>;
}

_MSLIB_END