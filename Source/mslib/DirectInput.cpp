//==========================================================================
// �_�C���N�C���v�b�g [DirectInput.cpp]
// author : MasyoLab
//==========================================================================
#include "DirectInput.h"

_MSLIB_BEGIN

namespace direct_input
{
	std::list<DirectInput*> DirectInput::m_direct_input; // �f�o�C�X�̊i�[

	DirectInput::DirectInput() : Component("DirectInput"), m_input(nullptr), m_device(nullptr)
	{
		m_direct_input.emplace_back(this);
	}

	DirectInput::~DirectInput()
	{
		Release();
		auto itr = std::find(m_direct_input.begin(), m_direct_input.end(), this);
		if (itr != m_direct_input.end())
			m_direct_input.erase(itr);
	}

	void DirectInput::UpdateAll()
	{
		for (auto& itr : m_direct_input)
			itr->Update();
	}

	std::list<DirectInput*>& DirectInput::GetInputList()
	{
		return m_direct_input;
	}

	void DirectInput::Release()
	{
		DestroyComponent();

		// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
		if (m_device != nullptr)
		{
			m_device->Unacquire();
			m_device->Release();
		}

		// DirectInput�I�u�W�F�N�g�̊J��
		if (m_input != nullptr)
			m_input->Release();
		m_input = nullptr;
		m_device = nullptr;
	}
}
_MSLIB_END