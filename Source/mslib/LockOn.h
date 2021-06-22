//==========================================================================
// 追従機能 [LockOn.h]
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
	// class : LockOn
	// Content : 追従機能
	//
	//==========================================================================
	class LockOn final :
		public component::Component,
		public initializer::Initializer
	{
	private:
		LockOn(const LockOn&) = delete;
		LockOn(LockOn&&) = delete;
		LockOn& operator=(const LockOn&) = delete;
		LockOn& operator=(LockOn&&) = delete;
	public:
		LockOn();
		~LockOn();
	private:
		void Init() override;
	public:
		/**
		@brief 対象の方向に向かせる(ベクトル計算を行い、処理を行います)
		@param _transform [in] ターゲット
		@param _power 向かせる力
		*/
		void Controller(transform::TransformReference _transform, float _power);

		/**
		@brief 対象の方向に向かせる(直接ベクトルを操作します)
		@param _transform [in] ターゲット
		*/
		void Controller(transform::TransformReference _transform);
	private:
		transform::TransformReference m_transform;
	};

	using LockOnReference = reference::IReference<LockOn>;
}

_MSLIB_END