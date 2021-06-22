//==========================================================================
// �T�E���h [Audio.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#include <stdio.h>
#include <XAudio2.h>

#include "mslib.hpp"
#include "Component.h"
#include "Reference.h"
#include "Loader.h"

_MSLIB_BEGIN

namespace audio
{
	//==========================================================================
	//
	// class : AudioData
	// Content : �f�[�^
	//
	//==========================================================================
	class AudioData :
		public resource_loader::Resource
	{
	private:
		AudioData(const AudioData&) = delete;
		AudioData(AudioData&&) = delete;
		AudioData& operator=(const AudioData&) = delete;
		AudioData& operator=(AudioData&&) = delete;
	public:
		AudioData();
		~AudioData();

		/**
		@brief �{�����[���̎擾
		@return volume
		*/
		float GetVolume() const;

		/**
		@brief �{�����[���̐ݒ�
		@param volume [in] 0.0f�`1.0f
		*/
		void SetVolume(float voice);

		/**
		@brief �Đ�
		@param loop [in] true �Ń��[�v
		@return Component Object Model defines, and macros
		*/
		HRESULT Start(bool loop = false);

		/**
		@brief �r������Đ�
		@param loop [in] true �Ń��[�v
		@return Component Object Model defines, and macros
		*/
		HRESULT ReStart(bool loop = false);

		/**
		@brief �T�E���h�̈ꎞ��~
		*/
		void Stop();

		/**
		@brief �T�E���h�̒�~
		*/
		void End();

		/**
		@brief ���݂̃��[�v�̈�̏I���ɒB�����Ƃ��ɁA�{�C�X�̃��[�v���~���܂��B
		*/
		HRESULT ExitLoop();

		/**
		@brief �Đ��@�\���~���܂�
		*/
		void StopEngine();

		/**
		@brief �Đ��@�\���J�n���܂�
		*/
		HRESULT StartEngine();

		/**
		@brief Audio��GUI�ł�
		*/
		void GUIAudio();

		/**
		@brief Audio�̑S�Ă�GUI�ł�
		*/
		static void GUIAudioList();
	protected:
		IXAudio2* m_xaudio2; // XAudio2
		IXAudio2SourceVoice* m_source_voice; // �T�E���h
		BYTE* m_audio_data; // �I�[�f�B�I�f�[�^�[
		DWORD m_audio_bytes; // �I�[�f�B�I�f�[�^�T�C�Y
		float m_volume; // �{�����[��
		int64_t m_createID; // ����ID
		WAVEFORMATEX m_format; // Base WAVEFORMATEX data
#if defined(_MSLIB_DEBUG)
		bool m_open; // GUI�\���p�̃t���O
		static std::list<AudioData*> m_audios; // audios
#endif
	};

	using AudioDataReference = resource_loader::ResourceReference<AudioData>;

	//==========================================================================
	//
	// class : AudioLoader
	// Content : �T�E���h��ǂݍ��ދ@�\�ł�
	//
	//==========================================================================
	class AudioLoader :
		public resource_loader::Loader
	{
		class AudioDataInput :
			public AudioData
		{
		public:
			AudioDataInput();
			AudioDataInput(
				IXAudio2* xaudio2,
				IXAudio2SourceVoice* SourceVoice,
				BYTE* AudioData,
				const DWORD& AudioBytes, 
				WAVEFORMATEX& format,
				int64_t createID,
				const std::string& tag,
				resource_loader::LoaderReference loader
			);
			~AudioDataInput();
		};
	private:
		AudioLoader(const AudioLoader&) = delete;
		AudioLoader(AudioLoader&&) = delete;
		AudioLoader& operator=(const AudioLoader&) = delete;
		AudioLoader& operator=(AudioLoader&&) = delete;
	public:
		AudioLoader();
		~AudioLoader();

		/**
		@brief ������
		@param hwnd [in] �C���X�^���X�n���h��
		@return Component Object Model defines, and macros
		*/
		HRESULT Init(HWND hwnd);

		/**
		@brief �T�E���h�f�[�^��ǂݍ���
		@param str [in] �ǂݍ��݃p�X
		@return �T�E���h�f�[�^
		*/
		AudioDataReference Load(const std::string& str);
	private:
		/**
		@brief �`�����N�̃`�F�b�N
		@param hFile [in]
		@param format [in]
		@param pChunkSize [in]
		@param pChunkDataPosition [in]
		*/
		HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);

		/**
		@brief �`�����N�f�[�^�̓ǂݍ���
		@param hFile [in]
		@param pBuffer [in]
		@param dwBuffersize [in]
		@param dwBufferoffset [in]
		*/
		HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	private:
		IXAudio2MasteringVoice* m_master_voice; // �}�X�^�[�{�C�X
		int64_t m_createIDCount; // �J�E���^
		IXAudio2* m_xaudio2; // XAudio2
		HWND m_hwnd; // �E�B���h�n���h��
	};

	using AudioLoaderReference = reference::IReference<AudioLoader>;
}

_MSLIB_END