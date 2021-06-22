//==========================================================================
// シーン遷移 [SceneManager.cpp]
// author : MasyoLab
//==========================================================================
#include <string>
#include <direct.h>
#include "SceneManager.h"
#include "Initializer.h"
#include "Manager.h"
#include "InOutFunction.h"
#include "Sprite.h"

_MSLIB_BEGIN

namespace scene_manager
{
	using namespace initializer;
	using namespace manager;

	constexpr char* _file_pass_ = "resource/Scene/";

	BaseScene::BaseScene(const std::string& _SceneName) :
		Component(_SceneName), m_initEndData(0), m_InitEnd(false)
	{
	}

	BaseScene::~BaseScene()
	{
	}

	bool BaseScene::Init()
	{
		if (m_InitEnd)
			return true;

		// 最大インスタンス数
		int initNumData = Initializer::GetInitAllSize() + m_initEndData;

		Initializer::InitAllLock();
		Initializer::InitOne();
		in_out_function::InOutFunction::InputDataAll(_file_pass_ + GetComponentName() + "/", ThisComponent());
		object::Sprite::Sort();

		// 初期化数をカウント
		m_initEndData++;

#if defined(_MSLIB_DEBUG)
		if (imgui::NewFrameCheckCall())
			imgui::_ProgressBar((float)m_initEndData / (float)initNumData);
#endif
		// 初期化が終了
		if (Initializer::GetInitAllSize() == 0) {
			Initializer::InitAllUnLock();
			in_out_function::InOutFunction::InputDataReleaseAll();
			m_InitEnd = true;
		}
		return m_InitEnd;
	}

	void BaseScene::Update()
	{
#if defined(_MSLIB_DEBUG)
		imgui::Separator();
		imgui::Text("Scene Name : " + GetComponentName());
		imgui::Separator();
#endif
	}

	void BaseScene::SaveSceneData()
	{
#if defined(_MSLIB_DEBUG)
		_mkdir("resource");
		_mkdir("resource/Scene");
		_mkdir((std::string("resource/Scene/") + GetComponentName()).c_str());
		in_out_function::InOutFunction::OutputDataAll(_file_pass_ + GetComponentName() + "/", ThisComponent());
#endif
	}
	reference::IReference<SceneManager> SceneManager::m_this;

	SceneManager::SceneManager() : Component("SceneManager")
	{
		m_init_end = false;
		if (m_this == nullptr)
			m_this = ThisComponent<SceneManager>();
	}

	SceneManager::~SceneManager()
	{
		m_this = nullptr;
	}

	bool SceneManager::Init()
	{
		if (!m_init_end)
		{
			if (m_main_scene == nullptr)
				return m_init_end;
			m_init_end = m_main_scene->Init();
			if (m_init_end)
				DestroyComponent(m_load_scene);
		}
		return m_init_end;
	}

	void SceneManager::Uninit()
	{
		DestroyComponent(m_main_scene);
		DestroyComponent(m_load_scene);
		m_main_scene = nullptr;
		m_load_scene = nullptr;
	}

	void SceneManager::Update()
	{
		if (m_main_scene != nullptr)
			m_main_scene->Update();
	}

	const std::string& SceneManager::GetSceneName() const
	{
		if (m_main_scene != nullptr)
			return m_main_scene->GetComponentName();
		return m_not_scene;
	}

	void SceneManager::SetScene(BaseScene* _scene)
	{
		if (m_this == nullptr)
			return;
		m_this->DestroyComponent(m_this->m_main_scene);
		m_this->m_main_scene = m_this->AddComponent(_scene);
		m_this->m_init_end = false;
	}

	void SceneManager::SetLoadScene(BaseScene* _scene)
	{
		if (m_this == nullptr)
			return;
		m_this->DestroyComponent(m_this->m_load_scene);
		m_this->m_load_scene = m_this->AddComponent(_scene);
		for (; m_this->m_load_scene->Init() != true;);
	}

	void SceneManager::SaveSceneData()
	{
		if (m_main_scene != nullptr)
			m_main_scene->SaveSceneData();
	}
}

_MSLIB_END