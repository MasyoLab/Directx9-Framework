//==========================================================================
// 距離コリジョン [DistanceCollider.cpp]
// author : MasyoLab
//==========================================================================
#include "DistanceCollider.h"

_MSLIB_BEGIN

namespace debug
{
	//==========================================================================
	//
	// class : DebugDistance
	// Content : 距離コリジョン
	//
	//==========================================================================
	class DebugDistance final :
		public Debug
	{
	private:
		DebugDistance(const DebugDistance&) = delete;
		DebugDistance(DebugDistance&&) = delete;
		DebugDistance& operator=(const DebugDistance&) = delete;
		DebugDistance& operator=(DebugDistance&&) = delete;
	public:
		DebugDistance();
		~DebugDistance();

		void SetTargetList(std::unordered_map<collider::Collider*, collider::_Data>* _this);
	private:
		/**
		@brief 初期化
		*/
		virtual void Init() override;

		/**
		@brief デバッグ描画
		@param device [in] デバイス
		*/
		virtual void Draw(LPDIRECT3DDEVICE9 device) override;

		/**
		@brief GUI
		*/
		virtual void GUISystem() override;
	private:
#if defined(_MSLIB_DEBUG)
		collider::DistanceColliderReference m_collider; // 親のコリジョン
		std::unordered_map<collider::Collider*, collider::_Data>* m_targets; // ターゲット
		transform::Transform m_transform;
		vertex3d::Vertex2* m_circle_default; // デフォルトの線
		vertex3d::Vertex2* m_circle_hit; // ヒット時の線
		vertex3d::Vertex2* m_decision; // 向きを表す
		float m_line_pi; // 円周率
#endif
	};
}

namespace collider
{
	DistanceCollider::DistanceCollider() :
		m_distance(1)
	{
		SetComponentName("DistanceCollider");
	}

	DistanceCollider::~DistanceCollider()
	{
	}

	void DistanceCollider::Init()
	{
		m_this = GetComponentParent<transform::Transform>();
#if defined(_MSLIB_DEBUG)
		if (m_this == nullptr)
			return;
		auto pdebug = AddComponent(new debug::DebugDistance);
		pdebug->SetActivity(true);
		pdebug->SetTargetList(&m_targets);
#endif
	}

	void DistanceCollider::Update()
	{
		if (m_this == nullptr)
			return;

		for (auto& itr : m_targets)
		{
			if (m_hit)
				return;

			if (!itr.second.GetTransform().check())
				continue;

			itr.second.GetTransform()->GetWorldMatrix();
			m_this->GetWorldMatrix();
			m_hit = Sphere(m_this, itr.second.GetTransform(), m_distance);
		}
	}

	void DistanceCollider::GUISystem()
	{
		GUICollider();
	}

	void DistanceCollider::SetDistance(float value)
	{
		m_distance = value;
	}

	float DistanceCollider::GetDistance()
	{
		return m_distance;
	}
}

namespace debug
{
	constexpr const int __num_line__ = 30;
	constexpr const int __decision_diagram__ = 4;
	constexpr const float __line_length__ = 0.2f;
	constexpr float _the_size_of_a_circle_ = 0.05f;

	DebugDistance::DebugDistance()
	{
		SetComponentName("DebugDistance");
#if defined(_MSLIB_DEBUG)
		m_targets = nullptr;
		m_circle_default = nullptr;
		m_circle_hit = nullptr;
		m_decision = nullptr;
		m_line_pi = 0.0f;
#endif
	}

	DebugDistance::~DebugDistance()
	{
#if defined(_MSLIB_DEBUG)
		mslib::_delete(m_circle_default);
		mslib::_delete(m_circle_hit);
		mslib::_delete(m_decision);
#endif
	}

	void DebugDistance::SetTargetList(std::unordered_map<collider::Collider*, collider::_Data>* _this)
	{
#if defined(_MSLIB_DEBUG)
		m_targets = _this;
#else
		_this;
#endif
	}

	void DebugDistance::Init()
	{
#if defined(_MSLIB_DEBUG)
		m_collider = GetComponentParent<collider::DistanceCollider>();
		if (m_collider == nullptr)
			return;

		mslib::_new(m_circle_default, __num_line__ + 1);
		mslib::_new(m_circle_hit, __num_line__ + 1);
		mslib::_new(m_decision, __decision_diagram__ + 1);
		m_line_pi = D3DX_PI * 2 / __num_line__;	// 円周率

		// 円の生成
		for (int i = 0; i < (__num_line__ + 1); i++)
		{
			m_circle_default[i].pos.x = ((0.0f + (cosf(m_line_pi * i) * _the_size_of_a_circle_)));
			m_circle_default[i].pos.y = 0.0f;
			m_circle_default[i].pos.z = ((0.0f + (sinf(m_line_pi * i) * _the_size_of_a_circle_)));
			m_circle_default[i].color = D3DCOLOR_RGBA(0, 255, 176, 255);

			m_circle_hit[i] = m_circle_default[i];
			m_circle_hit[i].color = D3DCOLOR_RGBA(255, 128, 0, 255);
		}
#endif
	}

	void DebugDistance::Draw(LPDIRECT3DDEVICE9 device)
	{
#if defined(_MSLIB_DEBUG)
		if (m_collider == nullptr)
			return;
		if (m_targets == nullptr)
			return;
		if (!m_collider->GetColliderThis().check())
			return;

		auto* mat1 = m_collider->GetColliderThis()->GetWorldMatrix();

		device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		device->SetTexture(0, nullptr);

		for (auto& itr : *m_targets)
		{
			if (!itr.second.GetTransform().check())
				continue;

			m_transform.SetPosition(mat1->_41, mat1->_42, mat1->_43);

			auto* mat2 = itr.second.GetTransform()->GetWorldMatrix();
			auto fdis = m_collider->GetDistance();
			auto angle = m_transform.ToSee(mat2);
			auto color = D3DCOLOR();
			mslib::vertex3d::Vertex2* circle_otr = nullptr;
			bool bhit = collider::Sphere(m_collider->GetColliderThis(), itr.second.GetTransform(), fdis);

			if (bhit) {
				circle_otr = m_circle_hit;
				color = D3DCOLOR_RGBA(255, 128, 0, 255);
			}
			else {
				circle_otr = m_circle_default;
				color = D3DCOLOR_RGBA(0, 255, 176, 255);
			}

			for (int i = 0; i < (__decision_diagram__ + 1); i++)
				m_decision[i].color = color;

			// 各種対象に向きを変える
			m_transform.GetLook().eye = -angle;
			m_transform.GetVector().front = angle;
			m_transform.GetVector().Normalize();
			m_transform.AddPosition(0, 0, fdis);
			auto* mat3 = m_transform.CreateWorldMatrix();

			m_decision[0].pos = D3DXVECTOR3(0, 0, fdis);
			m_decision[1].pos = D3DXVECTOR3(0, 0, 0);
			m_decision[2].pos = D3DXVECTOR3(-__line_length__, 0, 0);
			m_decision[3].pos = D3DXVECTOR3(__line_length__, 0, 0);
			m_decision[4].pos = m_decision[3].pos;

			// 真ん中
			device->SetTransform(D3DTS_WORLD, mat1);
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, __num_line__, circle_otr, sizeof(vertex3d::Vertex2));

			// 向き
			device->SetTransform(D3DTS_WORLD, mat3);
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, __num_line__, circle_otr, sizeof(vertex3d::Vertex2));
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, __decision_diagram__, m_decision, sizeof(vertex3d::Vertex2));
		}
#else
		device;
#endif
	}

	void DebugDistance::GUISystem()
	{
		GUIDebug();
	}
}

_MSLIB_END