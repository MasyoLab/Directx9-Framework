//==========================================================================
// �}�e���A�� [Material.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"

_MSLIB_BEGIN

namespace material
{
	//==========================================================================
	//
	// class : MaterialLighting
	// Content : �}�e���A���̃��C�e�B���O
	//
	//==========================================================================
	class MaterialLighting
	{
	public:
		MaterialLighting();
		~MaterialLighting();

		/**
		@brief �A���r�G���g���C�g
		@param color [in] ���C�g�ݒ�(0.0f�`1.0f)
		*/
		void SetAmbient(const D3DXCOLOR& color);

		/**
		@brief �f�B���N�V���i�����C�g
		@param color [in] ���C�g�ݒ�(0.0f�`1.0f)
		*/
		void SetDiffuse(const D3DXCOLOR& color);

		/**
		@brief �X�y�L�����[
		@param color [in] ���C�g�ݒ�(0.0f�`1.0f)
		*/
		void SetSpecular(const D3DXCOLOR& color);

		/**
		@brief ���ː�
		@param color [in] ���C�g�ݒ�(0.0f�`1.0f)
		*/
		void SetEmissive(const D3DXCOLOR& color);

		/**
		@brief �X�y�L�����[���̃p���[�l
		*/
		void SetSpecularPower(float power);

		/**
		@brief ���C�e�B���O�̎擾
		*/
		const D3DMATERIAL9& GetMaterialLighting();
	protected:
		void GUIMaterialLighting();
		void InputDataMaterialLighting(std::ifstream& _ifstream);
		void OutputDataMaterialLighting(std::ofstream& _ofstream);
	private:
		D3DMATERIAL9 m_material9;
	};
}

_MSLIB_END