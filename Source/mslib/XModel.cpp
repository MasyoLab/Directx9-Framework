//==========================================================================
// Xモデル [XModel.cpp]
// author : MasyoLab
//==========================================================================
#include "XModel.h"

_MSLIB_BEGIN

namespace xmodel
{
	XModelData::XModelData() :
		m_num_material(0), m_createID(0), m_mesh(nullptr)
	{

	}
	XModelData::~XModelData()
	{
		if (m_mesh != nullptr)
			m_mesh->Release();
		m_mesh = nullptr;
		m_material_list.clear();
		m_texture_list.clear();
	}

	DWORD XModelData::GetNumMaterial()
	{
		return m_num_material;
	}

	texture::TextureReference& XModelData::GetTexture(int _index)
	{
		return m_texture_list[_index];
	}

	std::vector<texture::TextureReference>& XModelData::GetTextures()
	{
		return m_texture_list;
	}

	const std::vector<D3DMATERIAL9>& XModelData::GetMaterials() const
	{
		return m_material_list;
	}

	const D3DVERTEXELEMENT9& XModelData::GetElements(int _value)
	{
		return m_elements[_value];
	}

	const LPD3DXMESH XModelData::GetMesh() const
	{
		return m_mesh;
	}

	XModelLoader::XModelLoader() :
		m_createIDCount(0), m_device(nullptr), m_hwnd(nullptr)
	{
		SetComponentName("XModelLoader");
	}
	XModelLoader::XModelLoader(LPDIRECT3DDEVICE9 _device, HWND _hwnd, texture::TextureLoaderReference _texture_loader)
		: m_createIDCount(0), m_device(_device), m_hwnd(_hwnd), m_texture_loader(_texture_loader)
	{
		SetComponentName("XModelLoader");
	}
	XModelLoader::~XModelLoader()
	{
		DestroyComponent();
	}

	XModelReference XModelLoader::Load(const std::string& _str)
	{
		auto itr = m_resource_list.find(_str);
		if (itr == m_resource_list.end())
			return LoadModel(_str);
		return itr->second;
	}

	XModelReference XModelLoader::LoadModel(const std::string& _str)
	{
		LPD3DXBUFFER pAdjacency = nullptr; // 隣接情報
		LPD3DXMESH pTempMesh = nullptr; // テンプレートメッシュ
		LPD3DXMESH pMesh = nullptr; // メッシュ
		LPD3DXBUFFER pMaterialBuffer = nullptr; // マテリアルバッファ
		DWORD num_material = (DWORD)0; // マテリアル数
		D3DVERTEXELEMENT9 elements_list[MAX_FVF_DECL_SIZE];

		// モデルの読み込み
		if (FAILED(Read(_str, num_material, pMesh, pAdjacency, pMaterialBuffer)))
			ErrorMessage("Xデータが読み込めませんでした。\n %s", _str.c_str());

		// 法線が無い場合は強制的に追加
		CloneMeshFVF(pMesh);

		// 最適化
		if (FAILED(Optimisation(pMesh, pAdjacency)))
			ErrorMessage("Xデータの最適化に失敗しました。\n %s", _str.c_str());

		// 頂点の宣言
		if (FAILED(Declaration(pMesh, elements_list)))
			ErrorMessage("頂点の宣言に失敗しました。\n %s", _str.c_str());

		// 複製
		if (FAILED(Replication(pMesh, elements_list, pTempMesh)))
			ErrorMessage("複製に失敗しました。\n %s", _str.c_str());

		// ファイルパスの生成
		auto strFilePass = CreateTexturePass(_str);

		// テクスチャの読み込み
		auto texture_list = LoadTexture(strFilePass, num_material, (LPD3DXMATERIAL)pMaterialBuffer->GetBufferPointer());

		// マテリアルを登録
		auto material_list = SetMaterial(num_material, (LPD3DXMATERIAL)pMaterialBuffer->GetBufferPointer());

		if (pMaterialBuffer != nullptr)
		{
			pMaterialBuffer->Release();
			pMaterialBuffer = nullptr;
		}
		if (pMesh != nullptr)
		{
			pMesh->Release();
			pMesh = nullptr;
		}
		if (pAdjacency != nullptr)
		{
			pAdjacency->Release();
			pAdjacency = nullptr;
		}

		m_createIDCount++; // 生成カウンタを回す
		return m_resource_list[_str] =
			XModelData::Create(new XModelDataInput(
				num_material, elements_list, material_list, texture_list, m_createIDCount, pTempMesh, _str, ThisComponent<Loader>()));
	}

	HRESULT XModelLoader::Read(const std::string& path, DWORD& _num_material, LPD3DXMESH& _lmesh, LPD3DXBUFFER& pAdjacency, LPD3DXBUFFER& pMaterialBuffer)
	{
		return D3DXLoadMeshFromX(path.c_str(), D3DXMESH_SYSTEMMEM, m_device, &pAdjacency, &pMaterialBuffer, nullptr, &_num_material, &_lmesh);
	}

	void XModelLoader::CloneMeshFVF(LPD3DXMESH& _lmesh)
	{
		// 法線が無い場合は強制的に追加
		if ((_lmesh->GetFVF() & D3DFVF_NORMAL) == 0) {
			LPD3DXMESH pMeshTmp = _lmesh;
			pMeshTmp->CloneMeshFVF(pMeshTmp->GetOptions(), pMeshTmp->GetFVF() | D3DFVF_NORMAL,
				m_device, &_lmesh);
			if (pMeshTmp != nullptr)
				pMeshTmp->Release();
			D3DXComputeNormals(_lmesh, NULL);
		}
	}

	HRESULT XModelLoader::Optimisation(LPD3DXMESH& _lmesh, LPD3DXBUFFER& pAdjacency)
	{
		return _lmesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, (DWORD*)pAdjacency->GetBufferPointer(), nullptr, nullptr, nullptr);
	}

	HRESULT XModelLoader::Declaration(LPD3DXMESH& _lmesh, D3DVERTEXELEMENT9* pElements)
	{
		return _lmesh->GetDeclaration(pElements);
	}

	HRESULT XModelLoader::Replication(LPD3DXMESH& _lmesh, D3DVERTEXELEMENT9* pElements, LPD3DXMESH& pTempMesh)
	{
		return _lmesh->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, pElements, m_device, &pTempMesh);
	}

	std::string XModelLoader::CreateTexturePass(const std::string& _str)
	{
		std::string out = _str;

		for (auto itr = --out.end(); itr != out.begin(); --itr)
		{
			if (itr == out.begin())
				break;
			if ((strcmp(&(*itr), "/") == 0) || (strcmp(&(*itr), "\0") == 0))
				break;
			out.erase(itr);
		}
		return out;
	}

	std::vector<texture::TextureReference> XModelLoader::LoadTexture(const std::string& _str, DWORD _num_material, const LPD3DXMATERIAL Input)
	{
		// 格納領域の予約
		std::vector<texture::TextureReference> texture;
		texture.reserve(_num_material);

		// マテリアルの数だけ
		for (int i = 0; i < (int)_num_material; i++)
		{
			// 使用しているテクスチャがあれば読み込む
			if (Input[i].pTextureFilename != nullptr && lstrlen(Input[i].pTextureFilename) > 0)
				texture.push_back(m_texture_loader->Load(_str + Input[i].pTextureFilename));
			else
				texture.push_back(m_texture_loader->Load(""));
		}

		return texture;
	}

	std::vector<D3DMATERIAL9> XModelLoader::SetMaterial(DWORD _num_material, const LPD3DXMATERIAL Input)
	{
		std::vector<D3DMATERIAL9> material;
		material.reserve(_num_material);

		for (int i = 0; i < (int)_num_material; i++)
		{
			material.push_back(Input[i].MatD3D);
			material[i].Ambient = material[i].Diffuse;
		}

		return material;
	}

	void XModelLoader::ErrorMessage(const std::string& text, const std::string& path)
	{
		size_t size = snprintf(nullptr, 0, text.c_str(), path.c_str()) + 1; // Extra space for '\0'
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, text.c_str(), path.c_str());
		MessageBox(m_hwnd, std::string(buf.get(), buf.get() + size - 1).c_str(), "ERROR", MB_OK | MB_ICONEXCLAMATION | MB_ICONWARNING);
	}

	SetXModel::SetXModel()
	{
	}

	SetXModel::~SetXModel()
	{
	}

	void SetXModel::SetXModelData(const XModelReference& data)
	{
		m_XModelData = data;
	}

	XModelReference& SetXModel::GetXModelData()
	{
		return m_XModelData;
	}

	XModelLoader::XModelDataInput::XModelDataInput()
	{
	}

	XModelLoader::XModelDataInput::XModelDataInput(
		DWORD _num,
		D3DVERTEXELEMENT9 _elements[MAX_FVF_DECL_SIZE],
		std::vector<D3DMATERIAL9>& _material,
		std::vector<texture::TextureReference>& _texture,
		int64_t _createID,
		LPD3DXMESH _mesh,
		const std::string& _tag,
		resource_loader::LoaderReference _loader)
	{
		m_num_material = _num;
		m_material_list = _material;
		m_texture_list = _texture;
		m_createID = _createID;
		m_mesh = _mesh;
		m_tag = _tag;
		m_loader_ptr = _loader;

		for (int i = 0; i < MAX_FVF_DECL_SIZE; i++)
			m_elements[i] = _elements[i];
	}

	XModelLoader::XModelDataInput::~XModelDataInput()
	{
	}
}

_MSLIB_END