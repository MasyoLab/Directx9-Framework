//==========================================================================
// ���b�V���I�u�W�F�N�g [MeshObject.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include "InOutFunction.h"

_MSLIB_BEGIN

namespace object
{
	//==========================================================================
	//
	// class : MeshObject
	// Content : ���b�V���I�u�W�F�N�g
	//
	//==========================================================================
	class MeshObject :
		public object::GameObject,
		public transform::Transform,
		public renderer::Renderer,
		public object::MaterialLighting,
		public texture::SetTexture,
		public mesh::SetMesh,
		public in_out_function::InOutFunction
	{
	public:
		MeshObject();
		/**
		@param _bInOutFunctionFlag [in] �ǂݎ��/�������݂�������t���O
		*/
		MeshObject(bool _bInOutFunctionFlag);
		~MeshObject();
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

	using MeshObjectReference = reference::IReference<MeshObject>;
}

_MSLIB_END