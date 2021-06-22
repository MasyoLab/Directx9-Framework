//==========================================================================
// �G�t�F�N�g [Effect.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Reference.h"
#include "Loader.h"

_MSLIB_BEGIN

namespace effect
{
	//==========================================================================
	//
	// class : EffectData
	// Content : �G�t�F�N�g�f�[�^
	//
	//==========================================================================
	class EffectData :
		public resource_loader::Resource
	{
	private:
		EffectData(const EffectData&) = delete;
		EffectData(EffectData&&) = delete;
		EffectData& operator=(const EffectData&) = delete;
		EffectData& operator=(EffectData&&) = delete;
	public:
		EffectData();
		~EffectData();
		int64_t GetCreateID();
		const LPD3DXEFFECT GetEffect() const;
	protected:
		int64_t m_createID; // ����ID
		LPD3DXEFFECT m_effect; // �G�t�F�N�g
	};

	using EffectReference = resource_loader::ResourceReference<EffectData>;

	//==========================================================================
	//
	// class : EffectLoader
	// Content : �G�t�F�N�g�ǂݍ��ݔj���N���X
	//
	//==========================================================================
	class EffectLoader :
		public resource_loader::Loader
	{
		class EffectDataInput :
			public EffectData
		{
		public:
			EffectDataInput();
			EffectDataInput(
				int64_t _id,
				LPD3DXEFFECT _effect,
				const std::string& _tag,
				resource_loader::LoaderReference _loader
			);
			~EffectDataInput();
		};
	private:
		// �R�s�[�֎~ (C++11)
		EffectLoader(const EffectLoader&) = delete;
		EffectLoader& operator=(const EffectLoader&) = delete;
		EffectLoader& operator=(EffectLoader&&) = delete;
	public:
		EffectLoader();
		EffectLoader(LPDIRECT3DDEVICE9 _device);
		~EffectLoader();

		/**
		@brief �G�t�F�N�g��ǂݍ��ށB
		@param _path [in] �ǂݍ��݃p�X
		@return �G�t�F�N�g�̃|�C���^
		*/
		EffectReference Load(const std::string& _path);
	private:
		LPDIRECT3DDEVICE9 m_device; // �f�o�C�X
		int64_t m_createIDCount; // �J�E���^
	};

	using EffectLoaderReference = reference::IReference<EffectLoader>;

	//==========================================================================
	//
	// class : SetEffect
	// Content : �G�t�F�N�g�o�^
	//
	//==========================================================================
	class SetEffect
	{
	public:
		SetEffect();
		~SetEffect();

		/**
		@brief �G�t�F�N�g�f�[�^�̓o�^
		@param _effect [in] �f�[�^
		*/
		void SetEffectData(const EffectReference& _effect);

		/**
		@brief �G�t�F�N�g�f�[�^�̎擾
		@return �G�t�F�N�g�̃|�C���^
		*/
		EffectReference GetEffectData();
	protected:
		EffectReference m_effect_data;
	};
}

_MSLIB_END