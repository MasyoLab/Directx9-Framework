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
		// GUI�̍X�V
		for (auto& itr : m_guis)
		{
			itr->GUICheck();
			itr->GUIStart();
			itr->GUIWindow();
			// �e�����݂���ꍇ�͂���ȏ���s���Ȃ�
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
		// ���݂̐e���A�A�N�Z�X����e�ƈႤ�ꍇ�͏������\�ɂ���
		if (m_gui_parent != nullptr)
			if (GetComponentParent() != m_gui_parent->ThisComponent())
				m_gui_init_flag = false;

		// ���������I����Ă���
		if (m_gui_init_flag)
			return;
		
		// �e�̎擾
		m_gui_init_flag = true;
		m_gui_parent = GetComponentParent<GUI>();
		if (m_gui_parent == nullptr)
			return;

		// �e�Ɏ��g�ւ̃A�N�Z�X����^����
		m_gui_parent->m_gui_child.push_back(this);
#endif	
	}

	void GUI::GUICheck()
	{
#if defined(_MSLIB_DEBUG)
		if (m_gui_parent == nullptr)
			return;

		// ���̎Q�Ƌ@�\�݂̂��Q�Ƃ��Ă���ꍇ
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
		// �e�����݂��Ȃ��̂ŁAGUI���Ăяo���܂�
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

		// �q��񂩂�A���g�̃A�N�Z�X������j�����܂�
		for (auto& itr : m_gui_child)
			itr->m_gui_parent = nullptr;
		m_gui_child.clear();

		// �e�����Ȃ���ΏI��
		if (m_gui_parent == nullptr)
			return;

		// �e����A���g�ւ̃A�N�Z�X������j�����܂�
		auto itr = std::find(m_gui_parent->m_gui_child.begin(), m_gui_parent->m_gui_child.end(), this);
		if (itr != m_gui_parent->m_gui_child.end())
			m_gui_parent->m_gui_child.erase(itr);
		m_gui_parent.clear();
#endif	
	}
}

_MSLIB_END