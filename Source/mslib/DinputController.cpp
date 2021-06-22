//==========================================================================
// コントローラー [DinputController.cpp]
// author : MasyoLab
//==========================================================================
#include "DinputController.h"

_MSLIB_BEGIN

namespace dinput_controller
{
	Stick::Stick() : m_left_right(0), m_up_under(0)
	{
	}

	Stick::Stick(const Stick& obj)
	{
		*this = obj;
	}

	Stick::~Stick()
	{
	}

	Stick& Stick::operator=(const Stick& obj)
	{
		m_left_right = obj.m_left_right;
		m_up_under = obj.m_up_under;
		return *this;
	}

	Controller::Controller()
	{
		SetComponentName("Controller");
	}

	Controller::~Controller()
	{
	}

	bool Controller::Init(HINSTANCE _hInstance, HWND _hWnd)
	{
		if (FAILED(DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)& m_input, nullptr)))
		{
			MessageBox(_hWnd, "DirectInputオブジェクトが作れませんでした", "警告", MB_OK);
			return true;
		}

		// デバイスの作成
		m_input->CreateDevice(GUID_Joystick, &m_device, nullptr);

		HRESULT hr;

		hr = m_input->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, nullptr, DIEDFL_FORCEFEEDBACK | DIEDFL_ATTACHEDONLY);
		if (FAILED(hr) || m_device == nullptr)
			m_input->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, nullptr, DIEDFL_ATTACHEDONLY);

		if (m_device == nullptr)
			return false;

		if (FAILED(m_device->SetDataFormat(&c_dfDIJoystick)))
		{
			MessageBox(_hWnd, "コントローラーの初期化に失敗.", "警告", MB_OK);
			return true;
		}

		if (FAILED(m_device->SetCooperativeLevel(_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		{
			MessageBox(_hWnd, "協調モードを設定できません", "警告", MB_OK);
			return true;
		}

		DIDEVCAPS diDevCaps; // デバイス機能
		diDevCaps.dwSize = sizeof(DIDEVCAPS);

		if (FAILED(m_device->GetCapabilities(&diDevCaps)))
		{
			MessageBox(_hWnd, "コントローラー機能を作成できません", "警告", MB_OK);
			return true;
		}

		if (FAILED(m_device->EnumObjects(EnumAxesCallback, (void*)_hWnd, DIDFT_AXIS)))
		{
			MessageBox(_hWnd, "プロパティを設定できません", "警告", MB_OK);
			return true;
		}

		if (FAILED(m_device->Poll()))
		{
			hr = m_device->Acquire();
			while (hr == DIERR_INPUTLOST)
				hr = m_device->Acquire();
		}

		return false;
	}

	void Controller::Update()
	{
		if (m_device == nullptr)
			return;

		DIJOYSTATE state;

		// アクセス権が存在しない場合取得
		if (!SUCCEEDED(m_device->GetDeviceState(sizeof(state), &state)))
		{
			m_device->Acquire();
			return;
		}

		// ボタン
		for (int i = 0; i < (int)sizeof(DIJOYSTATE::rgbButtons); i++)
		{
			// トリガー・リリース情報を生成
			m_state_trigger[i] = (m_state.rgbButtons[i] ^ state.rgbButtons[i]) & state.rgbButtons[i];
			m_state_release[i] = (m_state.rgbButtons[i] ^ state.rgbButtons[i]) & m_state.rgbButtons[i];

			// リピート情報を生成
			if (state.rgbButtons[i])
			{
				if (m_state_repeat_cnt[i] < 20)
				{
					m_state_repeat_cnt[i]++;
					// 押し始めた最初のフレーム、または一定時間経過したらリピート情報ON
					if (m_state_repeat_cnt[i] == 1 || m_state_repeat_cnt[i] >= 20)
						m_state_repeat[i] = state.rgbButtons[i];
					else
						m_state_repeat[i] = 0;
				}
			}
			else
			{
				m_state_repeat_cnt[i] = 0;
				m_state_repeat[i] = 0;
			}
			// プレス情報を保存
			m_state.rgbButtons[i] = state.rgbButtons[i];
		}

		BYTE pov_state[CrossKey::size()];

		// 方向キー
		for (int i = 0; i < CrossKey::size(); i++)
		{
			// 入力情報生成
			if (((state.rgdwPOV[0] / (DWORD)4500) + (DWORD)1) == (DWORD)(i + 1))
				pov_state[i] = 0x80;
			else
				pov_state[i] = 0x00;

			// トリガー・リリース情報を生成
			m_pov_trigger[i] = (m_pov_state[i] ^ pov_state[i]) & pov_state[i];
			m_pov_release[i] = (m_pov_state[i] ^ pov_state[i]) & m_pov_state[i];

			// リピート情報を生成
			if (pov_state[i])
			{
				if (m_pov_repeat_cnt[i] < 20)
				{
					m_pov_repeat_cnt[i]++;
					// 押し始めた最初のフレーム、または一定時間経過したらリピート情報ON
					if (m_pov_repeat_cnt[i] == 1 || m_pov_repeat_cnt[i] >= 20)
						m_pov_repeat[i] = pov_state[i];
					else
						m_pov_repeat[i] = 0x00;
				}
			}
			else
			{
				m_pov_repeat_cnt[i] = 0x00;
				m_pov_repeat[i] = 0x00;
			}
		}

		m_state.lX = state.lX;
		m_state.lY = state.lY;
		m_state.lZ = state.lZ;
		m_state.lRx = state.lRx;
		m_state.lRy = state.lRy;
		m_state.lRz = state.lRz;
	}

	BOOL CALLBACK Controller::EnumJoysticksCallback(const DIDEVICEINSTANCE* _didInstance, void* _context)
	{
		DIDEVCAPS diDevCaps;			// デバイス情報
		auto* pthis = reinterpret_cast<Controller*>(_context);

		if (pthis == nullptr)
			return DIENUM_CONTINUE; // 列挙を続ける

		// ジョイスティック用デバイスオブジェクトを作成
		if (FAILED(pthis->m_input->CreateDevice(_didInstance->guidInstance, &pthis->m_device, nullptr)))
			return DIENUM_CONTINUE; // 列挙を続ける

		// ジョイスティックの能力を調べる
		diDevCaps.dwSize = sizeof(DIDEVCAPS);
		if (FAILED(pthis->m_device->GetCapabilities(&diDevCaps)))
		{
			if (pthis->m_device)
			{
				pthis->m_device->Release();
				pthis->m_device = nullptr;
			}
			return DIENUM_CONTINUE;		// 列挙を続ける
		}
		return DIENUM_STOP; // このデバイスを使うので列挙を終了する
	}

	BOOL CALLBACK Controller::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE* _didoi, void* _context)
	{
		auto* pThis = reinterpret_cast<Controller*>(_context);

		// 軸の値の範囲を設定（-1000～1000）
		DIPROPRANGE diprg;

		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj = _didoi->dwType;
		diprg.diph.dwHow = DIPH_BYID;
		diprg.lMin = -1000;
		diprg.lMax = +1000;

		if (FAILED(pThis->m_device->SetProperty(DIPROP_RANGE, &diprg.diph)))
			return DIENUM_STOP;
		return DIENUM_CONTINUE;
	}

	Stick Controller::LeftStick()
	{
		return StickFunction(m_state.lX, m_state.lY);
	}

	Stick Controller::RightStick()
	{
		return StickFunction(m_state.lZ, m_state.lRz);
	}

	LONG Controller::L2()
	{
		if (m_device == nullptr)
			return (LONG)0;
		return m_state.lRx;
	}

	LONG Controller::R2()
	{
		if (m_device == nullptr)
			return (LONG)0;
		return m_state.lRy;
	}

	bool Controller::CrossButton(int _id)
	{
		int Num = 0;

		if (m_device == nullptr)
			return false;
		if ((int)(sizeof(m_state.rgdwPOV) / 4) < Num)
			return false;
		if ((LONG)4294967295 == m_state.rgdwPOV[Num])
			return false;
		if ((int)((m_state.rgdwPOV[Num] / (LONG)4500) + (LONG)1) == _id)
			return true;
		return false;
	}

	LONG Controller::Adjustment(LONG _set)
	{
		LONG stick;

		if (_set >= (LONG)50 || -(LONG)50 >= _set)
			stick = _set;
		else
			stick = (LONG)0;

		return stick;
	}

	Stick Controller::StickFunction(LONG _stick1, LONG _stick2)
	{
		Stick stick;

		if (m_device != nullptr)
		{
			stick.m_left_right = Adjustment(_stick1);
			stick.m_up_under = Adjustment(_stick2);
		}
		else
		{
			stick.m_left_right = (LONG)0;
			stick.m_up_under = (LONG)0;
		}

		return stick;
	}

	bool Controller::Press(int _id)
	{
		if (m_device == nullptr)
			return false;
		return (m_state.rgbButtons[_id] & 0x80) ? true : false;
	}

	bool Controller::Trigger(int _id)
	{
		if (m_device == nullptr)
			return false;
		return (m_state_trigger[_id] & 0x80) ? true : false;
	}

	bool Controller::Repeat(int _id)
	{
		if (m_device == nullptr)
			return false;
		return (m_pov_repeat[_id] & 0x80) ? true : false;
	}

	bool Controller::Release(int _id)
	{
		if (m_device == nullptr)
			return false;
		return (m_state_release[_id] & 0x80) ? true : false;
	}

	bool Controller::CrossButtonPress(int _id)
	{
		if (m_device == nullptr)
			return false;
		return (m_pov_state[_id] & 0x80) ? true : false;
	}

	bool Controller::CrossButtonTrigger(int _id)
	{
		if (m_device == nullptr)
			return false;
		return (m_pov_trigger[_id] & 0x80) ? true : false;
	}

	bool Controller::CrossButtonRepeat(int _id)
	{
		if (m_device == nullptr)
			return false;
		return (m_pov_repeat[_id] & 0x80) ? true : false;
	}

	bool Controller::CrossButtonRelease(int _id)
	{
		if (m_device == nullptr)
			return false;
		return (m_pov_release[_id] & 0x80) ? true : false;
	}
}
_MSLIB_END