//==========================================================================
// 画像の品質調整 [SamplerState.cpp]
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
		pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE); // 小さくなった時に白枠
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE); // 常に白枠
		pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); // 元のサイズより小さい時綺麗にする
	}

	void SamplerState::SamplerFitteringLINEAR(LPDIRECT3DDEVICE9 pDevice)
	{
		pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); // 小さくなった時に白枠
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // 常に白枠
		pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR); // 元のサイズより小さい時綺麗にする
	}

	void SamplerState::SamplerFitteringGraphical(LPDIRECT3DDEVICE9 pDevice)
	{
		pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); // 小さくなった時に白枠
		pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // 常に白枠
		pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE); // 元のサイズより小さい時綺麗にする
	}
}

_MSLIB_END