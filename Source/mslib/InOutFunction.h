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
		@brief �ǂݎ��Ɏg�p�����f�[�^��S�Ĕj������
		*/
		static void InputDataReleaseAll();

		/**
		@brief �S�ēǂݎ��
		*/
		static void InputDataAll(const std::string& _directory, component::ComponentReference& _directory_component);

		/**
		@brief �S�ď�������
		*/
		static void OutputDataAll(const std::string& _directory, component::ComponentReference& _directory_component);
	protected:
		/**
		@brief �ǂݎ��@�\(�p��)
		*/
		virtual void InputDataFunction(std::ifstream& _ifstream);
		/**
		@brief �������݋@�\(�p��)
		*/
		virtual void OutputDataFunction(std::ofstream& _ofstream);
	private:
		std::list<std::string> GetFolderList(component::ComponentReference& _directory_component);
		void InputDataStart(const std::string& _directory, component::ComponentReference& _directory_component);
		void OutputDataStart(const std::string& _directory, component::ComponentReference& _directory_component);
	private:
		bool m_flag;
		std::string m_Directory; // �f�B���N�g��
		static std::list<InOutFunction*> m_inputs; // �ǂݎ�胊�X�g
#if defined(_MSLIB_DEBUG)
		static std::list<InOutFunction*> m_outputs; // �������݃��X�g
#endif
	};
}

_MSLIB_END