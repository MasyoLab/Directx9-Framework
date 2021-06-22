//==========================================================================
// ダイレクトインプットのマウス [DinputMouse.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "DirectInput.h"

_MSLIB_BEGIN

namespace dinput_mouse
{
    class Speed
    {
    public:
		Speed();
		Speed(const DIMOUSESTATE2 & dim);
		~Speed();
    public:
		LONG x, y, z; // X軸速度
    };

    // 有効ボタン
	class Button
	{
		enum Key
		{
			ELeft = 0,	// 左クリック
			ERight,	// 右クリック
			EWheel,	// ホイール
			MAX,
		};
	public:
		static constexpr int
			Left = Key::ELeft,		// 左クリック
			Right = Key::ERight,	// 右クリック
			Wheel = Key::EWheel;	// ホイール
	public:
		static constexpr int size() { return Key::MAX; }
	};

    //==========================================================================
    //
    // class : Mouse
    // Content : マウス
    //
    //==========================================================================
    class Mouse :
		public direct_input::DirectInput
    {
	private:
		Mouse(const Mouse&) = delete;
		Mouse(Mouse&&) = delete;
		Mouse& operator=(const Mouse&) = delete;
		Mouse& operator=(Mouse&&) = delete;
	public:
        Mouse();
        ~Mouse();

        /**
        @brief 初期化
        @param _hInstance [in] インスタンスハンドル
        @param _hwnd [in] ウィンドウハンドル
        @return 失敗時 true が返ります
        */
        bool Init(HINSTANCE _hInstance, HWND _hwnd);

        /**
        @brief 更新
        */
        void Update()override;

        /**
        @brief プレス
        @param _id [in] 入力キー
        @return 入力されている場合 true が返ります
        */
        bool Press(int _id) override;

        /**
        @brief トリガー
        @param _id [in] 入力キー
        @return 入力されている場合 true が返ります
        */
        bool Trigger(int _id) override;

        /**
        @brief リピート
        @param _id [in] 入力キー
        @return 入力されている場合 true が返ります
        */
        bool Repeat(int _id) override;

        /**
        @brief リリース
        @param _id [in] 入力キー
        @return 入力されている場合 true が返ります
        */
        bool Release(int _id) override;

        /**
        @brief マウスの速度
        @return マウスの移動速度が返ります
        */
        Speed GetSpeed();

        /**
        @brief カーソルの座標
        @return 画面内座標が返ります
        */
        POINT Win32Cursor();

        /**
        @brief 左クリック
        @return 入力されている場合値が返ります
        */
        SHORT Win32LeftClick();

        /**
        @brief 右クリック
        @return 入力されている場合値が返ります
        */
        SHORT Win32RightClick();

        /**
        @brief マウスホイールのホールド判定
        @return 入力されている場合値が返ります
        */
        SHORT Win32WheelHold();
    private:
        static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *_didoi, void *_context);
    private: // DirectInput
        DIMOUSESTATE2 m_state; // 入力情報ワーク
        BYTE m_state_trigger[(int)sizeof(DIMOUSESTATE2::rgbButtons)];	// トリガー情報ワーク
        BYTE m_state_release[(int)sizeof(DIMOUSESTATE2::rgbButtons)]; // リリース情報ワーク
        BYTE m_state_repeat[(int)sizeof(DIMOUSESTATE2::rgbButtons)]; // リピート情報ワーク
        int m_state_repeat_cnt[(int)sizeof(DIMOUSESTATE2::rgbButtons)]; // リピートカウンタ
    private: // WindowsAPI
        POINT m_mouse_pos;
        HWND m_hwnd;
    };

	using MouseReference = reference::IReference<Mouse>;
}
_MSLIB_END