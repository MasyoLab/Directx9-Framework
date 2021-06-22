//==========================================================================
// Debug3D [Debug3D.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "mslib.hpp"
#include "Debug.h"
#include "Transform.h"
#include "Vertex3d.h"

_MSLIB_BEGIN

namespace debug
{
	//==========================================================================
	//
	// class : Debug3D
	// Content : 3Dデバッグ機能
	//
	//==========================================================================
	class Debug3D final:
		public Debug
	{
	private:
		Debug3D(const Debug3D&) = delete;
		Debug3D(Debug3D&&) = delete;
		Debug3D& operator=(const Debug3D&) = delete;
		Debug3D& operator=(Debug3D&&) = delete;
	public:
		Debug3D();
		~Debug3D();
	private:
		/**
		@brief 初期化
		*/
		virtual void Init() override;

		/**
		@brief デバッグ描画
		@param device [in] デバイス
		*/
		virtual void Draw(LPDIRECT3DDEVICE9 device) override;

		/**
		@brief GUI
		*/
		virtual void GUISystem() override;
	private:
#if defined(_MSLIB_DEBUG)
		transform::TransformReference m_transform;
		vertex3d::Vertex2* m_roundX;
		vertex3d::Vertex2* m_roundY;
		vertex3d::Vertex2* m_lineX;
		vertex3d::Vertex2* m_lineY;
		vertex3d::Vertex2* m_lineZ;
		int m_num_line; // 線の長さ
		int m_num_size;
		float m_line_pi; // 円周率
#endif
	};
}

_MSLIB_END