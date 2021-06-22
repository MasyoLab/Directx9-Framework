#include "SampleObject.h"

namespace sample2
{
	constexpr float _move_range_ = 5.0f;
	constexpr float _move_range_add_ = _move_range_ + 2.0f;
	constexpr float _direction_ = 1.0f;
	constexpr float _move_speed_ = 0.05f;

	SampleObject::SampleObject() :
		m_direction(_direction_)
	{
		SetComponentName("SampleObject");

		m_transform = AddComponent(new TransformObject);
		auto distance = m_transform->AddComponent(new mslib::collider::DistanceCollider);
		auto line_circle = m_transform->AddComponent(new mslib::collider::LineCircleCollider);
		m_transform->AddComponent(new mslib::debug::Debug3D)->SetActivity(true);
		m_transform->AddPosition(0, 5, 0);

		auto obj1 = AddComponent(new TransformObject);
		auto collider1 = obj1->AddComponent(new mslib::collider::Collider);
		obj1->AddComponent(new mslib::debug::Debug3D)->SetActivity(true);
		obj1->AddPosition(0, 0, 1);

		auto obj2 = AddComponent(new TransformObject);
		auto collider2 = obj2->AddComponent(new mslib::collider::Collider);
		obj2->AddComponent(new mslib::debug::Debug3D)->SetActivity(true);
		obj2->AddPosition(-_move_range_, 5, 1);

		auto obj3 = AddComponent(new TransformObject);
		auto collider3 = obj3->AddComponent(new mslib::collider::Collider);
		obj3->AddComponent(new mslib::debug::Debug3D)->SetActivity(true);
		obj3->AddPosition(_move_range_, 5, 1);

		distance->AddTarget(collider1);
		line_circle->AddTarget(collider2, collider3);
	}

	SampleObject::~SampleObject()
	{
	}

	void SampleObject::Update()
	{
		if (!m_transform.check())
			return;

		if ((_move_range_add_) < m_transform->GetPosition().x)
			m_direction = -_direction_;

		if (m_transform->GetPosition().x < -(_move_range_add_))
			m_direction = _direction_;

		m_transform->AddPosition(_move_speed_ * m_direction, 0, 0);
	}
	void SampleObject::UpdateMatrix()
	{
	}
	void SampleObject::GUISystem()
	{
		if (!m_transform.check())
			return;

		GUIGameObject();
		m_transform->GUISystem();
	}
}