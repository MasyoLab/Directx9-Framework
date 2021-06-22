//==========================================================================
// フォグ [Fog.cpp]
// author : MasyoLab
//==========================================================================
#include "Fog.h"

_MSLIB_BEGIN

namespace fog
{
	Fog::Fog(LPDIRECT3DDEVICE9 pDevice) :
		Component("Fog"), m_device(pDevice), m_color(255), m_vertex_mode(D3DFOGMODE::D3DFOG_NONE),
		m_table_mode(D3DFOGMODE::D3DFOG_NONE), m_effect_range(0, 0)
	{
		ZeroMemory(&m_caps, sizeof(m_caps));    //初期化
	}

	Fog::~Fog()
	{
		OFF();
	}

	void Fog::Init(const D3DXCOLOR& color, float start_pos, float end_pos, D3DFOGMODE VertexMode, D3DFOGMODE TableMode)
	{
		m_color = color;
		m_effect_range = EffectRangePos(start_pos, end_pos);
		m_vertex_mode = VertexMode;
		m_table_mode = TableMode;

		ON();
		m_device->GetDeviceCaps(&m_caps);
		m_device->SetRenderState(D3DRS_FOGCOLOR, m_color); //白色で不透明
		m_device->SetRenderState(D3DRS_FOGVERTEXMODE, m_vertex_mode); //頂点モード
		m_device->SetRenderState(D3DRS_FOGTABLEMODE, m_table_mode); //テーブルモード
		m_device->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&m_effect_range.start)); //開始位置
		m_device->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&m_effect_range.end)); //終了位置
	}

	void Fog::ON()
	{
		m_device->SetRenderState(D3DRS_FOGENABLE, D3DZB_TRUE);
	}

	void Fog::OFF()
	{
		m_device->SetRenderState(D3DRS_FOGENABLE, D3DZB_FALSE);
	}

	void Fog::SetTableMode(D3DFOGMODE TableMode)
	{
		m_table_mode = TableMode;
	}

	D3DFOGMODE Fog::GetTableMode()
	{
		return m_table_mode;
	}

	void Fog::SetVertexMode(D3DFOGMODE VertexMode)
	{
		m_vertex_mode = VertexMode;
	}

	D3DFOGMODE Fog::GetVertexMode()
	{
		return m_vertex_mode;
	}

	void Fog::SetEffectRange(float start_pos, float end_pos)
	{
		m_effect_range = EffectRangePos(start_pos, end_pos);
	}

	const EffectRangePos& Fog::GetEffectRange()
	{
		return m_effect_range;
	}

	void Fog::SetColor(const D3DXCOLOR& color)
	{
		m_color = color;
	}

	const D3DXCOLOR& Fog::GetColor()
	{
		return m_color;
	}
}

_MSLIB_END