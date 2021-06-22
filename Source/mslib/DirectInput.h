//==========================================================================
// ダイレクインプット [DirectInput.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800) // DirectInputのバージョン指定
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
	// Content : ダイレクインプット
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
		@brief 更新
		*/
		virtual void Update() = 0;
	public:
		virtual bool Press(int) = 0;
		virtual bool Trigger(int) = 0;
		virtual bool Repeat(int) = 0;
		virtual bool Release(int) = 0;

		/**
		@brief 登録済みデバイスの更新
		*/
		static void UpdateAll();

		/**
		@brief インプットリスト
		*/
		static std::list<DirectInput*>& GetInputList();
	private:
		/**
		@brief 解放
		*/
		void Release();
	private:
		static std::list<DirectInput*> m_direct_input; // デバイスの格納
	protected:
		LPDIRECTINPUT8 m_input; // DirectInputオブジェクトへのポインタ
		LPDIRECTINPUTDEVICE8 m_device; // 入力デバイス(キーボード)へのポインタ
	};
}

_MSLIB_END