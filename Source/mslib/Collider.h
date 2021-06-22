//==========================================================================
// コリジョン [Collider.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "mslib.hpp"
#include "Component.h"
#include "Reference.h"
#include "Initializer.h"
#include "Transform.h"
#include "Activity.h"
#include "Debug.h"
#include "Vertex3d.h"
#include "GUI.h"

_MSLIB_BEGIN

namespace collider
{
	class Collider;
	class _Data
	{
	public:
		_Data();
		_Data(Collider* _this, transform::TransformReference& _par);
		~_Data();
		Collider* GetCollider();
		transform::TransformReference GetTransform();
	private:
		Collider* m_collider;
		transform::TransformReference* m_transform;
	};

	//==========================================================================
	//
	// class : Collider
	// Content : コリジョン
	//
	//==========================================================================
	class Collider :
		virtual public component::Component,
		public gui::GUI,
		public activity::Activity,
		public initializer::Initializer
	{
	private:
		Collider(const Collider&) = delete;
		Collider(Collider&&) = delete;
		Collider& operator=(const Collider&) = delete;
		Collider& operator=(Collider&&) = delete;
	public:
		Collider();
		virtual ~Collider();

		/**
		@brief 更新リストを一気に更新
		*/
		static void UpdateAll();
	protected:
		/**
		@brief 初期化
		*/
		virtual void Init() override;

		/**
		@brief 更新
		*/
		virtual void Update();

		/**
		@brief GUIに表示する機能
		*/
		virtual void GUISystem() override;

		void GUICollider();
	public:
		/**
		@brief ターゲットの解放
		*/
		template <typename _Ty, bool isExtended = std::is_base_of<Collider, _Ty>::value>
		void DestroyTargets(reference::IReference<_Ty> _target)
		{
			static_assert(isExtended, "DestroyTargets<> : _Ty is not inherited from Collider Class");
			if (!_target.check())
				return;
			IsDestroyTargets(this);
			_target->IsDestroyAccess(this);
		}

		/**
		@brief ターゲットの解放
		*/
		void DestroyTargets();
	protected:
		/**
		@brief ターゲットの登録
		*/
		template <typename _Ty, bool isExtended = std::is_base_of<Collider, _Ty>::value>
		Collider * AddTargetCollider(reference::IReference<_Ty>& _target)
		{
			static_assert(isExtended, "AddTargetCollider<> : _Ty is not inherited from Collider Class");
			if (!_target.check())
				return nullptr;
			m_targets[_target->GetThis()] = _Data(_target->GetThis(), _target->m_this);
			_target->m_access[this] = _Data(this, m_this);
			return _target->GetThis();
		}
	private:
		/**
		@brief ターゲットの解放
		*/
		void IsDestroyAccess(Collider* _target);

		/**
		@brief ターゲットの解放
		*/
		void IsDestroyTargets(Collider* _target);
	public:
		/**
		@brief 親のtransform
		*/
		transform::TransformReference GetColliderThis();

		/**
		@brief Collider
		*/
		reference::IReference<Collider> GetCollider();

		/**
		@brief 判定の取得
		*/
		bool IsTrigger();

		/**
		@brief 判定の登録
		*/
		void SetTrigger(bool flag);
	private:
		Collider* GetThis();
	private:
		static std::list<Collider*> m_colliders; // コリジョンの処理管理
	protected:
		bool m_hit; // 当たり判定
		transform::TransformReference m_this; // 親のtransform
		std::shared_ptr<Collider> m_this_collider;
		std::unordered_map<Collider*, _Data> m_targets; // ターゲット
		std::unordered_map<Collider*, _Data> m_access; // アクセスしてきているコリダー
	};

	using ColliderReference = reference::IReference<Collider>;

	/**
	@brief 距離の計算
	*/
	float Distance(const transform::TransformReference& t1, const transform::TransformReference& t2);

	/**
	@brief 距離の計算
	*/
	float Distance(const D3DXVECTOR3& t1, const D3DXVECTOR3& t2);

	/**
	@brief 距離の計算
	*/
	float Distance(const transform::TransformReference& t1, const D3DXVECTOR3& t2);

	/**
	@brief 距離の計算
	*/
	float Distance(const D3DXVECTOR3& t1, const transform::TransformReference& t2);

	/**
	@brief 球体のコリジョン
	*/
	bool Sphere(const transform::TransformReference& t1, const transform::TransformReference& t2, float scale);

	/**
	@brief 球体のコリジョン
	*/
	bool Sphere(const D3DXVECTOR3& t1, const D3DXVECTOR3& t2, float scale);

	/**
	@brief 球体のコリジョン
	*/
	bool Sphere(const transform::TransformReference& t1, const D3DXVECTOR3& t2, float scale);

	/**
	@brief 球体のコリジョン
	*/
	bool Sphere(const D3DXVECTOR3& t1, const transform::TransformReference& t2, float scale);
}

_MSLIB_END