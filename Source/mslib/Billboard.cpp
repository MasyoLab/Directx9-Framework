//==========================================================================
// ビルボード [Billboard.cpp]
// author : MasyoLab
//==========================================================================
#include "Billboard.h"
#include "mslib_struct.h"

_MSLIB_BEGIN

namespace billboard
{
	constexpr float VCRCT = 0.5f;
	constexpr int NumDfaltIndex = 6;

	BillboardData::BillboardData()
	{}

	BillboardData::~BillboardData()
	{
		m_buffer.Release();
	}

	const create_buffer::Buffer& BillboardData::GetBuffer() const
	{
		return m_buffer;
	}

	CreateBillboard::CreateBillboard() :
		m_device(nullptr), m_hwnd(nullptr)
	{
		SetComponentName("CreateBillboard");
	}

	CreateBillboard::CreateBillboard(LPDIRECT3DDEVICE9 device, HWND hwnd) :
		m_device(device), m_hwnd(hwnd)
	{
		SetComponentName("CreateBillboard");
	}

	CreateBillboard::~CreateBillboard()
	{
		DestroyComponent();
	}

	BillboardReference CreateBillboard::Create()
	{
		if ((int)m_resource_list.size() != 0)
			return m_resource_list.begin()->second;

		vertex3d::Vertex4* pseudo = nullptr;
		WORD* index = nullptr;

		auto vertex_buffer = CreateVertexBuffer(m_device, m_hwnd, sizeof(vertex3d::Vertex4) * 4, D3DUSAGE_WRITEONLY, vertex3d::FVFVertex4, D3DPOOL_MANAGED, nullptr);
		if (vertex_buffer != nullptr)
		{
			vertex_buffer->Lock(0, 0, (void**)& pseudo, D3DLOCK_DISCARD);
			CreateVertex(pseudo);
			vertex_buffer->Unlock();
		}

		auto index_buffer = CreateIndexBuffer(m_device, m_hwnd, sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, nullptr);
		if (index_buffer != nullptr)
		{
			index_buffer->Lock(0, 0, (void**)& index, D3DLOCK_DISCARD);
			CreateIndex(index, 1);
			index_buffer->Unlock();
		}

		return m_resource_list[std::to_string(typeid(BillboardData).hash_code())] =
			BillboardData::Create(new BillboardDataInput(
				create_buffer::Buffer(vertex_buffer, index_buffer),
				std::to_string(typeid(BillboardData).hash_code()),
				ThisComponent<Loader>()));
	}

	void CreateBillboard::CreateVertex(vertex3d::Vertex4* pOut)
	{
		auto uv = floatUV(0.0f, 0.0f, 1.0f, 1.0f); // UV

		vertex3d::Vertex4 vVertex[] =
		{
			// 手前
			{ D3DXVECTOR3(-VCRCT, VCRCT,0.0f),D3DXVECTOR3(0,0,-1),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(uv.u0,uv.v0) }, // 左上
			{ D3DXVECTOR3(VCRCT, VCRCT,0.0f),D3DXVECTOR3(0,0,-1),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(uv.u1,uv.v0) }, // 右上
			{ D3DXVECTOR3(VCRCT,-VCRCT,0.0f),D3DXVECTOR3(0,0,-1),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(uv.u1,uv.v1) }, // 右下
			{ D3DXVECTOR3(-VCRCT,-VCRCT,0.0f),D3DXVECTOR3(0,0,-1),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(uv.u0,uv.v1) }, // 左下
		};

		for (int i = 0; i < (int)(sizeof(vVertex) / sizeof(vertex3d::Vertex4)); i++)
			pOut[i] = vVertex[i];
	}

	void CreateBillboard::CreateIndex(WORD* pOut, int num)
	{
		for (int i = 0, s = 0, ncount = 0; i < NumDfaltIndex * num; i++, s++, ncount++)
		{
			switch (ncount)
			{
			case 3:
				s -= 3;
				break;
			case 4:
				s += 1;
				break;
			case 6:
				ncount = 0;
				break;
			default:
				break;
			}
			pOut[i] = (WORD)s;
		}
	}

	SetBillboard::SetBillboard()
	{}

	SetBillboard::~SetBillboard()
	{}

	void SetBillboard::SetBillboardData(const BillboardReference& data)
	{
		m_billboard_data = data;
	}

	BillboardReference SetBillboard::GetBillboardData() const
	{
		return m_billboard_data;
	}

	CreateBillboard::BillboardDataInput::BillboardDataInput()
	{}

	CreateBillboard::BillboardDataInput::BillboardDataInput(const create_buffer::Buffer& buffer, const std::string& tag, resource_loader::LoaderReference loader)
	{
		m_buffer = buffer;
		m_tag = tag;
		m_loader_ptr = loader;
	}

	CreateBillboard::BillboardDataInput::~BillboardDataInput()
	{}
}
_MSLIB_END