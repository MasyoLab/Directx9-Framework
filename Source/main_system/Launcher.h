//==========================================================================
// ランチャー [Launcher.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#include <stdio.h>
#include <sal.h>
#include <vector>
#include "dxlib.h"

namespace main_system
{
	class WindowData
	{
	public:
		WindowData() {
			m_serect = 0;
			m_key = 0;
		};
		WindowData(int serect, bool key) {
			m_serect = serect;
			m_key = key;
		}
	public:
		int m_serect;
		bool m_key;
	};

	//==========================================================================
	//
	// class : Launcher
	// Content : ランチャー
	//
	//==========================================================================
	class Launcher :
		public mslib::component::Component
	{
	public:
		Launcher();
		Launcher(const std::string& class_name, const std::string& window_name);
		~Launcher();

		// ウィンドウ生成
		bool Window(HINSTANCE hInstance, int nCmdShow);

		// true の時はフルスクリーン
		bool GetWindowMode() {
			if (m_asp.Size() == m_data.m_serect) {
				return true;
			}
			return false;
		}

		// ウィンドウサイズの取得
		mslib::int2 GetWindowSize() {
			if (m_asp.Size() != m_data.m_serect) {
				return m_asp.Get(m_data.m_serect).m_size;
			}
			return mslib::int2(0, 0);
		}

		// ウィンドウモードのセット
		void SetAspectRatio(const mslib::aspect::AspectRatio::List& Input) {
			m_asp.Search(Input.m_size, Input.m_asp);
		}
	private:
		static void newtex();
		// ボタン
		static void Button(HWND hWnd, LPARAM* lParam, int posx, int posy);
		// 設定
		static void Config(HDC* hDC, mslib::intTexvec* vpos);
		// テキスト描画
		static void Text(HWND hWnd, HDC* hDC, LPCTSTR lpszStr, int posx, int posy);
		// イメージデータ表示場所
		static void ImgeData(HDC* hDC, mslib::intTexvec* vpos);
		// テクスチャ読み込み
		static void LoadTex(LPARAM* lp);
		// テクスチャ描画
		static void DrawTex(HWND hWnd, HDC* hDC, mslib::intTexvec* vpos);
		// ウインドウプロシージャ
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
	private:
		static HWND m_hWnd;
		static HWND m_combo;
		static HDC m_BackBufferDC;
		static HBITMAP m_BackBufferBMP;
		static HWND m_hWndButton10000;
		static HWND m_hWndButton10001;
		static HWND m_check;

		//ビットマップ
		static HBITMAP m_hBitmap;
		static BITMAP m_Bitmap;

		static WindowData m_data;

		static mslib::aspect::AspectRatio m_asp;
	};

	using LauncherReference = mslib::reference::IReference<Launcher>;
}