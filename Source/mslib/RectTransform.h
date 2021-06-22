//==========================================================================
// RectTransform [RectTransform.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Transform.h"

_MSLIB_BEGIN

namespace transform
{
	class RectTransform :
		public Transform
	{
	private:
		RectTransform(const RectTransform&) = delete;
		RectTransform(RectTransform&&) = delete;
		RectTransform& operator=(const RectTransform&) = delete;
		RectTransform& operator=(RectTransform&&) = delete;
	public:
		RectTransform();
		~RectTransform();

		/**
		@brief �|���S���̃T�C�Y�̎擾
		@return �|���S���̃T�C�Y
		*/
		const D3DXVECTOR2& GetPolygonSize() const;

		/**
		@brief �|���S���̃T�C�Y�̓o�^
		@param x [in] X���̃T�C�Y
		@param y [in] Y���̃T�C�Y
		*/
		void SetPolygonSize(float x, float y);

		/**
		@brief �|���S���̃T�C�Y�̓o�^
		@param size [in] �T�C�Y
		*/
		void SetPolygonSize(const D3DXVECTOR2& _size);

		/**
		@brief �|���S���̃T�C�Y�̉��Z
		@param x [in] X���̃T�C�Y
		@param y [in] Y���̃T�C�Y
		*/
		void AddPolygonSize(float x, float y);

		/**
		@brief �|���S���̃T�C�Y�̉��Z
		@param size [in] �T�C�Y
		*/
		void AddPolygonSize(const D3DXVECTOR2& _size);

		/**
		@brief �s�{�b�g�̎擾
		@return ��]��
		*/
		const D3DXVECTOR2& GetPivot() const;

		/**
		@brief �s�{�b�g�̓o�^
		@param x [in] ��]X��(0�`1)
		@param y [in] ��]Y��(0�`1)
		*/
		void SetPivot(float x, float y);

		/**
		@brief �s�{�b�g�̓o�^
		@param pivot [in] ��]���̈ʒu(0�`1)
		*/
		void SetPivot(const D3DXVECTOR2& _pivot);

		/**
		@brief �s�{�b�g�̉��Z
		@param x [in] ��]X��(0�`1)
		@param y [in] ��]Y��(0�`1)
		*/
		void AddPivot(float x, float y);

		/**
		@brief �s�{�b�g�̉��Z
		@param pivot [in] ��]���̈ʒu(0�`1)
		*/
		void AddPivot(const D3DXVECTOR2& _pivot);

		/**
		@brief �O���[�o���}�g���N�X�̐���
		@return �}�g���N�X
		*/
		D3DXMATRIX* CreateWorldMatrix() override;

		/**
		@brief ���[�J���}�g���N�X�̐���
		@return �}�g���N�X
		*/
		D3DXMATRIX* CreateLocalMatrix() override;

		/**
		@brief RectTransform �̃R�s�[
		*/
		void CopyRectTransform(reference::IReference<RectTransform> _rect);
	protected:
		void GUIRectTransform();
		void InputDataRectTransform(std::ifstream& _ifstream);
		void OutputDataRectTransform(std::ofstream& _ofstream);
	private:
		/**
		@brief ���g�̃|�C���^
		*/
		RectTransform* GetThisPtr();
	private:
		D3DXVECTOR2 m_polygon; // �|���S���T�C�Y
		D3DXVECTOR2 m_pivot; // �s�{�b�g
		D3DXMATRIX m_not_polygon_matrix; // ���[���h��Ԃ���Ƃ����|���S���T�C�Y���܂߂Ȃ��p��
		reference::IReference<RectTransform> m_rect_transform_parent;
	};

	using RectTransformReference = reference::IReference<RectTransform>;
}

_MSLIB_END