//==========================================================================
// Initializer [Initializer.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <list>

#include "mslib.hpp"

_MSLIB_BEGIN

namespace initializer
{
	class Initializer
	{
	private:
		Initializer(const Initializer&) = delete;
		Initializer(Initializer&&) = delete;
		Initializer& operator=(const Initializer&) = delete;
		Initializer& operator=(Initializer&&) = delete;
	public:
		Initializer();
		virtual ~Initializer();

		/**
		@brief �S�ď�����
		*/
		static void InitAll();

		/**
		@brief 1����������
		*/
		static void InitOne();

		/**
		@brief ���������̎擾
		*/
		static int GetInitAllSize();

		static void InitAllLock();
		static void InitAllUnLock();
	protected:
		/**
		@brief �p��������
		*/
		virtual void Init();
	private:
		static bool m_init_all_lock;
		static std::list<Initializer*> m_initializers; // ���������X�g
	};
}

_MSLIB_END