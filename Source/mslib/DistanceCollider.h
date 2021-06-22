//==========================================================================
// 距離コリジョン [DistanceCollider.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "Collider.h"

_MSLIB_BEGIN

namespace collider
{
	//==========================================================================
	//
	// class : DistanceCollider
	// Content : 距離コリジョン
	//
	//==========================================================================
	class DistanceCollider final:
		public Collider
	{
	private:
		DistanceCollider(const DistanceCollider&) = delete;
		DistanceCollider(DistanceCollider&&) = delete;
		DistanceCollider& operator=(const DistanceCollider&) = delete;
		DistanceCollider& operator=(DistanceCollider&&) = delete;
	public:
		DistanceCollider();
		~DistanceCollider();
	protected:
		/**
		@brief 初期化
		*/
		virtual void Init() override;

		/**
		@brief 更新
		*/
		virtual void Update() override;

		/**
		@brief GUIに表示する機能
		*/
		virtual void GUISystem() override;
	public:
		template <typename _Ty, bool isExtended = std::is_base_of<Collider, _Ty>::value>
		void AddTarget(reference::IReference<_Ty>& _target)
		{
			static_assert(isExtended, "AddTarget<> : _Ty is not inherited from Collider Class");
			AddTargetCollider(_target);
		}

		/**
		@brief 判定距離の登録
		@param value [in] 判定距離
		*/
		void SetDistance(float value);

		/**
		@brief 判定距離の取得
		*/
		float GetDistance();
	private:
		float m_distance;
	};

	using DistanceColliderReference = reference::IReference<DistanceCollider>;
}

_MSLIB_END