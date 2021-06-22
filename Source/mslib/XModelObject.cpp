//==========================================================================
// XModelオブジェクト [XModelObject.cpp]
// author : MasyoLab
//==========================================================================
#include "XModelObject.h"

_MSLIB_BEGIN

namespace object
{
	using renderer::RendererID;

	XModelObject::XModelObject() :
		Renderer(RendererID::Xmodel)
	{
		SetComponentName("Xmodel");
		SetActivity(true);
		SetMatrixType(MatrixType::World);
	}
	XModelObject::XModelObject(bool _bInOutFunctionFlag) :
		Renderer(RendererID::Xmodel), InOutFunction(_bInOutFunctionFlag)
	{
		SetComponentName("Xmodel");
		SetActivity(true);
		SetMatrixType(MatrixType::World);
	}
	XModelObject::~XModelObject()
	{
	}
	void XModelObject::Update()
	{
	}
	void XModelObject::UpdateMatrix()
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
	void XModelObject::Draw(LPDIRECT3DDEVICE9 device)
	{
		// 呼ばれたら更新の無効化
		SetUpdateKey(false);

		// 存在しない場合終了
		if (!m_XModelData.check())
			return;

		device->SetTransform(D3DTS_WORLD, &m_world_matrix);
		device->SetMaterial(&GetMaterialLighting());
		device->SetFVF(m_XModelData->GetMesh()->GetFVF());

		for (int i = 0; i < (int)m_XModelData->GetNumMaterial(); i++)
		{
			auto texture = m_XModelData->GetTexture(i);
			if (!texture.check())
				continue;
			device->SetTexture(0, texture->GetTexture());
			m_XModelData->GetMesh()->DrawSubset(i);
			device->SetTexture(0, nullptr);
		}
	}
	void XModelObject::GUISystem()
	{
		GUIGameObject();
		GUITransform();
		GUIMaterialLighting();
	}
	void XModelObject::InputDataFunction(std::ifstream& _ifstream)
	{
		InputDataTransform(_ifstream);
		InputDataMaterialLighting(_ifstream);
	}
	void XModelObject::OutputDataFunction(std::ofstream& _ofstream)
	{
		OutputDataTransform(_ofstream);
		OutputDataMaterialLighting(_ofstream);
	}
}

_MSLIB_END