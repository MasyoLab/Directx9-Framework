//==========================================================================
// �w��g���q�̃f�B���N�g�����T�� [file_path.hpp]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <stdexcept>

#include "mslib.hpp"

_MSLIB_BEGIN

namespace file_path
{
	/**
	@brief �w��t�@�C���f�B���N�g�����T��
	@param dir_name [in] �w��f�B���N�g��
	@param dir_name [in] �g���q
	@return ���΃p�X�̃t�@�C���f�B���N�g�����擾�ł��܂�
	*/
	std::vector<std::string> get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false);

	/**
	@brief �w��t�@�C���f�B���N�g����T�����Ȃ�
	@param dir_name [in] �w��f�B���N�g�� �w�肵�Ă��Ӗ��͂Ȃ�
	@param dir_name [in] �g���q
	@return ���΃p�X�̃t�@�C���f�B���N�g�����擾�ł��܂�
	*/
	std::vector<std::string> get_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false);
}

_MSLIB_END