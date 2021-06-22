//==========================================================================
// レンダーステート [RenderState.cpp]
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
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE); //アルファブレンディングの有効化
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); // αソースカラーの指定
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT); // ブレンディング処理
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); //アルファテストの無効化
	}

	void RenderState::SetRenderADD(LPDIRECT3DDEVICE9 pDevice)
	{
		// 半加算合成
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE); //アルファブレンディングの有効化
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //ブレンディングオプション加算
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //SRCの設定
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//DESTの設定
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); //アルファテストの無効化
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
	}

	void RenderState::SetRenderALPHAREF_START(LPDIRECT3DDEVICE9 pDevice, int Power)
	{
		// αテストによる透明領域の切り抜き

		//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE); //アルファテストの有効化
		//pDevice->SetRenderState(D3DRS_ALPHAREF, Power); //アルファ参照値
		//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL); //アルファテスト合格基準
		//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_FALSE); //アルファブレンディングの無効化

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE); //アルファテストの有効化
		pDevice->SetRenderState(D3DRS_ALPHAREF, Power); //アルファ参照値
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL); //アルファテスト合格基準
	}

	void RenderState::SetRenderALPHAREF_END(LPDIRECT3DDEVICE9 pDevice)
	{
		//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE); // αブレンドを許可
		//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); // αテスト

		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); // αテスト
	}

	void RenderState::SetRenderSUB(LPDIRECT3DDEVICE9 pDevice)
	{
		// 全加算合成
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, D3DZB_TRUE); //アルファブレンディングの有効化
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //ブレンディングオプション加算
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	//SRCの設定
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE); //DESTの設定
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_FALSE); //アルファテストの無効化
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