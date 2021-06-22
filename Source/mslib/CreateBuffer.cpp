//==========================================================================
// クリエイトバッファ [CreateBuffer.cpp]
// author : MasyoLab
//==========================================================================
#include "CreateBuffer.h"

_MSLIB_BEGIN

namespace create_buffer
{
	Buffer::Buffer() :
		VertexBuffer(nullptr), IndexBuffer(nullptr)
	{
	}

	Buffer::Buffer(LPDIRECT3DVERTEXBUFFER9 _vertex, LPDIRECT3DINDEXBUFFER9 _index) :
		VertexBuffer(_vertex), IndexBuffer(_index)
	{
	}

	Buffer::~Buffer()
	{
	}

	void Buffer::Release()
	{
		if (VertexBuffer != nullptr)
			VertexBuffer->Release();
		if (IndexBuffer != nullptr)
			IndexBuffer->Release();
		IndexBuffer = nullptr;
		VertexBuffer = nullptr;
	}

	LPDIRECT3DVERTEXBUFFER9 Buffer::GetVertexBuffer() const
	{
		return VertexBuffer;
	}

	LPDIRECT3DINDEXBUFFER9 Buffer::GetIndexBuffer() const
	{
		return IndexBuffer;
	}

	CreateBuffer::CreateBuffer()
	{
	}

	CreateBuffer::~CreateBuffer()
	{
	}

	LPDIRECT3DVERTEXBUFFER9 CreateBuffer::CreateVertexBuffer(LPDIRECT3DDEVICE9 pDevice, HWND hWid, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, HANDLE* pSharedHandle)
	{
		LPDIRECT3DVERTEXBUFFER9 vertex_buffer = nullptr;
		if (FAILED(pDevice->CreateVertexBuffer(Length, Usage, FVF, Pool, &vertex_buffer, pSharedHandle)))
			MessageBox(hWid, "頂点バッファが作れませんでした。", "ERROR", MB_OK | MB_ICONEXCLAMATION | MB_ICONWARNING);
		return vertex_buffer;
	}

	LPDIRECT3DINDEXBUFFER9 CreateBuffer::CreateIndexBuffer(LPDIRECT3DDEVICE9 pDevice, HWND hWid, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, HANDLE* pSharedHandle)
	{
		LPDIRECT3DINDEXBUFFER9 index_buffer = nullptr;
		if (FAILED(pDevice->CreateIndexBuffer(Length, Usage, Format, Pool, &index_buffer, pSharedHandle)))
			MessageBox(hWid, "インデックスバッファが作れませんでした。", "ERROR", MB_OK | MB_ICONEXCLAMATION | MB_ICONWARNING);
		return index_buffer;
	}
}
_MSLIB_END