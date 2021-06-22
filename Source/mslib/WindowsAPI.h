//==========================================================================
// WindowsAPI [WindowsAPI.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <windows.h>
#include <string>
#include <memory> // c++ ������
#include <cstdio> // 

#include "mslib.hpp"
#include "Component.h"

_MSLIB_BEGIN

namespace window
{
	// Class styles
	enum class WindowStyles
	{
		VREDRAW = CS_VREDRAW,
		HREDRAW = CS_HREDRAW,
		DBLCLKS = CS_DBLCLKS,
		OWNDC = CS_OWNDC,
		CLASSDC = CS_CLASSDC,
		PARENTDC = CS_PARENTDC,
		NOCLOSE = CS_NOCLOSE,
		SAVEBITS = CS_SAVEBITS,
		BYTEALIGNCLIENT = CS_BYTEALIGNCLIENT,
		BYTEALIGNWINDOW = CS_BYTEALIGNWINDOW,
		GLOBALCLAS = CS_GLOBALCLASS,
		VREDRAW_HREDRAW = CS_VREDRAW | CS_HREDRAW,
	};

	//==========================================================================
	//
	// class : WindowsAPI
	// Content : WindowsAPI
	//
	//=========================================================================
	class WindowsAPI :
		public component::Component
	{
	private:
		WindowsAPI() = delete;
		WindowsAPI(const WindowsAPI&) = delete;
		WindowsAPI(WindowsAPI&&) = delete;
		WindowsAPI& operator=(const WindowsAPI&) = delete;
		WindowsAPI& operator=(WindowsAPI&&) = delete;
	public:
		WindowsAPI(const std::string& _class_name, const std::string& _window_name);
		virtual ~WindowsAPI();

		/**
		@brief �E�B���h�E�N���X�ƃZ�b�g
		@param style [in] �E�B���h�E�̃X�^�C��
		@param __WndProc [in] WndProc
		@param hIcon [in] �A�C�R���̃n���h��
		@param hIconSm [in] 16�~16�̏������T�C�Y�̃A�C�R���̃n���h��
		@param lpszMenuName [in] �f�t�H���g���j���[
		@param hInstance [in] �C���X�^���X�n���h��
		@return BUGBUG - might want to remove this from minwin
		*/
		ATOM SetWindowClass(UINT _style, WNDPROC _WndProc, LPCSTR _Icon, LPCSTR _IconSm, LPCSTR _lpszMenuName, HINSTANCE _Instance);

		/**
		@brief �E�B���h�E�̐���
		@param dwStyle [in] �E�B���h�E�X�^�C��
		@param rect [in] �E�B���h�E�T�C�Y
		@param hWndParent [in] �e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
		@param hMenu [in] ���j���[�n���h���܂��͎q�E�B���h�E ID
		@param lpParam [in] �E�B���h�E�쐬�f�[�^
		@param nCmdShow [in] ShowWindow
		@return ���s���� true ���Ԃ�܂�
		*/
		bool Create(DWORD _dwStyle, RECT _rect, HWND _WndParent, HMENU _Menu, LPVOID _lpParam, int _CmdShow);

		/**
		@brief ���b�Z�[�W�̃Q�b�^�[
		@return Message
		*/
		MSG& GetMSG();

		/**
		@brief �E�B���h�E�n���h��
		@return hwnd
		*/
		HWND GetHWND();

		/**
		@brief �E�B���h�ERECT
		@param dwStyle [in] �E�B���h�E�X�^�C��
		@param Width [in] Width
		@param Height [in] Height
		@param bMenu [in] ���j���[�����邩�ǂ���
		@return �E�B���h�ERECT
		*/
		RECT GetWindowRECT(DWORD _dwStyle, int _Width, int _Height, bool _Menu);

		/**
		@brief �G���[���b�Z�[�W
		*/
		template <typename ... Args>
		void ErrorMessage(const char* _text, const Args& ... _args);
	private:
		std::string m_class_name; // �N���X��
		std::string m_window_name; // �E�B���h�E��
		RECT m_rect; // �E�B���h�ERECT
		HWND m_hWnd; // �E�B���h�E�n���h��
		MSG m_msg; // ���b�Z�[�W
		WNDCLASSEX m_wcex; // �E�B���h�E�N���X
	};

	/**
	@brief �G���[���b�Z�[�W
	*/
	template<typename ...Args>
	inline void WindowsAPI::ErrorMessage(const char* _text, const Args& ... _args)
	{
		size_t size = snprintf(nullptr, 0, _text, _args ...) + 1; // Extra space for '\0'
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, _text, _args ...);

		MessageBox(m_hWnd, std::string(buf.get(), buf.get() + size - 1).c_str(), "ERROR", MB_OK | MB_ICONEXCLAMATION | MB_ICONWARNING);
	}

	using WindowsAPIReference = reference::IReference<WindowsAPI>;
}
_MSLIB_END