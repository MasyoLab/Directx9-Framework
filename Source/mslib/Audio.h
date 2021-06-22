//==========================================================================
// サウンド [Audio.h]
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
	// Content : データ
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
		@brief ボリュームの取得
		@return volume
		*/
		float GetVolume() const;

		/**
		@brief ボリュームの設定
		@param volume [in] 0.0f～1.0f
		*/
		void SetVolume(float voice);

		/**
		@brief 再生
		@param loop [in] true でループ
		@return Component Object Model defines, and macros
		*/
		HRESULT Start(bool loop = false);

		/**
		@brief 途中から再生
		@param loop [in] true でループ
		@return Component Object Model defines, and macros
		*/
		HRESULT ReStart(bool loop = false);

		/**
		@brief サウンドの一時停止
		*/
		void Stop();

		/**
		@brief サウンドの停止
		*/
		void End();

		/**
		@brief 現在のループ領域の終わりに達したときに、ボイスのループを停止します。
		*/
		HRESULT ExitLoop();

		/**
		@brief 再生機能を停止します
		*/
		void StopEngine();

		/**
		@brief 再生機能を開始します
		*/
		HRESULT StartEngine();

		/**
		@brief AudioのGUIです
		*/
		void GUIAudio();

		/**
		@brief Audioの全てのGUIです
		*/
		static void GUIAudioList();
	protected:
		IXAudio2* m_xaudio2; // XAudio2
		IXAudio2SourceVoice* m_source_voice; // サウンド
		BYTE* m_audio_data; // オーディオデーター
		DWORD m_audio_bytes; // オーディオデータサイズ
		float m_volume; // ボリューム
		int64_t m_createID; // 生成ID
		WAVEFORMATEX m_format; // Base WAVEFORMATEX data
#if defined(_MSLIB_DEBUG)
		bool m_open; // GUI表示用のフラグ
		static std::list<AudioData*> m_audios; // audios
#endif
	};

	using AudioDataReference = resource_loader::ResourceReference<AudioData>;

	//==========================================================================
	//
	// class : AudioLoader
	// Content : サウンドを読み込む機能です
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
		@brief 初期化
		@param hwnd [in] インスタンスハンドル
		@return Component Object Model defines, and macros
		*/
		HRESULT Init(HWND hwnd);

		/**
		@brief サウンドデータを読み込む
		@param str [in] 読み込みパス
		@return サウンドデータ
		*/
		AudioDataReference Load(const std::string& str);
	private:
		/**
		@brief チャンクのチェック
		@param hFile [in]
		@param format [in]
		@param pChunkSize [in]
		@param pChunkDataPosition [in]
		*/
		HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);

		/**
		@brief チャンクデータの読み込み
		@param hFile [in]
		@param pBuffer [in]
		@param dwBuffersize [in]
		@param dwBufferoffset [in]
		*/
		HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	private:
		IXAudio2MasteringVoice* m_master_voice; // マスターボイス
		int64_t m_createIDCount; // カウンタ
		IXAudio2* m_xaudio2; // XAudio2
		HWND m_hwnd; // ウィンドハンドル
	};

	using AudioLoaderReference = reference::IReference<AudioLoader>;
}

_MSLIB_END