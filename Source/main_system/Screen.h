//==========================================================================
// �X�N���[�� [Screen.h]
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
	// Content : �X�N���[��
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
		// ������
		bool Init(HINSTANCE _hInstance, HWND _hwnd);
		// ���
		void Uninit();
		// �X�V
		bool Update();
		// �`��
		void Draw();
	private:
		// �`�惂�[�h
		void Fillmode(LPDIRECT3DDEVICE9 _device);

		// �`�惂�[�h
		void EndFillmode(LPDIRECT3DDEVICE9 _device);

		// �t�B���^�����O
		void Fittering(LPDIRECT3DDEVICE9 _device);

		// �f�o�b�O�p�V�[��change
		void DebugSceneChange();

		// SystemWindow
		void ImGuiSystemMenuBar();
	private:
		mslib::scene_manager::SceneManagerReference m_SceneManager;
#if defined(_MSLIB_DEBUG)
		mslib::boollist m_system; // �V�X�e��
#endif
	};
}