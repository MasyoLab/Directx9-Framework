//==========================================================================
// Xモデル [XModel.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <unordered_map>
#include <memory>

#include "mslib.hpp"
#include "Component.h"
#include "Reference.h"
#include "Loader.h"
#include "Texture.h"

_MSLIB_BEGIN

namespace xmodel
{
	//==========================================================================
	//
	// class : XModelData
	// Content : Xモデルデータ
	//
	//==========================================================================
	class XModelData :
		public resource_loader::Resource
	{
	private:
		XModelData(const XModelData&) = delete;
		XModelData(XModelData&&) = delete;
		XModelData& operator=(const XModelData&) = delete;
		XModelData& operator=(XModelData&&) = delete;
	public:
		XModelData();
		~XModelData();
		DWORD GetNumMaterial();
		texture::TextureReference& GetTexture(int _index);
		std::vector<texture::TextureReference>& GetTextures();
		const std::vector<D3DMATERIAL9>& GetMaterials() const;
		const D3DVERTEXELEMENT9& GetElements(int _value);
		const LPD3DXMESH GetMesh() const;
	protected:
		DWORD m_num_material; // マテリアル数
		D3DVERTEXELEMENT9 m_elements[MAX_FVF_DECL_SIZE]; // 頂点構造体
		std::vector<D3DMATERIAL9> m_material_list; // マトリクスのライティング
		std::vector<texture::TextureReference> m_texture_list; // テクスチャ
		int64_t m_createID; // 生成ID
		LPD3DXMESH m_mesh;
	};

	using XModelReference = resource_loader::ResourceReference<XModelData>;

	//==========================================================================
	//
	// class : XModelLoader
	// Content : Xモデル読み込み破棄クラス
	//
	//==========================================================================
	class XModelLoader :
		public resource_loader::Loader
	{
		class XModelDataInput :
			public XModelData
		{
		public:
			XModelDataInput();
			XModelDataInput(
				DWORD _num,
				D3DVERTEXELEMENT9 _elements[MAX_FVF_DECL_SIZE],
				std::vector<D3DMATERIAL9>& _material,
				std::vector<texture::TextureReference>& _texture,
				int64_t _createID,
				LPD3DXMESH _mesh,
				const std::string& _tag,
				resource_loader::LoaderReference _loader
			);
			~XModelDataInput();
		};
	private:
		XModelLoader(const XModelLoader&) = delete;
		XModelLoader(XModelLoader&&) = delete;
		XModelLoader& operator=(const XModelLoader&) = delete;
		XModelLoader& operator=(XModelLoader&&) = delete;
	public:
		XModelLoader();
		XModelLoader(LPDIRECT3DDEVICE9 _device, HWND _hwnd, texture::TextureLoaderReference _texture_loader);
		~XModelLoader();

		/**
		@brief Xモデルを読み込む。
		@param _str [in] 読み込みパス
		@return Xモデルのデータ
		*/
		XModelReference Load(const std::string& _str);
	private:
		/**
		@brief Xモデルの読み込み機能の本体
		@param _str [in] 読み込みパス
		@return Xモデルのデータ
		*/
		XModelReference LoadModel(const std::string& _str);

		/**
		@brief 読み込み
		@param path [in] 読み込みパス
		@param _num_material [out] マテリアル数
		@param _lmesh [out] メッシュ
		@param pAdjacency [in] ID3DXBuffer*
		@param pMaterialBuffer [in] ID3DXBuffer*
		@param pDevice [in] デバイス
		@return Component Object Model defines, and macros
		*/
		HRESULT Read(const std::string& path, DWORD& _num_material, LPD3DXMESH& _lmesh, LPD3DXBUFFER& pAdjacency, LPD3DXBUFFER& pMaterialBuffer);

		/**
		@brief 法線のチェック
		@param _lmesh [out] メッシュ
		*/
		void CloneMeshFVF(LPD3DXMESH& _lmesh);

		/**
		@brief 最適化
		@param _lmesh [out] メッシュ
		@param pAdjacency [in] ID3DXBuffer*
		@return Component Object Model defines, and macros
		*/
		HRESULT Optimisation(LPD3DXMESH& _lmesh, LPD3DXBUFFER& pAdjacency);

		/**
		@brief 頂点の宣言
		@param _lmesh [out] メッシュ
		@param pElements [in] D3DVERTEXELEMENT9
		@return Component Object Model defines, and macros
		*/
		HRESULT Declaration(LPD3DXMESH& _lmesh, D3DVERTEXELEMENT9* pElements);

		/**
		@brief 複製
		@param _lmesh [out] メッシュ
		@param pElements [in] D3DVERTEXELEMENT9
		@param pTempMesh [in] ID3DXMesh
		@param pDevice [in] デバイス
		@return Component Object Model defines, and macros
		*/
		HRESULT Replication(LPD3DXMESH& _lmesh, D3DVERTEXELEMENT9* pElements, LPD3DXMESH& pTempMesh);

		/**
		@brief ファイルパスの生成
		@param In [in] 読み込み対象
		@return 読み込み対象へのファイルパス受け取り
		*/
		std::string CreateTexturePass(const std::string& _str);

		/**
		@brief テクスチャの読み込み
		@param _str [in] ファイルパス
		@param _num_material [in] マテリアル数
		@param Input [in] マテリアル
		@return テクスチャリスト
		*/
		std::vector<texture::TextureReference> LoadTexture(const std::string& _str, DWORD _num_material, const LPD3DXMATERIAL Input);

		/**
		@brief マテリアルのセット
		@param _num_material [in] マテリアル数
		@param Input [in] マテリアル
		@return マテリアルリスト
		*/
		std::vector<D3DMATERIAL9> SetMaterial(DWORD _num_material, const LPD3DXMATERIAL Input);

		/**
		@brief エラーメッセージの表示
		@param text [in] メッセージ内容
		@param path [in] エラーが出たもの
		*/
		void ErrorMessage(const std::string& text, const std::string& path);
	private:
		LPDIRECT3DDEVICE9 m_device; // デバイス
		HWND m_hwnd; // ウィンドウハンドル
		int64_t m_createIDCount; // カウンタ
		texture::TextureLoaderReference m_texture_loader; // テクスチャ読み込み機能へのポインタ
	};

	//==========================================================================
	//
	// class : SetXModel
	// Content : Xモデル登録クラス
	//
	//==========================================================================
	class SetXModel
	{
	public:
		SetXModel();
		~SetXModel();

		/**
		@brief モデルデータの登録
		@param data [in] モデルデータ
		*/
		void SetXModelData(const XModelReference& data);

		/**
		@brief モデルデータの取得
		*/
		XModelReference& GetXModelData();
	protected:
		XModelReference m_XModelData; // モデルデータ
	};

	using XModelLoaderReference = reference::IReference<XModelLoader>;
}

_MSLIB_END