//==========================================================================
// キューブオブジェクト [CubeObject.cpp]
// author : MasyoLab
//==========================================================================
#include "CubeObject.h"
#include "Vertex3d.h"

_MSLIB_BEGIN

namespace object
{
	using renderer::RendererID;

	CubeObject::CubeObject() :
		Renderer(RendererID::Cube)
	{
		SetComponentName("Cube");
		SetActivity(true);
		SetMatrixType(MatrixType::World);
	}

	CubeObject::CubeObject(bool _bInOutFunctionFlag) :
		Renderer(RendererID::Cube), InOutFunction(_bInOutFunctionFlag)
	{
		SetComponentName("Cube");
		SetActivity(true);
		SetMatrixType(MatrixType::World);
	}

	CubeObject::~CubeObject()
	{
	}

	void CubeObject::Update()
	{
	}

	void CubeObject::UpdateMatrix()
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

	void CubeObject::Draw(LPDIRECT3DDEVICE9 device)
	{
		// 呼ばれたら更新の無効化
		SetUpdateKey(false);

		// 存在しない場合終了
		if (!m_cube_data.check())
			return;
		
		device->SetStreamSource(0, m_cube_data->GetBuffer().GetVertexBuffer(), 0, sizeof(vertex3d::Vertex4));
		device->SetIndices(m_cube_data->GetBuffer().GetIndexBuffer());
		device->SetFVF(vertex3d::FVFVertex4);
		device->SetMaterial(&GetMaterialLighting());
		device->SetTransform(D3DTS_WORLD, &m_world_matrix);
		if (m_texture_data.check())
			device->SetTexture(0, m_texture_data->GetTexture());
		else
			device->SetTexture(0, nullptr);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_cube_data->GetInfo().NumVertex, 0, m_cube_data->GetInfo().NumTriangle);
		device->SetTexture(0, nullptr);
	}

	void CubeObject::GUISystem()
	{
		GUIGameObject();
		GUITransform();
		GUIMaterialLighting();
		GUITexture();
	}

	void CubeObject::InputDataFunction(std::ifstream& _ifstream)
	{
		InputDataTransform(_ifstream);
		InputDataMaterialLighting(_ifstream);
	}

	void CubeObject::OutputDataFunction(std::ofstream& _ofstream)
	{
		OutputDataTransform(_ofstream);
		OutputDataMaterialLighting(_ofstream);
	}
}

_MSLIB_END