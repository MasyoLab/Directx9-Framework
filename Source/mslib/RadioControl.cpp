//==========================================================================
// ƒ‰ƒWƒRƒ“ [RadioControl.cpp]
// author : MasyoLab
//==========================================================================
#include "RadioControl.h"

_MSLIB_BEGIN

namespace controller
{
	RadioControl::RadioControl() :
		Component("RadioControl")
	{
	}

	RadioControl::~RadioControl()
	{
	}

	void RadioControl::Init()
	{
		m_transform = GetComponentParent<transform::Transform>();
	}

	void RadioControl::Controller(const D3DXVECTOR3& vecRight, float speed)
	{
		if (m_transform == nullptr)
			return;

		D3DXVECTOR3 vecCross;
		
		D3DXVec3Cross(&vecCross, &m_transform->GetVector().front, &vecRight);
		m_transform->AddRotation(D3DXVECTOR3((vecCross.y < 0.0f ? -0.01f : 0.01f) * speed, 0, 0));
	}
}

_MSLIB_END