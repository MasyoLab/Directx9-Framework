//==========================================================================
// Vertex [Vertex3d.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"

_MSLIB_BEGIN

namespace vertex3d
{
	struct Vertex4
	{
		D3DXVECTOR3 pos; // ���W
		D3DXVECTOR3 normal; // �@��
		D3DCOLOR color;  // �F
		D3DXVECTOR2 tex; // ���_
	};

	struct Vertex3
	{
		D3DXVECTOR4 pos; // ���W
		D3DCOLOR color;  // �F
		D3DXVECTOR2 tex; // ���_
	};

	struct Vertex2
	{
		D3DXVECTOR3 pos; // ���W�ϊ����K�v
		D3DCOLOR color; // �|���S���̐F
	};

	constexpr DWORD FVFVertex4 = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	constexpr DWORD FVFVertex3 = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	constexpr DWORD FVFVertex2 = (D3DFVF_XYZ | D3DFVF_DIFFUSE);
}

_MSLIB_END