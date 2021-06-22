//==========================================================================
// メッシュオブジェクト [MeshObject.cpp]
// author : MasyoLab
//==========================================================================
#include "MeshObject.h"
#include "Vertex3d.h"

_MSLIB_BEGIN

namespace object
{
	using renderer::RendererID;

	MeshObject::MeshObject() :
		Renderer(RendererID::Mesh)
	{
		SetComponentName("Mesh");
		SetActivity(true);
		SetMatrixType(MatrixType::World);
	}

	MeshObject::MeshObject(bool _bInOutFunctionFlag) :
		Renderer(RendererID::Mesh), InOutFunction(_bInOutFunctionFlag)
	{
		SetComponentName("Mesh");
		SetActivity(true);
		SetMatrixType(MatrixType::World);
	}

	MeshObject::~MeshObject()
	{
	}

	void MeshObject::Update()
	{
	}

	void MeshObject::UpdateMatrix()
	{
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
		default:
			CreateWorldMatrix();
			break;
		}
	}

	void MeshObject::Draw(LPDIRECT3DDEVICE9 device)
	{
		// 呼ばれたら更新の無効化
		SetUpdateKey(false);

		// 存在しない場合終了
		if (!m_mesh_data.check())
			return;

		// FVFの設定
		device->SetFVF(vertex3d::FVFVertex4);

		// パイプライン
		device->SetStreamSource(0, m_mesh_data->GetBuffer().GetVertexBuffer(), 0, sizeof(vertex3d::Vertex4));
		device->SetIndices(m_mesh_data->GetBuffer().GetIndexBuffer());

		// マテリアル情報をセット
		device->SetMaterial(&GetMaterialLighting());

		// 各種行列の設定
		device->SetTransform(D3DTS_WORLD, &m_world_matrix);
		if (m_texture_data.check())
			device->SetTexture(0, m_texture_data->GetTexture());
		else
			device->SetTexture(0, nullptr);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_mesh_data->GetInfo().MaxVertex, 0, m_mesh_data->GetInfo().MaxPrimitive);
		device->SetTexture(0, nullptr);
	}

	void MeshObject::GUISystem()
	{
		GUIGameObject();
		GUITransform();
		GUIMaterialLighting();
		GUITexture();
	}

	void MeshObject::InputDataFunction(std::ifstream& _ifstream)
	{
		InputDataTransform(_ifstream);
		InputDataMaterialLighting(_ifstream);
	}

	void MeshObject::OutputDataFunction(std::ofstream& _ofstream)
	{
		OutputDataTransform(_ofstream);
		OutputDataMaterialLighting(_ofstream);
	}
}

_MSLIB_END