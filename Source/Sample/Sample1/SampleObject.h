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
		@brief ������
		*/
		virtual void Init() override;

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
		mslib::object::SpriteReference m_sprite;
		mslib::audio::AudioDataReference m_audio;
		mslib::boollist m_bool_list;
	};
}