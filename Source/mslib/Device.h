//==========================================================================
// デバイス [Device.h]
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
	// Content : デバイス 
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
		@brief 初期化
		@return 失敗時に true が返ります
		*/
		void Init();

		/**
		@brief 解放
		*/
		void Release();

		/**
		@brief ウィンドウモードの生成
		@param size [in] ウィンドウサイズ
		@param Mode [in] ウィンドウモード true でフルスクリーン
		*/
		bool CreateWindowMode(const int2& _Size, bool _Mode);

		/**
		@brief デバイスの生成
		@return 失敗時に true が返ります
		*/
		bool CreateDevice();

		/**
		@brief デバイスの習得
		@return デバイス
		*/
		LPDIRECT3DDEVICE9 Getd3ddevice() const;

		/**
		@brief デバイスの習得
		@return デバイス
		*/
		D3DPRESENT_PARAMETERS& Getd3dpp();

		/**
		@brief ウィンドウサイズの習得
		@return ウィンドウサイズ
		*/
		const D3DXVECTOR2& GetWindowsSize() const;

		/**
		@brief 推奨されるウィンドウサイズの習得
		@return 推奨されるウィンドウサイズ
		*/
		const D3DXVECTOR2& GetDefaultWindowsSize() const;

		/**
		@brief ウィンドウハンドルの入力
		@param hWnd [in] ウィンドウハンドル
		*/
		void SetHwnd(HWND _hWnd);

		/**
		@brief ウィンドウハンドルの取得
		@return ウィンドウハンドル
		*/
		HWND GetHwnd() const;

		/**
		@brief 描画開始
		@return 描画可能な際に true が返ります
		*/
		bool DrawBegin();

		/**
		@brief 描画終了
		@param SourceRect [in]
		@param DestRect [in]
		@param hDestWindowOverride [in]
		@param DirtyRegion [in]
		@return Component Object Model defines, and macros
		*/
		HRESULT STDMETHODCALLTYPE DrawEnd(const RECT* _SourceRect, const RECT* _DestRect, HWND _DestWindowOverride, const RGNDATA* _DirtyRegion);

		/**
		@brief 描画終了
		@return Component Object Model defines, and macros
		*/
		HRESULT STDMETHODCALLTYPE DrawEnd();

		/**
		@brief エラーメッセージ
		@param text [in] テキスト入力
		@param args [in] 出力文字
		*/
		template <typename ... Args>
		void ErrorMessage(const char* _text, const Args& ... _args);
	private:
		LPDIRECT3D9 m_lpd3d; //ダイレクト3Dインターフェース
		LPDIRECT3DDEVICE9 m_lpd3ddevice;//ダイレクト3Dデバイス
		D3DPRESENT_PARAMETERS m_d3dpp; // パラメーター
		D3DDISPLAYMODE m_d3dpm; // ディスプレイモード
		HWND m_hwnd; // ウィンドウハンドル
		std::vector<D3DDISPLAYMODE> m_d3dsp_mode; // ディスプレイモード管理
		D3DXVECTOR2 m_windows_size; // ウィンドウサイズ
		D3DXVECTOR2 m_default_windows_size; // ウィンドウサイズ
		int m_adapter; // ディスプレイアダプタ番号
	};

	//==========================================================================
	/**
	@brief エラーメッセージ
	@param text [in] テキスト入力
	@param args [in] 出力文字
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