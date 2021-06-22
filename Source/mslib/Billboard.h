//==========================================================================
// ビルボード [Billboard.h]
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
	// Content : ビルボードデータ
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
		@brief バッファの取得
		*/
		const create_buffer::Buffer& GetBuffer() const;
	protected:
		create_buffer::Buffer m_buffer;
	};

	using BillboardReference = resource_loader::ResourceReference<BillboardData>;

	//==========================================================================
	//
	// class : CreateBillboard
	// Content : ビルボード生成
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
		@brief ビルボードを生成する。
		*/
		BillboardReference Create();
	private:
		/**
		@brief バーテックスの生成
		@param out [out] 受け取り
		*/
		void CreateVertex(vertex3d::Vertex4* pOut);

		/**
		@brief Indexの生成
		@param out [out] 受け取り
		@param num [in] 数
		*/
		void CreateIndex(WORD* pOut, int num);
	private:
		LPDIRECT3DDEVICE9 m_device; // デバイス
		HWND m_hwnd; // ウィンドウハンドル
	};

	using CreateBillboardReference = reference::IReference<CreateBillboard>;

	//==========================================================================
	//
	// class : SetBillboard
	// Content : ビルボード登録クラス
	//
	//==========================================================================
	class SetBillboard
	{
	public:
		SetBillboard();
		~SetBillboard();

		/**
		@brief ビルボードの登録
		@param data [in] ビルボード
		*/
		void SetBillboardData(const BillboardReference& data);

		/**
		@brief ビルボードの取得
		*/
		BillboardReference GetBillboardData() const;
	protected:
		BillboardReference m_billboard_data; // ビルボードデータ
	};
}

_MSLIB_END