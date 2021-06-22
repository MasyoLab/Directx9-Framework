//==========================================================================
// ���W�R�� [RadioControl.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "mslib.hpp"
#include "Component.h"
#include "Transform.h"
#include "Initializer.h"

_MSLIB_BEGIN

namespace controller
{
	//==========================================================================
	//
	// class : RadioControl
	// Content: ���W�R��
	//
	//==========================================================================
	class RadioControl final :
		public component::Component,
		public initializer::Initializer
	{
	private:
		RadioControl(const RadioControl&) = delete;
		RadioControl(RadioControl&&) = delete;
		RadioControl& operator=(const RadioControl&) = delete;
		RadioControl& operator=(RadioControl&&) = delete;
	public:
		RadioControl();
		~RadioControl();
	private:
		void Init() override;
	public:
		/**
		@brief ���W�R��
		@param vecRight [in] ���������������x�N�g��
		@param speed [in] �������鑬�x
		*/
		void Controller(const D3DXVECTOR3& vecRight, float speed);
	private:
		transform::TransformReference m_transform;
	};

	using RadioControlReference = reference::IReference<RadioControl>;
}

_MSLIB_END