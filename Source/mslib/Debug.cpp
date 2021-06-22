//==========================================================================
// Debug [Debug.h]
// author : MasyoLab
//==========================================================================
#include "Debug.h"

_MSLIB_BEGIN

namespace debug
{
#if defined(_MSLIB_DEBUG)
	std::list<Debug*> Debug::m_debugs; // XV‘ÎÛ
#endif

	Debug::Debug() : Component("Debug")
	{
#if defined(_MSLIB_DEBUG)
		m_debugs.push_back(this);
		SetActivity(false);
#endif
	}

	Debug::~Debug()
	{
#if defined(_MSLIB_DEBUG)
		auto itr = std::find(m_debugs.begin(), m_debugs.end(), this);
		if (itr != m_debugs.end())
			m_debugs.erase(itr);
#endif
	}

	void Debug::DrawAll(LPDIRECT3DDEVICE9 device)
	{
#if defined(_MSLIB_DEBUG)
		device->SetRenderState(D3DRS_LIGHTING, D3DZB_FALSE);
		for (auto& itr : m_debugs)
			if (itr->GetActivity())
				itr->Draw(device);
		device->SetRenderState(D3DRS_LIGHTING, D3DZB_TRUE);
#else
		device;
#endif
	}

	void Debug::SetAllActivity(bool _flag)
	{
#if defined(_MSLIB_DEBUG)
		for (auto& itr : m_debugs)
			itr->SetActivity(_flag);
#else
		_flag;
#endif
	}

	void Debug::Init()
	{
	}

	void Debug::Draw(LPDIRECT3DDEVICE9 device)
	{
		device;
	}

	void Debug::GUISystem()
	{
		GUIDebug();
	}

	void Debug::GUIDebug()
	{
#if defined(_MSLIB_DEBUG)
		bool bactivity = GetActivity();

		if (imgui::_Checkbox("Activity", &bactivity))
			SetActivity(bactivity);
#endif	
	}
}

_MSLIB_END