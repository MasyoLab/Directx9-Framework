//==========================================================================
// レンダーステート [RenderState.h]
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
	// Content : レンダーステート
	//
	//==========================================================================
	class RenderState
	{
	protected:
		RenderState();
		~RenderState();

		/**
		@brief 減算処理
		@param pDevice [in] デバイス
		*/
		static void SetRenderREVSUBTRACT(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief 半透明処理
		@param pDevice [in] デバイス
		*/
		static void SetRenderADD(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief アルファテスト
		@param pDevice [in] デバイス
		@param Power [in] パワー
		*/
		static void SetRenderALPHAREF_START(LPDIRECT3DDEVICE9 pDevice, int Power);

		/**
		@brief アルファテスト_終わり
		@param pDevice [in] デバイス
		*/
		static void SetRenderALPHAREF_END(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief 加算合成
		@param pDevice [in] デバイス
		*/
		static void SetRenderSUB(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief 描画時にZバッファを参照するか否か
		@param pDevice [in] デバイス
		*/
		static void SetRenderZENABLE_START(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief 描画時にZバッファを参照するか否か_終わり
		@param pDevice [in] デバイス
		*/
		static void SetRenderZENABLE_END(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief Zバッファを描画するか否か
		@param pDevice [in] デバイス
		*/
		static void SetRenderZWRITEENABLE_START(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief Zバッファを描画するか否か_終わり
		@param pDevice [in] デバイス
		*/
		static void SetRenderZWRITEENABLE_END(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief ワイヤフレームで描画します
		@param pDevice [in] デバイス
		*/
		static void SetRenderWIREFRAME(LPDIRECT3DDEVICE9 pDevice);

		/**
		@brief 塗りつぶします
		@param pDevice [in] デバイス
		*/
		static void SetRenderSOLID(LPDIRECT3DDEVICE9 pDevice);
	};
}

_MSLIB_END