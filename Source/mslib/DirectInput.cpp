//==========================================================================
// ダイレクインプット [DirectInput.cpp]
// author : MasyoLab
//==========================================================================
#include "DirectInput.h"

_MSLIB_BEGIN

namespace direct_input
{
	std::list<DirectInput*> DirectInput::m_direct_input; // デバイスの格納

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

		// 入力デバイス(キーボード)の開放
		// キーボードへのアクセス権を開放(入力制御終了)
		if (m_device != nullptr)
		{
			m_device->Unacquire();
			m_device->Release();
		}

		// DirectInputオブジェクトの開放
		if (m_input != nullptr)
			m_input->Release();
		m_input = nullptr;
		m_device = nullptr;
	}
}
_MSLIB_END