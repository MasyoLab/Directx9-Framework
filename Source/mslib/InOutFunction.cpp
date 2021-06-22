//==========================================================================
// InOutFunction [InOutFunction.cpp]
// author : MasyoLab
//==========================================================================
#include <time.h>
#include <chrono>
#include <direct.h>
#include "InOutFunction.h"

_MSLIB_BEGIN

namespace in_out_function
{
	std::list<InOutFunction*> InOutFunction::m_inputs; // 読み取りリスト
#if defined(_MSLIB_DEBUG)
	std::list<InOutFunction*> InOutFunction::m_outputs; // 書き込みリスト
#endif

	float get_time_sec();

	InOutFunction::InOutFunction() :
		m_flag(false)
	{
#if defined(_MSLIB_DEBUG)
#endif
	}

	InOutFunction::InOutFunction(bool _flag) :
		m_flag(_flag)
	{
		if (_flag)
			m_inputs.push_back(this);
#if defined(_MSLIB_DEBUG)
		if (_flag)
			m_outputs.push_back(this);
#endif
	}

	InOutFunction::~InOutFunction()
	{
		if (!m_flag)
			return;
		auto itr1 = std::find(m_inputs.begin(), m_inputs.end(), this);
		if (itr1 != m_inputs.end())
			m_inputs.erase(itr1);
#if defined(_MSLIB_DEBUG)
		auto itr2 = std::find(m_outputs.begin(), m_outputs.end(), this);
		if (itr2 != m_outputs.end())
			m_outputs.erase(itr2);
#endif
	}

	void InOutFunction::InputDataReleaseAll()
	{
		m_inputs.clear();
	}

	void InOutFunction::InputDataAll(const std::string& _directory, component::ComponentReference& _directory_component)
	{
		for (auto& itr : m_inputs)
		{
			// ノード生成のための初期化
			itr->InputDataStart(_directory, _directory_component);

			std::ifstream fin(itr->m_Directory + ".txt");

			// 開けない場合終了
			if (!fin)
				continue;

			// 各オブジェクトの機能を実行
			itr->InputDataFunction(fin);

			// 終了
			fin.close();
		}
	}

	void InOutFunction::OutputDataAll(const std::string& _directory, component::ComponentReference& _directory_component)
	{
#if defined(_MSLIB_DEBUG)

		for (auto& itr : m_outputs)
		{
			time_t timer;
			tm* date;
			std::string create_day; // 生成日
			std::string create_time; // 生成時間
			char str[256] = { 0 };
			float start_ms = get_time_sec();

			// 保存日時を記録
			timer = time(nullptr); // 経過時間を取得
			date = localtime(&timer); // 経過時間を時間を表す構造体 date に変換
			strftime(str, sizeof(str), "%Y/%m/%d", date); // 年月日時分秒
			create_day = str;
			strftime(str, sizeof(str), "%H:%M:%S", date); // 年月日時分秒
			create_time = str;

			// ノード生成のための初期化
			itr->OutputDataStart(_directory, _directory_component);

			std::ofstream fin(itr->m_Directory + ".txt");

			// 開けない場合終了
			if (!fin)
				continue;

			fin << std::string("#=============================================================================") << std::endl;
			fin << std::string("# " + itr->GetComponentName() + ".txt") << std::endl;
			fin << std::string("# " + create_day) << std::endl;
			fin << std::string("# " + create_time) << std::endl;
			fin << std::string("#=============================================================================") << std::endl;

			// 各オブジェクトの機能を実行
			itr->OutputDataFunction(fin);

			// 終了
			fin.close();
		}
#else
		_directory;
		_directory_component;
#endif
	}

	void InOutFunction::InputDataFunction(std::ifstream& _ifstream)
	{
		_ifstream;
	}

	void InOutFunction::OutputDataFunction(std::ofstream& _ofstream)
	{
		_ofstream;
	}

	std::list<std::string> InOutFunction::GetFolderList(component::ComponentReference& _directory_component)
	{
		std::list<std::string> directory_list; // フォルダ名

		// 対象の親になるまで繰り返します
		for (auto par = GetComponentParent(); par != nullptr; par = par->GetComponentParent())
		{
			// 対象の親になったら終了
			if (par == _directory_component)
				break;

			// フォルダ名にする
			directory_list.push_front(par->GetComponentName());
		}
		return directory_list;
	}

	void InOutFunction::InputDataStart(const std::string& _directory, component::ComponentReference& _directory_component)
	{
		auto folder_list = GetFolderList(_directory_component);

		// ディレクトリパスを生成します
		m_Directory = _directory;
		for (auto& itr : folder_list)
			m_Directory += itr + "/";
		m_Directory += GetComponentName();
	}

	void InOutFunction::OutputDataStart(const std::string& _directory, component::ComponentReference& _directory_component)
	{
#if defined(_MSLIB_DEBUG)
		auto folder_list = GetFolderList(_directory_component);

		// ディレクトリパスを生成します
		m_Directory = _directory;
		for (auto& itr : folder_list)
			m_Directory += itr + "/";
		m_Directory += GetComponentName();

		// フォルダを生成します
		std::string directory_str = _directory;
		for (auto& itr : folder_list)
		{
			directory_str += itr + "/";
			_mkdir(directory_str.c_str());
		}
#else
		_directory;
		_directory_component;
#endif
	}

	float get_time_sec()
	{
		return static_cast<float>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()) / (float)1000000000;
	}
}

_MSLIB_END