//==========================================================================
// Effekseerオブジェクト [EffekseerObject.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "EffekseerDX.h"
#include "InOutFunction.h"

_MSLIB_BEGIN

namespace object
{
	//==========================================================================
	//
	// class : EffekseerObject
	// Content : Effekseerオブジェクト
	//
	//==========================================================================
	class EffekseerObject :
		public object::GameObject,
		public transform::Transform,
		public effekseer_dx::SetEffekseer,
		public in_out_function::InOutFunction
	{
	public:
		EffekseerObject();
		/**
		@param _bInOutFunctionFlag [in] 読み取り/書き込みを許可するフラグ
		*/
		EffekseerObject(bool _bInOutFunctionFlag);
		virtual ~EffekseerObject();
		/**
		@brief 再生
		*/
		void Play();

		/**
		@brief 停止
		*/
		void Stop();

		/**
		@brief ターゲットの登録
		*/
		void SetTarget(transform::TransformReference obj);
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
	protected:
		transform::TransformReference m_transform;
		effekseer_dx::Handle m_handle;
	};

	using EffekseerObjectReference = reference::IReference<EffekseerObject>;
}

_MSLIB_END