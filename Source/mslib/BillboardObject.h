//==========================================================================
// �r���{�[�h�I�u�W�F�N�g [BillboardObject.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "Texture.h"
#include "Billboard.h"
#include "DrawTechnique.h"
#include "InOutFunction.h"

_MSLIB_BEGIN

namespace object
{
	//==========================================================================
	//
	// class : BillboardObject
	// Content : �r���{�[�h�I�u�W�F�N�g
	//
	//==========================================================================
	class BillboardObject :
		public object::GameObject,
		public transform::Transform,
		public renderer::Renderer,
		public object::MaterialLighting,
		public texture::SetTexture,
		public billboard::SetBillboard,
		public draw_technique::DrawTechnique,
		public in_out_function::InOutFunction
	{
	public:
		BillboardObject();
		/**
		@param bInOutFunctionFlag [in] �ǂݎ��/�������݂�������t���O
		*/
		BillboardObject(bool bInOutFunctionFlag);
		~BillboardObject();
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
		@brief GUI��\������@�\
		*/
		virtual void GUISystem() override;

		/**
		@brief �ǂݎ��@�\
		*/
		virtual void InputDataFunction(std::ifstream& ifs) override;

		/**
		@brief �������݋@�\
		*/
		virtual void OutputDataFunction(std::ofstream& ofs) override;
	};

	using BillboardObjectReference = reference::IReference<BillboardObject>;
}

_MSLIB_END