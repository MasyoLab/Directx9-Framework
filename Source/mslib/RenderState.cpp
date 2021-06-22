//==========================================================================
// �����_�[�X�e�[�g [RenderState.cpp]
// author : MasyoLab
//==========================================================================
#include "RenderState.h"

_MSLIB_BEGIN

namespace render_state
{
	RenderState::RenderState()
	{
	}

	RenderState::~RenderState()
	{
	}

	void RenderState::SetRenderREVSUBTRACT(LPDIRECT3DDEVICE9 pDevice)
	{
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE); //�A���t�@�u�����f�B���O�̗L����
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); // ���\�[�X�J���[�̎w��
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT); // �u�����f�B���O����
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); //�A���t�@�e�X�g�̖�����
	}

	void RenderState::SetRenderADD(LPDIRECT3DDEVICE9 pDevice)
	{
		// �����Z����
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE); //�A���t�@�u�����f�B���O�̗L����
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //�u�����f�B���O�I�v�V�������Z
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //SRC�̐ݒ�
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//DEST�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); //�A���t�@�e�X�g�̖�����
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
	}

	void RenderState::SetRenderALPHAREF_START(LPDIRECT3DDEVICE9 pDevice, int Power)
	{
		// ���e�X�g�ɂ�铧���̈�̐؂蔲��

		//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE); //�A���t�@�e�X�g�̗L����
		//pDevice->SetRenderState(D3DRS_ALPHAREF, Power); //�A���t�@�Q�ƒl
		//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL); //�A���t�@�e�X�g���i�
		//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_FALSE); //�A���t�@�u�����f�B���O�̖�����

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE); //�A���t�@�e�X�g�̗L����
		pDevice->SetRenderState(D3DRS_ALPHAREF, Power); //�A���t�@�Q�ƒl
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL); //�A���t�@�e�X�g���i�
	}

	void RenderState::SetRenderALPHAREF_END(LPDIRECT3DDEVICE9 pDevice)
	{
		//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE); // ���u�����h������
		//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); // ���e�X�g

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); // ���e�X�g
	}

	void RenderState::SetRenderSUB(LPDIRECT3DDEVICE9 pDevice)
	{
		// �S���Z����
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE); //�A���t�@�u�����f�B���O�̗L����
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //�u�����f�B���O�I�v�V�������Z
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	//SRC�̐ݒ�
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE); //DEST�̐ݒ�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); //�A���t�@�e�X�g�̖�����
	}

	void RenderState::SetRenderZENABLE_START(LPDIRECT3DDEVICE9 pDevice)
	{
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	}

	void RenderState::SetRenderZENABLE_END(LPDIRECT3DDEVICE9 pDevice)
	{
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}

	void RenderState::SetRenderZWRITEENABLE_START(LPDIRECT3DDEVICE9 pDevice)
	{
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);
	}

	void RenderState::SetRenderZWRITEENABLE_END(LPDIRECT3DDEVICE9 pDevice)
	{
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
	}

	void RenderState::SetRenderWIREFRAME(LPDIRECT3DDEVICE9 pDevice)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	void RenderState::SetRenderSOLID(LPDIRECT3DDEVICE9 pDevice)
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
}

_MSLIB_END