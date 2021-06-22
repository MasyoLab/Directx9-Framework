//==========================================================================
// ライト [Light.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "GameObject.h"
#include "Transform.h"
#include "InOutFunction.h"

_MSLIB_BEGIN

namespace object
{
	//==========================================================================
	//
	// class : LightData
	// Content : ライトのデータ
	//
	//==========================================================================
	class LightData :
		public D3DLIGHT9
	{
	public:
		LightData();
		~LightData();
	};

	//==========================================================================
	//
	// class : Light
	// Content : ライト 
	//
	//==========================================================================
	class Light :
		public GameObject,
		public transform::Transform,
		public in_out_function::InOutFunction
	{
	private:
		Light(const Light&) = delete;
		Light(Light&&) = delete;
		Light& operator=(const Light&) = delete;
		Light& operator=(Light&&) = delete;
	public:
		Light(LPDIRECT3DDEVICE9 pDevice);
		/**
		@param _bInOutFunctionFlag [in] 読み取り/書き込みを許可するフラグ
		*/
		Light(LPDIRECT3DDEVICE9 pDevice, bool _bInOutFunctionFlag);
		virtual ~Light();

		/**
		@brief 初期化
		*/
		void Init();

		/**
		@brief 初期化
		@param aVecDir [in] 光のベクトルを入れるところ
		*/
		void Init(const D3DXVECTOR3& aVecDir);
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
	private:
		void CreateLabel();
	private:
		LPDIRECT3DDEVICE9 m_device;
		LightData m_light;
		int m_label;
		static std::list<int> m_lights;
	};

	using LightObjectReference = reference::IReference<Light>;
}

_MSLIB_END