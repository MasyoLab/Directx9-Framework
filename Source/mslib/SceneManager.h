//==========================================================================
// シーン遷移 [SceneManager.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "mslib.hpp"
#include "Component.h" // コンポーネント
#include "MsImGui.h"

_MSLIB_BEGIN

namespace scene_manager
{
	//==========================================================================
	//
	// class : BaseScene
	// Content : ベースとなる継承用クラス
	//
	//==========================================================================
	class BaseScene :
		public component::Component
	{
	public:
		BaseScene(const std::string& _SceneName);
		~BaseScene();

		/**
		@brief 初期化
		@return 初期化終了時にtrueが返ります。
		*/
		bool Init();

		/**
		@brief 更新
		*/
		void Update();

		/**
		@brief シーンのデータを保存
		*/
		void SaveSceneData();
	private:
		int m_initEndData;
		bool m_InitEnd;
	};

	using BaseSceneReference = reference::IReference<BaseScene>;

	//==========================================================================
	//
	// class : SceneManager
	// Content : 全てのシーンの管理
	//
	//==========================================================================
	class SceneManager final :
		public component::Component
	{
	private:
		SceneManager(const SceneManager&) = delete;
		SceneManager(SceneManager&&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;
		SceneManager& operator=(SceneManager&&) = delete;
	public:
		SceneManager();
		~SceneManager();

		/**
		@brief 初期化
		@return 初期化終了時にtrueが返ります。
		*/
		bool Init();

		/**
		@brief 解放
		*/
		void Uninit();

		/**
		@brief 更新
		*/
		void Update();

		/**
		@brief シーン名取得
		@return シーン名が返ります
		*/
		const std::string& GetSceneName() const;

		/**
		@brief 実行するシーンを登録
		*/
		static void SetScene(BaseScene * _scene);

		/**
		@brief ロードシーンを登録
		*/
		static void SetLoadScene(BaseScene* _scene);

		/**
		@brief シーンのデータを保存
		*/
		void SaveSceneData();
	private:
		BaseSceneReference m_main_scene; // シーン
		BaseSceneReference m_load_scene; // シーン
		bool m_init_end;
		std::string m_not_scene;
		static reference::IReference<SceneManager> m_this;
	};

	using SceneManagerReference = reference::IReference<SceneManager>;
}

_MSLIB_END