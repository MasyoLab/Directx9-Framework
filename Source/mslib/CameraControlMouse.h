//==========================================================================
// �J�������}�E�X�ő��삷��@�\ [CameraControlMouse.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "mslib.hpp"
#include "Camera.h"
#include "GameObject.h"

_MSLIB_BEGIN

namespace camera
{
	//==========================================================================
	//
	// class : CameraControlMouse
	// Content : �J�������}�E�X�ő��삷��@�\
	//
	//==========================================================================
	class CameraControlMouse :
		public object::GameObject
	{
	private:
		CameraControlMouse(const CameraControlMouse&) = delete;
		CameraControlMouse(CameraControlMouse&&) = delete;
		CameraControlMouse& operator=(const CameraControlMouse&) = delete;
		CameraControlMouse& operator=(CameraControlMouse&&) = delete;
	public:
		CameraControlMouse();
		~CameraControlMouse();

		/**
		@brief ������
		*/
		virtual void Init() override;

		/**
		@brief �X�V
		*/
		virtual void Update() override;
	private:
		CameraReference m_camera;
	};

	using CameraControlMouseReference = reference::IReference<CameraControlMouse>;
}

_MSLIB_END