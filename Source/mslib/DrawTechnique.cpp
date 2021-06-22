//==========================================================================
// �`��e�N�j�b�N [DrawTechnique.cpp]
// author : MasyoLab
//==========================================================================
#include "DrawTechnique.h"

_MSLIB_BEGIN

namespace draw_technique
{
	DrawTechnique::DrawTechnique() :
		m_sub_flag(false)
	{
	}

	DrawTechnique::~DrawTechnique()
	{
	}

	void DrawTechnique::SetAdditiveSynthesis(bool _synt)
	{
		m_sub_flag = _synt;
	}

	bool DrawTechnique::GetAdditiveSynthesis()
	{
		return m_sub_flag;
	}

	void DrawTechnique::TechniqueAdd(LPDIRECT3DDEVICE9 device)
	{
		// �����Z����
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE); //�A���t�@�u�����f�B���O�̗L����
		device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //�u�����f�B���O�I�v�V�������Z
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //SRC�̐ݒ�
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//DEST�̐ݒ�
		device->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); //�A���t�@�e�X�g�̖�����
		device->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
	}

	void DrawTechnique::TechniqueAlpharefStart(LPDIRECT3DDEVICE9 device, int Power)
	{
		device->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE); //�A���t�@�e�X�g�̗L����
		device->SetRenderState(D3DRS_ALPHAREF, Power); //�A���t�@�Q�ƒl
		device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL); //�A���t�@�e�X�g���i�
	}

	void DrawTechnique::TechniqueAlpharefEnd(LPDIRECT3DDEVICE9 device)
	{
		device->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); // ���e�X�g
	}

	void DrawTechnique::TechniqueSub(LPDIRECT3DDEVICE9 device)
	{
		// �S���Z����
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE); //�A���t�@�u�����f�B���O�̗L����
		device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //�u�����f�B���O�I�v�V�������Z
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	//SRC�̐ݒ�
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE); //DEST�̐ݒ�
		device->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); //�A���t�@�e�X�g�̖�����
	}

	void DrawTechnique::TechniqueZwriteenableStart(LPDIRECT3DDEVICE9 device)
	{
		device->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);
	}

	void DrawTechnique::TechniqueZwriteenableEnd(LPDIRECT3DDEVICE9 device)
	{
		device->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
	}
}

_MSLIB_END