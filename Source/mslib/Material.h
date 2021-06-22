//==========================================================================
// マテリアル [Material.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"

_MSLIB_BEGIN

namespace material
{
	//==========================================================================
	//
	// class : MaterialLighting
	// Content : マテリアルのライティング
	//
	//==========================================================================
	class MaterialLighting
	{
	public:
		MaterialLighting();
		~MaterialLighting();

		/**
		@brief アンビエントライト
		@param color [in] ライト設定(0.0f～1.0f)
		*/
		void SetAmbient(const D3DXCOLOR& color);

		/**
		@brief ディレクショナルライト
		@param color [in] ライト設定(0.0f～1.0f)
		*/
		void SetDiffuse(const D3DXCOLOR& color);

		/**
		@brief スペキュラー
		@param color [in] ライト設定(0.0f～1.0f)
		*/
		void SetSpecular(const D3DXCOLOR& color);

		/**
		@brief 放射性
		@param color [in] ライト設定(0.0f～1.0f)
		*/
		void SetEmissive(const D3DXCOLOR& color);

		/**
		@brief スペキュラー光のパワー値
		*/
		void SetSpecularPower(float power);

		/**
		@brief ライティングの取得
		*/
		const D3DMATERIAL9& GetMaterialLighting();
	protected:
		void GUIMaterialLighting();
		void InputDataMaterialLighting(std::ifstream& _ifstream);
		void OutputDataMaterialLighting(std::ofstream& _ofstream);
	private:
		D3DMATERIAL9 m_material9;
	};
}

_MSLIB_END