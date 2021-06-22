//==========================================================================
// �A�X�y�N�g�� [AspectRatio.h]
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
	// Content : �A�X�y�N�g��
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
			int2 m_size; // �E�B���h�E�T�C�Y
			int2 m_asp; // �A�X�y�N�g��
		};
	public:
		AspectRatio() :
			Component("AspectRatio") {}
		~AspectRatio() {
			m_aspect_ratio.clear();
			m_aspect_ratio_all.clear();
		}

		/**
		@brief �A�X�y�N�g��`�F�b�N
		@param win [in] {x,y}�E�B���h�E�T�C�Y
		@param asps [in] {x,y}�w��A�X�y�N�g��
		@return �w��̃A�X�y�N�g��Ȃ�true���Ԃ�܂�
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

			// �f�[�^�̓o�^
			list.m_size = int2(_win);
			list.m_asp = asp;
			m_aspect_ratio_all.emplace_back(list);

			// �w�肷��A�X�y�N�g��Ȃ炻�̃E�B���h�E�T�C�Y�̓o�^
			if (_asps.x == asp.x && _asps.y == asp.y) {
				m_aspect_ratio.emplace_back(list);
				return true;
			}
			return false;
		}

		/**
		@brief �w�肵���A�X�y�N�g��ƈ�v�����f�[�^���̎擾
		@return ��v�����f�[�^��
		*/
		int Size() {
			return m_aspect_ratio.size();
		}

		/**
		@brief ���������f�[�^���̎擾
		@return ���������f�[�^��
		*/
		int AllSize() {
			return m_aspect_ratio_all.size();
		}

		/**
		@brief �w�肵���A�X�y�N�g��̃f�[�^�̂ݎ擾
		@param label �A�N�Z�XID
		@return �w�肵���A�X�y�N�g��
		*/
		List& Get(int _label) {
			return m_aspect_ratio[_label];
		}

		/**
		@brief ���������f�[�^�̌��ʂ��擾
		@param label �A�N�Z�XID
		@return ���������f�[�^�̌���
		*/
		List& AllDataGet(int _label) {
			return m_aspect_ratio_all[_label];
		}
	private:
		/**
		@brief �ő���񐔂����߂�
		@param size �E�B���h�E�T�C�Y
		@return ����
		*/
		int GCD(int2 _size) {
			int tmp = 0;

			// x����y�̒l���傫����΁Ctmp�ϐ����g���ē���ւ���
			if (_size.x < _size.y) {
				tmp = _size.x;
				_size.x = _size.y;
				_size.y = tmp;
			}

			// y�����R���łȂ����-1��Ԃ�
			if (_size.y <= 0)
				return -1;

			// x��y�Ŋ������]�肪0�ł���΁C���ꂪ�ő����
			if (_size.x % _size.y == 0)
				return _size.y;

			// �ċA�֐��i���if���Ɉ���������܂�GCD���J��Ԃ��j
			return GCD(int2(_size.y, _size.x % _size.y));
		}
	private:
		std::vector<List> m_aspect_ratio; // �q�b�g�����f�[�^�̊i�[
		std::vector<List> m_aspect_ratio_all; // �f�[�^�̊i�[
	};

	using AspectReference = reference::IReference<AspectRatio>;
}

_MSLIB_END