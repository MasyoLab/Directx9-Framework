//==========================================================================
// Loader [Loader.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "mslib.hpp"
#include "Component.h"
#include "Reference.h"

_MSLIB_BEGIN

namespace resource_loader
{
	class Resource;

	//==========================================================================
	//
	// class : Loader
	// Content : Loader Class
	//
	//==========================================================================
	class Loader :
		public component::Component
	{
	private:
		Loader(const Loader&) = delete;
		Loader(Loader&&) = delete;
		Loader& operator=(const Loader&) = delete;
		Loader& operator=(Loader&&) = delete;
	public:
		Loader();
		~Loader();

		/**
		@brief Resourceを破棄する。
		@param _resource [in] Resource
		*/
		template <typename _Ty>
		void Unload(reference::WrapperReference<_Ty, Resource>& _resource);
	protected:
		std::unordered_map<std::string, std::shared_ptr<Resource>> m_resource_list; // データ
	};

	using LoaderReference = reference::IReference<Loader>;

	//==========================================================================
	//
	// class : Resource
	// Content : Resource Class
	//
	//==========================================================================
	class Resource
	{
	public:
		Resource();
		~Resource();

		/**
		@brief Loaderの取得
		@return Loader
		*/
		LoaderReference GetLoader();

		/**
		@brief tagの取得
		@return tag
		*/
		const std::string& GetTag();

		/**
		@brief shared_ptr の生成
		@param _Pt [in] Resource のポインタ
		@return shared_ptr
		*/
		template <typename _Ty, bool isExtended = std::is_base_of<Resource, _Ty>::value>
		static std::shared_ptr<_Ty>Create(_Ty* _Ptr);
	protected:
		LoaderReference m_loader_ptr; // ローダーのポインタ
		std::string m_tag; // タグ
	};

	template <typename _Ty>
	using ResourceReference = reference::WrapperReference<_Ty, Resource>;

	template<typename _Ty>
	void Loader::Unload(reference::WrapperReference<_Ty, Resource>& _resource)
	{
		if (!_resource.check())
			return;
		auto itr = m_resource_list.find(_resource->GetTag());
		if (itr == m_resource_list.end())
			return;
		m_resource_list.erase(itr);
		_resource = nullptr;
	}

	template<typename _Ty, bool isExtended>
	inline std::shared_ptr<_Ty> Resource::Create(_Ty* _Ptr)
	{
		static_assert(isExtended, "Create<> : _Ty is not inherited from Resource Class");
		return std::shared_ptr<_Ty>(_Ptr);
	}
}

_MSLIB_END
