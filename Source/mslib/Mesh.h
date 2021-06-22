//==========================================================================
// メッシュ [Mesh.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Component.h"
#include "Reference.h"
#include "Loader.h"
#include "CreateBuffer.h"
#include "Vertex3d.h"

_MSLIB_BEGIN

namespace mesh
{
	//==========================================================================
	//
	// class : MeshInfo
	// Content :メッシュ情報
	//
	//==========================================================================
	class MeshInfo
	{
	public:
		MeshInfo();
		/**
		@brief メッシュ情報の生成
		@param x [in] X軸の面の数
		@param z [in] Z軸の面の数
		*/
		MeshInfo(int x, int z);
		~MeshInfo();
	public:
		int NumMeshX = 0; // 面の数
		int NumMeshZ = 0; // 面の数
		int VertexOverlap = 0; // 重複する頂点数
		int	NumXVertexWey = 0; // 視覚化されている1列の頂点数
		int	NumZVertex = 0; // 基礎頂点数
		int	NumXVertex = 0; // 基礎頂点数
		int	NumMeshVertex = 0; // 視覚化されている全体の頂点数
		int	MaxPrimitive = 0; // プリミティブ数
		int	MaxIndex = 0; // 最大Index数
		int	MaxVertex = 0; // 最大頂点数
	};

	//==========================================================================
	//
	// class : MeshData
	// Content : メッシュデータ
	//
	//==========================================================================
	class MeshData :
		public resource_loader::Resource
	{
	private:
		MeshData(const MeshData&) = delete;
		MeshData(MeshData&&) = delete;
		MeshData& operator=(const MeshData&) = delete;
		MeshData& operator=(MeshData&&) = delete;
	public:
		MeshData();
		~MeshData();
		const MeshInfo& GetInfo() const;
		int64_t GetID() const;
		const create_buffer::Buffer& GetBuffer() const;
	protected:
		MeshInfo m_info;
		int64_t m_createID; // 生成ID
		create_buffer::Buffer m_buffer;
	};

	using MeshReference = resource_loader::ResourceReference<MeshData>;

	//==========================================================================
	//
	// class : CreateMesh
	// Content: メッシュ生成
	//
	//==========================================================================
	class CreateMesh :
		public resource_loader::Loader,
		public create_buffer::CreateBuffer
	{
		class MeshDataInput :
			public MeshData
		{
		public:
			MeshDataInput();
			MeshDataInput(
				int64_t _id,
				const MeshInfo& _info,
				const create_buffer::Buffer& _buffer,
				const std::string& _tag,
				resource_loader::LoaderReference _loader
			);
			~MeshDataInput();
		};
	private:
		CreateMesh(const CreateMesh&) = delete;
		CreateMesh(CreateMesh&&) = delete;
		CreateMesh& operator=(const CreateMesh&) = delete;
		CreateMesh& operator=(CreateMesh&&) = delete;
	public:
		CreateMesh();
		CreateMesh(LPDIRECT3DDEVICE9 device, HWND hWnd);
		~CreateMesh();

		/**
		@brief メッシュを生成する。
		*/
		MeshReference Create(int x, int z);
	private:
		/**
		@brief インデックス情報の生成
		@param Output [out] データの出力
		@param Input [in] メッシュデータ
		*/
		void CreateIndex(LPWORD* Output, const MeshInfo& Input);

		/**
		@brief バーテックス情報の生成
		@param Output [out] データの出力
		@param Input [in] バーテックス
		*/
		void CreateVertex(vertex3d::Vertex4* Output, const MeshInfo& Input);
	private:
		int64_t m_createIDCount; // カウンタ
		LPDIRECT3DDEVICE9 m_device; // デバイス
		HWND m_hwnd; // ウィンドウハンドル
	};

	using CreateMeshReference = reference::IReference<CreateMesh>;

	//==========================================================================
	//
	// class : SetMesh
	// Content : メッシュ登録クラス
	//
	//==========================================================================
	class SetMesh
	{
	public:
		SetMesh();
		~SetMesh();

		/**
		@brief メッシュの登録
		@param data [in] メッシュ
		*/
		void SetMeshData(const MeshReference& data);

		/**
		@brief メッシュデータの取得
		*/
		MeshReference& GetMeshData();
	protected:
		MeshReference m_mesh_data; // メッシュデータ
	};
}
_MSLIB_END