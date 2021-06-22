//==========================================================================
// グリッド [Grid.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "GameObject.h"
#include "Vertex3d.h"
#include "Renderer.h"

_MSLIB_BEGIN

namespace object
{
	//==========================================================================
	//
	// class : Grid
	// Content : グリッド
	//
	//==========================================================================
	class Grid :
		public GameObject,
		public renderer::Renderer
	{
	private:
		Grid(const Grid&) = delete;
		Grid(Grid&&) = delete;
		Grid& operator=(const Grid&) = delete;
		Grid& operator=(Grid&&) = delete;
	public:
		Grid(int scale);
		virtual ~Grid();

		/**
		@brief 初期化
		@param scale [in] グリッドの表示範囲指定
		*/
		void Init(int scale);

		/**
		@brief 解放
		*/
		void Release();
	protected:
		/**
		@brief 描画
		@param device [in] デバイス
		*/
		void Draw(LPDIRECT3DDEVICE9 device) override;
	private:
		D3DXMATRIX m_world_matrix; // ワールド行列
		vertex3d::Vertex2* m_pos; // 頂点の作成
		int m_num; // 線の本数管理
		int m_scale; // サイズの記録
	};
}

_MSLIB_END