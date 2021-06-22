//==========================================================================
// ゲームオブジェクト [GameObject.cpp]
// author : MasyoLab
//==========================================================================
#include "GameObject.h"
#include "MsImGui.h"
#include "string_encode.hpp"

_MSLIB_BEGIN

namespace object
{
	std::list<GameObject*> GameObject::m_objects; // 更新対象

	GameObject::GameObject() :
		Component("GameObject"), m_mat_type(MatrixType::Default)
	{
		m_objects.push_back(this);
		SetActivity(true);
	}

	GameObject::~GameObject()
	{
		auto itr = std::find(m_objects.begin(), m_objects.end(), this);
		if (itr != m_objects.end())
			m_objects.erase(itr);
	}

	void GameObject::UpdateAll()
	{
		for (auto& itr : m_objects)
		{
			if (!itr->GetActivity())
				continue;
			itr->Update();
			itr->UpdateMatrix();
		}
	}

	void GameObject::Init()
	{
	}

	void GameObject::Update()
	{
	}

	void GameObject::UpdateMatrix()
	{
	}

	void GameObject::GUISystem()
	{
		GUIGameObject();
	}

	void GameObject::GUIGameObject()
	{
#if defined(_MSLIB_DEBUG)
		bool bactivity = GetActivity();

		if (imgui::_Checkbox("Activity", &bactivity))
			SetActivity(bactivity);
#endif	
	}

	void GameObject::SetMatrixType(MatrixType _type)
	{
		m_mat_type = _type;
	}

	MatrixType GameObject::GetMatrixType() const
	{
		return m_mat_type;
	}
}

_MSLIB_END