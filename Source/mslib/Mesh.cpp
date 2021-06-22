//==========================================================================
// メッシュ [Mesh.cpp]
// author : MasyoLab
//==========================================================================
#include "Mesh.h"

_MSLIB_BEGIN

namespace mesh
{
	const std::string create_key(int x, int z);
	const std::string create_key(int x, int z)
	{
		return std::to_string(x) + ":" + std::to_string(z);
	}

	MeshData::MeshData() :
		m_info(), m_createID(0)
	{
	}

	MeshData::~MeshData()
	{
		m_buffer.Release();
	}

	const MeshInfo& MeshData::GetInfo() const
	{
		return m_info;
	}

	int64_t MeshData::GetID() const
	{
		return m_createID;
	}

	const create_buffer::Buffer& MeshData::GetBuffer() const
	{
		return m_buffer;
	}

	CreateMesh::CreateMesh() :
		m_device(nullptr), m_hwnd(nullptr), m_createIDCount(0)
	{
		SetComponentName("CreateMesh");
	}

	CreateMesh::CreateMesh(LPDIRECT3DDEVICE9 device, HWND hWnd) :
		m_device(device), m_hwnd(hWnd), m_createIDCount(0)
	{
		SetComponentName("CreateMesh");
	}

	CreateMesh::~CreateMesh()
	{
		DestroyComponent();
	}

	MeshReference CreateMesh::Create(int x, int z)
	{
		auto str_name = create_key(x, z);

		auto itr = m_resource_list.find(str_name);
		if (itr != m_resource_list.end())
			return itr->second;

		vertex3d::Vertex4* pPseudo = nullptr;
		LPWORD* pIndex = nullptr;

		auto info = MeshInfo(x, z);
		auto vertex_buffer = CreateVertexBuffer(m_device, m_hwnd, sizeof(vertex3d::Vertex4) * info.MaxVertex, D3DUSAGE_WRITEONLY, vertex3d::FVFVertex4, D3DPOOL_MANAGED, nullptr);
		if (vertex_buffer != nullptr)
		{
			vertex_buffer->Lock(0, 0, (void**)& pPseudo, D3DLOCK_DISCARD);
			CreateVertex(pPseudo, info);
			vertex_buffer->Unlock();
		}

		auto index_buffer = CreateIndexBuffer(m_device, m_hwnd, sizeof(LPWORD) * info.MaxIndex, D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, nullptr);
		if (index_buffer != nullptr)
		{
			index_buffer->Lock(0, 0, (void**)& pIndex, D3DLOCK_DISCARD);
			CreateIndex(pIndex, info);
			index_buffer->Unlock();
		}

		m_createIDCount++;

		return m_resource_list[str_name]
			= MeshData::Create(new MeshDataInput(
				m_createIDCount,
				info,
				create_buffer::Buffer(vertex_buffer, index_buffer),
				str_name,
				ThisComponent<Loader>()));
	}

	void CreateMesh::CreateIndex(LPWORD* Output, const MeshInfo& Input)
	{
		for (int i = 0, Index1 = 0, Index2 = Input.NumXVertex, Overlap = 0; i < Input.MaxIndex; Index1++, Index2++)
		{
			// 通常頂点
			Output[i] = (LPWORD)Index2;
			i++;

			// 重複点
			if (Overlap == Input.NumXVertexWey && i < Input.MaxIndex)
			{
				Output[i] = (LPWORD)Index2;
				i++;
				Overlap = 0;
			}

			// 通常頂点
			Output[i] = (LPWORD)Index1;
			i++;

			Overlap += 2;

			// 重複点
			if (Overlap == Input.NumXVertexWey && i < Input.MaxIndex)
			{
				Output[i] = (LPWORD)Index1;
				i++;
			}
		}
	}

	void CreateMesh::CreateVertex(vertex3d::Vertex4* Output, const MeshInfo& Input)
	{
		bool bZ = false;
		bool bX = false;
		float fPosZ = Input.NumMeshZ * 0.5f;
		float fPosX = 0.0f;

		for (int iZ = 0; iZ < Input.NumZVertex; iZ++, fPosZ--)
		{
			bX = true;
			fPosX = -(Input.NumMeshX * 0.5f);
			for (int iX = 0; iX < Input.NumXVertex; iX++, fPosX++, Output++)
			{
				Output->pos = D3DXVECTOR3(fPosX, 0.0f, fPosZ);
				Output->color = D3DCOLOR_RGBA(255, 255, 255, 255);
				Output->tex = D3DXVECTOR2((FLOAT)bX, (FLOAT)bZ);
				Output->normal = D3DXVECTOR3(0, 1, 0);
				bX = bX ^ 1;
			}
			bZ = bZ ^ 1;
		}
	}

	SetMesh::SetMesh()
	{
	}

	SetMesh::~SetMesh()
	{
	}

	void SetMesh::SetMeshData(const MeshReference& data)
	{
		m_mesh_data = data;
	}

	MeshReference& SetMesh::GetMeshData()
	{
		return m_mesh_data;
	}

	CreateMesh::MeshDataInput::MeshDataInput()
	{
	}

	CreateMesh::MeshDataInput::MeshDataInput(int64_t _id, const MeshInfo& _info, const create_buffer::Buffer& _buffer, const std::string& _tag, resource_loader::LoaderReference _loader)
	{
		m_createID = _id;
		m_info = _info;
		m_buffer = _buffer;
		m_tag = _tag;
		m_loader_ptr = _loader;
	}

	CreateMesh::MeshDataInput::~MeshDataInput()
	{
	}

	MeshInfo::MeshInfo()
	{
	}

	MeshInfo::MeshInfo(int x, int z)
	{
		NumMeshX = x;
		NumMeshZ = z;
		NumXVertex = x + 1; // 基礎頂点数
		NumZVertex = z + 1; // 基礎頂点数
		MaxVertex = NumXVertex * NumZVertex; // 最大頂点数
		NumXVertexWey = 2 * NumXVertex; // 視覚化されている1列の頂点数
		VertexOverlap = 2 * (z - 1); // 重複する頂点数
		NumMeshVertex = NumXVertexWey * z; // 視覚化されている全体の頂点数
		MaxIndex = NumMeshVertex + VertexOverlap; // 最大Index数
		MaxPrimitive = ((x * z) * 2) + (VertexOverlap * 2); // プリミティブ数
	}

	MeshInfo::~MeshInfo()
	{
	}
}

_MSLIB_END