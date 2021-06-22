//==========================================================================
// ���b�V�� [Mesh.h]
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
	// Content :���b�V�����
	//
	//==========================================================================
	class MeshInfo
	{
	public:
		MeshInfo();
		/**
		@brief ���b�V�����̐���
		@param x [in] X���̖ʂ̐�
		@param z [in] Z���̖ʂ̐�
		*/
		MeshInfo(int x, int z);
		~MeshInfo();
	public:
		int NumMeshX = 0; // �ʂ̐�
		int NumMeshZ = 0; // �ʂ̐�
		int VertexOverlap = 0; // �d�����钸�_��
		int	NumXVertexWey = 0; // ���o������Ă���1��̒��_��
		int	NumZVertex = 0; // ��b���_��
		int	NumXVertex = 0; // ��b���_��
		int	NumMeshVertex = 0; // ���o������Ă���S�̂̒��_��
		int	MaxPrimitive = 0; // �v���~�e�B�u��
		int	MaxIndex = 0; // �ő�Index��
		int	MaxVertex = 0; // �ő咸�_��
	};

	//==========================================================================
	//
	// class : MeshData
	// Content : ���b�V���f�[�^
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
		int64_t m_createID; // ����ID
		create_buffer::Buffer m_buffer;
	};

	using MeshReference = resource_loader::ResourceReference<MeshData>;

	//==========================================================================
	//
	// class : CreateMesh
	// Content: ���b�V������
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
		@brief ���b�V���𐶐�����B
		*/
		MeshReference Create(int x, int z);
	private:
		/**
		@brief �C���f�b�N�X���̐���
		@param Output [out] �f�[�^�̏o��
		@param Input [in] ���b�V���f�[�^
		*/
		void CreateIndex(LPWORD* Output, const MeshInfo& Input);

		/**
		@brief �o�[�e�b�N�X���̐���
		@param Output [out] �f�[�^�̏o��
		@param Input [in] �o�[�e�b�N�X
		*/
		void CreateVertex(vertex3d::Vertex4* Output, const MeshInfo& Input);
	private:
		int64_t m_createIDCount; // �J�E���^
		LPDIRECT3DDEVICE9 m_device; // �f�o�C�X
		HWND m_hwnd; // �E�B���h�E�n���h��
	};

	using CreateMeshReference = reference::IReference<CreateMesh>;

	//==========================================================================
	//
	// class : SetMesh
	// Content : ���b�V���o�^�N���X
	//
	//==========================================================================
	class SetMesh
	{
	public:
		SetMesh();
		~SetMesh();

		/**
		@brief ���b�V���̓o�^
		@param data [in] ���b�V��
		*/
		void SetMeshData(const MeshReference& data);

		/**
		@brief ���b�V���f�[�^�̎擾
		*/
		MeshReference& GetMeshData();
	protected:
		MeshReference m_mesh_data; // ���b�V���f�[�^
	};
}
_MSLIB_END