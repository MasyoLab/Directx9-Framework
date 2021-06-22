//==========================================================================
// X���f�� [XModel.h]
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
	// Content : X���f���f�[�^
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
		DWORD m_num_material; // �}�e���A����
		D3DVERTEXELEMENT9 m_elements[MAX_FVF_DECL_SIZE]; // ���_�\����
		std::vector<D3DMATERIAL9> m_material_list; // �}�g���N�X�̃��C�e�B���O
		std::vector<texture::TextureReference> m_texture_list; // �e�N�X�`��
		int64_t m_createID; // ����ID
		LPD3DXMESH m_mesh;
	};

	using XModelReference = resource_loader::ResourceReference<XModelData>;

	//==========================================================================
	//
	// class : XModelLoader
	// Content : X���f���ǂݍ��ݔj���N���X
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
		@brief X���f����ǂݍ��ށB
		@param _str [in] �ǂݍ��݃p�X
		@return X���f���̃f�[�^
		*/
		XModelReference Load(const std::string& _str);
	private:
		/**
		@brief X���f���̓ǂݍ��݋@�\�̖{��
		@param _str [in] �ǂݍ��݃p�X
		@return X���f���̃f�[�^
		*/
		XModelReference LoadModel(const std::string& _str);

		/**
		@brief �ǂݍ���
		@param path [in] �ǂݍ��݃p�X
		@param _num_material [out] �}�e���A����
		@param _lmesh [out] ���b�V��
		@param pAdjacency [in] ID3DXBuffer*
		@param pMaterialBuffer [in] ID3DXBuffer*
		@param pDevice [in] �f�o�C�X
		@return Component Object Model defines, and macros
		*/
		HRESULT Read(const std::string& path, DWORD& _num_material, LPD3DXMESH& _lmesh, LPD3DXBUFFER& pAdjacency, LPD3DXBUFFER& pMaterialBuffer);

		/**
		@brief �@���̃`�F�b�N
		@param _lmesh [out] ���b�V��
		*/
		void CloneMeshFVF(LPD3DXMESH& _lmesh);

		/**
		@brief �œK��
		@param _lmesh [out] ���b�V��
		@param pAdjacency [in] ID3DXBuffer*
		@return Component Object Model defines, and macros
		*/
		HRESULT Optimisation(LPD3DXMESH& _lmesh, LPD3DXBUFFER& pAdjacency);

		/**
		@brief ���_�̐錾
		@param _lmesh [out] ���b�V��
		@param pElements [in] D3DVERTEXELEMENT9
		@return Component Object Model defines, and macros
		*/
		HRESULT Declaration(LPD3DXMESH& _lmesh, D3DVERTEXELEMENT9* pElements);

		/**
		@brief ����
		@param _lmesh [out] ���b�V��
		@param pElements [in] D3DVERTEXELEMENT9
		@param pTempMesh [in] ID3DXMesh
		@param pDevice [in] �f�o�C�X
		@return Component Object Model defines, and macros
		*/
		HRESULT Replication(LPD3DXMESH& _lmesh, D3DVERTEXELEMENT9* pElements, LPD3DXMESH& pTempMesh);

		/**
		@brief �t�@�C���p�X�̐���
		@param In [in] �ǂݍ��ݑΏ�
		@return �ǂݍ��ݑΏۂւ̃t�@�C���p�X�󂯎��
		*/
		std::string CreateTexturePass(const std::string& _str);

		/**
		@brief �e�N�X�`���̓ǂݍ���
		@param _str [in] �t�@�C���p�X
		@param _num_material [in] �}�e���A����
		@param Input [in] �}�e���A��
		@return �e�N�X�`�����X�g
		*/
		std::vector<texture::TextureReference> LoadTexture(const std::string& _str, DWORD _num_material, const LPD3DXMATERIAL Input);

		/**
		@brief �}�e���A���̃Z�b�g
		@param _num_material [in] �}�e���A����
		@param Input [in] �}�e���A��
		@return �}�e���A�����X�g
		*/
		std::vector<D3DMATERIAL9> SetMaterial(DWORD _num_material, const LPD3DXMATERIAL Input);

		/**
		@brief �G���[���b�Z�[�W�̕\��
		@param text [in] ���b�Z�[�W���e
		@param path [in] �G���[���o������
		*/
		void ErrorMessage(const std::string& text, const std::string& path);
	private:
		LPDIRECT3DDEVICE9 m_device; // �f�o�C�X
		HWND m_hwnd; // �E�B���h�E�n���h��
		int64_t m_createIDCount; // �J�E���^
		texture::TextureLoaderReference m_texture_loader; // �e�N�X�`���ǂݍ��݋@�\�ւ̃|�C���^
	};

	//==========================================================================
	//
	// class : SetXModel
	// Content : X���f���o�^�N���X
	//
	//==========================================================================
	class SetXModel
	{
	public:
		SetXModel();
		~SetXModel();

		/**
		@brief ���f���f�[�^�̓o�^
		@param data [in] ���f���f�[�^
		*/
		void SetXModelData(const XModelReference& data);

		/**
		@brief ���f���f�[�^�̎擾
		*/
		XModelReference& GetXModelData();
	protected:
		XModelReference m_XModelData; // ���f���f�[�^
	};

	using XModelLoaderReference = reference::IReference<XModelLoader>;
}

_MSLIB_END