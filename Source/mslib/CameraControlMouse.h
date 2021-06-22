//==========================================================================
// カメラをマウスで操作する機能 [CameraControlMouse.h]
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
	// Content : カメラをマウスで操作する機能
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
		@brief 初期化
		*/
		virtual void Init() override;

		/**
		@brief 更新
		*/
		virtual void Update() override;
	private:
		CameraReference m_camera;
	};

	using CameraControlMouseReference = reference::IReference<CameraControlMouse>;
}

_MSLIB_END