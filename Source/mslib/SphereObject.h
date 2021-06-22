//==========================================================================
// ���̃I�u�W�F�N�g [SphereObject.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "Texture.h"
#include "Sphere.h"
#include "InOutFunction.h"

_MSLIB_BEGIN

namespace object
{
	//==========================================================================
	//
	// class : SphereObject
	// Content : ���̃I�u�W�F�N�g
	//
	//==========================================================================
	class SphereObject :
		public object::GameObject,
		public transform::Transform,
		public renderer::Renderer,
		public object::MaterialLighting,
		public sphere::SetSphere,
		public texture::SetTexture,
		public in_out_function::InOutFunction
	{
	public:
		SphereObject();
		/**
		@param _bInOutFunctionFlag [in] �ǂݎ��/�������݂�������t���O
		*/
		SphereObject(bool _bInOutFunctionFlag);
		virtual ~SphereObject();
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

	using SphereObjectReference = reference::IReference<SphereObject>;
}

_MSLIB_END