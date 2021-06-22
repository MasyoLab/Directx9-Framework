//==========================================================================
// �R���W���� [Collider.h]
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
	// Content : �R���W����
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
		@brief �X�V���X�g����C�ɍX�V
		*/
		static void UpdateAll();
	protected:
		/**
		@brief ������
		*/
		virtual void Init() override;

		/**
		@brief �X�V
		*/
		virtual void Update();

		/**
		@brief GUI�ɕ\������@�\
		*/
		virtual void GUISystem() override;

		void GUICollider();
	public:
		/**
		@brief �^�[�Q�b�g�̉��
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
		@brief �^�[�Q�b�g�̉��
		*/
		void DestroyTargets();
	protected:
		/**
		@brief �^�[�Q�b�g�̓o�^
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
		@brief �^�[�Q�b�g�̉��
		*/
		void IsDestroyAccess(Collider* _target);

		/**
		@brief �^�[�Q�b�g�̉��
		*/
		void IsDestroyTargets(Collider* _target);
	public:
		/**
		@brief �e��transform
		*/
		transform::TransformReference GetColliderThis();

		/**
		@brief Collider
		*/
		reference::IReference<Collider> GetCollider();

		/**
		@brief ����̎擾
		*/
		bool IsTrigger();

		/**
		@brief ����̓o�^
		*/
		void SetTrigger(bool flag);
	private:
		Collider* GetThis();
	private:
		static std::list<Collider*> m_colliders; // �R���W�����̏����Ǘ�
	protected:
		bool m_hit; // �����蔻��
		transform::TransformReference m_this; // �e��transform
		std::shared_ptr<Collider> m_this_collider;
		std::unordered_map<Collider*, _Data> m_targets; // �^�[�Q�b�g
		std::unordered_map<Collider*, _Data> m_access; // �A�N�Z�X���Ă��Ă���R���_�[
	};

	using ColliderReference = reference::IReference<Collider>;

	/**
	@brief �����̌v�Z
	*/
	float Distance(const transform::TransformReference& t1, const transform::TransformReference& t2);

	/**
	@brief �����̌v�Z
	*/
	float Distance(const D3DXVECTOR3& t1, const D3DXVECTOR3& t2);

	/**
	@brief �����̌v�Z
	*/
	float Distance(const transform::TransformReference& t1, const D3DXVECTOR3& t2);

	/**
	@brief �����̌v�Z
	*/
	float Distance(const D3DXVECTOR3& t1, const transform::TransformReference& t2);

	/**
	@brief ���̂̃R���W����
	*/
	bool Sphere(const transform::TransformReference& t1, const transform::TransformReference& t2, float scale);

	/**
	@brief ���̂̃R���W����
	*/
	bool Sphere(const D3DXVECTOR3& t1, const D3DXVECTOR3& t2, float scale);

	/**
	@brief ���̂̃R���W����
	*/
	bool Sphere(const transform::TransformReference& t1, const D3DXVECTOR3& t2, float scale);

	/**
	@brief ���̂̃R���W����
	*/
	bool Sphere(const D3DXVECTOR3& t1, const transform::TransformReference& t2, float scale);
}

_MSLIB_END