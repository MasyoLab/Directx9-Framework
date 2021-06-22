//==========================================================================
// 球体 [Sphere.cpp]
// author : MasyoLab
//==========================================================================
#include "Sphere.h"

_MSLIB_BEGIN

namespace sphere
{
	SphereData::SphereData() :
		m_createID(0), m_quality(0), m_clone_mesh(nullptr), m_mesh(nullptr), m_buffer(nullptr)
	{
	}

	SphereData::~SphereData()
	{
		if (m_clone_mesh != nullptr)
			m_clone_mesh->Release();
		if (m_mesh != nullptr)
			m_mesh->Release();
		if (m_buffer != nullptr)
			m_buffer->Release();
		m_clone_mesh = nullptr;
		m_mesh = nullptr;
		m_buffer = nullptr;
	}

	int SphereData::GetQuality() const
	{
		return m_quality;
	}

	const LPD3DXMESH SphereData::GetMesh() const
	{
		return m_clone_mesh;
	}

	const LPDIRECT3DVERTEXBUFFER9 SphereData::GetBuffer() const
	{
		return m_buffer;
	}

	int64_t SphereData::GetCreateID() const
	{
		return m_createID;
	}

	CreateSphere::CreateSphere() :
		m_device(nullptr), m_hwnd(nullptr), m_createIDCount(0)
	{
		SetComponentName("CreateSphere");
	}

	CreateSphere::CreateSphere(LPDIRECT3DDEVICE9 device, HWND hWnd) :
		m_device(device), m_hwnd(hWnd), m_createIDCount(0)
	{
		SetComponentName("CreateSphere");
	}

	CreateSphere::~CreateSphere()
	{
		DestroyComponent();
		m_resource_list.clear();
	}

	SphereReference CreateSphere::Create(int _quality)
	{
		auto itr = m_resource_list.find(std::to_string(_quality));
		if (itr == m_resource_list.end())
			return CreateData(_quality);
		return itr->second;
	}

	SphereReference CreateSphere::CreateData(int _quality)
	{
		LPD3DXMESH mesh = nullptr;
		LPD3DXMESH clone_mesh = nullptr;
		LPDIRECT3DVERTEXBUFFER9 buffer = nullptr;

		m_createIDCount++;
		D3DXCreateSphere(m_device, 1.0f, _quality * 2, _quality, &mesh, nullptr);
		mesh->CloneMeshFVF(0, vertex3d::FVFVertex4, m_device, &clone_mesh);
		clone_mesh->GetVertexBuffer(&buffer);
		CreateUV(clone_mesh, buffer);

		return m_resource_list[std::to_string(_quality)]
			= SphereData::Create(new SphereDataInput(
				m_createIDCount,
				_quality,
				mesh,
				clone_mesh,
				buffer,
				std::to_string(_quality),
				ThisComponent<Loader>()));
	}

	void CreateSphere::CreateUV(LPD3DXMESH _mesh, LPDIRECT3DVERTEXBUFFER9 _buffer)
	{
		vertex3d::Vertex4* pseudo = nullptr;// 頂点バッファのロック
		constexpr float rad = 1.0f;

		_buffer->Lock(0, 0, (void**)& pseudo, 0);

		for (DWORD i = 0; i < _mesh->GetNumVertices(); i++)
		{
			float q = 0.0f;
			float q2 = 0.0f;
			auto* pPseudo = &pseudo[i];

			q = atan2(pPseudo->pos.z, pPseudo->pos.x);

			pPseudo->tex.x = q / (2.0f * _pi_<float>);
			q2 = asin(pPseudo->pos.y / rad);
			pPseudo->tex.y = (1.0f - q2 / (_pi_<float> / 2.0f)) / 2.0f;
			if (pPseudo->tex.x > 1.0f)
				pPseudo->tex.x = 1.0f;

			pPseudo->tex = -pPseudo->tex;
			pPseudo->color = D3DCOLOR_RGBA(255, 255, 255, 255);
			pPseudo->normal = D3DXVECTOR3(1, 1, 1);
		}
		_buffer->Unlock();
	}

	SetSphere::SetSphere() 
	{
	}

	SetSphere::~SetSphere()
	{
	}

	void SetSphere::SetSphereData(const SphereReference& data)
	{
		m_sphere_data = data;
	}

	SphereReference& SetSphere::GetSphereData()
	{
		return m_sphere_data;
	}

	CreateSphere::SphereDataInput::SphereDataInput()
	{
	}

	CreateSphere::SphereDataInput::SphereDataInput(
		int64_t _id,
		int _quality,
		LPD3DXMESH _mesh,
		LPD3DXMESH _clone_mesh,
		LPDIRECT3DVERTEXBUFFER9 _buffer,
		const std::string& _tag,
		resource_loader::LoaderReference _loader)
	{
		m_createID = _id;
		m_quality = _quality;
		m_mesh = _mesh;
		m_clone_mesh = _clone_mesh;
		m_buffer = _buffer;
		m_tag = _tag;
		m_loader_ptr = _loader;
	}

	CreateSphere::SphereDataInput::~SphereDataInput()
	{
	}
}

_MSLIB_END