//==========================================================================
// ビルボードオブジェクト [BillboardObject.h]
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
	// Content : ビルボードオブジェクト
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
		@param bInOutFunctionFlag [in] 読み取り/書き込みを許可するフラグ
		*/
		BillboardObject(bool bInOutFunctionFlag);
		~BillboardObject();
	protected:
		/**
		@brief 更新
		*/
		virtual void Update() override;

		/**
		@brief 姿勢行列の更新
		*/
		virtual void UpdateMatrix() override;

		/**
		@brief 描画
		@param device [in] デバイス
		*/
		virtual void Draw(LPDIRECT3DDEVICE9 device) override;

		/**
		@brief GUIを表示する機能
		*/
		virtual void GUISystem() override;

		/**
		@brief 読み取り機能
		*/
		virtual void InputDataFunction(std::ifstream& ifs) override;

		/**
		@brief 書き込み機能
		*/
		virtual void OutputDataFunction(std::ofstream& ofs) override;
	};

	using BillboardObjectReference = reference::IReference<BillboardObject>;
}

_MSLIB_END