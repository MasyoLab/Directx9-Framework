//==========================================================================
// �摜�̕i������ [SamplerState.cpp]
// author : MasyoLab
//==========================================================================
#include "SamplerState.h"

_MSLIB_BEGIN

namespace sampler_state
{
	SamplerState::SamplerState()
	{
	}

	SamplerState::~SamplerState()
	{
	}

	void SamplerState::SamplerFitteringNONE(LPDIRECT3DDEVICE9 pDevice)
	{
		pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE); // �������Ȃ������ɔ��g
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE); // ��ɔ��g
		pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); // ���̃T�C�Y��菬�������Y��ɂ���
	}

	void SamplerState::SamplerFitteringLINEAR(LPDIRECT3DDEVICE9 pDevice)
	{
		pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); // �������Ȃ������ɔ��g
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // ��ɔ��g
		pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR); // ���̃T�C�Y��菬�������Y��ɂ���
	}

	void SamplerState::SamplerFitteringGraphical(LPDIRECT3DDEVICE9 pDevice)
	{
		pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); // �������Ȃ������ɔ��g
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // ��ɔ��g
		pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); // ���̃T�C�Y��菬�������Y��ɂ���
	}
}

_MSLIB_END