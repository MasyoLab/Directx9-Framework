//==========================================================================
// 球体 [Sphere.h]
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
	// Content : 球体のデータ
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
		int m_quality; // 品質
		LPD3DXMESH m_mesh; // メッシュ
		LPD3DXMESH m_clone_mesh; // メッシュ
		LPDIRECT3DVERTEXBUFFER9 m_buffer; // バッファ
		int64_t m_createID; // 生成ID
	};

	using SphereReference = resource_loader::ResourceReference<SphereData>;

	//==========================================================================
	//
	// class : CreateSphere
	// Content : 球体の生成機能
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
		@brief キューブを生成する。
		@param Quality [in] 品質
		*/
		SphereReference Create(int _quality);
	private:
		/**
		@brief 生成
		@param Quality [in] クオリティ
		*/
		SphereReference CreateData(int _quality);

		/**
		@brief UVの生成
		@param _mesh [out] メッシュ
		@param _buffer [out] バッファ
		*/
		void CreateUV(LPD3DXMESH _mesh, LPDIRECT3DVERTEXBUFFER9 _buffer);
	private:
		LPDIRECT3DDEVICE9 m_device; // デバイス
		HWND m_hwnd; // ウィンドウハンドル
		int64_t m_createIDCount; // カウンタ
	};

	using CreateSphereReference = reference::IReference<CreateSphere>;

	//==========================================================================
	//
	// class : SetSphere
	// Content : 球体登録クラス
	//
	//==========================================================================
	class SetSphere
	{
	public:
		SetSphere();
		~SetSphere();

		/**
		@brief 球体の登録
		@param data [in] 球体
		*/
		void SetSphereData(const SphereReference& data);

		/**
		@brief 球体の取得
		*/
		SphereReference& GetSphereData();
	protected:
		SphereReference m_sphere_data; // 球体データ
	};
}

_MSLIB_END