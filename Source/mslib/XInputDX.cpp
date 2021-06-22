//==========================================================================
// Xインプット [XInputDX.cpp]
// author : MasyoLab
//==========================================================================
#include "XInputDX.h"

_MSLIB_BEGIN

namespace xinput
{
	Bool4::Bool4() :
		m_up(false), m_down(false), m_left(false), m_right(false)
	{
	}

	Bool4::Bool4(bool _up, bool _down, bool _left, bool _right) :
		m_up(_up), m_down(_down), m_left(_left), m_right(_right)
	{
	}

	Bool4::~Bool4()
	{
	}

	XInput::XInput() :
		Component("XInput"), m_state(nullptr), m_stateOld(nullptr), m_statedat(nullptr), m_trigger(nullptr), m_numdata(0)
	{
	}

	XInput::~XInput()
	{
		Release();
	}

	bool XInput::Init(int _num)
	{
		DWORD dwResult;

		Release();

		// 登録数の代入
		m_numdata = _num;
		mslib::_new(m_statedat, _num);
		mslib::_new(m_state, _num);
		mslib::_new(m_stateOld, _num);
		mslib::_new(m_trigger, _num);

		for (int i = 0; i < m_numdata; i++)
		{
			// 中身をきれいにする
			ZeroMemory(&m_state[i], sizeof(XINPUT_STATE));

			// コントローラーの情報の取得
			dwResult = XInputGetState((DWORD)i, &m_state[i]);
			if (dwResult != ERROR_SUCCESS)
				m_statedat[i] = false;
			else
				m_statedat[i] = true;
		}
		return false;
	}

	void XInput::Release()
	{
		mslib::_delete(m_state);
		mslib::_delete(m_stateOld);
		mslib::_delete(m_statedat);
		mslib::_delete(m_trigger);
	}

	void XInput::Update()
	{
		for (int i = 0; i < m_numdata; i++)
		{
			// アクセス速度の向上
			auto* pnew = &m_state[i];
			auto* pold = &m_stateOld[i];
			auto* panatri = &m_trigger[i];

			// コントローラ情報の複製
			*pold = *pnew;

			// コントローラーの情報の取得
			XInputGetState(i, pnew);

			// 左スティックのデッドゾーン
			if ((pnew->Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pnew->Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
				(pnew->Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && pnew->Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
			{
				pnew->Gamepad.sThumbLX = 0;
				pnew->Gamepad.sThumbLY = 0;
			}

			// 右スティックのデッドゾーン
			if ((pnew->Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pnew->Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
				(pnew->Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && pnew->Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
			{
				pnew->Gamepad.sThumbRX = 0;
				pnew->Gamepad.sThumbRY = 0;
			}

			// アナログスティックトリガー用更新
			panatri->update();

			// 左アナログのトリガー処理
			if (pnew->Gamepad.sThumbLY > /*XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE*/(SHORT)31000 ||
				pnew->Gamepad.sThumbLY < -/*XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE*/(SHORT)31000 ||
				pnew->Gamepad.sThumbLX < -/*XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE*/(SHORT)31000 ||
				pnew->Gamepad.sThumbLX > /*XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE*/(SHORT)31000)
			{
				panatri->ifset(panatri->ifbool((1.41421356f / 2.0f), (float)pnew->Gamepad.sThumbLY), panatri->m_Ltrigger.m_up);
				panatri->ifset(panatri->ifbool((float)pnew->Gamepad.sThumbLY, -(1.41421356f / 2.0f)), panatri->m_Ltrigger.m_down);
				panatri->ifset(panatri->ifbool((float)pnew->Gamepad.sThumbLX, -(1.41421356f / 2.0f)), panatri->m_Ltrigger.m_left);
				panatri->ifset(panatri->ifbool((1.41421356f / 2.0f), (float)pnew->Gamepad.sThumbLX), panatri->m_Ltrigger.m_right);
			}
			else
			{
				panatri->m_Ltrigger = Bool4();
			}

			// 右アナログのトリガー処理
			if (pnew->Gamepad.sThumbRY > /*XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE*/(SHORT)31000 ||
				pnew->Gamepad.sThumbRY < -/*XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE*/(SHORT)31000 ||
				pnew->Gamepad.sThumbRX < -/*XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE*/(SHORT)31000 ||
				pnew->Gamepad.sThumbRX > /*XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE*/(SHORT)31000)
			{
				panatri->ifset(panatri->ifbool((1.41421356f / 2.0f), (float)pnew->Gamepad.sThumbRY), panatri->m_Rtrigger.m_up);
				panatri->ifset(panatri->ifbool((float)pnew->Gamepad.sThumbRY, -(1.41421356f / 2.0f)), panatri->m_Rtrigger.m_down);
				panatri->ifset(panatri->ifbool((float)pnew->Gamepad.sThumbRX, -(1.41421356f / 2.0f)), panatri->m_Rtrigger.m_left);
				panatri->ifset(panatri->ifbool((1.41421356f / 2.0f), (float)pnew->Gamepad.sThumbRX), panatri->m_Rtrigger.m_right);
			}
			else
			{
				panatri->m_Rtrigger = Bool4();
			}
		}
	}

	bool XInput::Press(Button _button, int _index)
	{
		return (m_state[_index].Gamepad.wButtons & (WORD)_button) ? true : false;
	}

	bool XInput::Trigger(Button _button, int _index)
	{
		return KeyTrigger(
			(bool)((m_state[_index].Gamepad.wButtons & (WORD)_button) ? true : false),
			(bool)((m_stateOld[_index].Gamepad.wButtons & (WORD)_button) ? true : false)
		);
	}

	bool XInput::Release(Button _button, int _index)
	{
		return KeyRelease(
			(m_state[_index].Gamepad.wButtons & (WORD)_button) ? true : false,
			(m_stateOld[_index].Gamepad.wButtons & (WORD)_button) ? true : false
		);
	}

	bool XInput::AnalogL(int _index, D3DXVECTOR3& _out)
	{
		auto* pstate = &m_state[_index];

		_out = D3DXVECTOR3(pstate->Gamepad.sThumbLX, 0.0f, pstate->Gamepad.sThumbLY);
		D3DXVec3Normalize(&_out, &_out);

		return AnalogL(_index);
	}

	bool XInput::AnalogL(int _index)
	{
		auto* pstate = &m_state[_index];

		if (pstate->Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
			pstate->Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
			pstate->Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
			pstate->Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			return true;
		}

		return false;
	}

	bool XInput::AnalogR(int index, D3DXVECTOR3& Out)
	{
		auto* pstate = &m_state[index];

		Out = D3DXVECTOR3(pstate->Gamepad.sThumbRX, 0.0f, pstate->Gamepad.sThumbRY);
		D3DXVec3Normalize(&Out, &Out);

		return AnalogR(index);
	}

	bool XInput::AnalogR(int _index)
	{
		auto* pstate = &m_state[_index];

		if (pstate->Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
			pstate->Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
			pstate->Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
			pstate->Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			return true;
		}

		return false;
	}

	bool XInput::AnalogLTrigger(AnalogButton _button, int _index)
	{
		switch (_button)
		{
		case AnalogButton::UP:
			return KeyTrigger(m_trigger[_index].m_Ltrigger.m_up, m_trigger[_index].m_LtriggerOld.m_up);
			break;
		case AnalogButton::DOWN:
			return KeyTrigger(m_trigger[_index].m_Ltrigger.m_down, m_trigger[_index].m_LtriggerOld.m_down);
			break;
		case AnalogButton::LEFT:
			return KeyTrigger(m_trigger[_index].m_Ltrigger.m_left, m_trigger[_index].m_LtriggerOld.m_left);
			break;
		case AnalogButton::RIGHT:
			return KeyTrigger(m_trigger[_index].m_Ltrigger.m_right, m_trigger[_index].m_LtriggerOld.m_right);
			break;
		default:
			break;
		}
		return false;
	}

	bool XInput::AnalogLTrigger(AnalogButton _button, int _index, D3DXVECTOR3& _out)
	{
		auto* pstate = &m_state[_index];

		_out = D3DXVECTOR3(pstate->Gamepad.sThumbLX, 0.0f, pstate->Gamepad.sThumbLY);
		D3DXVec3Normalize(&_out, &_out);

		return AnalogLTrigger(_button, _index);
	}

	bool XInput::AnalogRTrigger(AnalogButton _button, int _index)
	{
		switch (_button)
		{
		case AnalogButton::UP:
			return KeyTrigger(m_trigger[_index].m_Rtrigger.m_up, m_trigger[_index].m_RtriggerOld.m_up);
			break;
		case AnalogButton::DOWN:
			return KeyTrigger(m_trigger[_index].m_Rtrigger.m_down, m_trigger[_index].m_RtriggerOld.m_down);
			break;
		case AnalogButton::LEFT:
			return KeyTrigger(m_trigger[_index].m_Rtrigger.m_left, m_trigger[_index].m_RtriggerOld.m_left);
			break;
		case AnalogButton::RIGHT:
			return KeyTrigger(m_trigger[_index].m_Rtrigger.m_right, m_trigger[_index].m_RtriggerOld.m_right);
			break;
		default:
			break;
		}
		return false;
	}

	bool XInput::AnalogRTrigger(AnalogButton _button, int _index, D3DXVECTOR3& _out)
	{
		auto* pstate = &m_state[_index];

		_out = D3DXVECTOR3(pstate->Gamepad.sThumbRX, 0.0f, pstate->Gamepad.sThumbRY);
		D3DXVec3Normalize(&_out, &_out);

		return AnalogRTrigger(_button, _index);
	}

	bool XInput::LT(int _index)
	{
		return (m_state[_index].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? true : false;
	}

	bool XInput::RT(int _index)
	{
		return (m_state[_index].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) ? true : false;
	}

	bool XInput::Check(int _index)
	{
		return m_statedat[_index];
	}

	XinputState XInput::GetState(int _index)
	{
		return std::shared_ptr<XINPUT_STATE>(&m_state[_index], [](XINPUT_STATE* p) {p = nullptr; });
	}

	int XInput::Size()
	{
		return m_numdata;
	}

	bool XInput::KeyTrigger(bool _new, bool _old)
	{
		return (_old ^ _new) & _new;
	}

	bool XInput::KeyRelease(bool _new, bool _old)
	{
		return _old ^ _new & _old;
	}

	AnalogTrigger::AnalogTrigger()
	{
	}

	AnalogTrigger::~AnalogTrigger()
	{
	}

	void AnalogTrigger::update()
	{
		m_LtriggerOld = m_Ltrigger;
		m_RtriggerOld = m_Rtrigger;
	}

	void AnalogTrigger::ifset(bool _input, bool& _Out)
	{
		_Out = ((_input == true) ? true : false);
	}

	bool AnalogTrigger::ifbool(float _in1, float _in2)
	{
		return (_in1 < _in2) ? true : false;
	}
}
_MSLIB_END