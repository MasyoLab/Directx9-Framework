//==========================================================================
// ���� [Sphere.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Component.h"
#include "Reference.h"
#include "Loader.h"
#include "Vertex3d.h"

_MSLIB_BEGIN

namespace sphere
{
	//==========================================================================
	//
	// class : SphereData
	// Content : ���̂̃f�[�^
	//
	//==========================================================================
	class SphereData :
		public resource_loader::Resource
	{
	private:
		SphereData(const SphereData&) = delete;
		SphereData(SphereData&&) = delete;
		SphereData& operator=(const SphereData&) = delete;
		SphereData& operator=(SphereData&&) = delete;
	public:
		SphereData();
		~SphereData();
		int GetQuality() const;
		const LPD3DXMESH GetMesh() const;
		const LPDIRECT3DVERTEXBUFFER9 GetBuffer() const;
		int64_t GetCreateID() const;
	protected:
		int m_quality; // �i��
		LPD3DXMESH m_mesh; // ���b�V��
		LPD3DXMESH m_clone_mesh; // ���b�V��
		LPDIRECT3DVERTEXBUFFER9 m_buffer; // �o�b�t�@
		int64_t m_createID; // ����ID
	};

	using SphereReference = resource_loader::ResourceReference<SphereData>;

	//==========================================================================
	//
	// class : CreateSphere
	// Content : ���̂̐����@�\
	//
	//==========================================================================
	class CreateSphere :
		public resource_loader::Loader
	{
		class SphereDataInput :
			public SphereData
		{
		public:
			SphereDataInput();
			SphereDataInput(
				int64_t _id,
				int _quality,
				LPD3DXMESH _mesh,
				LPD3DXMESH _clone_mesh,
				LPDIRECT3DVERTEXBUFFER9 _buffer,
				const std::string& _tag,
				resource_loader::LoaderReference _loader
			);
			~SphereDataInput();
		};
	private:
		CreateSphere(const CreateSphere&) = delete;
		CreateSphere(CreateSphere&&) = delete;
		CreateSphere& operator=(const CreateSphere&) = delete;
		CreateSphere& operator=(CreateSphere&&) = delete;
	public:
		CreateSphere();
		CreateSphere(LPDIRECT3DDEVICE9 device, HWND hWnd);
		~CreateSphere();

		/**
		@brief �L���[�u�𐶐�����B
		@param Quality [in] �i��
		*/
		SphereReference Create(int _quality);
	private:
		/**
		@brief ����
		@param Quality [in] �N�I���e�B
		*/
		SphereReference CreateData(int _quality);

		/**
		@brief UV�̐���
		@param _mesh [out] ���b�V��
		@param _buffer [out] �o�b�t�@
		*/
		void CreateUV(LPD3DXMESH _mesh, LPDIRECT3DVERTEXBUFFER9 _buffer);
	private:
		LPDIRECT3DDEVICE9 m_device; // �f�o�C�X
		HWND m_hwnd; // �E�B���h�E�n���h��
		int64_t m_createIDCount; // �J�E���^
	};

	using CreateSphereReference = reference::IReference<CreateSphere>;

	//==========================================================================
	//
	// class : SetSphere
	// Content : ���̓o�^�N���X
	//
	//==========================================================================
	class SetSphere
	{
	public:
		SetSphere();
		~SetSphere();

		/**
		@brief ���̂̓o�^
		@param data [in] ����
		*/
		void SetSphereData(const SphereReference& data);

		/**
		@brief ���̂̎擾
		*/
		SphereReference& GetSphereData();
	protected:
		SphereReference m_sphere_data; // ���̃f�[�^
	};
}

_MSLIB_END