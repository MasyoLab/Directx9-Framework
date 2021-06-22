//==========================================================================
// 球体オブジェクト [SphereObject.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "Texture.h"
#include "Sphere.h"
#include "InOutFunction.h"

_MSLIB_BEGIN

namespace object
{
	//==========================================================================
	//
	// class : SphereObject
	// Content : 球体オブジェクト
	//
	//==========================================================================
	class SphereObject :
		public object::GameObject,
		public transform::Transform,
		public renderer::Renderer,
		public object::MaterialLighting,
		public sphere::SetSphere,
		public texture::SetTexture,
		public in_out_function::InOutFunction
	{
	public:
		SphereObject();
		/**
		@param _bInOutFunctionFlag [in] 読み取り/書き込みを許可するフラグ
		*/
		SphereObject(bool _bInOutFunctionFlag);
		virtual ~SphereObject();
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
		@brief GUIに表示する機能
		*/
		virtual void GUISystem() override;

		/**
		@brief 読み取り機能
		*/
		virtual void InputDataFunction(std::ifstream& _ifstream) override;

		/**
		@brief 書き込み機能
		*/
		virtual void OutputDataFunction(std::ofstream& _ofstream) override;
	};

	using SphereObjectReference = reference::IReference<SphereObject>;
}

_MSLIB_END