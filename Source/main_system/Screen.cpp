//==========================================================================
// スクリーン [Screen.cpp]
// author : MasyoLab
//==========================================================================
#include "Screen.h"
#include "Sample/Sample1/Sample1.h"
#include "Sample/Sample2/Sample2.h"
#include "LoadScene/LoadScene.h"
#include "resource_list.h"

namespace main_system
{
	//==========================================================================
	// 実体
	//==========================================================================
	//mslib::scene_manager::BaseScene *CScreen::m_next_scene = nullptr; // name

	//==========================================================================
	// 定数定義
	//==========================================================================
	constexpr int __ImGuiWindowY = 26;

	Screen::Screen() : Component("Screen")
	{
#if defined(_MSLIB_DEBUG)
		m_system.Get("Fill Mode");
		m_system.Get("Fittering");
#endif
	}

	Screen::~Screen()
	{
		Uninit();
	}

	bool Screen::Init(HINSTANCE _hInstance, HWND _hwnd)
	{
		srand((unsigned)time(nullptr));
		mslib::manager::Manager manager; // マネージャー

		if (manager.GetDevice()->CreateDevice())
			return true;
		auto device = manager.GetDevice();	//デバイス渡し	
		if (manager.GetDInputKeyboard()->Init(_hInstance, _hwnd))
			return true;
		if (manager.GetDInputController()->Init(_hInstance, _hwnd))
			return true;
		if (manager.GetDInputMouse()->Init(_hInstance, _hwnd))
			return true;
		if (manager.GetAudioLoader()->Init(_hwnd))
			return true;
		m_SceneManager = manager.GetSceneManager();

		mslib::object::Sprite::CreateRenderer(manager.GetEffectLoader()->Load(RESOURCE_Sprite2D_fx), device->Getd3ddevice());
#if defined(_MSLIB_DEBUG)
		mslib::imgui::Init(_hwnd, device->Getd3ddevice());
#endif
		return false;
	}

	void Screen::Uninit()
	{
#if defined(_MSLIB_DEBUG)
		mslib::imgui::Uninit();
#endif
		m_SceneManager->Uninit();
	}

	bool Screen::Update()
	{
#if defined(_MSLIB_DEBUG)
		// ImGui 新しいフレーム
		mslib::imgui::NewFrame();
		mslib::imgui::NewWindow("Operation window", true, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoSavedSettings);

		// システムウィンドウ
		ImGuiSystemMenuBar();
#endif
		m_SceneManager->Init();
		m_SceneManager->Update();
		mslib::manager::Manager::UpdateManager();
#if defined(_MSLIB_DEBUG)
		mslib::imgui::EndWindow();
		mslib::imgui::EndFrame();
#endif
		return false;
	}

	void Screen::Draw()
	{
		auto device = mslib::manager::Manager::GetDevice();
		Fillmode(device->Getd3ddevice());
		Fittering(device->Getd3ddevice());
		auto flag = mslib::manager::Manager::DrawManager();
		EndFillmode(device->Getd3ddevice());
#if defined(_MSLIB_DEBUG)
		if (flag)
			mslib::imgui::Draw(device->Getd3ddevice());
		if (device->DrawEnd() == D3DERR_DEVICELOST && device->Getd3ddevice()->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
			mslib::imgui::DeviceReset(device->Getd3ddevice(), &device->Getd3dpp());
#else
		flag;
		if (device->DrawEnd() == D3DERR_DEVICELOST && device->Getd3ddevice()->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
			if (device->Getd3ddevice()->Reset(&device->Getd3dpp()) == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
#endif
	}

	void Screen::Fillmode(LPDIRECT3DDEVICE9 _device)
	{
#if defined(_MSLIB_DEBUG)
		if (m_system.Get("Fill Mode"))
			SetRenderWIREFRAME(_device);
		else
			SetRenderSOLID(_device);
#else
		_device;
#endif
	}

	void Screen::EndFillmode(LPDIRECT3DDEVICE9 _device)
	{
#if defined(_MSLIB_DEBUG)
		if (m_system.Get("Fill Mode"))
			SetRenderSOLID(_device);
#else
		_device;
#endif
	}

	void Screen::Fittering(LPDIRECT3DDEVICE9 _device)
	{
#if defined(_MSLIB_DEBUG)
		if (m_system.Get("Fittering"))
			SamplerFitteringGraphical(_device);
		else
			SamplerFitteringLINEAR(_device);
#else
		_device;
#endif
	}

	void Screen::DebugSceneChange()
	{
		#if defined(_MSLIB_DEBUG)
		if (!mslib::imgui::NewMenu("Scene Manager", true))
			return;
		mslib::imgui::_Bullet();
		if (mslib::imgui::MenuItem("Sample1"))
		{
			mslib::scene_manager::SceneManager::SetLoadScene(new load_screen::LoadScene);
			mslib::scene_manager::SceneManager::SetScene(new sample1::Sample1);
		}
		mslib::imgui::_Bullet();
		if (mslib::imgui::MenuItem("Sample2"))
		{
			mslib::scene_manager::SceneManager::SetLoadScene(new load_screen::LoadScene);
			mslib::scene_manager::SceneManager::SetScene(new sample2::Sample2);
		}
		mslib::imgui::_Bullet();
		if (mslib::imgui::MenuItem("Load"))
		{
			mslib::scene_manager::SceneManager::SetScene(new load_screen::LoadScene);
		}
		mslib::imgui::EndMenu();
		#endif
	}

	void Screen::ImGuiSystemMenuBar()
	{
#if defined(_MSLIB_DEBUG)
		// ImGui System Bar
		auto device = mslib::manager::Manager::GetDevice();

		if (mslib::imgui::_BeginMenuBar())
		{
			if (mslib::imgui::NewMenu("System"))
			{
				// ワイヤーフレームに切り替える
				mslib::imgui::Checkbox("Switch to wire frame", m_system.Get("Fill Mode"));
				// フィルタリングのセット
				mslib::imgui::Checkbox("Change filtering", m_system.Get("Fittering"));
				if (mslib::imgui::Button("Save Scene Data"))
					m_SceneManager->SaveSceneData();
				mslib::imgui::EndMenu();
			}
			// ImGui ウィンドウ情報
			mslib::imgui::WindowInfo();

			// ImGui シーンボタン
			DebugSceneChange();

			mslib::imgui::EndMenuBar();
		}
#endif
	}
}