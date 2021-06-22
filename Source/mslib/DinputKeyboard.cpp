//==========================================================================
// �L�[�{�[�h���͏��� [DinputKeyboard.cpp]
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
		// DirectInput�I�u�W�F�N�g�̍쐬
		if (FAILED(DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)& m_input, nullptr)))
		{
			MessageBox(_hWnd, "DirectInput�I�u�W�F�N�g�����܂���ł���", "�x��", MB_ICONWARNING);
			return true;
		}

		// �f�o�C�X�̍쐬
		if (FAILED(m_input->CreateDevice(GUID_SysKeyboard, &m_device, nullptr)))
		{
			MessageBox(_hWnd, "�L�[�{�[�h������܂���ł���", "�x��", MB_ICONWARNING);
			return true;
		}

		if (m_device == nullptr)
			return false;

		// �f�[�^�t�H�[�}�b�g��ݒ�
		if (FAILED(m_device->SetDataFormat(&c_dfDIKeyboard)))
		{
			MessageBox(_hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x��", MB_ICONWARNING);
			return true;
		}

		// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
		if (FAILED(m_device->SetCooperativeLevel(_hWnd, (DISCL_FOREGROUND/*DISCL_BACKGROUND*/ | DISCL_NONEXCLUSIVE))))
		{
			MessageBox(_hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x��", MB_ICONWARNING);
			return true;
		}

		// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
		m_device->Acquire();

		return false;
	}

	void Keyboard::Update()
	{
		if (m_device == nullptr)
			return;

		BYTE state[Button::size()];

		// �A�N�Z�X�������݂��Ȃ��ꍇ�擾
		if (!SUCCEEDED(m_device->GetDeviceState(sizeof(state), state)))
		{
			m_device->Acquire();
			return;
		}

		// aKeyState[m_KeyMax]&0x80
		for (int i = 0; i < Button::size(); i++)
		{
			// �L�[�g���K�[�E�����[�X���𐶐�
			m_state_trigger[i] = (m_state[i] ^ state[i]) & state[i];
			m_state_release[i] = (m_state[i] ^ state[i]) & m_state[i];

			// �L�[���s�[�g���𐶐�
			if (state[i])
			{
				if (m_state_repeat_cnt[i] < 20)
				{
					m_state_repeat_cnt[i]++;
					if (m_state_repeat_cnt[i] == 1 || m_state_repeat_cnt[i] >= 20)
					{// �L�[�������n�߂��ŏ��̃t���[���A�܂��͈�莞�Ԍo�߂�����L�[���s�[�g���ON
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

			// �L�[�v���X����ۑ�
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