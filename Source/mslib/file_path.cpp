//==========================================================================
// 指定拡張子のディレクトリ内探索 [file_path.cpp]
// author : MasyoLab
//==========================================================================
#include "file_path.hpp"

_MSLIB_BEGIN

namespace file_path
{
	std::vector<std::string> get_file_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false)
	{
		HANDLE hFind;
		WIN32_FIND_DATA win32fd;//defined at Windwos.h
		std::vector<std::string> file_names;

		ZeroMemory(&win32fd, sizeof(WIN32_FIND_DATA));

		//拡張子の設定
		auto search_name = dir_name + "\\*." + extension;

		hFind = FindFirstFile(search_name.c_str(), &win32fd);

		if (win32fd.dwFileAttributes != 0) {
			if (hFind == INVALID_HANDLE_VALUE) {
				throw std::runtime_error("file not found");
			}

			do {
				if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				}
				else {
					file_names.push_back(win32fd.cFileName);
					printf("%s\n", file_names.back().c_str());

				}
			} while (FindNextFile(hFind, &win32fd));
		}

		FindClose(hFind);

		return file_names;
	}

	std::vector<std::string> get_path_in_dir(const std::string& dir_name, const std::string& extension) noexcept(false)
	{
		HANDLE hFind;
		WIN32_FIND_DATA win32fd;//defined at Windwos.h
		std::vector<std::string> file_names;

		ZeroMemory(&win32fd, sizeof(WIN32_FIND_DATA));

		//拡張子の設定
		auto search_name = dir_name + "*." + extension;

		hFind = FindFirstFile(search_name.c_str(), &win32fd);

		if (win32fd.dwFileAttributes != 0) {
			if (hFind == INVALID_HANDLE_VALUE) {
				throw std::runtime_error("file not found");
			}

			do {
				if (win32fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				}
				else {
					file_names.push_back(win32fd.cFileName);
					printf("%s\n", file_names.back().c_str());

				}
			} while (FindNextFile(hFind, &win32fd));
		}

		FindClose(hFind);

		return file_names;
	}
}

_MSLIB_END