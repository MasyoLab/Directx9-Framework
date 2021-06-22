//==========================================================================
// キーボード入力処理 [DinputKeyboard.cpp]
// author : MasyoLab
//==========================================================================
#include "DinputKeyboard.h"

_MSLIB_BEGIN

namespace dinput_keyboard
{
	Keyboard::Keyboard()
	{
		SetComponentName("Keyboard");
	}

	Keyboard::~Keyboard()
	{
	}

	bool Keyboard::Init(HINSTANCE _hInstance, HWND _hWnd)
	{
		// DirectInputオブジェクトの作成
		if (FAILED(DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)& m_input, nullptr)))
		{
			MessageBox(_hWnd, "DirectInputオブジェクトが作れませんでした", "警告", MB_ICONWARNING);
			return true;
		}

		// デバイスの作成
		if (FAILED(m_input->CreateDevice(GUID_SysKeyboard, &m_device, nullptr)))
		{
			MessageBox(_hWnd, "キーボードがありませんでした", "警告", MB_ICONWARNING);
			return true;
		}

		if (m_device == nullptr)
			return false;

		// データフォーマットを設定
		if (FAILED(m_device->SetDataFormat(&c_dfDIKeyboard)))
		{
			MessageBox(_hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告", MB_ICONWARNING);
			return true;
		}

		// 協調モードを設定（フォアグラウンド＆非排他モード）
		if (FAILED(m_device->SetCooperativeLevel(_hWnd, (DISCL_FOREGROUND/*DISCL_BACKGROUND*/ | DISCL_NONEXCLUSIVE))))
		{
			MessageBox(_hWnd, "キーボードの協調モードを設定できませんでした。", "警告", MB_ICONWARNING);
			return true;
		}

		// キーボードへのアクセス権を獲得(入力制御開始)
		m_device->Acquire();

		return false;
	}

	void Keyboard::Update()
	{
		if (m_device == nullptr)
			return;

		BYTE state[Button::size()];

		// アクセス権が存在しない場合取得
		if (!SUCCEEDED(m_device->GetDeviceState(sizeof(state), state)))
		{
			m_device->Acquire();
			return;
		}

		// aKeyState[m_KeyMax]&0x80
		for (int i = 0; i < Button::size(); i++)
		{
			// キートリガー・リリース情報を生成
			m_state_trigger[i] = (m_state[i] ^ state[i]) & state[i];
			m_state_release[i] = (m_state[i] ^ state[i]) & m_state[i];

			// キーリピート情報を生成
			if (state[i])
			{
				if (m_state_repeat_cnt[i] < 20)
				{
					m_state_repeat_cnt[i]++;
					if (m_state_repeat_cnt[i] == 1 || m_state_repeat_cnt[i] >= 20)
					{// キーを押し始めた最初のフレーム、または一定時間経過したらキーリピート情報ON
						m_state_repeat[i] = state[i];
					}
					else
					{
						m_state_repeat[i] = 0;
					}
				}
			}
			else
			{
				m_state_repeat_cnt[i] = 0;
				m_state_repeat[i] = 0;
			}

			// キープレス情報を保存
			m_state[i] = state[i];
		}
	}

	bool Keyboard::Press(int _id)
	{
		if (m_device == nullptr)
			return false;
		return (m_state[_id] & 0x80) ? true : false;
	}

	bool Keyboard::Trigger(int _id)
	{
		if (m_device == nullptr)
			return false;
		return (m_state_trigger[_id] & 0x80) ? true : false;
	}

	bool Keyboard::Repeat(int _id)
	{
		if (m_device == nullptr)
			return false;
		return (m_state_repeat[_id] & 0x80) ? true : false;
	}

	bool Keyboard::Release(int _id)
	{
		if (m_device == nullptr)
			return false;
		return (m_state_release[_id] & 0x80) ? true : false;
	}
}
_MSLIB_END