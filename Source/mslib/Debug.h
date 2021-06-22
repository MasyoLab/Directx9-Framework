//==========================================================================
// Debug [Debug.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Activity.h"
#include "Component.h"
#include "Initializer.h"
#include "RectTransform.h"
#include "GUI.h"
#include "MsImGui.h"

_MSLIB_BEGIN

namespace debug
{
	//==========================================================================
	//
	// class : Debug
	// Content : �f�o�b�O�@�\
	//
	//==========================================================================
	class Debug :
		virtual public component::Component,
		public activity::Activity,
		public gui::GUI,
		public initializer::Initializer
	{
	private:
		Debug(const Debug&) = delete;
		Debug(Debug&&) = delete;
		Debug& operator=(const Debug&) = delete;
		Debug& operator=(Debug&&) = delete;
	public:
		Debug();
		virtual ~Debug();
		static void DrawAll(LPDIRECT3DDEVICE9 device);
		static void SetAllActivity(bool _flag);
	protected:
		/**
		@brief ������
		*/
		virtual void Init() override;

		/**
		@brief �f�o�b�O�`��
		@param device [in] �f�o�C�X
		*/
		virtual void Draw(LPDIRECT3DDEVICE9 device);

		/**
		@brief GUI
		*/
		virtual void GUISystem() override;

		void GUIDebug();
	private:
#if defined(_MSLIB_DEBUG)
		static std::list<Debug*> m_debugs; // �X�V�Ώ�
#endif
	};

	using DebugReference = reference::IReference<Debug>;
}

_MSLIB_END