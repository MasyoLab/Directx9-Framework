//==========================================================================
// Initializer [Initializer.cpp]
// author : MasyoLab
//==========================================================================
#include "Initializer.h"

_MSLIB_BEGIN

namespace initializer
{
	std::list<Initializer*> Initializer::m_initializers; // ‰Šú‰»ƒŠƒXƒg
	bool Initializer::m_init_all_lock = false;

	Initializer::Initializer()
	{
		m_initializers.push_back(this);
	}

	Initializer::~Initializer()
	{
		auto itr = std::find(m_initializers.begin(), m_initializers.end(), this);
		if (itr != m_initializers.end())
			m_initializers.erase(itr);
	}

	void Initializer::InitAll()
	{
		if (m_init_all_lock)
			return;
		for (auto& itr : m_initializers)
			itr->Init();
		m_initializers.clear();
	}

	void Initializer::InitOne()
	{
		if ((int)m_initializers.size() == 0)
			return;

		auto itr = m_initializers.begin();
		(*itr)->Init();
		m_initializers.erase(itr);
	}

	int Initializer::GetInitAllSize()
	{
		return m_initializers.size();
	}

	void Initializer::InitAllLock()
	{
		m_init_all_lock = true;
	}

	void Initializer::InitAllUnLock()
	{
		m_init_all_lock = false;
	}

	void Initializer::Init()
	{
	}
}

_MSLIB_END