//==========================================================================
// �O���b�h [Grid.h]
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
	// Content : �O���b�h
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
		@brief ������
		@param scale [in] �O���b�h�̕\���͈͎w��
		*/
		void Init(int scale);

		/**
		@brief ���
		*/
		void Release();
	protected:
		/**
		@brief �`��
		@param device [in] �f�o�C�X
		*/
		void Draw(LPDIRECT3DDEVICE9 device) override;
	private:
		D3DXMATRIX m_world_matrix; // ���[���h�s��
		vertex3d::Vertex2* m_pos; // ���_�̍쐬
		int m_num; // ���̖{���Ǘ�
		int m_scale; // �T�C�Y�̋L�^
	};
}

_MSLIB_END