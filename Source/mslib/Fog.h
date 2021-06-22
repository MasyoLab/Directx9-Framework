//==========================================================================
// �t�H�O [Fog.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Component.h"

_MSLIB_BEGIN

namespace fog
{
	class EffectRangePos
	{
	public:
		EffectRangePos() {}
		EffectRangePos(float _start, float _end) {
			start = _start;
			end = _end;
		}
		~EffectRangePos() {}
	public:
		float start = 0.0f;
		float end = 0.0f;
	};

	//==========================================================================
	//
	// class : Fog
	// Content : �t�H�O
	//
	//==========================================================================
	class Fog :
		public component::Component
	{
	private:
		Fog(const Fog&) = delete;
		Fog(Fog&&) = delete;
		Fog& operator=(const Fog&) = delete;
		Fog& operator=(Fog&&) = delete;
	public:
		Fog(LPDIRECT3DDEVICE9 pDevice);
		virtual ~Fog();

		/**
		@brief ������
		@param color [in] �F
		@param start_pos [in] �t�H�O�e���J�n�n�_
		@param end_pos [in] �t�H�O���S�e���n�_
		@param VertexMode [in] ���_�̃��[�h�w��
		@param TableMode [in] �e�[�u�����[�h�ݒ�
		*/
		void Init(const D3DXCOLOR& color, float start_pos = 10.0f, float end_pos = 100.0f, D3DFOGMODE VertexMode = D3DFOG_NONE, D3DFOGMODE TableMode = D3DFOG_LINEAR);

		/**
		@brief �t�H�N�̗L����
		*/
		void ON();

		/**
		@brief �t�H�N�̖�����
		*/
		void OFF();

		/**
		@brief �e�[�u�����[�h�ݒ�
		@param TableMode [in] �e�[�u�����[�h
		*/
		void SetTableMode(D3DFOGMODE TableMode);

		/**
		@brief �e�[�u�����[�h�̎擾
		@return ���[�h���
		*/
		D3DFOGMODE GetTableMode();

		/**
		@brief ���_���[�h�ݒ�
		@param VertexMode [in] ���_���[�h
		*/
		void SetVertexMode(D3DFOGMODE VertexMode);

		/**
		@brief ���_���[�h�̎擾
		@return ���[�h���
		*/
		D3DFOGMODE GetVertexMode();

		/**
		@brief ���ʔ͈͂̐ݒ�
		@param start_pos [in] �t�H�O�e���J�n�n�_
		@param end_pos [in]�@�t�H�O���S�e���n�_
		*/
		void SetEffectRange(float start_pos, float end_pos);

		/**
		@brief ���ʔ͈͂̎擾
		@return ���ʔ͈�
		*/
		const EffectRangePos& GetEffectRange();

		/**
		@brief �F�̐ݒ�
		@param color [in] �F
		*/
		void SetColor(const D3DXCOLOR& color);

		/**
		@brief �F�̎擾
		@return �F
		*/
		const D3DXCOLOR& GetColor();
	private:
		LPDIRECT3DDEVICE9 m_device; // �f�o�C�X
		D3DXCOLOR m_color; // �F
		D3DFOGMODE m_vertex_mode; // ���_���[�h
		D3DFOGMODE m_table_mode; // �e�[�u�����[�h
		EffectRangePos m_effect_range; // ���ʔ͈�
		D3DCAPS9 m_caps;
	};
}

_MSLIB_END