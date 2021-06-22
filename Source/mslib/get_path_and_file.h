//==========================================================================
// �t�@�C���̃p�X�A�t�@�C�����A�g���q�̎擾 [get_path_and_file.cpp]
// author : MasyoLab
//==========================================================================
#pragma once

#include <string>

#include "mslib.hpp"

_MSLIB_BEGIN
namespace get_path_and_file
{
	inline auto GetPathAndFile(const std::string& _str)
	{
		class _get_path_and_file final
		{
		public:
			_get_path_and_file() {}
			_get_path_and_file(const std::string& _pathname, const std::string& _extname, const std::string& _filename) :
				m_path_name(_pathname), m_ext_name(_extname), m_file_name(_filename)
			{}
		public:
			std::string m_path_name; // �f�B���N�g��
			std::string m_ext_name; // �g���q
			std::string m_file_name; // �t�@�C����
		};

		int npath = _str.find_last_of("/") + 1;
		int next = _str.find_last_of(".");
		if (next == -1)
			return _get_path_and_file();

		return _get_path_and_file(
			_str.substr(0, npath + 1), // �f�B���N�g��
			_str.substr(next, _str.size() - next), // �g���q���擾
			_str.substr(npath, next - npath) // �t�@�C�������擾
		);
	}
}
_MSLIB_END
