//==========================================================================
// mslib [mslib.hpp]
// author : MasyoLab
//==========================================================================
#pragma once

#include <chrono> // c++ ���ԉ��Z
#include <codecvt> // c++ �����R�[�h�ϊ�
#include <cstdlib> // c++ ���l�ϊ�
#include <locale> // c++ �����̔���
#include <system_error> // c++ OS�G���[
#include <vector> // c++ ���I�\����
#include <list> // c++ �o����list
#include <map> // c++ ���t�񕪖� �\�[�g�@�\�t��
#include <unordered_map> // c++ ���t�񕪖� �\�[�g�@�\����
#include <iomanip> // c++ ����
#include <string> // c++ char
#include <random> // c++ rand
#include <fstream> // ifstream, ofstream
#include <sstream> // istringstream
#include <type_traits> // c++ ���^�֐�
#include <algorithm> // c++ �A���S���Y��
#include <memory> // c++ ������
#include <cstdio> // 
#include <limits> // �^�̍ő�l��Ԃ�
#include <stdio.h>

//==========================================================================
// namespace
//==========================================================================

#ifndef _MSLIB_BEGIN
#define _MSLIB_BEGIN namespace mslib {
#endif // !_MSLIB_BEGIN

#ifndef _MSLIB
#define _MSLIB mslib::
#endif // !_MSLIB

#ifndef _MSLIB_
#define _MSLIB_ ::mslib::
#endif // !_MSLIB_

#ifndef _MSLIB_END
#define _MSLIB_END }
#endif // !_MSLIB_END

_MSLIB_BEGIN
/**
@brief max
@param a [in] ��r�Ώ�
@param b [in] ��r�Ώ�
@return �傫�������Ԃ�܂�
*/
template<typename _Ty>
inline _Ty _max(_Ty& a, _Ty& b) {
	return (((a) > (b)) ? (a) : (b));
}
/**
@brief min
@param a [in] ��r�Ώ�
@param b [in] ��r�Ώ�
@return �����������Ԃ�܂�
*/
template<typename _Ty>
inline _Ty _min(_Ty& a, _Ty& b) {
	return (((a) < (b)) ? (a) : (b));
}
/**
@brief �f�[�^�v�f��
@param p [in] �T�C�Y�v��
@return �v�f��
*/
template<typename _Ty, size_t p>
inline int _sizeof(const _Ty(&)[p]) {
	return (int)size_t(p);
}
/**
@brief �������m��
@param p [in] �A�h���X��n���Ώ�
@param size [in] �m�ې�
@return �擪�A�h���X
*/
template<typename _Ty>
inline _Ty* _new(_Ty*& p, int size) {
	p = nullptr;
	p = new _Ty[size];
	return p;
}
/**
@brief �������m��
@param p [in] �A�h���X��n���Ώ�
@return �擪�A�h���X
*/
template<typename _Ty>
inline _Ty* _new(_Ty*& p) {
	p = nullptr;
	p = new _Ty[1];
	return p;
}
/**
@brief ���������
@param p [in] delete[]
*/
template<typename _Ty>
inline void _delete(_Ty*& p) {
	if (p != nullptr) {
		delete[]p;
		p = nullptr;
	}
}
/**
@brief �f�R�C
@param p [in] �f�R�C���Ώ�
*/
template<typename _Ty>
inline void _decoy(const _Ty& p) {
	(p);
}
/**
@brief ���������
@param p [in] ����Ώ�
@return ����[false]/�[true]
*/
template<typename _Ty>
inline bool _even_or_odd(const _Ty& p) {
	return ((((int)(p)) % 2)) ? true : false;
}
/**
@brief ���������̃f�[�^�j��
@param p [in] p->Release();
*/
template<typename _Ty>
inline void _release(_Ty*& p) {
	if (p != nullptr) {
		p->Release();
		p = nullptr;
	}
}
/**
@brief null check
@param p [in] �`�F�b�N�Ώ�
@return null �ł͂Ȃ��ꍇtrue
*/
inline bool nullptr_check(const void* p) {
	return (p != nullptr) ? true : false;
}

/**
@brief bool change
@param p [in] �ύX�Ώ�
@return ����
*/
inline bool bool_change(bool& p) {
	return p = p ^ true;
}

/**
@brief ptr�L���X�g
@param _ptr [in] ptr
@return �w��N���X��cast����ptr
*/
template<typename _Ty>
inline _Ty* cast(void* _ptr) {
	return ((_Ty*)_ptr);
}

/**
@brief �L���X�g �Ӗ��̂Ȃ��֐��ł��B
@param v [in] �Ώ�
@return �L���X�g����
*/
template<typename _Ty>
inline _Ty& cast(_Ty& v) {
	return ((_Ty)v);
}

/**
@brief �e�L�X�g����
@param text [in] ���͕�����
@param args [in] �\�����������l
@return string �e�L�X�g
*/
template<typename ...Args>
inline const std::string text(const char* text, const Args& ... args)
{
	size_t size = snprintf(nullptr, 0, text, args ...) + 1; // Extra space for '\0'
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, text, args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

/**
@brief �~����
*/
template <typename _Ty> constexpr _Ty _pi_ = static_cast<_Ty>(3.141592654);

/**
@brief ���W�A���p�ɕϊ����܂�
*/
template <typename _Ty>
inline constexpr _Ty ToRadian(_Ty degree)
{
	return static_cast<_Ty>(degree * (_pi_<_Ty> / (_Ty)180));
}

/**
@brief �p�x�ɕϊ����܂�
*/
template <typename _Ty>
inline constexpr _Ty ToDegree(_Ty radian)
{
	return static_cast<_Ty>(radian * ((_Ty)180 / _pi_<_Ty>));
}

/**
@brief �}�C�i�X�ɕϊ����܂�
*/
template <typename _Ty>
inline constexpr _Ty ToMinus(_Ty plus)
{
	if (((_Ty)0) < plus)
		return -plus;

	return plus;
}

/**
@brief �v���X�ɕϊ����܂�
*/
template <typename _Ty>
inline constexpr _Ty ToPlus(_Ty minus)
{
	if (minus < ((_Ty)0))
		return -minus;

	return minus;
}

/**
@brief 60 * value = �b
*/
inline constexpr int Seconds(int value) {
	return 60 * value;
}

/**
@brief Seconds(60) * value = ��
*/
inline constexpr int Minute(int value) {
	return Seconds(60) * value;
}

template <typename _Ty>
inline std::shared_ptr<_Ty> shared_ptr(_Ty* _Ptr) {
	return std::shared_ptr<_Ty>(_Ptr);
}

template <typename _Ty>
inline std::shared_ptr<_Ty> shared_ptr_not_destroy(_Ty* _Ptr) {
	return std::shared_ptr<_Ty>(_Ptr, [](_Ty* p) {p = nullptr; });
}

class boollist
{
public:
	boollist() {}
	~boollist() { data.clear(); }
	/**
	@brief �擾/����
	*/
	bool& Get(const std::string& key_name) {
		auto itr = data.find(key_name);

		// ���݂���
		if (itr != data.end())
			return itr->second;

		// ���݂��Ȃ�
		if (itr == data.end())
			data[key_name] = false;

		return data[key_name];
	}
	/**
	@brief ������
	*/
	void clear() {
		data.clear();
	}
	/**
	@brief ���݂̃`�F�b�N
	*/
	bool Check(const std::string& key_name) {
		return data.find(key_name) != data.end() ? true : false;
	}
	/**
	@brief ���
	*/
	void Release(const std::string& key_name) {
		auto itr = data.find(key_name);
		if (itr == data.end())
			return;
		data.erase(itr);
	}
	/**
	@brief ���̎擾
	*/
	std::list<std::string> GetKeyList() {
		std::list<std::string> itr2;
		for (auto& itr : data)
			itr2.push_back(itr.first);
		return itr2;
	}
private:
	std::unordered_map<std::string, bool> data;
};

using rand_int = std::uniform_int_distribution<int>;
using rand_float = std::uniform_real_distribution<float>;
template <typename _Ty> using list = std::list<_Ty>;
template <typename _Ty> using vector = std::vector<_Ty>;
template <typename _Key, typename _Ty> using unordered_map = std::unordered_map<_Key, _Ty>;
using string = std::string;

#define _DEBUG_SYSTEM
#if defined(_DEBUG) || defined(DEBUG) || defined(_DEBUG_SYSTEM)
#define _MSLIB_DEBUG
#endif

_MSLIB_END