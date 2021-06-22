#pragma once

#include "dxlib.h"

namespace sample1
{
	class SampleObject :
		public mslib::object::GameObject
	{
	public:
		SampleObject();
		~SampleObject();

		/**
		@brief 初期化
		*/
		virtual void Init() override;

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
		mslib::object::SpriteReference m_sprite;
		mslib::audio::AudioDataReference m_audio;
		mslib::boollist m_bool_list;
	};
}