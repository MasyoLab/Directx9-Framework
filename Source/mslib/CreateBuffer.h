//==========================================================================
// CreateBuffer [CreateBuffer.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"

_MSLIB_BEGIN

namespace create_buffer
{
	//==========================================================================
	//
	// class : Buffer
	// Content : �o�b�t�@
	//
	//==========================================================================
	class Buffer
	{
	public:
		Buffer();
		Buffer(LPDIRECT3DVERTEXBUFFER9 _vertex, LPDIRECT3DINDEXBUFFER9 _index);
		~Buffer();
		void Release();
		LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer() const;
		LPDIRECT3DINDEXBUFFER9 GetIndexBuffer() const;
	protected:
		LPDIRECT3DVERTEXBUFFER9 VertexBuffer; // �o�[�e�b�N�X�o�b�t�@
		LPDIRECT3DINDEXBUFFER9 IndexBuffer; // �C���f�b�N�X�o�b�t�@
	};

	//==========================================================================
	//
	// class : CreateBuffer
	// Content : �N���G�C�g�o�b�t�@
	//
	//==========================================================================
	class CreateBuffer
	{
	public:
		CreateBuffer();
		~CreateBuffer();
	protected:
		/**
		@brief �o�[�e�b�N�X�o�b�t�@�̐���
		@param pDevice [in] �f�o�C�X
		@param hWid [in] �E�B���h�E�n���h��
		@param Length [in] �f�[�^�^�̃T�C�Y
		@param Usage [in] Usages for Vertex/Index buffers
		@param FVF [in] FVF
		@param Pool [in] Pool types
		@param pSharedHandle [in] Handle to an Object
		@return vertex buffer
		*/
		LPDIRECT3DVERTEXBUFFER9 CreateVertexBuffer(LPDIRECT3DDEVICE9 pDevice, HWND hWid, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, HANDLE* pSharedHandle);

		/**
		@brief �C���f�b�N�X�o�b�t�@�̐���
		@param pDevice [in] �f�o�C�X
		@param hWid [in] �E�B���h�E�n���h��
		@param Length [in] �f�[�^�^�̃T�C�Y
		@param Usage [in] Usages for Vertex/Index buffers
		@param Format [in] D3D9Ex only
		@param Pool [in] Pool types
		@param pSharedHandle [in] Handle to an Object
		@return index buffer
		*/
		LPDIRECT3DINDEXBUFFER9 CreateIndexBuffer(LPDIRECT3DDEVICE9 pDevice, HWND hWid, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, HANDLE* pSharedHandle);
	};
}

_MSLIB_END