//==========================================================================
// ロードスクリーン[LoadScreen.h]
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
	// Content: ロードスクリーン
	//
	//==========================================================================
	class LoadScreen : public mslib::object::GameObject
	{
	private:
		// パラメータ
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
			int m_a; // α
			bool m_Change; // change
		};
	public:
		LoadScreen();
		~LoadScreen();

		/**
		@brief 初期化
		*/
		virtual void Init() override;

		/**
		@brief 更新
		*/
		virtual void Update() override;
	private:
		// αチェンジ
		void Change(int Speed);
	private:
		Param m_paramload; // パラメータ
		DWORD m_NewTime = 0, m_OldTime = 0; //時間格納
		mslib::object::SpriteReference m_ring;
		mslib::object::SpriteReference m_font;
	};
}