//==========================================================================
// �Ǐ]�@�\ [LockOn.h]
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
	// Content : �Ǐ]�@�\
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
		@brief �Ώۂ̕����Ɍ�������(�x�N�g���v�Z���s���A�������s���܂�)
		@param _transform [in] �^�[�Q�b�g
		@param _power ���������
		*/
		void Controller(transform::TransformReference _transform, float _power);

		/**
		@brief �Ώۂ̕����Ɍ�������(���ڃx�N�g���𑀍삵�܂�)
		@param _transform [in] �^�[�Q�b�g
		*/
		void Controller(transform::TransformReference _transform);
	private:
		transform::TransformReference m_transform;
	};

	using LockOnReference = reference::IReference<LockOn>;
}

_MSLIB_END