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
		@brief 更新
		*/
		virtual void Update() override;

		/**
		@brief 姿勢行列の更新
		*/
		virtual void UpdateMatrix() override;

		/**
		@brief GUIに表示する機能
		*/
		virtual void GUISystem() override;
	private:
		mslib::reference::IReference<TransformObject> m_transform;
		float m_direction; // 向き
	};
}