//==========================================================================
// Xインプット [XInputDX.h]
// author : MasyoLab
//==========================================================================
#pragma once

#pragma comment (lib, "xinput.lib") // ライブラリのインポート
#include <Windows.h>
#include <XInput.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Component.h"
#include "Reference.h"

_MSLIB_BEGIN

namespace xinput
{
	using XinputState = reference::WrapperReference<XINPUT_STATE, XINPUT_STATE>;

	//==========================================================================
	//
	// class : Bool4
	// Content : Bool4
	//
	//==========================================================================
	class Bool4
	{
	public:
		Bool4();
		Bool4(bool _up, bool _down, bool _left, bool _right);
		~Bool4();
	public:
		bool m_up, m_down, m_left, m_right;
	};

	//==========================================================================
	//
	// class : AnalogTrigger
	// Content : アナログスティックのトリガー
	//
	//==========================================================================
	class AnalogTrigger
	{
	public:
		AnalogTrigger();
		~AnalogTrigger();
	public:
		/**
		@brief 更新
		*/
		void update();

		/**
		@brief 切り替え
		@param input [in] 判定キー
		@param out [in/out] 対象
		*/
		void ifset(bool _input, bool& _out);

		/**
		@brief 比較 in1 < in2
		@param in1 [in] 対象1
		@param in2 [in/out] 対象2
		@return in2 が大きい場合 true
		*/
		bool ifbool(float _in1, float _in2);
	public:
		Bool4 m_Ltrigger; // 左アナログのトリガー
		Bool4 m_LtriggerOld; // 左アナログの古いトリガー
		Bool4 m_Rtrigger; // 右アナログのトリガー
		Bool4 m_RtriggerOld; // 右アナログの古いトリガー
	};

	// アナログのボタン
	enum class AnalogButton
	{
		UP, // 上
		DOWN, // 下
		LEFT, // 左
		RIGHT, // 右
	};

	// xBoxの押せるボタン
	enum class Button
	{
		DPAD_UP = XINPUT_GAMEPAD_DPAD_UP, // 十字ボタン 上
		DPAD_DOWN = XINPUT_GAMEPAD_DPAD_DOWN, // 十字ボタン 下
		DPAD_LEFT = XINPUT_GAMEPAD_DPAD_LEFT, // 十字ボタン 左
		DPAD_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT, // 十字ボタン 右
		START = XINPUT_GAMEPAD_START, // STARTボタン
		BACK = XINPUT_GAMEPAD_BACK, // BACKボタン
		LEFT_THUMB = XINPUT_GAMEPAD_LEFT_THUMB, // 左アナログスティックのボタン
		RIGHT_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB, // 右アナログスティックのボタン
		LEFT_LB = XINPUT_GAMEPAD_LEFT_SHOULDER, // LBボタン
		RIGHT_RB = XINPUT_GAMEPAD_RIGHT_SHOULDER, // RBボタン
		A = XINPUT_GAMEPAD_A, // Aボタン
		B = XINPUT_GAMEPAD_B, // Bボタン
		X = XINPUT_GAMEPAD_X, // Xボタン
		Y = XINPUT_GAMEPAD_Y, // Yボタン
	};

	//==========================================================================
	//
	// class : XInput
	// Content : Xインプット
	//
	//==========================================================================
	class XInput :
		public component::Component
	{
	private:
		XInput(const XInput&) = delete;
		XInput(XInput&&) = delete;
		XInput& operator=(const XInput&) = delete;
		XInput& operator=(XInput&&) = delete;
	public:
		XInput();
		virtual ~XInput();

		/**
		@brief 初期化
		@param num [in] 取るコントローラーの数
		@return 失敗時 true
		*/
		bool Init(int _num);

		/**
		@brief 解放
		*/
		void Release();

		/**
		@brief 更新
		*/
		void Update();

		/**
		@brief プレス
		@param button [in] ボタンID
		@param index [in] 処理コントローラー
		@return 押しているとき true
		*/
		bool Press(Button _button, int _index);

		/**
		@brief トリガー
		@param button [in] ボタンID
		@param index [in] 処理コントローラー
		@return 押しているとき true
		*/
		bool Trigger(Button _button, int _index);

		/**
		@brief リリース
		@param button [in] ボタンID
		@param index [in] 処理コントローラー
		@return 押しているとき true
		*/
		bool Release(Button _button, int _index);

		/**
		@brief 左アナログスティック
		@param index [in] 処理コントローラー
		@param Out [in] 傾きベクトル
		@return 押しているとき true
		*/
		bool AnalogL(int _index, D3DXVECTOR3& _out);

		/**
		@brief 左アナログスティック
		@param index [in] 処理コントローラー
		@return 押しているとき true
		*/
		bool AnalogL(int _index);

		/**
		@brief 右アナログスティック
		@param index [in] 処理コントローラー
		@param Out [in] 傾きベクトル
		@return 押しているとき true
		*/
		bool AnalogR(int index, D3DXVECTOR3& Out);

		/**
		@brief 右アナログスティック
		@param index [in] 処理コントローラー
		@return 押しているとき true
		*/
		bool AnalogR(int _index);

		/**
		@brief 左アナログスティックのトリガー
		@param button [in] ボタンID
		@param index [in] 処理コントローラー
		@return 押しているとき true
		*/
		bool AnalogLTrigger(AnalogButton _button, int _index);

		/**
		@brief 左アナログスティックのトリガー
		@param index [in] 処理コントローラー
		@param button [in] ボタンID
		@param out [in/out] 傾きベクトル
		@return 押しているとき true
		*/
		bool AnalogLTrigger(AnalogButton _button, int _index, D3DXVECTOR3& _out);

		/**
		@brief 右アナログスティックのトリガー
		@param index [in] 処理コントローラー
		@param key [in] ボタンID
		@return 押しているとき true
		*/
		bool AnalogRTrigger(AnalogButton _button, int _index);

		/**
		@brief 右アナログスティックのトリガー
		@param index [in] 処理コントローラー
		@param key [in] ボタンID
		@param Out [in] 傾きベクトル
		@return 押しているとき true
		*/
		bool AnalogRTrigger(AnalogButton _button, int _index, D3DXVECTOR3& _out);

		/**
		@brief 左トリガーボタン
		@param index [in] 処理コントローラー
		@return 押しているとき true
		*/
		bool LT(int _index);

		/**
		@brief 右トリガーボタン
		@param index [in] 処理コントローラー
		@return 押しているとき true
		*/
		bool RT(int _index);

		/**
		@brief コントローラーの存在の確認
		@param index [in] 処理コントローラー
		@return 存在する場合 true
		*/
		bool Check(int _index);

		/**
		@brief コントローラーの現在の状態を取得
		@param index [in] 処理コントローラー
		@return インスタンス
		*/
		XinputState GetState(int _index);

		/**
		@brief サイズ
		@return コントローラー数
		*/
		int Size();
	private:
		/**
		@brief コントローラのキートリガー
		@param new [in] 新しい判定キー
		@param old [in] 古い判定キー
		@return 結果
		*/
		bool KeyTrigger(bool _new, bool _old);

		/**
		@brief コントローラのキーリリース
		@param new [in] 新しい判定キー
		@param old [in] 古い判定キー
		@return 結果
		*/
		bool KeyRelease(bool _new, bool _old);
	private:
		XINPUT_STATE* m_state; // コントローラーのステータス
		XINPUT_STATE* m_stateOld; // 古い情報
		AnalogTrigger* m_trigger; // アナログのトリガー
		bool* m_statedat; //パッドの有無
		int m_numdata; // 登録されたデータ数
	};

	using XInputReference = reference::IReference<XInput>;
}

_MSLIB_END