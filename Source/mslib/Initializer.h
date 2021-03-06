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
		@brief 全て初期化
		*/
		static void InitAll();

		/**
		@brief 1つだけ初期化
		*/
		static void InitOne();

		/**
		@brief 初期化数の取得
		*/
		static int GetInitAllSize();

		static void InitAllLock();
		static void InitAllUnLock();
	protected:
		/**
		@brief 継承初期化
		*/
		virtual void Init();
	private:
		static bool m_init_all_lock;
		static std::list<Initializer*> m_initializers; // 初期化リスト
	};
}

_MSLIB_END