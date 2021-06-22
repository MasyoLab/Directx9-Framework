//==========================================================================
// コリジョン [Collider.cpp]
// author : MasyoLab
//==========================================================================
#include "Collider.h"

_MSLIB_BEGIN

namespace collider
{
	std::list<Collider*> Collider::m_colliders; // コリジョンの処理管理

	_Data::_Data() :
		m_collider(nullptr), m_transform(nullptr)
	{
	}

	collider::_Data::_Data(Collider* _this, transform::TransformReference& _par) :
		m_collider(_this), m_transform(&_par)
	{
	}

	_Data::~_Data()
	{
	}

	Collider* _Data::GetCollider()
	{
		return m_collider;
	}

	transform::TransformReference _Data::GetTransform()
	{
		return *m_transform;
	}

	Collider::Collider() :
		m_hit(false)
	{
		SetComponentName("Collider");
		SetActivity(true);
		m_this_collider = std::shared_ptr<Collider>(this, [](Collider* p) {p = nullptr; });
		m_colliders.push_back(this);
	}

	Collider::~Collider()
	{
		DestroyTargets();
		auto itr = std::find(m_colliders.begin(), m_colliders.end(), this);
		if (itr != m_colliders.end())
			m_colliders.erase(itr);
	}

	void Collider::UpdateAll()
	{
		for (auto& itr : m_colliders)
		{
			if (!itr->GetActivity())
				continue;
			itr->m_hit = false;
			itr->Update();
		}
	}

	void Collider::Init()
	{
		m_this = GetComponentParent<transform::Transform>();
	}

	void Collider::Update()
	{
	}

	void Collider::GUISystem()
	{
		GUICollider();
	}

	void Collider::GUICollider()
	{
#if defined(_MSLIB_DEBUG)
		bool bactivity = GetActivity();

		if (imgui::_Checkbox("Activity", &bactivity))
			SetActivity(bactivity);
#endif	
	}

	void Collider::DestroyTargets()
	{
		for (auto& itr : m_access)
			itr.second.GetCollider()->IsDestroyTargets(this);
		for (auto& itr : m_targets)
			itr.second.GetCollider()->IsDestroyAccess(this);
		m_targets.clear();
		m_access.clear();
	}

	void Collider::IsDestroyAccess(Collider* _target)
	{
		if (_target == nullptr)
			return;
		auto itr = m_access.find(_target);
		if (itr != m_access.end())
			m_access.erase(itr);
	}

	void Collider::IsDestroyTargets(Collider* _target)
	{
		if (_target == nullptr)
			return;
		auto itr = m_targets.find(_target);
		if (itr != m_targets.end())
			m_targets.erase(itr);
	}

	transform::TransformReference Collider::GetColliderThis()
	{
		return m_this;
	}

	reference::IReference<Collider> Collider::GetCollider()
	{
		return m_this_collider;
	}

	bool Collider::IsTrigger()
	{
		return m_hit;
	}

	void Collider::SetTrigger(bool flag)
	{
		m_hit = flag;
	}

	Collider* Collider::GetThis()
	{
		return this;
	}

	float Distance(const transform::TransformReference& t1, const transform::TransformReference& t2)
	{
		auto* m1 = t1->GetWorldMatrix();
		auto* m2 = t2->GetWorldMatrix();

		return Distance(D3DXVECTOR3(m1->_41, m1->_42, m1->_43), D3DXVECTOR3(m2->_41, m2->_42, m2->_43));
	}

	float Distance(const D3DXVECTOR3& t1, const D3DXVECTOR3& t2)
	{
		auto t3 = t2 - t1;
		return D3DXVec3LengthSq(&t3);
	}

	float Distance(const transform::TransformReference& t1, const D3DXVECTOR3& t2)
	{
		auto* m1 = t1->GetWorldMatrix();

		return Distance(D3DXVECTOR3(m1->_41, m1->_42, m1->_43), t2);
	}

	float Distance(const D3DXVECTOR3& t1, const transform::TransformReference& t2)
	{
		auto* m2 = t2->GetWorldMatrix();

		return Distance(t1, D3DXVECTOR3(m2->_41, m2->_42, m2->_43));
	}

	bool Sphere(const transform::TransformReference& t1, const transform::TransformReference& t2, float scale)
	{
		return Distance(t1, t2) < scale ? true : false;
	}

	bool Sphere(const D3DXVECTOR3& t1, const D3DXVECTOR3& t2, float scale)
	{
		return Distance(t1, t2) < scale ? true : false;
	}

	bool Sphere(const transform::TransformReference& t1, const D3DXVECTOR3& t2, float scale)
	{
		return Distance(t1, t2) < scale ? true : false;
	}

	bool Sphere(const D3DXVECTOR3& t1, const transform::TransformReference& t2, float scale)
	{
		return Distance(t1, t2) < scale ? true : false;
	}
}


_MSLIB_END