//==========================================================================
// キューブ [Cube.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "mslib_struct.h"
#include "Component.h"
#include "Reference.h"
#include "Loader.h"
#include "CreateBuffer.h"
#include "Vertex3d.h"

_MSLIB_BEGIN

namespace cube
{
	struct CubeInfo
	{
		int MaxIndex = 0; // インデックス数 
		int NumVertex = 0; // 頂点数
		int NumTriangle = 0; // 三角形の数
		int Direction1 = 0; // 一行の面の数
		int Direction2 = 0; // 一列の面の数
		int Pattern = 0; // 面の数
	};

	//==========================================================================
	//
	// class : CubeData
	// Content : キューブデータ
	//
	//==========================================================================
	class CubeData :
		public resource_loader::Resource
	{
	private:
		CubeData(const CubeData&) = delete;
		CubeData(CubeData&&) = delete;
		CubeData& operator=(const CubeData&) = delete;
		CubeData& operator=(CubeData&&) = delete;
	public:
		CubeData();
		~CubeData();
		const CubeInfo& GetInfo() const;
		const floatTexvec& GetTexSize() const;
		const floatTexvec& GetTexCutSize() const;
		const create_buffer::Buffer& GetBuffer() const;
	protected:
		CubeInfo m_info; // キューブの情報
		floatTexvec m_texsize; // テクスチャのサイズ
		floatTexvec m_texcutsize; // テクスチャの切り取りサイズ
		create_buffer::Buffer m_buffer;
	};

	using CubeReference = resource_loader::ResourceReference<CubeData>;

	//==========================================================================
	//
	// class : CreateCube
	// Content : キューブ生成機能
	//
	//==========================================================================
	class CreateCube :
		public resource_loader::Loader,
		public create_buffer::CreateBuffer
	{
		class CubeDataInput :
			public CubeData
		{
		public:
			CubeDataInput();
			CubeDataInput(
				const CubeInfo& _info,
				const floatTexvec& _texsize,
				const floatTexvec& _texcutsize,
				const create_buffer::Buffer& _buffer,
				const std::string& _tag,
				resource_loader::LoaderReference _loader
			);
			~CubeDataInput();
		};
	private:
		CreateCube(const CreateCube&) = delete;
		CreateCube(CreateCube&&) = delete;
		CreateCube& operator=(const CreateCube&) = delete;
		CreateCube& operator=(CreateCube&&) = delete;
	public:
		CreateCube();
		CreateCube(LPDIRECT3DDEVICE9 device, HWND hWnd);
		~CreateCube();

		/**
		@brief キューブを生成する。
		*/
		CubeReference Create();
	private:
		/**
		@brief キューブ生成
		@param Output [out] 頂点情報
		@param _this [in] UV座標
		*/
		void CreateVertex(vertex3d::Vertex4* Output, const floatUV* _this);

		/**
		@brief Indexの生成
		@param Output [in/out] 受け取り
		@param NumRectangle [in] 数
		*/
		void CreateIndex(WORD* Output, int NumRectangle);

		/**
		@brief UV生成
		@param _info [in] CubeInfo
		@param _texcutsize [in] floatTexvec
		@param _num [in] 現在の面
		@return uv
		*/
		floatUV CreateUV(const CubeInfo& _info, const floatTexvec& _texcutsize, int _num);
	private:
		LPDIRECT3DDEVICE9 m_device; // デバイス
		HWND m_hwnd; // ウィンドウハンドル
	};

	using CreateCubeReference = reference::IReference<CreateCube>;

	//==========================================================================
	//
	// class : SetCube
	// Content : キューブ登録クラス
	//
	//==========================================================================
	class SetCube
	{
	public:
		SetCube();
		~SetCube();

		/**
		@brief キューブの登録
		@param data [in] キューブ
		*/
		void SetCubeData(const CubeReference& data);

		/**
		@brief キューブの取得
		*/
		CubeReference& GetCubeData();
	protected:
		CubeReference m_cube_data; // キューブデータ
	};
}

_MSLIB_END