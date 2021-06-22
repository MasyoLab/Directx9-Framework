//==========================================================================
// ビルボードオブジェクト [BillboardObject.cpp]
// author : MasyoLab
//==========================================================================
#include "BillboardObject.h"
#include "Vertex3d.h"

_MSLIB_BEGIN

namespace object
{
	BillboardObject::BillboardObject() :
		Renderer(renderer::RendererID::Billboard)
	{
		SetComponentName("Billboard");
		SetActivity(true);
		SetMatrixType(MatrixType::World);
	}

	BillboardObject::BillboardObject(bool bInOutFunctionFlag) :
		Renderer(renderer::RendererID::Billboard), InOutFunction(bInOutFunctionFlag)
	{
		SetComponentName("Billboard");
		SetActivity(true);
		SetMatrixType(MatrixType::World);
	}

	BillboardObject::~BillboardObject()
	{}

	void BillboardObject::Update()
	{}

	void BillboardObject::UpdateMatrix()
	{
		// 行列生成
		switch (GetMatrixType())
		{
		case MatrixType::Default:
			CreateWorldMatrix();
			break;
		case MatrixType::World:
			CreateWorldMatrix();
			break;
		case MatrixType::Local:
			CreateLocalMatrix();
			break;
		case MatrixType::WorldView:
			CreateLocalViewMatrix();
			break;
		case MatrixType::LocalView:
			CreateLocalViewMatrix();
			break;
		default:
			CreateWorldMatrix();
			break;
		}
	}

	void BillboardObject::Draw(LPDIRECT3DDEVICE9 device)
	{
		// 呼ばれたら更新の無効化
		SetUpdateKey(false);

		// 存在しない場合終了
		if (!m_billboard_data.check())
			return;

		// 加算合成のフラグ
		if (GetAdditiveSynthesis())
		{
			TechniqueAlpharefEnd(device);
			TechniqueZwriteenableStart(device);
			TechniqueSub(device);
		}

		// 描画情報を登録
		device->SetFVF(vertex3d::FVFVertex4);
		device->SetStreamSource(0, m_billboard_data->GetBuffer().GetVertexBuffer(), 0, sizeof(vertex3d::Vertex4));
		device->SetIndices(m_billboard_data->GetBuffer().GetIndexBuffer());
		device->SetMaterial(&GetMaterialLighting());
		device->SetTransform(D3DTS_WORLD, &m_world_matrix);
		if (m_texture_data.check())
			device->SetTexture(0, m_texture_data->GetTexture());
		else
			device->SetTexture(0, nullptr);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
		device->SetTexture(0, nullptr);

		// 加算合成のフラグ
		if (GetAdditiveSynthesis())
		{
			TechniqueAlpharefStart(device, 100);
			TechniqueZwriteenableEnd(device);
			TechniqueAdd(device);
		}
	}

	void BillboardObject::GUISystem()
	{
		GUIGameObject();
		GUITransform();
		GUIMaterialLighting();
		GUITexture();
	}

	void BillboardObject::InputDataFunction(std::ifstream& ifs)
	{
		InputDataTransform(ifs);
		InputDataMaterialLighting(ifs);
	}

	void BillboardObject::OutputDataFunction(std::ofstream& ofs)
	{
		OutputDataTransform(ofs);
		OutputDataMaterialLighting(ofs);
	}
}

_MSLIB_END