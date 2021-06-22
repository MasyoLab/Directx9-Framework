//==========================================================================
// �����R���W���� [DistanceCollider.h]
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
	// Content : �����R���W����
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
		@brief ������
		*/
		virtual void Init() override;

		/**
		@brief �X�V
		*/
		virtual void Update() override;

		/**
		@brief GUI�ɕ\������@�\
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
		@brief ���苗���̓o�^
		@param value [in] ���苗��
		*/
		void SetDistance(float value);

		/**
		@brief ���苗���̎擾
		*/
		float GetDistance();
	private:
		float m_distance;
	};

	using DistanceColliderReference = reference::IReference<DistanceCollider>;
}

_MSLIB_END