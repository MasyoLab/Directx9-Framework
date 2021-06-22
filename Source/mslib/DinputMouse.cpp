//==========================================================================
// ダイレクトインプットのマウス [DinputMouse.cpp]
// author : MasyoLab
//==========================================================================
#include "DinputMouse.h"

_MSLIB_BEGIN

namespace dinput_mouse
{
	Speed::Speed() :x(0), y(0), z(0)
	{
	}

	Speed::Speed(const DIMOUSESTATE2 & dim) :
		x(dim.lX), y(dim.lY), z(dim.lZ)
	{
	}

    Speed::~Speed()
    {
    }

	Mouse::Mouse() :
		m_hwnd(nullptr)
	{
		SetComponentName("Mouse");
    }

    Mouse::~Mouse()
    {
    }

    bool Mouse::Init(HINSTANCE _hInstance, HWND _hwnd)
    {
		m_hwnd = _hwnd;
		m_mouse_pos.x = m_mouse_pos.y = (LONG)0;

        if (FAILED(DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_input, nullptr)))
        {
            MessageBox(_hwnd, "DirectInputオブジェクトが作れませんでした", "警告", MB_OK);
            return true;
        }

        if (FAILED(m_input->CreateDevice(GUID_SysMouse, &m_device, nullptr)))
        {
            MessageBox(_hwnd, "マウスがありませんでした。", "警告", MB_OK);
            return true;
        }

		if (m_device == nullptr)
			return false;

		// マウス用のデータ・フォーマットを設定
		if (FAILED(m_device->SetDataFormat(&c_dfDIMouse2)))
		{
			MessageBox(_hwnd, "マウスのデータフォーマットを設定できませんでした。", "警告", MB_ICONWARNING);
			return true;
		}

		// 協調モードを設定（フォアグラウンド＆非排他モード）
		if (FAILED(m_device->SetCooperativeLevel(_hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
		{
			MessageBox(_hwnd, "マウスの協調モードを設定できませんでした。", "警告", MB_ICONWARNING);
			return true;
		}

		if (FAILED(m_device->EnumObjects(EnumAxesCallback, _hwnd, DIDFT_AXIS)))
		{
			MessageBox(_hwnd, "プロパティを設定できません", "警告", MB_OK);
			return true;
		}

		if (FAILED(m_device->Poll()))
			while (m_device->Acquire() == DIERR_INPUTLOST)
				m_device->Acquire();

        return false;
    }

    BOOL CALLBACK Mouse::EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *_didoi, void *_context)
    {
        DIPROPDWORD diprop;

		_context;
        diprop.diph.dwSize = sizeof(DIPROPDWORD);
        diprop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
        diprop.diph.dwHow = DIPH_DEVICE;
        diprop.diph.dwObj = _didoi->dwType;
        diprop.dwData = DIPROPAXISMODE_REL; // 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）    

        return DIENUM_CONTINUE;
    }

    void Mouse::Update()
    {
		GetCursorPos(&m_mouse_pos);
		ScreenToClient(m_hwnd, &m_mouse_pos);

		if (m_device == nullptr)
			return;

        DIMOUSESTATE2 state;

		// アクセス権が存在しない場合取得
		if (!SUCCEEDED(m_device->GetDeviceState(sizeof(state), &state)))
		{
			m_device->Acquire();
			return;
		}

		for (int i = 0; i < (int)sizeof(DIMOUSESTATE2::rgbButtons); i++)
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
					if (m_state_repeat_cnt[i] == 1 || m_state_repeat_cnt[i] >= 20)
					{// 押し始めた最初のフレーム、または一定時間経過したらリピート情報ON
						m_state_repeat[i] = state.rgbButtons[i];
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
			// プレス情報を保存
			m_state.rgbButtons[i] = state.rgbButtons[i];
		}
		m_state.lX = state.lX;
		m_state.lY = state.lY;
		m_state.lZ = state.lZ;
    }

    bool Mouse::Press(int _id)
    {
        if (m_device == nullptr)
			return false;
        return (m_state.rgbButtons[_id] & 0x80) ? true : false;
    }

    bool Mouse::Trigger(int _id)
    {
        if (m_device == nullptr)
			return false;
        return (m_state_trigger[_id] & 0x80) ? true : false;
    }

    bool Mouse::Repeat(int _id)
    {
        if (m_device == nullptr)
			return false;
        return (m_state_repeat[_id] & 0x80) ? true : false;
    }

    bool Mouse::Release(int _id)
    {
        if (m_device == nullptr)
			return false;
        return (m_state_release[_id] & 0x80) ? true : false;
    }

    Speed Mouse::GetSpeed()
    {
        return m_state;
    }

    POINT Mouse::Win32Cursor()
    {
        return m_mouse_pos;
    }

    SHORT Mouse::Win32LeftClick()
    {
        return GetAsyncKeyState(VK_LBUTTON);
    }

    SHORT Mouse::Win32RightClick()
    {
        return GetAsyncKeyState(VK_RBUTTON);
    }

    SHORT Mouse::Win32WheelHold()
    {
        return GetAsyncKeyState(VK_MBUTTON);
    }
}
_MSLIB_END