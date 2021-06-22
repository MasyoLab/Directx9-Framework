//==========================================================================
// ü‚Æ‹…‚ÌƒRƒŠƒWƒ‡ƒ“ [LineCircleCollider.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "Collider.h"

_MSLIB_BEGIN

namespace collider
{
	inline D3DXVECTOR3 operator*(const D3DXVECTOR3& _Left, const D3DXVECTOR3& _Right) {
		return D3DXVECTOR3(_Left.x * _Right.x, _Left.y * _Right.y, _Left.z * _Right.z);
	}

	class _EndPoint
	{
	public:
		_EndPoint();
		_EndPoint(mslib::collider::Collider* _EndPointA, mslib::collider::Collider* _EndPointB);
		~_EndPoint();
		mslib::collider::Collider* GetEndPointA();
		mslib::collider::Collider* GetEndPointB();
		bool IsTrigger();
		void SetTrigger(bool flag);
		// ‰~‚Ì’†S‚©‚çü•ª‚ÖL‚Ñ‚é‚ü
		void SetIntersection(const D3DXVECTOR3& _inte);
		// ‰~‚Ì’†S‚©‚çü•ª‚ÖL‚Ñ‚é‚ü
		const D3DXVECTOR3& GetIntersection()const;
	private:
		mslib::collider::Collider* m_EndPointA;
		mslib::collider::Collider* m_EndPointB;
		D3DXVECTOR3 m_Intersection; // ‰~‚Ì’†S‚©‚çü•ª‚ÖL‚Ñ‚é‚ü
		bool m_hit;
	};

	class LineCircleCollider final :
		public mslib::collider::Collider
	{
	private:
		LineCircleCollider(const LineCircleCollider&) = delete;
		LineCircleCollider(LineCircleCollider&&) = delete;
		LineCircleCollider& operator=(const LineCircleCollider&) = delete;
		LineCircleCollider& operator=(LineCircleCollider&&) = delete;
	public:
		LineCircleCollider();
		~LineCircleCollider();
	protected:
		/**
		@brief ‰Šú‰»
		*/
		virtual void Init() override;

		/**
		@brief XV
		*/
		virtual void Update() override;
	public:
		template <typename _Ty, bool isExtended = std::is_base_of<Collider, _Ty>::value>
		void AddTarget(mslib::reference::IReference<_Ty>& _EndPointA, mslib::reference::IReference<_Ty>& _EndPointB)
		{
			static_assert(isExtended, "AddTarget<> : _Ty is not inherited from Collider Class");
			m_EndPoint.push_back(_EndPoint(AddTargetCollider(_EndPointA), AddTargetCollider(_EndPointB)));
		}

		/**
		@brief ”»’è‹——£‚Ì“o˜^
		@param value [in] ”»’è‹——£
		*/
		void SetDistance(float value);

		/**
		@brief ”»’è‹——£‚Ìæ“¾
		*/
		float GetDistance();
	private:
		std::list<_EndPoint> m_EndPoint; // ƒ^[ƒQƒbƒg
		float m_distance; // ƒTƒCƒY
	};

	using LineCircleColliderReference = mslib::reference::IReference<LineCircleCollider>;
}

_MSLIB_END