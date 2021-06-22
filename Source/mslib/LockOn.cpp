//==========================================================================
// í«è]ã@î\ [LockOn.cpp]
// author : MasyoLab
//==========================================================================
#include "LockOn.h"

_MSLIB_BEGIN

namespace controller
{
	LockOn::LockOn() :
		Component("LockOn")
	{
	}

	LockOn::~LockOn()
	{
	}

	void LockOn::Init()
	{
		m_transform = GetComponentParent<transform::Transform>();
	}

	void LockOn::Controller(transform::TransformReference _transform, float _power)
	{
		if (m_transform != nullptr)
			m_transform->AddRotationX(m_transform->ToSee(_transform->GetWorldMatrix()), _power);
	}

	void LockOn::Controller(transform::TransformReference _transform)
	{
		if (m_transform == nullptr)
			return;

		auto angle = m_transform->ToSee(_transform->GetWorldMatrix());

		m_transform->GetLook().eye = -angle;
		m_transform->GetVector().front = angle;
		m_transform->GetVector().Normalize();
		m_transform->SetUpdateKey(true);
	}
}

_MSLIB_END