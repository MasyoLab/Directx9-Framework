//==========================================================================
// 球体オブジェクト [SphereObject.cpp]
// author : MasyoLab
//==========================================================================
#include "SphereObject.h"

_MSLIB_BEGIN

namespace object
{
	using renderer::RendererID;

	SphereObject::SphereObject() :
		Renderer(RendererID::Sphere)
	{
		SetComponentName("Sphere");
		SetActivity(true);
		SetMatrixType(MatrixType::World);
	}
	SphereObject::SphereObject(bool _bInOutFunctionFlag) :
		Renderer(RendererID::Sphere), InOutFunction(_bInOutFunctionFlag)
	{
		SetComponentName("Sphere");
		SetActivity(true);
		SetMatrixType(MatrixType::World);
	}
	SphereObject::~SphereObject()
	{
	}
	void SphereObject::Update()
	{
	}
	void SphereObject::UpdateMatrix()
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
	void SphereObject::Draw(LPDIRECT3DDEVICE9 device)
	{
		// 呼ばれたら更新の無効化
		SetUpdateKey(false);

		// 存在しない場合終了
		if (!m_sphere_data.check())
			return;

		device->SetFVF(m_sphere_data->GetMesh()->GetFVF());
		device->SetMaterial(&GetMaterialLighting());
		device->SetTransform(D3DTS_WORLD, &m_world_matrix);
		if (m_texture_data.check())
			device->SetTexture(0, m_texture_data->GetTexture());
		m_sphere_data->GetMesh()->DrawSubset(0);
		device->SetTexture(0, nullptr);
	}
	void SphereObject::GUISystem()
	{
		GUIGameObject();
		GUITransform();
		GUIMaterialLighting();
		GUITexture();
	}
	void SphereObject::InputDataFunction(std::ifstream& _ifstream)
	{
		InputDataTransform(_ifstream);
		InputDataMaterialLighting(_ifstream);
	}
	void SphereObject::OutputDataFunction(std::ofstream& _ofstream)
	{
		OutputDataTransform(_ofstream);
		OutputDataMaterialLighting(_ofstream);
	}
}

_MSLIB_END