//==========================================================================
// エフェクト [Effect.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Reference.h"
#include "Loader.h"

_MSLIB_BEGIN

namespace effect
{
	//==========================================================================
	//
	// class : EffectData
	// Content : エフェクトデータ
	//
	//==========================================================================
	class EffectData :
		public resource_loader::Resource
	{
	private:
		EffectData(const EffectData&) = delete;
		EffectData(EffectData&&) = delete;
		EffectData& operator=(const EffectData&) = delete;
		EffectData& operator=(EffectData&&) = delete;
	public:
		EffectData();
		~EffectData();
		int64_t GetCreateID();
		const LPD3DXEFFECT GetEffect() const;
	protected:
		int64_t m_createID; // 生成ID
		LPD3DXEFFECT m_effect; // エフェクト
	};

	using EffectReference = resource_loader::ResourceReference<EffectData>;

	//==========================================================================
	//
	// class : EffectLoader
	// Content : エフェクト読み込み破棄クラス
	//
	//==========================================================================
	class EffectLoader :
		public resource_loader::Loader
	{
		class EffectDataInput :
			public EffectData
		{
		public:
			EffectDataInput();
			EffectDataInput(
				int64_t _id,
				LPD3DXEFFECT _effect,
				const std::string& _tag,
				resource_loader::LoaderReference _loader
			);
			~EffectDataInput();
		};
	private:
		// コピー禁止 (C++11)
		EffectLoader(const EffectLoader&) = delete;
		EffectLoader& operator=(const EffectLoader&) = delete;
		EffectLoader& operator=(EffectLoader&&) = delete;
	public:
		EffectLoader();
		EffectLoader(LPDIRECT3DDEVICE9 _device);
		~EffectLoader();

		/**
		@brief エフェクトを読み込む。
		@param _path [in] 読み込みパス
		@return エフェクトのポインタ
		*/
		EffectReference Load(const std::string& _path);
	private:
		LPDIRECT3DDEVICE9 m_device; // デバイス
		int64_t m_createIDCount; // カウンタ
	};

	using EffectLoaderReference = reference::IReference<EffectLoader>;

	//==========================================================================
	//
	// class : SetEffect
	// Content : エフェクト登録
	//
	//==========================================================================
	class SetEffect
	{
	public:
		SetEffect();
		~SetEffect();

		/**
		@brief エフェクトデータの登録
		@param _effect [in] データ
		*/
		void SetEffectData(const EffectReference& _effect);

		/**
		@brief エフェクトデータの取得
		@return エフェクトのポインタ
		*/
		EffectReference GetEffectData();
	protected:
		EffectReference m_effect_data;
	};
}

_MSLIB_END