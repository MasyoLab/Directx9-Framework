//==========================================================================
// 描画テクニック [DrawTechnique.h]
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
	// Content : 描画テクニック
	//
	//==========================================================================
	class DrawTechnique
	{
	public:
		DrawTechnique();
		~DrawTechnique();

		/**
		@brief 加算合成の設定
		*/
		void SetAdditiveSynthesis(bool _flag);

		/**
		@brief 加算合成の判定
		*/
		bool GetAdditiveSynthesis();
	protected:
		/**
		@brief 半透明処理
		@param pDevice [in] デバイス
		*/
		void TechniqueAdd(LPDIRECT3DDEVICE9 device);

		/**
		@brief アルファテスト
		@param pDevice [in] デバイス
		@param Power [in] パワー
		*/
		void TechniqueAlpharefStart(LPDIRECT3DDEVICE9 device, int Power);

		/**
		@brief アルファテスト_終わり
		@param pDevice [in] デバイス
		*/
		void TechniqueAlpharefEnd(LPDIRECT3DDEVICE9 device);

		/**
		@brief 加算合成
		@param pDevice [in] デバイス
		*/
		void TechniqueSub(LPDIRECT3DDEVICE9 device);

		/**
		@brief Zバッファを描画するか否か
		@param pDevice [in] デバイス
		*/
		void TechniqueZwriteenableStart(LPDIRECT3DDEVICE9 device);

		/**
		@brief Zバッファを描画するか否か_終わり
		@param pDevice [in] デバイス
		*/
		void TechniqueZwriteenableEnd(LPDIRECT3DDEVICE9 device);
	private:
		bool m_sub_flag;
	};
}

_MSLIB_END