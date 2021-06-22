//==========================================================================
// �����_�[�X�e�[�g [RenderState.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"

_MSLIB_BEGIN

namespace render_state
{
	//==========================================================================
	//
	// class : RenderState
	// Content : �����_�[�X�e�[�g
	//
	//==========================================================================
	class RenderState
	{
	protected:
		RenderState();
		~RenderState();

		/**
		@brief ���Z����
		@param pDevice [in] �f�o�C�X
		*/
		static void SetRenderREVSUBTRACT(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief ����������
		@param pDevice [in] �f�o�C�X
		*/
		static void SetRenderADD(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief �A���t�@�e�X�g
		@param pDevice [in] �f�o�C�X
		@param Power [in] �p���[
		*/
		static void SetRenderALPHAREF_START(LPDIRECT3DDEVICE9 pDevice, int Power);

		/**
		@brief �A���t�@�e�X�g_�I���
		@param pDevice [in] �f�o�C�X
		*/
		static void SetRenderALPHAREF_END(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief ���Z����
		@param pDevice [in] �f�o�C�X
		*/
		static void SetRenderSUB(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief �`�掞��Z�o�b�t�@���Q�Ƃ��邩�ۂ�
		@param pDevice [in] �f�o�C�X
		*/
		static void SetRenderZENABLE_START(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief �`�掞��Z�o�b�t�@���Q�Ƃ��邩�ۂ�_�I���
		@param pDevice [in] �f�o�C�X
		*/
		static void SetRenderZENABLE_END(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief Z�o�b�t�@��`�悷�邩�ۂ�
		@param pDevice [in] �f�o�C�X
		*/
		static void SetRenderZWRITEENABLE_START(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief Z�o�b�t�@��`�悷�邩�ۂ�_�I���
		@param pDevice [in] �f�o�C�X
		*/
		static void SetRenderZWRITEENABLE_END(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief ���C���t���[���ŕ`�悵�܂�
		@param pDevice [in] �f�o�C�X
		*/
		static void SetRenderWIREFRAME(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief �h��Ԃ��܂�
		@param pDevice [in] �f�o�C�X
		*/
		static void SetRenderSOLID(LPDIRECT3DDEVICE9 pDevice);
	};
}

_MSLIB_END