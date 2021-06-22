//==========================================================================
// カメラをマウスで操作する機能 [CameraControlMouse.cpp]
// author : MasyoLab
//==========================================================================
#include "CameraControlMouse.h"

_MSLIB_BEGIN

namespace camera
{
	CameraControlMouse::CameraControlMouse()
	{
		SetComponentName("CameraControlMouse");
	}

	CameraControlMouse::~CameraControlMouse()
	{
	}

	void CameraControlMouse::Init()
	{
		m_camera = GetComponentParent<Camera>();
	}

	void CameraControlMouse::Update()
	{
		if (!m_camera.check())
			return;

		// ホイールを押したときの処理
		if (GetDInputMouse()->Press(MouseButton::Wheel))
			m_camera->AddPosition(-(float)GetDInputMouse()->GetSpeed().x * 0.01f, (float)GetDInputMouse()->GetSpeed().y * 0.01f, 0);

		// 右クリックの時の処理
		if (GetDInputMouse()->Press(MouseButton::Right))
		{
			m_camera->AddViewRotation((float)GetDInputMouse()->GetSpeed().x * 0.0025f, (float)GetDInputMouse()->GetSpeed().y * 0.0025f, 0);
			m_camera->AddCameraRotation((float)GetDInputMouse()->GetSpeed().x * 0.0025f, (float)GetDInputMouse()->GetSpeed().y * 0.0025f, 0);
		}

		// マウスの移動速度(Z)を加算
		m_camera->AddPosition(0, 0, (float)GetDInputMouse()->GetSpeed().z * 0.0025f);
	}
}

_MSLIB_END