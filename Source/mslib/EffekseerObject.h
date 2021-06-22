//==========================================================================
// Effekseer�I�u�W�F�N�g [EffekseerObject.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "EffekseerDX.h"
#include "InOutFunction.h"

_MSLIB_BEGIN

namespace object
{
	//==========================================================================
	//
	// class : EffekseerObject
	// Content : Effekseer�I�u�W�F�N�g
	//
	//==========================================================================
	class EffekseerObject :
		public object::GameObject,
		public transform::Transform,
		public effekseer_dx::SetEffekseer,
		public in_out_function::InOutFunction
	{
	public:
		EffekseerObject();
		/**
		@param _bInOutFunctionFlag [in] �ǂݎ��/�������݂�������t���O
		*/
		EffekseerObject(bool _bInOutFunctionFlag);
		virtual ~EffekseerObject();
		/**
		@brief �Đ�
		*/
		void Play();

		/**
		@brief ��~
		*/
		void Stop();

		/**
		@brief �^�[�Q�b�g�̓o�^
		*/
		void SetTarget(transform::TransformReference obj);
	protected:
		/**
		@brief �X�V
		*/
		virtual void Update() override;

		/**
		@brief �p���s��̍X�V
		*/
		virtual void UpdateMatrix() override;

		/**
		@brief GUI�ɕ\������@�\
		*/
		virtual void GUISystem() override;

		/**
		@brief �ǂݎ��@�\
		*/
		virtual void InputDataFunction(std::ifstream& _ifstream) override;

		/**
		@brief �������݋@�\
		*/
		virtual void OutputDataFunction(std::ofstream& _ofstream) override;
	protected:
		transform::TransformReference m_transform;
		effekseer_dx::Handle m_handle;
	};

	using EffekseerObjectReference = reference::IReference<EffekseerObject>;
}

_MSLIB_END