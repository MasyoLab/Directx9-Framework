//==========================================================================
// �e�N�X�`�� [Texture.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <list>
#include <unordered_map>
#include <memory>

#include "mslib.hpp"
#include "Component.h"
#include "Reference.h"
#include "Loader.h"

_MSLIB_BEGIN

namespace texture
{
	class ImageInfo :
		public D3DXIMAGE_INFO
	{
	public:
		ImageInfo();
		ImageInfo(UINT _width, UINT _height, UINT _depth, UINT _mipLevels, D3DFORMAT _format, D3DRESOURCETYPE _resourceType, D3DXIMAGE_FILEFORMAT _imageFileFormat);
		~ImageInfo();
	};

	//==========================================================================
	//
	// class : TextureData
	// Content : �e�N�X�`���f�[�^
	//
	//==========================================================================
	class TextureData :
		public resource_loader::Resource
	{
	private:
		TextureData(const TextureData&) = delete;
		TextureData(TextureData&&) = delete;
		TextureData& operator=(const TextureData&) = delete;
		TextureData& operator=(TextureData&&) = delete;
	public:
		TextureData();
		~TextureData();
		const LPDIRECT3DTEXTURE9 GetTexture() const;
		const ImageInfo& GetImageInfo() const;
		int64_t GetCreateID();
		void GUITexture();
		static void GUITextureList();
	protected:
		LPDIRECT3DTEXTURE9 m_texture;
		ImageInfo m_info; // �摜���
		int64_t m_createID; // ����ID
	private:
#if defined(_MSLIB_DEBUG)
		bool m_open;
		static std::list<TextureData*> m_textures;
#endif
	};

	using TextureReference = resource_loader::ResourceReference<TextureData>;

	//==========================================================================
	//
	// class : TextureLoader
	// Content : �e�N�X�`���ǂݍ��ݔj���N���X
	//
	//==========================================================================
	class TextureLoader :
		public resource_loader::Loader
	{
		class TextureDataInput :
			public TextureData
		{
		public:
			TextureDataInput();
			TextureDataInput(int64_t _id, const ImageInfo& _info, LPDIRECT3DTEXTURE9 _texture, const std::string& _tag, resource_loader::LoaderReference _loader);
			~TextureDataInput();
		};
	private:
		TextureLoader(const TextureLoader&) = delete;
		TextureLoader(TextureLoader&&) = delete;
		TextureLoader& operator=(const TextureLoader&) = delete;
		TextureLoader& operator=(TextureLoader&&) = delete;
	public:
		TextureLoader();
		TextureLoader(LPDIRECT3DDEVICE9 _device, HWND _hwnd);
		~TextureLoader();

		/**
		@brief �e�N�X�`����ǂݍ��ށB
		@param _str [in] �ǂݍ��݃p�X
		@return �e�N�X�`���̃|�C���^
		*/
		TextureReference Load(const std::string& _str);

		/**
		@brief �e�N�X�`���𐶐�����
		@param _width [in], _height [in] size in pixels. these must be non-zero
		@param _mip_levels [in] number of mip levels desired. if zero or D3DX_DEFAULT, a complete mipmap chain will be created.
		@param _usage [in] Texture usage flags
		@param _format [in] Pixel format.
		@param _pool [in] Memory pool to be used to create texture
		@return �e�N�X�`���̃|�C���^
		*/
		TextureReference CreateTexture(UINT _width, UINT _height, UINT _mip_levels, DWORD _usage, D3DFORMAT _format, D3DPOOL _pool);

		std::list<TextureReference> GetData();
	private:
		/**
		@brief �e�N�X�`���̓ǂݍ��݋@�\�̖{��
		@param _path [in] �ǂݍ��݌��p�X
		@param _out [out] �󂯎���
		*/
		TextureReference LoadTexture(const std::string& _path);
	private:
		LPDIRECT3DDEVICE9 m_device; // �f�o�C�X
		HWND m_hwnd; // �E�B���h�E�n���h��
		int64_t m_createIDCount; // �J�E���^
	};

	using TextureLoaderReference = reference::IReference<TextureLoader>;

	//==========================================================================
	//
	// class : SetTexture
	// Content : �e�N�X�`���o�^�N���X
	//
	//==========================================================================
	class SetTexture
	{
	public:
		SetTexture();
		~SetTexture();

		/**
		@brief �e�N�X�`���f�[�^�̓o�^
		@param _textureData [in] �e�N�X�`��
		*/
		virtual void SetTextureData(const TextureReference& _textureData);

		/**
		@brief �e�N�X�`���f�[�^�̎擾
		*/
		TextureReference GetTextureData();
	protected:
		void GUITexture();
	protected:
		TextureReference m_texture_data; // �e�N�X�`���f�[�^
	};
}

_MSLIB_END