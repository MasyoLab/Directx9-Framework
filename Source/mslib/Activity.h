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
	// Content : �A�N�e�B�r�e�B
	//
	//==========================================================================
	class Activity
	{
	public:
		Activity();
		~Activity();

		/**
		@brief �A�N�e�B�r�e�B�̎擾
		@return false = �A�N�e�B�u�ł͂Ȃ� : true = �A�N�e�B�u�ł���
		*/
		bool GetActivity() const;

		/**
		@brief �A�N�e�B�r�e�B�̓o�^(false = �A�N�e�B�u�ł͂Ȃ� : true = �A�N�e�B�u�ł���)
		@param flag [in] �A�N�e�B�r�e�B�t���O
		*/
		void SetActivity(bool flag);
	private:
		bool m_activity; // �A�N�e�B�r�e�B
	};
}

_MSLIB_END