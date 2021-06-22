//==========================================================================
// 画像の品質調整 [SamplerState.h]
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
	// Content : 画像の品質を調整するクラス
	//
	//==========================================================================
	class SamplerState
	{
	protected:
		SamplerState();
		~SamplerState();

		/**
		@brief 初期値
		@param pDevice [in] デバイス
		*/
		static void SamplerFitteringNONE(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief ぼや
		@param pDevice [in] デバイス
		*/
		static void SamplerFitteringLINEAR(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief グラフィカル
		@param pDevice [in] デバイス
		*/
		static void SamplerFitteringGraphical(LPDIRECT3DDEVICE9 pDevice);
	};
}

_MSLIB_END