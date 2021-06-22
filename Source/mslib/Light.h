//==========================================================================
// ���C�g [Light.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "GameObject.h"
#include "Transform.h"
#include "InOutFunction.h"

_MSLIB_BEGIN

namespace object
{
	//==========================================================================
	//
	// class : LightData
	// Content : ���C�g�̃f�[�^
	//
	//==========================================================================
	class LightData :
		public D3DLIGHT9
	{
	public:
		LightData();
		~LightData();
	};

	//==========================================================================
	//
	// class : Light
	// Content : ���C�g 
	//
	//==========================================================================
	class Light :
		public GameObject,
		public transform::Transform,
		public in_out_function::InOutFunction
	{
	private:
		Light(const Light&) = delete;
		Light(Light&&) = delete;
		Light& operator=(const Light&) = delete;
		Light& operator=(Light&&) = delete;
	public:
		Light(LPDIRECT3DDEVICE9 pDevice);
		/**
		@param _bInOutFunctionFlag [in] �ǂݎ��/�������݂�������t���O
		*/
		Light(LPDIRECT3DDEVICE9 pDevice, bool _bInOutFunctionFlag);
		virtual ~Light();

		/**
		@brief ������
		*/
		void Init();

		/**
		@brief ������
		@param aVecDir [in] ���̃x�N�g��������Ƃ���
		*/
		void Init(const D3DXVECTOR3& aVecDir);
	protected:
		/**
		@brief �X�V
		*/
		virtual void Update() override;

		/**
		@brief �p���s��̍X�V
		*/
		virtual void UpdateMatrix() override;

		/**
		@brief GUI�ɕ\������@�\
		*/
		virtual void GUISystem() override;

		/**
		@brief �ǂݎ��@�\
		*/
		virtual void InputDataFunction(std::ifstream& _ifstream) override;

		/**
		@brief �������݋@�\
		*/
		virtual void OutputDataFunction(std::ofstream& _ofstream) override;
	private:
		void CreateLabel();
	private:
		LPDIRECT3DDEVICE9 m_device;
		LightData m_light;
		int m_label;
		static std::list<int> m_lights;
	};

	using LightObjectReference = reference::IReference<Light>;
}

_MSLIB_END