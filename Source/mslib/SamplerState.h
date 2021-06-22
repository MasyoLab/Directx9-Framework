//==========================================================================
// �摜�̕i������ [SamplerState.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"

_MSLIB_BEGIN

namespace sampler_state
{
	//==========================================================================
	//
	// class : SamplerState
	// Content : �摜�̕i���𒲐�����N���X
	//
	//==========================================================================
	class SamplerState
	{
	protected:
		SamplerState();
		~SamplerState();

		/**
		@brief �����l
		@param pDevice [in] �f�o�C�X
		*/
		static void SamplerFitteringNONE(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief �ڂ�
		@param pDevice [in] �f�o�C�X
		*/
		static void SamplerFitteringLINEAR(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief �O���t�B�J��
		@param pDevice [in] �f�o�C�X
		*/
		static void SamplerFitteringGraphical(LPDIRECT3DDEVICE9 pDevice);
	};
}

_MSLIB_END