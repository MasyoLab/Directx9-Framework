//==========================================================================
// �L���[�u [Cube.h]
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
		int MaxIndex = 0; // �C���f�b�N�X�� 
		int NumVertex = 0; // ���_��
		int NumTriangle = 0; // �O�p�`�̐�
		int Direction1 = 0; // ��s�̖ʂ̐�
		int Direction2 = 0; // ���̖ʂ̐�
		int Pattern = 0; // �ʂ̐�
	};

	//==========================================================================
	//
	// class : CubeData
	// Content : �L���[�u�f�[�^
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
		CubeInfo m_info; // �L���[�u�̏��
		floatTexvec m_texsize; // �e�N�X�`���̃T�C�Y
		floatTexvec m_texcutsize; // �e�N�X�`���̐؂���T�C�Y
		create_buffer::Buffer m_buffer;
	};

	using CubeReference = resource_loader::ResourceReference<CubeData>;

	//==========================================================================
	//
	// class : CreateCube
	// Content : �L���[�u�����@�\
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
		@brief �L���[�u�𐶐�����B
		*/
		CubeReference Create();
	private:
		/**
		@brief �L���[�u����
		@param Output [out] ���_���
		@param _this [in] UV���W
		*/
		void CreateVertex(vertex3d::Vertex4* Output, const floatUV* _this);

		/**
		@brief Index�̐���
		@param Output [in/out] �󂯎��
		@param NumRectangle [in] ��
		*/
		void CreateIndex(WORD* Output, int NumRectangle);

		/**
		@brief UV����
		@param _info [in] CubeInfo
		@param _texcutsize [in] floatTexvec
		@param _num [in] ���݂̖�
		@return uv
		*/
		floatUV CreateUV(const CubeInfo& _info, const floatTexvec& _texcutsize, int _num);
	private:
		LPDIRECT3DDEVICE9 m_device; // �f�o�C�X
		HWND m_hwnd; // �E�B���h�E�n���h��
	};

	using CreateCubeReference = reference::IReference<CreateCube>;

	//==========================================================================
	//
	// class : SetCube
	// Content : �L���[�u�o�^�N���X
	//
	//==========================================================================
	class SetCube
	{
	public:
		SetCube();
		~SetCube();

		/**
		@brief �L���[�u�̓o�^
		@param data [in] �L���[�u
		*/
		void SetCubeData(const CubeReference& data);

		/**
		@brief �L���[�u�̎擾
		*/
		CubeReference& GetCubeData();
	protected:
		CubeReference m_cube_data; // �L���[�u�f�[�^
	};
}

_MSLIB_END