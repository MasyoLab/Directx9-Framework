//==========================================================================
// �`��e�N�j�b�N [DrawTechnique.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "mslib.hpp"

_MSLIB_BEGIN

namespace draw_technique
{
	//==========================================================================
	//
	// class : DrawTechnique
	// Content : �`��e�N�j�b�N
	//
	//==========================================================================
	class DrawTechnique
	{
	public:
		DrawTechnique();
		~DrawTechnique();

		/**
		@brief ���Z�����̐ݒ�
		*/
		void SetAdditiveSynthesis(bool _flag);

		/**
		@brief ���Z�����̔���
		*/
		bool GetAdditiveSynthesis();
	protected:
		/**
		@brief ����������
		@param pDevice [in] �f�o�C�X
		*/
		void TechniqueAdd(LPDIRECT3DDEVICE9 device);

		/**
		@brief �A���t�@�e�X�g
		@param pDevice [in] �f�o�C�X
		@param Power [in] �p���[
		*/
		void TechniqueAlpharefStart(LPDIRECT3DDEVICE9 device, int Power);

		/**
		@brief �A���t�@�e�X�g_�I���
		@param pDevice [in] �f�o�C�X
		*/
		void TechniqueAlpharefEnd(LPDIRECT3DDEVICE9 device);

		/**
		@brief ���Z����
		@param pDevice [in] �f�o�C�X
		*/
		void TechniqueSub(LPDIRECT3DDEVICE9 device);

		/**
		@brief Z�o�b�t�@��`�悷�邩�ۂ�
		@param pDevice [in] �f�o�C�X
		*/
		void TechniqueZwriteenableStart(LPDIRECT3DDEVICE9 device);

		/**
		@brief Z�o�b�t�@��`�悷�邩�ۂ�_�I���
		@param pDevice [in] �f�o�C�X
		*/
		void TechniqueZwriteenableEnd(LPDIRECT3DDEVICE9 device);
	private:
		bool m_sub_flag;
	};
}

_MSLIB_END