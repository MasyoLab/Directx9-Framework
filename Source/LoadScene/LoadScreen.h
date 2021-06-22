//==========================================================================
// ���[�h�X�N���[��[LoadScreen.h]
// author: MasyoLab
//==========================================================================
#pragma once

//==========================================================================
// include
//==========================================================================
#include "dxlib.h"

namespace load_screen
{
	//==========================================================================
	//
	// class  : LoadScreen
	// Content: ���[�h�X�N���[��
	//
	//==========================================================================
	class LoadScreen : public mslib::object::GameObject
	{
	private:
		// �p�����[�^
		class Param
		{
		public:
			Param()
			{
				m_a = 0;
				m_Change = false;
			}
			~Param() {}
		public:
			int m_a; // ��
			bool m_Change; // change
		};
	public:
		LoadScreen();
		~LoadScreen();

		/**
		@brief ������
		*/
		virtual void Init() override;

		/**
		@brief �X�V
		*/
		virtual void Update() override;
	private:
		// ���`�F���W
		void Change(int Speed);
	private:
		Param m_paramload; // �p�����[�^
		DWORD m_NewTime = 0, m_OldTime = 0; //���Ԋi�[
		mslib::object::SpriteReference m_ring;
		mslib::object::SpriteReference m_font;
	};
}