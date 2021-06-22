//==========================================================================
// Effekseer [EffekseerDX.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <Effekseer/Effekseer.h>
#include <Effekseer/EffekseerRendererDX9.h>
#include <Effekseer/EffekseerSoundXAudio2.h>

#include "mslib.hpp"
#include "Component.h"
#include "Reference.h"
#include "Loader.h"

#if _DEBUG
#pragma comment(lib, "VS2017/Debug/Effekseer.lib" )
#pragma comment(lib, "VS2017/Debug/EffekseerRendererDX9.lib" )
#pragma comment(lib, "VS2017/Debug/EffekseerSoundXAudio2.lib" )
#else
#pragma comment(lib, "VS2017/Release/Effekseer.lib" )
#pragma comment(lib, "VS2017/Release/EffekseerRendererDX9.lib" )
#pragma comment(lib, "VS2017/Release/EffekseerSoundXAudio2.lib" )
#endif

_MSLIB_BEGIN

namespace effekseer_dx
{
	constexpr const int stop_handle = -1; // 停止ハンドル

	using Effekseer::Handle;

	//==========================================================================
	//
	// class : Renderer
	// Content : 描画機能
	//
	//==========================================================================
	class Renderer
	{
	private:
		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) = delete;
	public:
		Renderer();
		virtual ~Renderer();
		static void UpdateAll();
		static void DrawAll();
	protected:
		void SetUpManager(LPDIRECT3DDEVICE9 _device, int32_t _squareMaxCount, int _instance_max, bool _autoFlip);
		void SetUpSound(IXAudio2* _xaudio2, int32_t _num1chVoices, int32_t _num2chVoices);
	private:
		static std::list<Renderer*> m_renderers;
	protected:
		std::shared_ptr<Effekseer::Manager> m_manager; // マネージャー
		std::shared_ptr<EffekseerRendererDX9::Renderer> m_renderer; // レンダラー
		std::shared_ptr<EffekseerSound::Sound> m_sound; // サウンド
	};

	//==========================================================================
	//
	// class : EffekseerData
	// Content : エフェクシアのデータ
	//
	//==========================================================================
	class EffekseerData :
		public resource_loader::Resource
	{
	private:
		EffekseerData(const EffekseerData&) = delete;
		EffekseerData(EffekseerData&&) = delete;
		EffekseerData& operator=(const EffekseerData&) = delete;
		EffekseerData& operator=(EffekseerData&&) = delete;
	public:
		EffekseerData();
		~EffekseerData();
		reference::IReference<Effekseer::Manager> GetManager();
		reference::IReference<EffekseerRendererDX9::Renderer> GetRenderer();
		reference::IReference<EffekseerSound::Sound> GetSound();
		reference::IReference<Effekseer::Effect> GetEffect();
		void SetHandle(Effekseer::Handle _handle);
		Effekseer::Handle Play(float x, float y, float z);
		Effekseer::Handle Play(D3DXVECTOR3 pos);
	protected:
		reference::IReference<Effekseer::Manager> m_manager; // マネージャー
		reference::IReference<EffekseerRendererDX9::Renderer> m_renderer; // レンダラー
		reference::IReference<EffekseerSound::Sound> m_sound; // サウンド
		std::shared_ptr<Effekseer::Effect> m_effect; // エフェクト
		std::list<Effekseer::Handle> m_handle_list; // ハンドルコンテナ
	};

	using EffekseerReference = resource_loader::ResourceReference<EffekseerData>;

	//==========================================================================
	//
	// class : EffekseerLoader
	// Content : Effekseer読み込み機能
	//
	//==========================================================================
	class EffekseerLoader :
		public resource_loader::Loader,
		public resource_loader::Resource,
		public Renderer
	{
		class EffekseerDataInput :
			public EffekseerData
		{
		public:
			EffekseerDataInput();
			EffekseerDataInput(
				const std::string& _tag,
				reference::IReference<Effekseer::Manager> _manager,
				reference::IReference<EffekseerRendererDX9::Renderer> _renderer,
				reference::IReference<EffekseerSound::Sound> _sound,
				std::shared_ptr<Effekseer::Effect> _effect,
				resource_loader::LoaderReference _loader
			);
			~EffekseerDataInput();
		};
	private:
		EffekseerLoader(const EffekseerLoader&) = delete;
		EffekseerLoader(EffekseerLoader&&) = delete;
		EffekseerLoader& operator=(const EffekseerLoader&) = delete;
		EffekseerLoader& operator=(EffekseerLoader&&) = delete;
	public:
		EffekseerLoader();
		EffekseerLoader(LPDIRECT3DDEVICE9 device);
		~EffekseerLoader();

		/**
		@brief マネージャーを生成する。
		@param	squareMaxCount [in]	最大描画スプライト数
		@param	_instance_max [in] 最大インスタンス数
		@param	_autoFlip [in] 自動でスレッド間のデータを入れ替えるかどうか、を指定する。trueの場合、Update時に入れ替わる。
		*/
		void InitManager(int32_t _squareMaxCount, int _instance_max, bool _autoFlip = true);

		/**
		@brief	インスタンスを生成する。
		@param	_xaudio2 [in]	XAudio2のデバイス
		@param	_num1chVoices [in] モノラルボイス数
		@param	_num2chVoices [in] ステレオボイス数
		*/
		void InitSound(IXAudio2* _xaudio2, int32_t _num1chVoices, int32_t _num2chVoices);

		/**
		@brief エフェクトを読み込む。
		@param path [in] 読み込みパス
		@return エフェクトのポインタ
		*/
		EffekseerReference Load(const EFK_CHAR* path, const std::string& effect_name);
	private:
		LPDIRECT3DDEVICE9 m_device;
	};

	using EffekseerLoaderReference = resource_loader::ResourceReference<EffekseerLoader>;

	class CreateEffekseerLoader :
		public resource_loader::Loader
	{
		class EffekseerLoaderInput :
			public EffekseerLoader
		{
		public:
			EffekseerLoaderInput();
			EffekseerLoaderInput(const std::string& _tag, resource_loader::LoaderReference _loader, LPDIRECT3DDEVICE9 device);
			~EffekseerLoaderInput();
		};
	private:
		CreateEffekseerLoader(const CreateEffekseerLoader&) = delete;
		CreateEffekseerLoader(CreateEffekseerLoader&&) = delete;
		CreateEffekseerLoader& operator=(const CreateEffekseerLoader&) = delete;
		CreateEffekseerLoader& operator=(CreateEffekseerLoader&&) = delete;
	public:
		CreateEffekseerLoader();
		CreateEffekseerLoader(LPDIRECT3DDEVICE9 device);
		~CreateEffekseerLoader();

		/**
		@brief エフェクシア読み込み機能の生成
		@param _str [in] 読み込み機能の名前
		@return 読み込み機能
		*/
		EffekseerLoaderReference Create(const std::string& _str);
	private:
		LPDIRECT3DDEVICE9 m_device;
		EffekseerLoaderReference m_effekseer_loader;
	};

	using CreateEffekseerLoaderReference = reference::IReference<CreateEffekseerLoader>;

	//==========================================================================
	//
	// class  : SetEffekseer
	// Content: エフェクト登録クラス
	//
	//==========================================================================
	class SetEffekseer
	{
	public:
		SetEffekseer();
		~SetEffekseer();

		/**
		@brief エフェクトデータの登録
		@param TextureData [in] テクスチャ
		*/
		void SetEffekseerData(const EffekseerReference& effekseer);

		/**
		@brief エフェクトデータの取得
		*/
		EffekseerReference GetEffekseerData();
	protected:
		/**
		@brief マネージャーの取得
		*/
		reference::IReference<Effekseer::Manager> GetManager();

		/**
		@brief エフェクトの取得
		*/
		reference::IReference<Effekseer::Effect> GetEffect();

		/**
		@brief サウンドの取得
		*/
		reference::IReference<EffekseerSound::Sound> GetSound();
	protected:
		EffekseerReference m_effekseer_data; // テクスチャデータ

	};
}

_MSLIB_END