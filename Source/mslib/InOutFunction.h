//==========================================================================
// InOutFunction [InOutFunction.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "mslib.hpp"
#include "Component.h"
#include "Reference.h"

_MSLIB_BEGIN

namespace in_out_function
{
	//==========================================================================
	//
	// class : InOutFunction
	// Content : Input/Output
	//
	//==========================================================================
	class InOutFunction :
		virtual public component::Component
	{
	private:
		InOutFunction(const InOutFunction&) = delete;
		InOutFunction(InOutFunction&&) = delete;
		InOutFunction& operator=(const InOutFunction&) = delete;
		InOutFunction& operator=(InOutFunction&&) = delete;
	public:
		InOutFunction();
		InOutFunction(bool _flag);
		virtual ~InOutFunction();

		/**
		@brief 読み取りに使用したデータを全て破棄する
		*/
		static void InputDataReleaseAll();

		/**
		@brief 全て読み取る
		*/
		static void InputDataAll(const std::string& _directory, component::ComponentReference& _directory_component);

		/**
		@brief 全て書き込む
		*/
		static void OutputDataAll(const std::string& _directory, component::ComponentReference& _directory_component);
	protected:
		/**
		@brief 読み取り機能(継承)
		*/
		virtual void InputDataFunction(std::ifstream& _ifstream);
		/**
		@brief 書き込み機能(継承)
		*/
		virtual void OutputDataFunction(std::ofstream& _ofstream);
	private:
		std::list<std::string> GetFolderList(component::ComponentReference& _directory_component);
		void InputDataStart(const std::string& _directory, component::ComponentReference& _directory_component);
		void OutputDataStart(const std::string& _directory, component::ComponentReference& _directory_component);
	private:
		bool m_flag;
		std::string m_Directory; // ディレクトリ
		static std::list<InOutFunction*> m_inputs; // 読み取りリスト
#if defined(_MSLIB_DEBUG)
		static std::list<InOutFunction*> m_outputs; // 書き込みリスト
#endif
	};
}

_MSLIB_END