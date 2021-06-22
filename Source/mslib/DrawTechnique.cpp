//==========================================================================
// 描画テクニック [DrawTechnique.cpp]
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
		// 半加算合成
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE); //アルファブレンディングの有効化
		device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //ブレンディングオプション加算
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //SRCの設定
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//DESTの設定
		device->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); //アルファテストの無効化
		device->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
	}

	void DrawTechnique::TechniqueAlpharefStart(LPDIRECT3DDEVICE9 device, int Power)
	{
		device->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE); //アルファテストの有効化
		device->SetRenderState(D3DRS_ALPHAREF, Power); //アルファ参照値
		device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL); //アルファテスト合格基準
	}

	void DrawTechnique::TechniqueAlpharefEnd(LPDIRECT3DDEVICE9 device)
	{
		device->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); // αテスト
	}

	void DrawTechnique::TechniqueSub(LPDIRECT3DDEVICE9 device)
	{
		// 全加算合成
		device->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE); //アルファブレンディングの有効化
		device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //ブレンディングオプション加算
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	//SRCの設定
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE); //DESTの設定
		device->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); //アルファテストの無効化
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