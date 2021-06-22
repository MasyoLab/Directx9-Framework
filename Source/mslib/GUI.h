//==========================================================================
// GUI [GUI.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "mslib.hpp"
#include "Component.h"
#include "Reference.h"

_MSLIB_BEGIN

namespace gui
{
	//==========================================================================
	//
	// class : GUI
	// Content : GUI
	//
	//==========================================================================
	class GUI :
		virtual public component::Component
	{
	private:
		GUI(const GUI&) = delete;
		GUI(GUI&&) = delete;
		GUI& operator=(const GUI&) = delete;
		GUI& operator=(GUI&&) = delete;
	public:
		GUI();
		virtual ~GUI();
		static void GUIUpdateAll();
	protected:
		/**
		@brief GUI
		*/
		virtual void GUISystem();
	private:
		void GUIStart();
		void GUICheck();
		void GUIWindow();
		void GUICall();
		void GUIEnd();
	private:
#if defined(_MSLIB_DEBUG)
		reference::IReference<GUI> m_gui_parent;
		std::list<GUI*> m_gui_child;
		bool m_gui_init_flag;
		mslib::boollist m_bool_list;
		static std::list<GUI*> m_guis;
#endif
	};
}

_MSLIB_END