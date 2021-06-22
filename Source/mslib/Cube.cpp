//==========================================================================
// キューブ [Cube.cpp]
// author : MasyoLab
//==========================================================================
#include <string>
#include "Cube.h"

_MSLIB_BEGIN

namespace cube
{
	constexpr float VCRCT = 0.5f;
	constexpr int g_max_index = 36; // インデックス数
	constexpr int g_num_vertex = 24; // 頂点数
	constexpr int g_num_triangle = 12; // 三角形の数
	constexpr int g_num_dfalt_index = 6; // 面の数

	CubeData::CubeData()
	{
	}

	CubeData::~CubeData()
	{
	}

	const CubeInfo& CubeData::GetInfo() const
	{
		return m_info;
	}

	const floatTexvec& CubeData::GetTexSize() const
	{
		return m_texsize;
	}

	const floatTexvec& CubeData::GetTexCutSize() const
	{
		return m_texcutsize;
	}

	const create_buffer::Buffer& CubeData::GetBuffer() const
	{
		return m_buffer;
	}

	CreateCube::CreateCube() :
		m_device(nullptr), m_hwnd(nullptr)
	{
		SetComponentName("CreateCube");
	}
	CreateCube::CreateCube(LPDIRECT3DDEVICE9 device, HWND hWnd) :
		m_device(device), m_hwnd(hWnd)
	{
		SetComponentName("CreateCube");
	}
	CreateCube::~CreateCube()
	{
		DestroyComponent();
	}

	CubeReference CreateCube::Create()
	{
		if ((int)m_resource_list.size() != 0)
			return m_resource_list.begin()->second;

		floatUV aUv[6]; // 各面のUV
		vertex3d::Vertex4* pPseudo = nullptr;// 頂点バッファのロック
		WORD* pIndex = nullptr;
		CubeInfo info;
		floatTexvec texsize;
		floatTexvec texcutsize;

		info.Direction1 = 4;
		info.Direction2 = 4;
		info.Pattern = g_num_dfalt_index;
		info.MaxIndex = g_max_index;
		info.NumVertex = g_num_vertex;
		info.NumTriangle = g_num_triangle;

		// 画像データの格納
		texsize = floatTexvec(0, 0, 1.0f, 1.0f);
		texcutsize = floatTexvec(0, 0, 0, 0);
		texcutsize.w = texsize.w / info.Direction1;
		texcutsize.h = texsize.h / info.Direction2;

		for (int i = 0; i < info.Pattern; i++)
			aUv[i] = CreateUV(info, texcutsize, i);

		auto vertex_buffer = CreateVertexBuffer(m_device, m_hwnd, sizeof(vertex3d::Vertex4) * g_num_vertex, D3DUSAGE_WRITEONLY, vertex3d::FVFVertex4, D3DPOOL_MANAGED, nullptr);
		if (vertex_buffer != nullptr)
		{
			vertex_buffer->Lock(0, 0, (void**)& pPseudo, D3DLOCK_DISCARD);
			CreateVertex(pPseudo, aUv);
			vertex_buffer->Unlock();	// ロック解除
		}

		auto index_buffer = CreateIndexBuffer(m_device, m_hwnd, sizeof(WORD) * g_max_index, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, nullptr);
		if (index_buffer != nullptr)
		{
			index_buffer->Lock(0, 0, (void**)& pIndex, D3DLOCK_DISCARD);
			CreateIndex(pIndex, g_max_index / g_num_dfalt_index);
			index_buffer->Unlock();	// ロック解除
		}

		// ハッシュ値で保存
		return m_resource_list[std::to_string(typeid(CubeData).hash_code())] = CubeData::Create(new CubeDataInput(
			info, texsize, texcutsize, create_buffer::Buffer(vertex_buffer, index_buffer),
			std::to_string(typeid(CubeData).hash_code()), ThisComponent<Loader>()));
	}

	void CreateCube::CreateVertex(vertex3d::Vertex4* Output, const floatUV* _this)
	{
		vertex3d::Vertex4 vVertex[] =
		{
			// 手前
			{ D3DXVECTOR3(-VCRCT, VCRCT,-VCRCT),D3DXVECTOR3(0,0,-1),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[0].u0,_this[0].v0) }, // 左上
			{ D3DXVECTOR3( VCRCT, VCRCT,-VCRCT),D3DXVECTOR3(0,0,-1),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[0].u1,_this[0].v0) }, // 右上
			{ D3DXVECTOR3( VCRCT,-VCRCT,-VCRCT),D3DXVECTOR3(0,0,-1),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[0].u1,_this[0].v1) }, // 右下
			{ D3DXVECTOR3(-VCRCT,-VCRCT,-VCRCT),D3DXVECTOR3(0,0,-1),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[0].u0,_this[0].v1) }, // 左下

			// 奥
			{ D3DXVECTOR3(-VCRCT,-VCRCT,VCRCT),D3DXVECTOR3(0,0,1),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[1].u0,_this[1].v0) }, // 左上
			{ D3DXVECTOR3( VCRCT,-VCRCT,VCRCT),D3DXVECTOR3(0,0,1),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[1].u1,_this[1].v0) }, // 右上
			{ D3DXVECTOR3( VCRCT, VCRCT,VCRCT),D3DXVECTOR3(0,0,1),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[1].u1,_this[1].v1) }, // 右下
			{ D3DXVECTOR3(-VCRCT, VCRCT,VCRCT),D3DXVECTOR3(0,0,1),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[1].u0,_this[1].v1) }, // 左下

			// 右
			{ D3DXVECTOR3(-VCRCT,-VCRCT,-VCRCT),D3DXVECTOR3(-1,0,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[2].u0,_this[2].v0) }, // 左上
			{ D3DXVECTOR3(-VCRCT,-VCRCT, VCRCT),D3DXVECTOR3(-1,0,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[2].u1,_this[2].v0) }, // 右上
			{ D3DXVECTOR3(-VCRCT, VCRCT, VCRCT),D3DXVECTOR3(-1,0,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[2].u1,_this[2].v1) }, // 右下
			{ D3DXVECTOR3(-VCRCT, VCRCT,-VCRCT),D3DXVECTOR3(-1,0,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[2].u0,_this[2].v1) }, // 左下

			// 左
			{ D3DXVECTOR3(VCRCT, VCRCT,-VCRCT),D3DXVECTOR3(1,0,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[3].u0,_this[3].v0) }, // 左上
			{ D3DXVECTOR3(VCRCT, VCRCT, VCRCT),D3DXVECTOR3(1,0,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[3].u1,_this[3].v0) }, // 右上
			{ D3DXVECTOR3(VCRCT,-VCRCT, VCRCT),D3DXVECTOR3(1,0,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[3].u1,_this[3].v1) }, // 右下
			{ D3DXVECTOR3(VCRCT,-VCRCT,-VCRCT),D3DXVECTOR3(1,0,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[3].u0,_this[3].v1) }, // 左下

			// 上
			{ D3DXVECTOR3(-VCRCT,VCRCT, VCRCT),D3DXVECTOR3(0,1,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[4].u0,_this[4].v0) }, // 左上
			{ D3DXVECTOR3( VCRCT,VCRCT, VCRCT),D3DXVECTOR3(0,1,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[4].u1,_this[4].v0) }, // 右上
			{ D3DXVECTOR3( VCRCT,VCRCT,-VCRCT),D3DXVECTOR3(0,1,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[4].u1,_this[4].v1) }, // 右下
			{ D3DXVECTOR3(-VCRCT,VCRCT,-VCRCT),D3DXVECTOR3(0,1,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[4].u0,_this[4].v1) }, // 左下

			// 下
			{ D3DXVECTOR3(-VCRCT,-VCRCT,-VCRCT),D3DXVECTOR3(0,-1,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[5].u0,_this[5].v0) }, // 左上
			{ D3DXVECTOR3( VCRCT,-VCRCT,-VCRCT),D3DXVECTOR3(0,-1,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[5].u1,_this[5].v0) }, // 右上
			{ D3DXVECTOR3( VCRCT,-VCRCT, VCRCT),D3DXVECTOR3(0,-1,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[5].u1,_this[5].v1) }, // 右下
			{ D3DXVECTOR3(-VCRCT,-VCRCT, VCRCT),D3DXVECTOR3(0,-1,0),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(_this[5].u0,_this[5].v1) }, // 左下
		};

		for (int i = 0; i < (int)(sizeof(vVertex) / sizeof(vertex3d::Vertex4)); i++)
			Output[i] = vVertex[i];
	}

	void CreateCube::CreateIndex(WORD* Output, int NumRectangle)
	{
		for (int i = 0, s = 0, ncount = 0; i < g_num_dfalt_index * NumRectangle; i++, s++, ncount++)
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
			Output[i] = (WORD)s;
		}
	}

	floatUV CreateCube::CreateUV(const CubeInfo& _info, const floatTexvec& _texcutsize, int _num)
	{
		int patternNum = (_num / 1) % _info.Pattern; //2フレームに１回	%10=パターン数
		int patternV = patternNum % _info.Direction1; //横方向のパターン
		int patternH = patternNum / _info.Direction2; //縦方向のパターン
		float fTcx = patternV * _texcutsize.w; //切り取りサイズ
		float fTcy = patternH * _texcutsize.h; //切り取りサイズ

		return floatUV(fTcx, fTcy, fTcx + _texcutsize.w, fTcy + _texcutsize.h);
	}

	SetCube::SetCube()
	{

	}

	SetCube::~SetCube()
	{

	}

	void SetCube::SetCubeData(const CubeReference& data)
	{
		m_cube_data = data;
	}

	CubeReference& SetCube::GetCubeData()
	{
		return m_cube_data;
	}

	CreateCube::CubeDataInput::CubeDataInput()
	{
	}

	CreateCube::CubeDataInput::CubeDataInput(
		const CubeInfo& _info,
		const floatTexvec& _texsize,
		const floatTexvec& _texcutsize,
		const create_buffer::Buffer& _buffer,
		const std::string& _tag,
		resource_loader::LoaderReference _loader)
	{
		m_info = _info;
		m_texsize = _texsize;
		m_texcutsize = _texcutsize;
		m_buffer = _buffer;
		m_tag = _tag;
		m_loader_ptr = _loader;
	}

	CreateCube::CubeDataInput::~CubeDataInput()
	{
	}
}

_MSLIB_END