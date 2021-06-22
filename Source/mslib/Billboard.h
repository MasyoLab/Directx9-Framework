//==========================================================================
// �r���{�[�h [Billboard.h]
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

namespace billboard
{
	//==========================================================================
	//
	// class : BillboardData
	// Content : �r���{�[�h�f�[�^
	//
	//==========================================================================
	class BillboardData :
		public resource_loader::Resource
	{
	private:
		BillboardData(const BillboardData&) = delete;
		BillboardData(BillboardData&&) = delete;
		BillboardData& operator=(const BillboardData&) = delete;
		BillboardData& operator=(BillboardData&&) = delete;
	public:
		BillboardData();
		~BillboardData();

		/**
		@brief �o�b�t�@�̎擾
		*/
		const create_buffer::Buffer& GetBuffer() const;
	protected:
		create_buffer::Buffer m_buffer;
	};

	using BillboardReference = resource_loader::ResourceReference<BillboardData>;

	//==========================================================================
	//
	// class : CreateBillboard
	// Content : �r���{�[�h����
	//
	//==========================================================================
	class CreateBillboard :
		public resource_loader::Loader,
		public create_buffer::CreateBuffer
	{
		class BillboardDataInput :
			public BillboardData
		{
		public:
			BillboardDataInput();
			BillboardDataInput(
				const create_buffer::Buffer& buffer,
				const std::string& tag,
				resource_loader::LoaderReference loader
			);
			~BillboardDataInput();
		};
	private:
		CreateBillboard(const CreateBillboard&) = delete;
		CreateBillboard(CreateBillboard&&) = delete;
		CreateBillboard& operator=(const CreateBillboard&) = delete;
		CreateBillboard& operator=(CreateBillboard&&) = delete;
	public:
		CreateBillboard();
		CreateBillboard(LPDIRECT3DDEVICE9 device, HWND hwnd);
		~CreateBillboard();

		/**
		@brief �r���{�[�h�𐶐�����B
		*/
		BillboardReference Create();
	private:
		/**
		@brief �o�[�e�b�N�X�̐���
		@param out [out] �󂯎��
		*/
		void CreateVertex(vertex3d::Vertex4* pOut);

		/**
		@brief Index�̐���
		@param out [out] �󂯎��
		@param num [in] ��
		*/
		void CreateIndex(WORD* pOut, int num);
	private:
		LPDIRECT3DDEVICE9 m_device; // �f�o�C�X
		HWND m_hwnd; // �E�B���h�E�n���h��
	};

	using CreateBillboardReference = reference::IReference<CreateBillboard>;

	//==========================================================================
	//
	// class : SetBillboard
	// Content : �r���{�[�h�o�^�N���X
	//
	//==========================================================================
	class SetBillboard
	{
	public:
		SetBillboard();
		~SetBillboard();

		/**
		@brief �r���{�[�h�̓o�^
		@param data [in] �r���{�[�h
		*/
		void SetBillboardData(const BillboardReference& data);

		/**
		@brief �r���{�[�h�̎擾
		*/
		BillboardReference GetBillboardData() const;
	protected:
		BillboardReference m_billboard_data; // �r���{�[�h�f�[�^
	};
}

_MSLIB_END