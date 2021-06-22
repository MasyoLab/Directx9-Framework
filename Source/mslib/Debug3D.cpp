//==========================================================================
// Debug3D [Debug3D.cpp]
// author : MasyoLab
//==========================================================================
#include "Debug3D.h"

_MSLIB_BEGIN

namespace debug
{
	Debug3D::Debug3D()
	{
		SetComponentName("Debug3D");
#if defined(_MSLIB_DEBUG)
		m_roundX = nullptr;
		m_roundY = nullptr;
		m_lineX = nullptr;
		m_lineY = nullptr;
		m_lineZ = nullptr;
		m_num_line = 0;
		m_num_size = 0;
		m_line_pi = 0.0f;
#endif
	}

	Debug3D::~Debug3D()
	{
#if defined(_MSLIB_DEBUG)
		mslib::_delete(m_roundX);
		mslib::_delete(m_roundY);
		mslib::_delete(m_lineX);
		mslib::_delete(m_lineY);
		mslib::_delete(m_lineZ);
#endif
	}

	void Debug3D::Init()
	{
#if defined(_MSLIB_DEBUG)
		m_transform = GetComponentParent<transform::Transform>();
		if (m_transform == nullptr)
			return;

		// å¸Ç´ÉxÉNÉgÉãèÓïÒ
		constexpr float fPosZ[] = { -1.0f,1.0f,0.8f,0.8f ,1.0f };
		constexpr float fPosX[] = { 0.0f,0.0f,0.1f,-0.1f,0.0f };
		m_num_size = sizeof(fPosZ) / sizeof(float);

		m_num_line = 30;
		m_line_pi = D3DX_PI * 2 / m_num_line;	// â~é¸ó¶

		mslib::_new(m_roundX, m_num_line + 1);
		mslib::_new(m_roundY, m_num_line + 1);
		mslib::_new(m_lineX, m_num_size);
		mslib::_new(m_lineY, m_num_size);
		mslib::_new(m_lineZ, m_num_size);

		// â~ÇÃê∂ê¨
		for (int i = 0; i < (m_num_line + 1); i++)
		{
			m_roundX[i].pos.x = ((0.0f + cosf(m_line_pi * i)));
			m_roundX[i].pos.y = 0.0f;
			m_roundX[i].pos.z = ((0.0f + sinf(m_line_pi * i)));
			m_roundX[i].color = D3DCOLOR_RGBA(255, 0, 0, 255);

			m_roundY[i].pos.x = 0.0f;
			m_roundY[i].pos.y = ((0.0f + cosf(m_line_pi * i)));
			m_roundY[i].pos.z = ((0.0f + sinf(m_line_pi * i)));
			m_roundY[i].color = D3DCOLOR_RGBA(0, 255, 0, 255);
		}

		// ñÓàÛÇÃê∂ê¨
		for (int i = 0; i < m_num_size; i++)
		{
			m_lineX[i].pos.z = fPosX[i];
			m_lineX[i].pos.x = fPosZ[i];
			m_lineX[i].pos.y = 0.0f;
			m_lineX[i].color = D3DCOLOR_RGBA(255, 0, 0, 255);

			m_lineY[i].pos.z = fPosX[i];
			m_lineY[i].pos.x = 0.0f;
			m_lineY[i].pos.y = fPosZ[i];
			m_lineY[i].color = D3DCOLOR_RGBA(0, 255, 0, 255);

			m_lineZ[i].pos.z = -fPosZ[i];
			m_lineZ[i].pos.x = fPosX[i];
			m_lineZ[i].pos.y = 0.0f;
			m_lineZ[i].color = D3DCOLOR_RGBA(0, 0, 255, 255);
		}
#endif
	}

	void Debug3D::Draw(LPDIRECT3DDEVICE9 device)
	{
#if defined(_MSLIB_DEBUG)
		if (m_transform == nullptr)
			return;

		device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		device->SetTransform(D3DTS_WORLD, m_transform->GetWorldMatrix());
		device->SetTexture(0, nullptr);

		// ï`âÊ
		device->DrawPrimitiveUP(D3DPT_LINESTRIP, m_num_line, m_roundX, sizeof(vertex3d::Vertex2));
		device->DrawPrimitiveUP(D3DPT_LINESTRIP, m_num_line, m_roundY, sizeof(vertex3d::Vertex2));
		device->DrawPrimitiveUP(D3DPT_LINESTRIP, (m_num_size - 1), m_lineZ, sizeof(vertex3d::Vertex2));
		device->DrawPrimitiveUP(D3DPT_LINESTRIP, (m_num_size - 1), m_lineX, sizeof(vertex3d::Vertex2));
		device->DrawPrimitiveUP(D3DPT_LINESTRIP, (m_num_size - 1), m_lineY, sizeof(vertex3d::Vertex2));
#else
		device;
#endif
	}

	void Debug3D::GUISystem()
	{
		GUIDebug();
	}
}

_MSLIB_END
