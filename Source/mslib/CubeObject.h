//==========================================================================
// �L���[�u�I�u�W�F�N�g [CubeObject.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "Texture.h"
#include "Cube.h"
#include "InOutFunction.h"

_MSLIB_BEGIN

namespace object
{
	//==========================================================================
	//
	// class : CubeObject
	// Content : �L���[�u�I�u�W�F�N�g
	//
	//==========================================================================
	class CubeObject :
		public object::GameObject,
		public transform::Transform,
		public renderer::Renderer,
		public object::MaterialLighting,
		public texture::SetTexture,
		public cube::SetCube,
		public in_out_function::InOutFunction
	{
	public:
		CubeObject();
		/**
		@param _bInOutFunctionFlag [in] �ǂݎ��/�������݂�������t���O
		*/
		CubeObject(bool _bInOutFunctionFlag);
		~CubeObject();
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

	using CubeObjectReference = reference::IReference<CubeObject>;
}

_MSLIB_END