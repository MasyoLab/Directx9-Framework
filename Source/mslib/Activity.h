//==========================================================================
// Activity [Activity.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "mslib.hpp"

_MSLIB_BEGIN

namespace activity
{
	//==========================================================================
	//
	// class : Activity
	// Content : アクティビティ
	//
	//==========================================================================
	class Activity
	{
	public:
		Activity();
		~Activity();

		/**
		@brief アクティビティの取得
		@return false = アクティブではない : true = アクティブである
		*/
		bool GetActivity() const;

		/**
		@brief アクティビティの登録(false = アクティブではない : true = アクティブである)
		@param flag [in] アクティビティフラグ
		*/
		void SetActivity(bool flag);
	private:
		bool m_activity; // アクティビティ
	};
}

_MSLIB_END