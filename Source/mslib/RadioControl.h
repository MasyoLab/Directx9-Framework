//==========================================================================
// ラジコン [RadioControl.h]
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
	// Content: ラジコン
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
		@brief ラジコン
		@param vecRight [in] 向かせたい方向ベクトル
		@param speed [in] 向かせる速度
		*/
		void Controller(const D3DXVECTOR3& vecRight, float speed);
	private:
		transform::TransformReference m_transform;
	};

	using RadioControlReference = reference::IReference<RadioControl>;
}

_MSLIB_END