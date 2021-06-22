//==========================================================================
// 線と球のコリジョン [LineCircleCollider.cpp]
// author : MasyoLab
//==========================================================================
#include "LineCircleCollider.h"

_MSLIB_BEGIN

namespace debug
{
	inline D3DXVECTOR3 operator*(const D3DXVECTOR3& _Left, const D3DXVECTOR3& _Right) {
		return D3DXVECTOR3(_Left.x * _Right.x, _Left.y * _Right.y, _Left.z * _Right.z);
	}

	//==========================================================================
	//
	// class : DebugLineCircle
	// Content : 
	//
	//==========================================================================
	class DebugLineCircle final :
		public Debug
	{
	private:
		DebugLineCircle(const DebugLineCircle&) = delete;
		DebugLineCircle(DebugLineCircle&&) = delete;
		DebugLineCircle& operator=(const DebugLineCircle&) = delete;
		DebugLineCircle& operator=(DebugLineCircle&&) = delete;
	public:
		DebugLineCircle();
		~DebugLineCircle();

		void SetTargetList(std::list<collider::_EndPoint>* _this1, std::unordered_map<collider::Collider*, collider::_Data>* _this2);
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
		collider::LineCircleColliderReference m_collider; // 親のコリジョン
		std::unordered_map<collider::Collider*, collider::_Data>* m_targets; // ターゲット
		std::list<collider::_EndPoint>* m_EndPoint; // 端点
		transform::Transform m_PointATransform; // 端点A
		transform::Transform m_PointBTransform; // 端点B
		transform::Transform m_PointCTransform; // 線分と円との距離
		transform::Transform m_PointDTransform; // 線分と円との距離
		vertex3d::Vertex2* m_circle_default; // デフォルトの線
		vertex3d::Vertex2* m_circle_hit; // ヒット時の線
		vertex3d::Vertex2* m_EndPointLine; // 端点を結ぶ線
		vertex3d::Vertex2* m_decision; // 向きを表す
		float m_line_pi; // 円周率
#endif
	};
}

namespace collider
{
	float Intersection(D3DXVECTOR3& v1, D3DXVECTOR3& v2, D3DXVECTOR3& pos);
	float Intersection(D3DXVECTOR3& v1, D3DXVECTOR3& v2, D3DXVECTOR3& pos)
	{
		auto Vec1 = (pos - v1) * (v2 - v1);
		auto Vec2 = (v2 - v1) * (v2 - v1);
		return (Vec1.x + Vec1.y + Vec1.z) / (Vec2.x + Vec2.y + Vec2.z);
	}

	_EndPoint::_EndPoint()
	{
		m_EndPointA = nullptr;
		m_EndPointB = nullptr;
		m_Intersection = D3DXVECTOR3(0, 0, 0);
		m_hit = false;
	}
	_EndPoint::_EndPoint(collider::Collider* _EndPointA, collider::Collider* _EndPointB) :
		m_EndPointA(_EndPointA), m_EndPointB(_EndPointB), m_Intersection(0, 0, 0)
	{
	}
	_EndPoint::~_EndPoint()
	{
	}
	collider::Collider* collider::_EndPoint::GetEndPointA()
	{
		return m_EndPointA;
	}

	collider::Collider* collider::_EndPoint::GetEndPointB()
	{
		return m_EndPointB;
	}

	bool _EndPoint::IsTrigger()
	{
		return m_hit;
	}

	void _EndPoint::SetTrigger(bool flag)
	{
		m_hit = flag;
	}

	void _EndPoint::SetIntersection(const D3DXVECTOR3& _inte)
	{
		m_Intersection = _inte;
	}

	const D3DXVECTOR3& _EndPoint::GetIntersection() const
	{
		return m_Intersection;
	}

	LineCircleCollider::LineCircleCollider() :
		m_distance(1)
	{
		SetComponentName("LineCircleCollider");
	}
	LineCircleCollider::~LineCircleCollider()
	{
	}
	void LineCircleCollider::Init()
	{
		m_this = GetComponentParent<transform::Transform>();
#if defined(_MSLIB_DEBUG)
		if (m_this == nullptr)
			return;
		auto pdebug = AddComponent(new debug::DebugLineCircle);
		pdebug->SetActivity(true);
		pdebug->SetTargetList(&m_EndPoint, &m_targets);
#endif
	}
	void LineCircleCollider::Update()
	{
		if (m_this == nullptr)
			return;

		for (auto& itr : m_EndPoint)
		{
			if (m_hit)
				return;

			// 端点を取り出す
			auto endPointA = m_targets.find(itr.GetEndPointA());
			auto endPointB = m_targets.find(itr.GetEndPointB());
			itr.SetTrigger(false);

			// 端点が存在しない場合
			if (endPointA == m_targets.end() || endPointB == m_targets.end())
				continue;
			// 端点がnullだった場合
			if (endPointA->second.GetTransform() == nullptr || endPointB->second.GetTransform() == nullptr)
				continue;
			
			// 線分の端点と円の中心までの距離でチェック ------------------------------------
			// 端点
			bool bA = collider::Sphere(m_this, endPointA->second.GetTransform(), m_distance);
			bool bB = collider::Sphere(m_this, endPointB->second.GetTransform(), m_distance);
			if (bA || bB) {
				itr.SetTrigger(true);
				m_hit = true;
			}

			// 交点を求める ------------------------------------
			auto* matA = endPointA->second.GetTransform()->GetWorldMatrix();
			auto* matB = endPointB->second.GetTransform()->GetWorldMatrix();
			auto* matP = m_this->GetWorldMatrix();
			auto LinePos1 = D3DXVECTOR3(matA->_41, matA->_42, matA->_43);
			auto LinePos2 = D3DXVECTOR3(matB->_41, matB->_42, matB->_43);
			auto CirclePos = D3DXVECTOR3(matP->_41, matP->_42, matP->_43);
			float t = Intersection(LinePos1, LinePos2, CirclePos);

			// 線分と円との最短距離でチェック ------------------------------------
			if (0 <= t && t <= 1)
			{
				// 円の中心から線分へ伸びる垂線を考える ------------------------------------
				itr.SetIntersection((LinePos2 - LinePos1) * t + LinePos1);

				auto pc3 = (CirclePos - itr.GetIntersection()) * (CirclePos - itr.GetIntersection());
				auto r2 = m_distance * m_distance;

				if (pc3.x + pc3.y + pc3.z < r2) {
					itr.SetTrigger(true);
					m_hit = true;
				}
			}
		}
	}
	void LineCircleCollider::SetDistance(float value)
	{
		m_distance = value;
	}
	float LineCircleCollider::GetDistance()
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
	constexpr const int __EndPointLine__ = 2;

	DebugLineCircle::DebugLineCircle()
	{
		SetComponentName("DebugLineCircle");
#if defined(_MSLIB_DEBUG)
		m_EndPoint = nullptr;
		m_targets = nullptr;
		m_circle_default = nullptr;
		m_circle_hit = nullptr;
		m_decision = nullptr;
		m_EndPointLine = nullptr;
		m_line_pi = 0.0f;
#endif
	}
	DebugLineCircle::~DebugLineCircle()
	{
#if defined(_MSLIB_DEBUG)
		mslib::_delete(m_circle_default);
		mslib::_delete(m_circle_hit);
		mslib::_delete(m_decision);
		mslib::_delete(m_EndPointLine);
#endif
	}
	void DebugLineCircle::SetTargetList(std::list<collider::_EndPoint>* _this1, std::unordered_map<collider::Collider*, collider::_Data>* _this2)
	{
#if defined(_MSLIB_DEBUG)
		m_EndPoint = _this1;
		m_targets = _this2;
#else
		_this1;
		_this2;
#endif
	}
	void DebugLineCircle::Init()
	{
#if defined(_MSLIB_DEBUG)
		m_collider = GetComponentParent<collider::LineCircleCollider>();
		if (m_collider == nullptr)
			return;

		mslib::_new(m_circle_default, __num_line__ + 1);
		mslib::_new(m_circle_hit, __num_line__ + 1);
		mslib::_new(m_decision, __decision_diagram__ + 1);
		mslib::_new(m_EndPointLine, __EndPointLine__ + 1);
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
	void DebugLineCircle::Draw(LPDIRECT3DDEVICE9 device)
	{
#if defined(_MSLIB_DEBUG)
		if (m_collider == nullptr)
			return;
		if (m_EndPoint == nullptr)
			return;
		if (m_targets == nullptr)
			return;
		if (!m_collider->GetColliderThis().check())
			return;

		auto* mat1 = m_collider->GetColliderThis()->GetWorldMatrix();

		device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		device->SetTexture(0, nullptr);

		for (auto& itr : *m_EndPoint)
		{
			// 端点を取り出す
			auto endPointA = m_targets->find(itr.GetEndPointA());
			auto endPointB = m_targets->find(itr.GetEndPointB());

			// 端点が存在しない場合
			if (endPointA == m_targets->end() || endPointB == m_targets->end())
				continue;
			// 端点がnullだった場合
			if (endPointA->second.GetTransform() == nullptr || endPointB->second.GetTransform() == nullptr)
				continue;

			m_PointATransform.SetPosition(mat1->_41, mat1->_42, mat1->_43);
			m_PointBTransform.SetPosition(mat1->_41, mat1->_42, mat1->_43);
			m_PointCTransform.SetPosition(mat1->_41, mat1->_42, mat1->_43);
			m_PointDTransform.SetPosition(itr.GetIntersection());

			auto* matendPointA = endPointA->second.GetTransform()->GetWorldMatrix();
			auto* matendPointB = endPointB->second.GetTransform()->GetWorldMatrix();
			auto* matendPointC = m_PointDTransform.CreateWorldMatrix();
			auto fdis = m_collider->GetDistance();
			auto angleA = m_PointATransform.ToSee(matendPointA);
			auto angleB = m_PointBTransform.ToSee(matendPointB);
			auto angleC = m_PointCTransform.ToSee(matendPointC);
			auto color = D3DCOLOR();
			D3DXMATRIX mat;
			vertex3d::Vertex2* circle_otr = nullptr;

			if (itr.IsTrigger()) {
				circle_otr = m_circle_hit;
				color = D3DCOLOR_RGBA(255, 128, 0, 255);
			}
			else {
				circle_otr = m_circle_default;
				color = D3DCOLOR_RGBA(0, 255, 176, 255);
			}

			for (int i = 0; i < (__decision_diagram__ + 1); i++)
				m_decision[i].color = color;
			for (int i = 0; i < (__EndPointLine__ + 1); i++)
				m_EndPointLine[i].color = color;

			// 各種対象に向きを変える
			m_PointATransform.GetLook().eye = -angleA;
			m_PointATransform.GetVector().front = angleA;
			m_PointATransform.GetVector().Normalize();
			m_PointATransform.AddPosition(0, 0, fdis);
			m_PointBTransform.GetLook().eye = -angleB;
			m_PointBTransform.GetVector().front = angleB;
			m_PointBTransform.GetVector().Normalize();
			m_PointBTransform.AddPosition(0, 0, fdis);
			m_PointCTransform.GetLook().eye = -angleC;
			m_PointCTransform.GetVector().front = angleC;
			m_PointCTransform.GetVector().Normalize();
			m_PointCTransform.AddPosition(0, 0, fdis);
			auto* mat2 = m_PointATransform.CreateWorldMatrix();
			auto* mat3 = m_PointBTransform.CreateWorldMatrix();
			auto* mat4 = m_PointCTransform.CreateWorldMatrix();

			m_decision[0].pos = D3DXVECTOR3(0, 0, fdis);
			m_decision[1].pos = D3DXVECTOR3(0, 0, 0);
			m_decision[2].pos = D3DXVECTOR3(-__line_length__, 0, 0);
			m_decision[3].pos = D3DXVECTOR3(__line_length__, 0, 0);
			m_decision[4].pos = m_decision[3].pos;

			m_EndPointLine[0].pos = D3DXVECTOR3(matendPointA->_41, matendPointA->_42, matendPointA->_43);
			m_EndPointLine[1].pos = D3DXVECTOR3(matendPointB->_41, matendPointB->_42, matendPointB->_43);
			m_EndPointLine[2].pos = m_EndPointLine[1].pos;

			// 真ん中
			device->SetTransform(D3DTS_WORLD, mat1);
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, __num_line__, circle_otr, sizeof(vertex3d::Vertex2));

			// 端点を結ぶ線と真ん中の位置
			device->SetTransform(D3DTS_WORLD, matendPointC);
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, __num_line__, circle_otr, sizeof(vertex3d::Vertex2));

			// 端点への向きA
			device->SetTransform(D3DTS_WORLD, mat2);
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, __num_line__, circle_otr, sizeof(vertex3d::Vertex2));
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, __decision_diagram__, m_decision, sizeof(vertex3d::Vertex2));

			// 端点への向きB
			device->SetTransform(D3DTS_WORLD, mat3);
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, __num_line__, circle_otr, sizeof(vertex3d::Vertex2));
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, __decision_diagram__, m_decision, sizeof(vertex3d::Vertex2));

			// 端点を結ぶ線
			device->SetTransform(D3DTS_WORLD, mat4);
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, __num_line__, circle_otr, sizeof(vertex3d::Vertex2));
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, __decision_diagram__, m_decision, sizeof(vertex3d::Vertex2));

			// 端点を繋ぐ線
			device->SetTransform(D3DTS_WORLD, D3DXMatrixIdentity(&mat));
			device->DrawPrimitiveUP(D3DPT_LINESTRIP, __EndPointLine__, m_EndPointLine, sizeof(vertex3d::Vertex2));
		}
#else
		device;
#endif
	}
	void DebugLineCircle::GUISystem()
	{
		GUIDebug();
	}
}

_MSLIB_END