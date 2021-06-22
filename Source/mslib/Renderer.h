//==========================================================================
// Renderer [Renderer.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Component.h"
#include "Activity.h"
#include "RenderState.h"

_MSLIB_BEGIN

namespace renderer
{
	// RendererID
	enum class RendererID : int
	{
		Begin = -1,
		Object, // オブジェクト
		Grid, // グリッド
		Field, // フィールド
		Cube, // キューブ
		Shadow, // 影
		Sphere, // 球体
		Xmodel, // Xモデル
		Mesh, // メッシュ
		Billboard, // ビルボード
		Effect, // エフェクト
		Text, // テキスト
		End,
	};

	//==========================================================================
	//
	// class : Renderer
	// Content : 描画機能
	//
	//==========================================================================
	class Renderer :
		virtual public activity::Activity,
		private render_state::RenderState
	{
	private:
		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) = delete;
	public:
		Renderer(RendererID id);
		virtual ~Renderer();

		/**
		@brief 描画リストを一気に描画
		@param device [in] デバイス
		*/
		static void DrawAll(LPDIRECT3DDEVICE9 device);

		RendererID GetRendererID();
	protected:
		/**
		@brief 描画
		@param device [in] デバイス
		*/
		virtual void Draw(LPDIRECT3DDEVICE9 device);
	private:
		/**
		@brief 描画機能を切り替えます
		@param device [in] デバイス
		*/
		static void ChangeRender(LPDIRECT3DDEVICE9 device, RendererID id);
	private:
		RendererID m_renderer_id;
		static RendererID m_serect_renderer;
		static std::unordered_map<RendererID, std::list<Renderer*>> m_renderers; // 描画対象リスト
	};

	using RendererReference = reference::IReference<Renderer>;
}

_MSLIB_END