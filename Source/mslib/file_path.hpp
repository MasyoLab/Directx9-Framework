//==========================================================================
// 指定拡張子のディレクトリ内探索 [file_path.hpp]
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
	@brief 指定ファイルディレクトリ内探索
	@param dir_name [in] 指定ディレクトリ
	@param dir_name [in] 拡張子
	@return 相対パスのファイルディレクトリを取得できます
	*/
	std::vector<std::string> get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false);

	/**
	@brief 指定ファイルディレクトリを探索しない
	@param dir_name [in] 指定ディレクトリ 指定しても意味はない
	@param dir_name [in] 拡張子
	@return 相対パスのファイルディレクトリを取得できます
	*/
	std::vector<std::string> get_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false);
}

_MSLIB_END