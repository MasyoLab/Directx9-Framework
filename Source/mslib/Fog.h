//==========================================================================
// フォグ [Fog.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Component.h"

_MSLIB_BEGIN

namespace fog
{
	class EffectRangePos
	{
	public:
		EffectRangePos() {}
		EffectRangePos(float _start, float _end) {
			start = _start;
			end = _end;
		}
		~EffectRangePos() {}
	public:
		float start = 0.0f;
		float end = 0.0f;
	};

	//==========================================================================
	//
	// class : Fog
	// Content : フォグ
	//
	//==========================================================================
	class Fog :
		public component::Component
	{
	private:
		Fog(const Fog&) = delete;
		Fog(Fog&&) = delete;
		Fog& operator=(const Fog&) = delete;
		Fog& operator=(Fog&&) = delete;
	public:
		Fog(LPDIRECT3DDEVICE9 pDevice);
		virtual ~Fog();

		/**
		@brief 初期化
		@param color [in] 色
		@param start_pos [in] フォグ影響開始地点
		@param end_pos [in] フォグ完全影響地点
		@param VertexMode [in] 頂点のモード指定
		@param TableMode [in] テーブルモード設定
		*/
		void Init(const D3DXCOLOR& color, float start_pos = 10.0f, float end_pos = 100.0f, D3DFOGMODE VertexMode = D3DFOG_NONE, D3DFOGMODE TableMode = D3DFOG_LINEAR);

		/**
		@brief フォクの有効化
		*/
		void ON();

		/**
		@brief フォクの無効化
		*/
		void OFF();

		/**
		@brief テーブルモード設定
		@param TableMode [in] テーブルモード
		*/
		void SetTableMode(D3DFOGMODE TableMode);

		/**
		@brief テーブルモードの取得
		@return モード情報
		*/
		D3DFOGMODE GetTableMode();

		/**
		@brief 頂点モード設定
		@param VertexMode [in] 頂点モード
		*/
		void SetVertexMode(D3DFOGMODE VertexMode);

		/**
		@brief 頂点モードの取得
		@return モード情報
		*/
		D3DFOGMODE GetVertexMode();

		/**
		@brief 効果範囲の設定
		@param start_pos [in] フォグ影響開始地点
		@param end_pos [in]　フォグ完全影響地点
		*/
		void SetEffectRange(float start_pos, float end_pos);

		/**
		@brief 効果範囲の取得
		@return 効果範囲
		*/
		const EffectRangePos& GetEffectRange();

		/**
		@brief 色の設定
		@param color [in] 色
		*/
		void SetColor(const D3DXCOLOR& color);

		/**
		@brief 色の取得
		@return 色
		*/
		const D3DXCOLOR& GetColor();
	private:
		LPDIRECT3DDEVICE9 m_device; // デバイス
		D3DXCOLOR m_color; // 色
		D3DFOGMODE m_vertex_mode; // 頂点モード
		D3DFOGMODE m_table_mode; // テーブルモード
		EffectRangePos m_effect_range; // 効果範囲
		D3DCAPS9 m_caps;
	};
}

_MSLIB_END