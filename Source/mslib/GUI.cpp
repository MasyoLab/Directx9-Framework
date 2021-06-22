//==========================================================================
// GUI [GUI.cpp]
// author : MasyoLab
//==========================================================================
#include "GUI.h"
#include "MsImGui.h"
#include "string_encode.hpp"

_MSLIB_BEGIN

namespace gui
{
#if defined(_MSLIB_DEBUG)
	std::list<GUI*> GUI::m_guis;
#endif
	
	GUI::GUI()
	{
#if defined(_MSLIB_DEBUG)
		m_gui_init_flag = false;
		m_guis.push_back(this);
#endif
	}

	GUI::~GUI()
	{
#if defined(_MSLIB_DEBUG)
		auto itr = std::find(m_guis.begin(), m_guis.end(), this);
		if (itr != m_guis.end())
			m_guis.erase(itr);
#endif
	}

	void GUI::GUIUpdateAll()
	{
#if defined(_MSLIB_DEBUG)
		// GUIの更新
		for (auto& itr : m_guis)
		{
			itr->GUICheck();
			itr->GUIStart();
			itr->GUIWindow();
			// 親が存在する場合はこれ以上実行しない
			if (itr->m_gui_parent.check())
				continue;
			itr->GUICall();
		}
#endif
	}

	void GUI::GUISystem()
	{
#if defined(_MSLIB_DEBUG)
#endif	
	}

	void GUI::GUIStart()
	{
#if defined(_MSLIB_DEBUG)
		// 現在の親が、アクセスする親と違う場合は初期化可能にする
		if (m_gui_parent != nullptr)
			if (GetComponentParent() != m_gui_parent->ThisComponent())
				m_gui_init_flag = false;

		// 初期化が終わっている
		if (m_gui_init_flag)
			return;
		
		// 親の取得
		m_gui_init_flag = true;
		m_gui_parent = GetComponentParent<GUI>();
		if (m_gui_parent == nullptr)
			return;

		// 親に自身へのアクセス権を与える
		m_gui_parent->m_gui_child.push_back(this);
#endif	
	}

	void GUI::GUICheck()
	{
#if defined(_MSLIB_DEBUG)
		if (m_gui_parent == nullptr)
			return;

		// この参照機能のみが参照している場合
		if (m_gui_parent.use_count() == (long)1)
			GUIEnd();
#endif	
	}

	void GUI::GUIWindow()
	{
#if defined(_MSLIB_DEBUG)
		if (!m_bool_list.Get(imgui::CreateText("%p", this)))
			return;

		ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoSavedSettings;
		auto label_str = GetComponentName() + " : " + imgui::CreateText("%p", this);

		imgui::_Begin(string_encode::ansi_to_utf8_encode(("Window : " + label_str)).c_str(), &m_bool_list.Get(imgui::CreateText("%p", this)), WindowFlags);
		GUISystem();
		imgui::_End();
#endif	
	}

	void GUI::GUICall()
	{
#if defined(_MSLIB_DEBUG)
		// 親が存在しないので、GUIを呼び出します
		auto label_str = GetComponentName() + " : " + imgui::CreateText("%p", this);
		if (imgui::NewTreeNode(label_str, false))
		{
			imgui::Checkbox(label_str, m_bool_list.Get(imgui::CreateText("%p", this)));
			for (auto& itr : m_gui_child)
				itr->GUICall();
			imgui::EndTreeNode();
		}
#endif	
	}

	void GUI::GUIEnd()
	{
#if defined(_MSLIB_DEBUG)
		m_bool_list.Release(imgui::CreateText("%p", this));

		// 子情報から、自身のアクセス権限を破棄します
		for (auto& itr : m_gui_child)
			itr->m_gui_parent = nullptr;
		m_gui_child.clear();

		// 親がいなければ終了
		if (m_gui_parent == nullptr)
			return;

		// 親から、自身へのアクセス権限を破棄します
		auto itr = std::find(m_gui_parent->m_gui_child.begin(), m_gui_parent->m_gui_child.end(), this);
		if (itr != m_gui_parent->m_gui_child.end())
			m_gui_parent->m_gui_child.erase(itr);
		m_gui_parent.clear();
#endif	
	}
}

_MSLIB_END