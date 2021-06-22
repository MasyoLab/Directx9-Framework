//==========================================================================
// スクリーン [Screen.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "dxlib.h"
//#include "Load\LoadScene.h"

namespace main_system
{
	//==========================================================================
	//
	// class : Screen
	// Content : スクリーン
	//
	//==========================================================================
	class Screen :
		private mslib::render_state::RenderState,
		private mslib::sampler_state::SamplerState,
		public mslib::component::Component
	{
	public:
		Screen();
		~Screen();
		// 初期化
		bool Init(HINSTANCE _hInstance, HWND _hwnd);
		// 解放
		void Uninit();
		// 更新
		bool Update();
		// 描画
		void Draw();
	private:
		// 描画モード
		void Fillmode(LPDIRECT3DDEVICE9 _device);

		// 描画モード
		void EndFillmode(LPDIRECT3DDEVICE9 _device);

		// フィルタリング
		void Fittering(LPDIRECT3DDEVICE9 _device);

		// デバッグ用シーンchange
		void DebugSceneChange();

		// SystemWindow
		void ImGuiSystemMenuBar();
	private:
		mslib::scene_manager::SceneManagerReference m_SceneManager;
#if defined(_MSLIB_DEBUG)
		mslib::boollist m_system; // システム
#endif
	};
}