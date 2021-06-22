//==========================================================================
// Activity [Activity.cpp]
// author : MasyoLab
//==========================================================================
#include "Activity.h"
#include <algorithm>

_MSLIB_BEGIN

namespace activity
{
	Activity::Activity() :
		m_activity(false)
	{}

	Activity::~Activity(){}

	bool Activity::GetActivity() const
	{
		return m_activity;
	}

	void Activity::SetActivity(bool flag)
	{
		m_activity = flag;
	}
}

_MSLIB_END