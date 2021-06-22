//==========================================================================
// アスペクト比 [AspectRatio.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "mslib.hpp"
#include "mslib_struct.h"
#include "Component.h"
#include "Reference.h"

_MSLIB_BEGIN

namespace aspect
{
	//==========================================================================
	//
	// class : AspectRatio
	// Content : アスペクト比
	//
	//==========================================================================
	class AspectRatio final :
		public component::Component
	{
	private:
		AspectRatio(const AspectRatio&) = delete;
		AspectRatio(AspectRatio&&) = delete;
		AspectRatio& operator=(const AspectRatio&) = delete;
		AspectRatio& operator=(AspectRatio&&) = delete;
	public:
		struct List {
			int2 m_size; // ウィンドウサイズ
			int2 m_asp; // アスペクト比
		};
	public:
		AspectRatio() :
			Component("AspectRatio") {}
		~AspectRatio() {
			m_aspect_ratio.clear();
			m_aspect_ratio_all.clear();
		}

		/**
		@brief アスペクト比チェック
		@param win [in] {x,y}ウィンドウサイズ
		@param asps [in] {x,y}指定アスペクト比
		@return 指定のアスペクト比ならtrueが返ります
		*/
		bool Search(const int2& _win, const int2& _asps) {
			int n = 0;
			int2 size(_win);
			int2 asp;
			List list;

			if ((n = GCD(size)) > 0) {
				asp.x = size.x / n;
				asp.y = size.y / n;
			}

			// データの登録
			list.m_size = int2(_win);
			list.m_asp = asp;
			m_aspect_ratio_all.emplace_back(list);

			// 指定するアスペクト比ならそのウィンドウサイズの登録
			if (_asps.x == asp.x && _asps.y == asp.y) {
				m_aspect_ratio.emplace_back(list);
				return true;
			}
			return false;
		}

		/**
		@brief 指定したアスペクト比と一致したデータ数の取得
		@return 一致したデータ数
		*/
		int Size() {
			return m_aspect_ratio.size();
		}

		/**
		@brief 処理したデータ数の取得
		@return 処理したデータ数
		*/
		int AllSize() {
			return m_aspect_ratio_all.size();
		}

		/**
		@brief 指定したアスペクト比のデータのみ取得
		@param label アクセスID
		@return 指定したアスペクト比
		*/
		List& Get(int _label) {
			return m_aspect_ratio[_label];
		}

		/**
		@brief 処理したデータの結果を取得
		@param label アクセスID
		@return 処理したデータの結果
		*/
		List& AllDataGet(int _label) {
			return m_aspect_ratio_all[_label];
		}
	private:
		/**
		@brief 最大公約数を求める
		@param size ウィンドウサイズ
		@return 公約数
		*/
		int GCD(int2 _size) {
			int tmp = 0;

			// xよりもyの値が大きければ，tmp変数を使って入れ替える
			if (_size.x < _size.y) {
				tmp = _size.x;
				_size.x = _size.y;
				_size.y = tmp;
			}

			// yが自然数でなければ-1を返す
			if (_size.y <= 0)
				return -1;

			// xをyで割った余りが0であれば，それが最大公約数
			if (_size.x % _size.y == 0)
				return _size.y;

			// 再帰関数（上のif文に引っかかるまでGCDを繰り返す）
			return GCD(int2(_size.y, _size.x % _size.y));
		}
	private:
		std::vector<List> m_aspect_ratio; // ヒットしたデータの格納
		std::vector<List> m_aspect_ratio_all; // データの格納
	};

	using AspectReference = reference::IReference<AspectRatio>;
}

_MSLIB_END