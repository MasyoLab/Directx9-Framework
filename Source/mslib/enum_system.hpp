//==========================================================================
// enum‹@”\Šg’£ [enum_system.hpp]
// author : MasyoLab
//==========================================================================
#pragma once

#include <type_traits>

#include "mslib.hpp"

_MSLIB_BEGIN

namespace enum_system
{
	// ‰‰Z
	template<typename T>
	struct calculation : std::false_type {};
	// Bit‰‰Z
	template<typename T>
	struct has_bitwise_operators : std::false_type {};
	// AND/OR‰‰Z
	template<typename T>
	struct has_and_or_operators : has_bitwise_operators<T> {};

	//==========================================================================
	// Šî’êŒ^æ“¾
	//==========================================================================
	namespace type_traits {
		template<bool con> using concept_t = typename std::enable_if<con, std::nullptr_t>::type;
		template<typename T> using underlying_type_t = typename std::underlying_type<T>::type;//C++11‚É‚Í‚È‚¢
	}

	//==========================================================================
	// Šî’êŒ^æ“¾
	//==========================================================================
	namespace detail {
		using namespace type_traits;
		template<typename T, concept_t<std::is_enum<T>::value> = nullptr>
		constexpr underlying_type_t<T> underlying_cast(T e) { return static_cast<underlying_type_t<T>>(e); }
	}

	//==========================================================================
	// AND/OR‰‰Z ‚±‚±‚©‚ç
	//==========================================================================
	template<typename T, typename S, type_traits::concept_t<enum_system::has_and_or_operators<T>::value> = nullptr>
	constexpr T operator&(T l, S r) {
		return static_cast<T>(detail::underlying_cast((T)l) & detail::underlying_cast((T)r));
	}

	template<typename T, typename S, type_traits::concept_t<enum_system::has_and_or_operators<T>::value> = nullptr>
	T & operator&=(T & l, S r) {
		l = static_cast<T>(detail::underlying_cast((T)l) & detail::underlying_cast((T)r));
		return l;
	}

	template<typename T, typename S, type_traits::concept_t<enum_system::has_and_or_operators<T>::value> = nullptr>
	constexpr T operator|(T l, S r) {
		return static_cast<T>(detail::underlying_cast((T)l) | detail::underlying_cast((T)r));
	}

	template<typename T, typename S, type_traits::concept_t<enum_system::has_and_or_operators<T>::value> = nullptr>
	T & operator|=(T & l, S r) {
		l = static_cast<T>(detail::underlying_cast((T)l) | detail::underlying_cast((T)r));
		return l;
	}

	//==========================================================================
	// AND/OR‰‰Z ‚±‚±‚Ü‚Å
	//==========================================================================

	//==========================================================================
	// Bit‰‰Z ‚±‚±‚©‚ç
	//==========================================================================
	template<typename T, typename S, type_traits::concept_t<enum_system::has_bitwise_operators<T>::value> = nullptr>
	constexpr T operator^(T l, S r) {
		return static_cast<T>(detail::underlying_cast((T)l) ^ detail::underlying_cast((T)r));
	}

	template<typename T, typename S, type_traits::concept_t<enum_system::has_bitwise_operators<T>::value> = nullptr>
	T & operator^=(T & l, S r) {
		l = static_cast<T>(detail::underlying_cast((T)l) ^ detail::underlying_cast((T)r));
		return l;
	}

	template<typename T, type_traits::concept_t<enum_system::has_bitwise_operators<T>::value> = nullptr>
	constexpr T operator~(T op) {
		return static_cast<T>(~detail::underlying_cast(op));
	}

	//==========================================================================
	// Bit‰‰Z ‚±‚±‚Ü‚Å
	//==========================================================================

	//==========================================================================
	// ‰‰Z ‚±‚±‚©‚ç
	//==========================================================================
	template<typename T, typename S, type_traits::concept_t<enum_system::calculation<T>::value> = nullptr>
	constexpr T operator+(T l, S r) {
		return static_cast<T>(detail::underlying_cast((T)l) + detail::underlying_cast((T)r));
	}

	template<typename T, typename S, type_traits::concept_t<enum_system::calculation<T>::value> = nullptr>
	constexpr T operator-(T l, S r) {
		return static_cast<T>(detail::underlying_cast((T)l) - detail::underlying_cast((T)r));
	}

	template<typename T, typename S, type_traits::concept_t<enum_system::calculation<T>::value> = nullptr>
	constexpr T operator/(T l, S r) {
		return static_cast<T>(detail::underlying_cast((T)l) / detail::underlying_cast((T)r));
	}

	template<typename T, typename S, type_traits::concept_t<enum_system::calculation<T>::value> = nullptr>
	constexpr T operator*(T l, S r) {
		return static_cast<T>(detail::underlying_cast((T)l) * detail::underlying_cast((T)r));
	}

	template<typename T, type_traits::concept_t<enum_system::calculation<T>::value> = nullptr>
	constexpr T operator++(T & l) {
		l = static_cast<T>(detail::underlying_cast(l) + detail::underlying_cast((T)1));
		return l;
	}

	template<typename T, type_traits::concept_t<enum_system::calculation<T>::value> = nullptr>
	constexpr T operator--(T & l) {
		l = static_cast<T>(detail::underlying_cast((T)l) - detail::underlying_cast((T)1));
		return l;
	}

	template<typename T, typename S, type_traits::concept_t<enum_system::calculation<T>::value> = nullptr>
	constexpr T operator+=(T & l, S r) {
		l = static_cast<T>(detail::underlying_cast((T)l) + detail::underlying_cast((T)r));
		return l;
	}

	template<typename T, typename S, type_traits::concept_t<enum_system::calculation<T>::value> = nullptr>
	constexpr T operator-=(T & l, S r) {
		l = static_cast<T>(detail::underlying_cast((T)l) - detail::underlying_cast((T)r));
		return l;
	}

	template<typename T, typename S, type_traits::concept_t<enum_system::calculation<T>::value> = nullptr>
	constexpr T operator*=(T & l, S r) {
		l = static_cast<T>(detail::underlying_cast((T)l) * detail::underlying_cast((T)r));
		return l;
	}

	template<typename T, typename S, type_traits::concept_t<enum_system::calculation<T>::value> = nullptr>
	constexpr T operator/=(T & l, S r) {
		l = static_cast<T>(detail::underlying_cast((T)l) / detail::underlying_cast((T)r));
		return l;
	}
}
_MSLIB_END
//==========================================================================
// ‰‰Z ‚±‚±‚Ü‚Å
//==========================================================================

#if 0
/*

enumAenum class ‚ÌŒ^–¼‚ğ<T>‚É“ü‚ê‚é‚Æ‚±‚É‚æ‚è”Šw“Iˆ—‚ğ‰Â”\‚É‚·‚éclass‚Å‚·

template<> struct enum_system::calculation<T> : std::true_type {};
template<> struct enum_system::has_and_or_operators<T> : std::true_type {};
template<> struct enum_system::has_bitwise_operators<T> : std::true_type {};

*/
#endif