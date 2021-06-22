//==========================================================================
// Loader [Loader.cpp]
// author : MasyoLab
//==========================================================================
#include "Loader.h"

_MSLIB_BEGIN

namespace resource_loader
{
	Loader::Loader() :
		Component("Loader")
	{
	}

	Loader::~Loader()
	{
		DestroyComponent();
		m_resource_list.clear();
	}

	Resource::Resource()
	{
	}

	Resource::~Resource()
	{
		m_loader_ptr = nullptr;
		m_tag.c_str();
	}

	LoaderReference Resource::GetLoader()
	{
		return m_loader_ptr;
	}

	const std::string& Resource::GetTag()
	{
		return m_tag;
	}
}

_MSLIB_END