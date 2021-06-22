//==========================================================================
// コントローラー [DinputController.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "DirectInput.h"

_MSLIB_BEGIN

namespace dinput_controller
{
	// 方向キー
	class CrossKey
	{
		// 方向キー
		enum Key
		{
			EUp,
			EUpRight,
			ERight,
			EUnderRight,
			EUnder,
			EUnderLeft,
			ELeft,
			EUpLeft,
			MAX
		};
	public:
		static constexpr int
			Up = Key::EUp,
			UpRight = Key::EUpRight,
			Right = Key::ERight,
			UnderRight = Key::EUnderRight,
			Under = Key::EUnder,
			UnderLeft = Key::EUnderLeft,
			Left = Key::ELeft,
			UpLeft = Key::EUpLeft;
	public:
		static constexpr int size() { return Key::MAX; }
	};

	// PS4 ボタン
	class PS4Button
	{
		enum Key
		{
			ESquare,	// □
			EXButton,	// Ｘ
			ERound,		// 〇
			ETriangle,	// △
			EL1,		// L1
			ER1,		// R1
			EL2,		// L2
			ER2,		// R2
			ESHARE,		// SHARE
			ESOPTIONS,	// OPTIONS
			EL3,		// L3
			ER3,		// R3
			EPS,		// PS
			ETouchPad,	// TouchPad
			MAX
		};
	public:
		static constexpr int
			Square = Key::ESquare,
			XButton = Key::EXButton,
			Round = Key::ERound,
			Triangle = Key::ETriangle,
			L1 = Key::EL1,
			R1 = Key::ER1,
			L2 = Key::EL2,
			R2 = Key::ER2,
			SHARE = Key::ESHARE,
			SOPTIONS = Key::ESOPTIONS,
			L3 = Key::EL3,
			R3 = Key::ER3,
			PS = Key::EPS,
			TouchPad = Key::ETouchPad;
	public:
		static constexpr int size() { return Key::MAX; }
	};

	//==========================================================================
	//
	// class : CPS4
	// Content : PS4コントローラー
	//
	//==========================================================================
	class Stick
	{
	public:
		Stick();
		Stick(const Stick& obj);
		~Stick();
		Stick& operator =(const Stick& obj);
	public:
		LONG m_left_right;
		LONG m_up_under;
	};

	//==========================================================================
	//
	// class : Controller
	// Content : コントローラー
	//
	//==========================================================================
	class Controller :
		public direct_input::DirectInput
	{
	private:
		Controller(const Controller&) = delete;
		Controller(Controller&&) = delete;
		Controller& operator=(const Controller&) = delete;
		Controller& operator=(Controller&&) = delete;
	public:
		Controller();
		~Controller();

		/**
		@brief 初期化
		@param hInstance [in] インスタンスハンドル
		@param hWnd [in] ウィンドウハンドル
		@return 失敗時に true が返ります
		*/
		bool Init(HINSTANCE _hInstance, HWND _hWnd);

		/**
		@brief 更新
		*/
		void Update()override;

		/**
		@brief 左スティックの状態取得
		@return ステックの情報
		*/
		Stick LeftStick();

		/**
		@brief 右スティックの状態取得
		@return ステックの情報
		*/
		Stick RightStick();

		/**
		@brief L2ボタンの状態取得
		@return L2ボタンの情報
		*/
		LONG L2();

		/**
		@brief R2ボタンの状態取得
		@return R2ボタンの情報
		*/
		LONG R2();

		/**
		@brief PS4 方向キー
		@param _id [in] 使用キーの指定
		@return 入力されている場合 true が返ります
		*/
		bool CrossButton(int _id);

		/**
		@brief PS4 方向キー プレス
		@param _id [in] 使用キーの指定
		@return 入力されている場合 true が返ります
		*/
		bool CrossButtonPress(int _id);

		/**
		@brief PS4 方向キー トリガー
		@param _id [in] 使用キーの指定
		@return 入力されている場合 true が返ります
		*/
		bool CrossButtonTrigger(int _id);

		/**
		@brief PS4 方向キー リピート
		@param _id [in] 使用キーの指定
		@return 入力されている場合 true が返ります
		*/
		bool CrossButtonRepeat(int _id);

		/**
		@brief PS4 方向キー リリ－ス
		@param _id [in] 使用キーの指定
		@return 入力されている場合 true が返ります
		*/
		bool CrossButtonRelease(int _id);

		/**
		@brief PS4 ボタン プレス
		@param _id [in] 使用キーの指定
		@return 入力されている場合 true が返ります
		*/
		bool Press(int _id) override;

		/**
		@brief PS4 ボタン トリガー
		@param _id [in] 使用キーの指定
		@return 入力されている場合 true が返ります
		*/
		bool Trigger(int _id) override;

		/**
		@brief PS4 ボタン リピート
		@param _id [in] 使用キーの指定
		@return 入力されている場合 true が返ります
		*/
		bool Repeat(int _id) override;

		/**
		@brief PS4 ボタン リリ－ス
		@param _id [in] 使用キーの指定
		@return 入力されている場合 true が返ります
		*/
		bool Release(int _id) override;
	private:
		/**
		@brief PS4 入力誤差修正
		@param _set [in] 入力
		@return 値が返ります
		*/
		LONG Adjustment(LONG _set);

		/**
		@brief PS4 ステック入力制御
		@param _stick1 [in] 入力
		@param _stick2 [in] 入力
		@return 値が返ります
		*/
		Stick StickFunction(LONG _stick1, LONG _stick2);
	private:
		static BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE* _didInstance, void* _context);
		static BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE* _didoi, void* _context);
	private:
		DIJOYSTATE m_state; // 入力情報ワーク
		BYTE m_state_trigger[(int)sizeof(DIJOYSTATE::rgbButtons)]; // トリガー情報ワーク
		BYTE m_state_release[(int)sizeof(DIJOYSTATE::rgbButtons)]; // リリース情報ワーク
		BYTE m_state_repeat[(int)sizeof(DIJOYSTATE::rgbButtons)]; // リピート情報ワーク
		int m_state_repeat_cnt[(int)sizeof(DIJOYSTATE::rgbButtons)]; // リピートカウンタ

		BYTE m_pov_state[CrossKey::size()]; // POV入力情報ワーク
		BYTE m_pov_trigger[CrossKey::size()]; // トリガー情報ワーク
		BYTE m_pov_release[CrossKey::size()]; // リリース情報ワーク
		BYTE m_pov_repeat[CrossKey::size()]; // リピート情報ワーク
		int m_pov_repeat_cnt[CrossKey::size()]; // リピートカウンタ
	};

	using ControllerReference = reference::IReference<Controller>;
}

_MSLIB_END