//==========================================================================
// RectTransform [RectTransform.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Transform.h"

_MSLIB_BEGIN

namespace transform
{
	class RectTransform :
		public Transform
	{
	private:
		RectTransform(const RectTransform&) = delete;
		RectTransform(RectTransform&&) = delete;
		RectTransform& operator=(const RectTransform&) = delete;
		RectTransform& operator=(RectTransform&&) = delete;
	public:
		RectTransform();
		~RectTransform();

		/**
		@brief ポリゴンのサイズの取得
		@return ポリゴンのサイズ
		*/
		const D3DXVECTOR2& GetPolygonSize() const;

		/**
		@brief ポリゴンのサイズの登録
		@param x [in] X軸のサイズ
		@param y [in] Y軸のサイズ
		*/
		void SetPolygonSize(float x, float y);

		/**
		@brief ポリゴンのサイズの登録
		@param size [in] サイズ
		*/
		void SetPolygonSize(const D3DXVECTOR2& _size);

		/**
		@brief ポリゴンのサイズの加算
		@param x [in] X軸のサイズ
		@param y [in] Y軸のサイズ
		*/
		void AddPolygonSize(float x, float y);

		/**
		@brief ポリゴンのサイズの加算
		@param size [in] サイズ
		*/
		void AddPolygonSize(const D3DXVECTOR2& _size);

		/**
		@brief ピボットの取得
		@return 回転軸
		*/
		const D3DXVECTOR2& GetPivot() const;

		/**
		@brief ピボットの登録
		@param x [in] 回転X軸(0～1)
		@param y [in] 回転Y軸(0～1)
		*/
		void SetPivot(float x, float y);

		/**
		@brief ピボットの登録
		@param pivot [in] 回転軸の位置(0～1)
		*/
		void SetPivot(const D3DXVECTOR2& _pivot);

		/**
		@brief ピボットの加算
		@param x [in] 回転X軸(0～1)
		@param y [in] 回転Y軸(0～1)
		*/
		void AddPivot(float x, float y);

		/**
		@brief ピボットの加算
		@param pivot [in] 回転軸の位置(0～1)
		*/
		void AddPivot(const D3DXVECTOR2& _pivot);

		/**
		@brief グローバルマトリクスの生成
		@return マトリクス
		*/
		D3DXMATRIX* CreateWorldMatrix() override;

		/**
		@brief ローカルマトリクスの生成
		@return マトリクス
		*/
		D3DXMATRIX* CreateLocalMatrix() override;

		/**
		@brief RectTransform のコピー
		*/
		void CopyRectTransform(reference::IReference<RectTransform> _rect);
	protected:
		void GUIRectTransform();
		void InputDataRectTransform(std::ifstream& _ifstream);
		void OutputDataRectTransform(std::ofstream& _ofstream);
	private:
		/**
		@brief 自身のポインタ
		*/
		RectTransform* GetThisPtr();
	private:
		D3DXVECTOR2 m_polygon; // ポリゴンサイズ
		D3DXVECTOR2 m_pivot; // ピボット
		D3DXMATRIX m_not_polygon_matrix; // ワールド空間を基準としたポリゴンサイズを含めない姿勢
		reference::IReference<RectTransform> m_rect_transform_parent;
	};

	using RectTransformReference = reference::IReference<RectTransform>;
}

_MSLIB_END