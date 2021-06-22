//==========================================================================
// �O���b�h [Grid.cpp]
// author : MasyoLab
//==========================================================================
#include "Grid.h"

_MSLIB_BEGIN

namespace object
{
	using renderer::RendererID;

	Grid::Grid(int scale) :
		Renderer(RendererID::Grid), m_pos(nullptr), m_num(0), m_scale(0)
	{
		SetComponentName("Grid");
		Init(scale);
		SetActivity(true);
		D3DXMatrixIdentity(&m_world_matrix);
	}

	Grid::~Grid()
	{
		Release();
	}

	void Grid::Init(int scale)
	{
		m_scale = scale; // �T�C�Y�̋L�^
		m_num = 4; // �\������邽�߂̐�
		float X = (float)m_scale; // �T�C�Y�̋L�^
		float Z = (float)m_scale; // �T�C�Y�̋L�^

		// �T�C�Y���̊O�g�̐���ǉ�
		for (int i = 0; i < m_scale; i++)
			m_num += 8;

		Release();

		m_pos = new vertex3d::Vertex2[m_num];

		int nNumLine = (int)(m_num / 2);

		for (int i = 0; i < nNumLine; i += 2, X--, Z--)
		{
			m_pos[i].pos = D3DXVECTOR3(1.0f * X, 0.0f, (float)m_scale); // x���W�ɐ�
			m_pos[i + 1].pos = D3DXVECTOR3(1.0f * X, 0.0f, -(float)m_scale); // x���W�ɐ�
			m_pos[nNumLine + i].pos = D3DXVECTOR3((float)m_scale, 0.0f, 1.0f * Z); // z���W�ɐ�
			m_pos[nNumLine + i + 1].pos = D3DXVECTOR3(-(float)m_scale, 0.0f, 1.0f * Z); // z���W�ɐ�

			m_pos[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			m_pos[i + 1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			m_pos[nNumLine + i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
			m_pos[nNumLine + i + 1].color = D3DCOLOR_RGBA(255, 255, 255, 255);

			if (i == (int)((float)m_scale * 2))
			{
				m_pos[i].color = D3DCOLOR_RGBA(255, 0, 0, 255);
				m_pos[i + 1].color = D3DCOLOR_RGBA(255, 0, 0, 255);
				m_pos[nNumLine + i].color = D3DCOLOR_RGBA(255, 0, 0, 255);
				m_pos[nNumLine + i + 1].color = D3DCOLOR_RGBA(255, 0, 0, 255);
			}
		}
	}

	void Grid::Release()
	{
		mslib::_delete(m_pos);
	}

	void Grid::Draw(LPDIRECT3DDEVICE9 device)
	{
		// �e��s��̐ݒ�
		device->SetTransform(D3DTS_WORLD, &m_world_matrix);

		// FVF�̐ݒ�
		device->SetFVF(vertex3d::FVFVertex2);

		device->SetTexture(0, nullptr);
		device->DrawPrimitiveUP(D3DPT_LINELIST, (int)(m_num / 2), m_pos, sizeof(vertex3d::Vertex2));
	}
}

_MSLIB_END