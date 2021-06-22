//==========================================================================
// �_�C���N�C���v�b�g [DirectInput.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800) // DirectInput�̃o�[�W�����w��
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include <list>

#include "mslib.hpp"
#include "Component.h"

_MSLIB_BEGIN

namespace direct_input
{
	//==========================================================================
	//
	// class : DirectInput
	// Content : �_�C���N�C���v�b�g
	//
	//==========================================================================
	class DirectInput :
		public component::Component
	{
	private:
		DirectInput(const DirectInput&) = delete;
		DirectInput(DirectInput&&) = delete;
		DirectInput& operator=(const DirectInput&) = delete;
		DirectInput& operator=(DirectInput&&) = delete;
	protected:
		DirectInput();
		virtual ~DirectInput();
		/**
		@brief �X�V
		*/
		virtual void Update() = 0;
	public:
		virtual bool Press(int) = 0;
		virtual bool Trigger(int) = 0;
		virtual bool Repeat(int) = 0;
		virtual bool Release(int) = 0;

		/**
		@brief �o�^�ς݃f�o�C�X�̍X�V
		*/
		static void UpdateAll();

		/**
		@brief �C���v�b�g���X�g
		*/
		static std::list<DirectInput*>& GetInputList();
	private:
		/**
		@brief ���
		*/
		void Release();
	private:
		static std::list<DirectInput*> m_direct_input; // �f�o�C�X�̊i�[
	protected:
		LPDIRECTINPUT8 m_input; // DirectInput�I�u�W�F�N�g�ւ̃|�C���^
		LPDIRECTINPUTDEVICE8 m_device; // ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
	};
}

_MSLIB_END