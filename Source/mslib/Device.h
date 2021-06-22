//==========================================================================
// �f�o�C�X [Device.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <memory> 
#include <vector>

#include "mslib.hpp"
#include "mslib_struct.h"
#include "Reference.h"
#include "Component.h"

_MSLIB_BEGIN

namespace device
{
	//==========================================================================
	//
	// class : Device
	// Content : �f�o�C�X 
	//
	//==========================================================================
	class Device :
		public component::Component
	{
	private:
		Device(const Device&) = delete;
		Device(Device&&) = delete;
		Device& operator=(const Device&) = delete;
		Device& operator=(Device&&) = delete;
	public:
		Device();
		~Device();

		/**
		@brief ������
		@return ���s���� true ���Ԃ�܂�
		*/
		void Init();

		/**
		@brief ���
		*/
		void Release();

		/**
		@brief �E�B���h�E���[�h�̐���
		@param size [in] �E�B���h�E�T�C�Y
		@param Mode [in] �E�B���h�E���[�h true �Ńt���X�N���[��
		*/
		bool CreateWindowMode(const int2& _Size, bool _Mode);

		/**
		@brief �f�o�C�X�̐���
		@return ���s���� true ���Ԃ�܂�
		*/
		bool CreateDevice();

		/**
		@brief �f�o�C�X�̏K��
		@return �f�o�C�X
		*/
		LPDIRECT3DDEVICE9 Getd3ddevice() const;

		/**
		@brief �f�o�C�X�̏K��
		@return �f�o�C�X
		*/
		D3DPRESENT_PARAMETERS& Getd3dpp();

		/**
		@brief �E�B���h�E�T�C�Y�̏K��
		@return �E�B���h�E�T�C�Y
		*/
		const D3DXVECTOR2& GetWindowsSize() const;

		/**
		@brief ���������E�B���h�E�T�C�Y�̏K��
		@return ���������E�B���h�E�T�C�Y
		*/
		const D3DXVECTOR2& GetDefaultWindowsSize() const;

		/**
		@brief �E�B���h�E�n���h���̓���
		@param hWnd [in] �E�B���h�E�n���h��
		*/
		void SetHwnd(HWND _hWnd);

		/**
		@brief �E�B���h�E�n���h���̎擾
		@return �E�B���h�E�n���h��
		*/
		HWND GetHwnd() const;

		/**
		@brief �`��J�n
		@return �`��\�ȍۂ� true ���Ԃ�܂�
		*/
		bool DrawBegin();

		/**
		@brief �`��I��
		@param SourceRect [in]
		@param DestRect [in]
		@param hDestWindowOverride [in]
		@param DirtyRegion [in]
		@return Component Object Model defines, and macros
		*/
		HRESULT STDMETHODCALLTYPE DrawEnd(const RECT* _SourceRect, const RECT* _DestRect, HWND _DestWindowOverride, const RGNDATA* _DirtyRegion);

		/**
		@brief �`��I��
		@return Component Object Model defines, and macros
		*/
		HRESULT STDMETHODCALLTYPE DrawEnd();

		/**
		@brief �G���[���b�Z�[�W
		@param text [in] �e�L�X�g����
		@param args [in] �o�͕���
		*/
		template <typename ... Args>
		void ErrorMessage(const char* _text, const Args& ... _args);
	private:
		LPDIRECT3D9 m_lpd3d; //�_�C���N�g3D�C���^�[�t�F�[�X
		LPDIRECT3DDEVICE9 m_lpd3ddevice;//�_�C���N�g3D�f�o�C�X
		D3DPRESENT_PARAMETERS m_d3dpp; // �p�����[�^�[
		D3DDISPLAYMODE m_d3dpm; // �f�B�X�v���C���[�h
		HWND m_hwnd; // �E�B���h�E�n���h��
		std::vector<D3DDISPLAYMODE> m_d3dsp_mode; // �f�B�X�v���C���[�h�Ǘ�
		D3DXVECTOR2 m_windows_size; // �E�B���h�E�T�C�Y
		D3DXVECTOR2 m_default_windows_size; // �E�B���h�E�T�C�Y
		int m_adapter; // �f�B�X�v���C�A�_�v�^�ԍ�
	};

	//==========================================================================
	/**
	@brief �G���[���b�Z�[�W
	@param text [in] �e�L�X�g����
	@param args [in] �o�͕���
	*/
	template<typename ...Args>
	inline void Device::ErrorMessage(const char* _text, const Args& ... _args)
	{
		size_t size = snprintf(nullptr, 0, _text, _args ...) + 1; // Extra space for '\0'
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, _text, _args ...);

		MessageBox(m_hwnd, std::string(buf.get(), buf.get() + size - 1).c_str(), "ERROR", MB_OK | MB_ICONEXCLAMATION | MB_ICONWARNING);
	}

	using DeviceReference = reference::IReference<Device>;
}

_MSLIB_END