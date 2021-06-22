//==========================================================================
// mslib [mslib.hpp]
// author : MasyoLab
//==========================================================================
#pragma once

#include <chrono> // c++ 時間演算
#include <codecvt> // c++ 文字コード変換
#include <cstdlib> // c++ 数値変換
#include <locale> // c++ 文字の判定
#include <system_error> // c++ OSエラー
#include <vector> // c++ 動的構造体
#include <list> // c++ 双方向list
#include <map> // c++ 平衡二分木 ソート機能付き
#include <unordered_map> // c++ 平衡二分木 ソート機能無し
#include <iomanip> // c++ 時間
#include <string> // c++ char
#include <random> // c++ rand
#include <fstream> // ifstream, ofstream
#include <sstream> // istringstream
#include <type_traits> // c++ メタ関数
#include <algorithm> // c++ アルゴリズム
#include <memory> // c++ メモリ
#include <cstdio> // 
#include <limits> // 型の最大値を返す
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
@param a [in] 比較対象
@param b [in] 比較対象
@return 大きい方が返ります
*/
template<typename _Ty>
inline _Ty _max(_Ty& a, _Ty& b) {
	return (((a) > (b)) ? (a) : (b));
}
/**
@brief min
@param a [in] 比較対象
@param b [in] 比較対象
@return 小さい方が返ります
*/
template<typename _Ty>
inline _Ty _min(_Ty& a, _Ty& b) {
	return (((a) < (b)) ? (a) : (b));
}
/**
@brief データ要素数
@param p [in] サイズ計測
@return 要素数
*/
template<typename _Ty, size_t p>
inline int _sizeof(const _Ty(&)[p]) {
	return (int)size_t(p);
}
/**
@brief メモリ確保
@param p [in] アドレスを渡す対象
@param size [in] 確保数
@return 先頭アドレス
*/
template<typename _Ty>
inline _Ty* _new(_Ty*& p, int size) {
	p = nullptr;
	p = new _Ty[size];
	return p;
}
/**
@brief メモリ確保
@param p [in] アドレスを渡す対象
@return 先頭アドレス
*/
template<typename _Ty>
inline _Ty* _new(_Ty*& p) {
	p = nullptr;
	p = new _Ty[1];
	return p;
}
/**
@brief メモリ解放
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
@brief デコイ
@param p [in] デコイ化対象
*/
template<typename _Ty>
inline void _decoy(const _Ty& p) {
	(p);
}
/**
@brief 奇数偶数判定
@param p [in] 判定対象
@return 偶数[false]/奇数[true]
*/
template<typename _Ty>
inline bool _even_or_odd(const _Ty& p) {
	return ((((int)(p)) % 2)) ? true : false;
}
/**
@brief メモリ内のデータ破棄
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
@param p [in] チェック対象
@return null ではない場合true
*/
inline bool nullptr_check(const void* p) {
	return (p != nullptr) ? true : false;
}

/**
@brief bool change
@param p [in] 変更対象
@return 結果
*/
inline bool bool_change(bool& p) {
	return p = p ^ true;
}

/**
@brief ptrキャスト
@param _ptr [in] ptr
@return 指定クラスにcastしたptr
*/
template<typename _Ty>
inline _Ty* cast(void* _ptr) {
	return ((_Ty*)_ptr);
}

/**
@brief キャスト 意味のない関数です。
@param v [in] 対象
@return キャスト結果
*/
template<typename _Ty>
inline _Ty& cast(_Ty& v) {
	return ((_Ty)v);
}

/**
@brief テキスト生成
@param text [in] 入力文字列
@param args [in] 表示させたい値
@return string テキスト
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
@brief 円周率
*/
template <typename _Ty> constexpr _Ty _pi_ = static_cast<_Ty>(3.141592654);

/**
@brief ラジアン角に変換します
*/
template <typename _Ty>
inline constexpr _Ty ToRadian(_Ty degree)
{
	return static_cast<_Ty>(degree * (_pi_<_Ty> / (_Ty)180));
}

/**
@brief 角度に変換します
*/
template <typename _Ty>
inline constexpr _Ty ToDegree(_Ty radian)
{
	return static_cast<_Ty>(radian * ((_Ty)180 / _pi_<_Ty>));
}

/**
@brief マイナスに変換します
*/
template <typename _Ty>
inline constexpr _Ty ToMinus(_Ty plus)
{
	if (((_Ty)0) < plus)
		return -plus;

	return plus;
}

/**
@brief プラスに変換します
*/
template <typename _Ty>
inline constexpr _Ty ToPlus(_Ty minus)
{
	if (minus < ((_Ty)0))
		return -minus;

	return minus;
}

/**
@brief 60 * value = 秒
*/
inline constexpr int Seconds(int value) {
	return 60 * value;
}

/**
@brief Seconds(60) * value = 分
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
	@brief 取得/生成
	*/
	bool& Get(const std::string& key_name) {
		auto itr = data.find(key_name);

		// 存在する
		if (itr != data.end())
			return itr->second;

		// 存在しない
		if (itr == data.end())
			data[key_name] = false;

		return data[key_name];
	}
	/**
	@brief 初期化
	*/
	void clear() {
		data.clear();
	}
	/**
	@brief 存在のチェック
	*/
	bool Check(const std::string& key_name) {
		return data.find(key_name) != data.end() ? true : false;
	}
	/**
	@brief 解放
	*/
	void Release(const std::string& key_name) {
		auto itr = data.find(key_name);
		if (itr == data.end())
			return;
		data.erase(itr);
	}
	/**
	@brief 鍵の取得
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