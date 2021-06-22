//==========================================================================
// �V�[���J�� [SceneManager.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "mslib.hpp"
#include "Component.h" // �R���|�[�l���g
#include "MsImGui.h"

_MSLIB_BEGIN

namespace scene_manager
{
	//==========================================================================
	//
	// class : BaseScene
	// Content : �x�[�X�ƂȂ�p���p�N���X
	//
	//==========================================================================
	class BaseScene :
		public component::Component
	{
	public:
		BaseScene(const std::string& _SceneName);
		~BaseScene();

		/**
		@brief ������
		@return �������I������true���Ԃ�܂��B
		*/
		bool Init();

		/**
		@brief �X�V
		*/
		void Update();

		/**
		@brief �V�[���̃f�[�^��ۑ�
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
	// Content : �S�ẴV�[���̊Ǘ�
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
		@brief ������
		@return �������I������true���Ԃ�܂��B
		*/
		bool Init();

		/**
		@brief ���
		*/
		void Uninit();

		/**
		@brief �X�V
		*/
		void Update();

		/**
		@brief �V�[�����擾
		@return �V�[�������Ԃ�܂�
		*/
		const std::string& GetSceneName() const;

		/**
		@brief ���s����V�[����o�^
		*/
		static void SetScene(BaseScene * _scene);

		/**
		@brief ���[�h�V�[����o�^
		*/
		static void SetLoadScene(BaseScene* _scene);

		/**
		@brief �V�[���̃f�[�^��ۑ�
		*/
		void SaveSceneData();
	private:
		BaseSceneReference m_main_scene; // �V�[��
		BaseSceneReference m_load_scene; // �V�[��
		bool m_init_end;
		std::string m_not_scene;
		static reference::IReference<SceneManager> m_this;
	};

	using SceneManagerReference = reference::IReference<SceneManager>;
}

_MSLIB_END