#pragma once

#include "dxlib.h"
#include "TransformObject.h"

namespace sample2
{
	class SampleObject :
		public mslib::object::GameObject
	{
	public:
		SampleObject();
		~SampleObject();
		/**
		@brief �X�V
		*/
		virtual void Update() override;

		/**
		@brief �p���s��̍X�V
		*/
		virtual void UpdateMatrix() override;

		/**
		@brief GUI�ɕ\������@�\
		*/
		virtual void GUISystem() override;
	private:
		mslib::reference::IReference<TransformObject> m_transform;
		float m_direction; // ����
	};
}