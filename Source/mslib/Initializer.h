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
		@brief ‘S‚Ä‰Šú‰»
		*/
		static void InitAll();

		/**
		@brief 1‚Â‚¾‚¯‰Šú‰»
		*/
		static void InitOne();

		/**
		@brief ‰Šú‰»”‚Ìæ“¾
		*/
		static int GetInitAllSize();

		static void InitAllLock();
		static void InitAllUnLock();
	protected:
		/**
		@brief Œp³‰Šú‰»
		*/
		virtual void Init();
	private:
		static bool m_init_all_lock;
		static std::list<Initializer*> m_initializers; // ‰Šú‰»ƒŠƒXƒg
	};
}

_MSLIB_END