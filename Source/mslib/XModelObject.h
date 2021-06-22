//==========================================================================
// XModel�I�u�W�F�N�g [XModelObject.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "XModel.h"
#include "InOutFunction.h"

_MSLIB_BEGIN

namespace object
{
	//==========================================================================
	//
	// class : XModelObject
	// Content : XModel�I�u�W�F�N�g
	//
	//==========================================================================
	class XModelObject :
		public object::GameObject,
		public transform::Transform,
		public renderer::Renderer,
		public object::MaterialLighting,
		public xmodel::SetXModel,
		public in_out_function::InOutFunction
	{
	public:
		XModelObject();
		/**
		@param _bInOutFunctionFlag [in] �ǂݎ��/�������݂�������t���O
		*/
		XModelObject(bool _bInOutFunctionFlag);
		~XModelObject();
	protected:
		/**d
		@brief �X�V
		*/
		virtual void Update() override;

		/**
		@brief �p���s��̍X�V
		*/
		virtual void UpdateMatrix() override;

		/**
		@brief �`��
		@param device [in] �f�o�C�X
		*/
		virtual void Draw(LPDIRECT3DDEVICE9 device) override;

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
	};

	using XModelObjectReference = reference::IReference<XModelObject>;
}

_MSLIB_END