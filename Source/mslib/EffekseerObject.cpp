//==========================================================================
// Effekseerオブジェクト [EffekseerObject.cpp]
// author : MasyoLab
//==========================================================================
#include "EffekseerObject.h"

_MSLIB_BEGIN

namespace object
{
	EffekseerObject::EffekseerObject() :
		m_handle(effekseer_dx::stop_handle)
	{
		SetComponentName("EffekseerObject");
		SetActivity(true);
		SetMatrixType(MatrixType::World);
	}
	EffekseerObject::EffekseerObject(bool _bInOutFunctionFlag) :
		InOutFunction(_bInOutFunctionFlag), m_handle(effekseer_dx::stop_handle)
	{
		SetComponentName("EffekseerObject");
		SetActivity(true);
		SetMatrixType(MatrixType::World);
	}
	EffekseerObject::~EffekseerObject()
	{
		Stop();
	}
	void EffekseerObject::Play()
	{
		if (!m_effekseer_data.check())
			return;
		if (m_effekseer_data->GetManager()->Exists(m_handle))
			m_effekseer_data->GetManager()->StopEffect(m_handle);
		m_handle = m_effekseer_data->Play(m_world_matrix._41, m_world_matrix._42, m_world_matrix._43);
	}
	void EffekseerObject::Stop()
	{
		if (!m_effekseer_data.check())
			return;
		if (m_handle == effekseer_dx::stop_handle)
			return;

		if (m_effekseer_data->GetManager()->Exists(m_handle))
			m_effekseer_data->GetManager()->StopEffect(m_handle);
		m_handle = effekseer_dx::stop_handle;
	}
	void EffekseerObject::SetTarget(transform::TransformReference obj)
	{
		m_transform = obj;
	}
	void EffekseerObject::Update()
	{
		if (!m_effekseer_data.check())
			return;
		if (m_handle == effekseer_dx::stop_handle)
			return;
		
		m_effekseer_data->GetManager()->SetLocation(m_handle, m_world_matrix._41, m_world_matrix._42, m_world_matrix._43);
		m_effekseer_data->GetManager()->SetScale(m_handle, m_parameter.scale.x, m_parameter.scale.y, m_parameter.scale.z);
		m_effekseer_data->GetManager()->SetRotation(m_handle, m_parameter.rotation.y, m_parameter.rotation.x, m_parameter.rotation.z);

		if (m_transform == nullptr)
			return;
		auto mat = m_transform->GetWorldMatrix();
		m_effekseer_data->GetManager()->SetTargetLocation(m_handle, mat->_41, mat->_42, mat->_43);
	}
	void EffekseerObject::UpdateMatrix()
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
	void EffekseerObject::GUISystem()
	{
		GUIGameObject();
		GUITransform();
	}
	void EffekseerObject::InputDataFunction(std::ifstream& _ifstream)
	{
		InputDataTransform(_ifstream);
	}
	void EffekseerObject::OutputDataFunction(std::ofstream& _ofstream)
	{
		OutputDataTransform(_ofstream);
	}
}

_MSLIB_END