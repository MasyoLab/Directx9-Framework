//==========================================================================
// �T�E���h [Audio.cpp]
// author : MasyoLab
//==========================================================================
#include "Audio.h"
#include "MsImGui.h"
#include "get_path_and_file.h"

_MSLIB_BEGIN

namespace audio
{
#if defined(_MSLIB_DEBUG)
	std::list<AudioData*> AudioData::m_audios;
#endif
	AudioLoader::AudioLoader() : 
		m_master_voice(nullptr), m_xaudio2(nullptr), m_hwnd(nullptr), m_createIDCount(0)
	{
		SetComponentName("AudioLoader");
	}

	AudioLoader::~AudioLoader()
	{
		DestroyComponent();
		m_resource_list.clear();
		if (m_master_voice != nullptr)
			m_master_voice->DestroyVoice();
		if (m_xaudio2 != nullptr)
			m_xaudio2->Release();
		m_master_voice = nullptr;
		m_xaudio2 = nullptr;

		// COM���C�u�����̏I������
		CoUninitialize();
	}

	HRESULT AudioLoader::Init(HWND hwnd)
	{
		if (m_xaudio2 != nullptr)
			return S_OK;

		m_hwnd = hwnd;

		// COM���C�u�����̏�����
		if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED)))
		{
			MessageBox(hwnd, "�������Ɏ��s���܂���", "Error", MB_ICONWARNING);
			return E_FAIL;
		}

		// XAudio2�I�u�W�F�N�g�̍쐬
		// UINT32 Flags = 0
		// XAUDIO2_PROCESSOR XAudio2Processor = XAUDIO2_DEFAULT_PROCESSOR
		if (FAILED(XAudio2Create(&m_xaudio2, 0)))
		{
			MessageBox(hwnd, "XAudio2�I�u�W�F�N�g�̎��s���܂���", "Error", MB_ICONWARNING);
			return E_FAIL;
		}

		// �}�X�^�[�{�C�X�̐���
		// UINT32 InputChannels = XAUDIO2_DEFAULT_CHANNELS
		// UINT32 InputSampleRate = XAUDIO2_DEFAULT_SAMPLERATE,
		// UINT32 Flags = 0
		// UINT32 DeviceIndex = 0
		// const XAUDIO2_EFFECT_CHAIN *pEffectChain = NULL
		if (FAILED(m_xaudio2->CreateMasteringVoice(&m_master_voice)))
		{
			MessageBox(hwnd, "�}�X�^�[�{�C�X�̐����Ɏ��s���܂���", "Error", MB_ICONWARNING);
			return E_FAIL;
		}
		return S_OK;
	}

	AudioDataReference AudioLoader::Load(const std::string& str)
	{
		auto itr = m_resource_list.find(str);
		if (itr != m_resource_list.end())
			return itr->second;

		HANDLE hFile;
		DWORD dwChunkSize = 0, dwChunkPosition = 0, dwFiletype = 0, sizeAudio = 0;
		WAVEFORMATEXTENSIBLE wfx;
		IXAudio2SourceVoice* pSourceVoice = nullptr; // �T�E���h
		BYTE* pAudioData = nullptr;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(str.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(m_hwnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s(1)", "�x��", MB_ICONWARNING);
			return AudioDataReference();
		}

		// �t�@�C���|�C���^��擪�Ɉړ�
		if (SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{
			MessageBox(m_hwnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s(2)", "�x��", MB_ICONWARNING);
			return AudioDataReference();
		}

		// WAVE�t�@�C���̃`�F�b�N
		if (FAILED(CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition)))
		{
			MessageBox(m_hwnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s(1)", "�x��", MB_ICONWARNING);
			return AudioDataReference();
		}

		if (FAILED(ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition)))
		{
			MessageBox(m_hwnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s(2)", "�x��", MB_ICONWARNING);
			return AudioDataReference();
		}

		if (dwFiletype != 'EVAW')
		{
			MessageBox(m_hwnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s(3)", "�x��", MB_ICONWARNING);
			return AudioDataReference();
		}

		// �t�H�[�}�b�g�`�F�b�N
		if (FAILED(CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition)))
		{
			MessageBox(m_hwnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s(1)", "�x��", MB_ICONWARNING);
			return AudioDataReference();
		}

		if (FAILED(ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition)))
		{
			MessageBox(m_hwnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s(2)", "�x��", MB_ICONWARNING);
			return AudioDataReference();
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		if (FAILED(CheckChunk(hFile, 'atad', &sizeAudio, &dwChunkPosition)))
		{
			MessageBox(m_hwnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s(1)", "�x��", MB_ICONWARNING);
			return AudioDataReference();
		}

		// �������m��
		mslib::_new(pAudioData, sizeAudio);

		if (FAILED(ReadChunkData(hFile, pAudioData, sizeAudio, dwChunkPosition)))
		{
			MessageBox(m_hwnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s(2)", "�x��", MB_ICONWARNING);
			mslib::_delete(pAudioData);
			return AudioDataReference();
		}

		// �\�[�X�{�C�X�̐���
		if (FAILED(m_xaudio2->CreateSourceVoice(&pSourceVoice, &wfx.Format)))
		{
			MessageBox(m_hwnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x��", MB_ICONWARNING);
			mslib::_delete(pAudioData);
			return AudioDataReference();
		}

		auto path_str = get_path_and_file::GetPathAndFile(str);

		m_createIDCount++; // �����J�E���^����
		return m_resource_list[str] = AudioData::Create(new AudioDataInput(
			m_xaudio2, pSourceVoice, pAudioData, sizeAudio, wfx.Format, m_createIDCount, path_str.m_file_name + path_str.m_ext_name, ThisComponent<Loader>()));
	}

	HRESULT AudioLoader::CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition)
	{
		HRESULT hr = S_OK;
		DWORD dwRead;
		DWORD dwChunkType;
		DWORD dwChunkDataSize;
		DWORD dwRIFFDataSize = 0;
		DWORD dwFileType;
		DWORD dwBytesRead = 0;
		DWORD dwOffset = 0;

		// �t�@�C���|�C���^��擪�Ɉړ�
		if (SetFilePointer(hFile, 0, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
			return HRESULT_FROM_WIN32(GetLastError());

		while (hr == S_OK)
		{
			// �`�����N�̓ǂݍ���
			if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, nullptr) == 0)
				hr = HRESULT_FROM_WIN32(GetLastError());

			// �`�����N�f�[�^�̓ǂݍ���
			if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, nullptr) == 0)
				hr = HRESULT_FROM_WIN32(GetLastError());

			switch (dwChunkType)
			{
			case 'FFIR':
				dwRIFFDataSize = dwChunkDataSize;
				dwChunkDataSize = 4;

				// �t�@�C���^�C�v�̓ǂݍ���
				if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, nullptr) == 0)
					hr = HRESULT_FROM_WIN32(GetLastError());
				break;
			default:
				// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				if (SetFilePointer(hFile, dwChunkDataSize, nullptr, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
					return HRESULT_FROM_WIN32(GetLastError());
			}

			dwOffset += sizeof(DWORD) * 2;
			if (dwChunkType == format)
			{
				*pChunkSize = dwChunkDataSize;
				*pChunkDataPosition = dwOffset;
				return S_OK;
			}

			dwOffset += dwChunkDataSize;
			if (dwBytesRead >= dwRIFFDataSize)
				return S_FALSE;
		}

		return S_OK;
	}

	HRESULT AudioLoader::ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
	{
		DWORD dwRead;

		// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		if (SetFilePointer(hFile, dwBufferoffset, nullptr, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
			return HRESULT_FROM_WIN32(GetLastError());

		// �f�[�^�̓ǂݍ���
		if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, nullptr) == 0)
			return HRESULT_FROM_WIN32(GetLastError());

		return S_OK;
	}

	AudioData::AudioData() :
		m_xaudio2(nullptr), m_source_voice(nullptr), m_audio_data(nullptr), m_audio_bytes(0), m_volume(1), m_createID(0), m_format({ 0 })
	{
#if defined(_MSLIB_DEBUG)
		m_open = false;
		m_audios.push_back(this);
#endif
	}

	AudioData::~AudioData()
	{
#if defined(_MSLIB_DEBUG)
		auto itr = std::find(m_audios.begin(), m_audios.end(), this);
		if (itr != m_audios.end())
			m_audios.erase(itr);
#endif
		if (m_source_voice == nullptr)
			return;

		XAUDIO2_VOICE_STATE xa2state;

		m_source_voice->GetState(&xa2state);

		// �Đ���
		if (xa2state.BuffersQueued != 0)
		{
			// �ꎞ��~
			m_source_voice->Stop(0);

			// �I�[�f�B�I�o�b�t�@�̍폜
			m_source_voice->FlushSourceBuffers();
		}

		// �\�[�X�{�C�X�̔j��
		m_source_voice->DestroyVoice();
		m_source_voice = nullptr;

		// �I�[�f�B�I�f�[�^�̊J��
		mslib::_delete(m_audio_data);
	}

	float AudioData::GetVolume() const
	{
		return m_volume;
	}

	void AudioData::SetVolume(float voice)
	{
		m_volume = voice;
	}

	HRESULT AudioData::Start(bool loop)
	{
		if (m_source_voice == nullptr)
			return E_NOTIMPL;

		HRESULT ret;
		XAUDIO2_BUFFER buffer;

		// �Đ��O�ɒ�~����
		End();

		memset(&buffer, 0, sizeof(buffer));

		// �o�b�t�@�̒l�ݒ�
		buffer.AudioBytes = m_audio_bytes;
		buffer.pAudioData = m_audio_data;
		buffer.Flags = XAUDIO2_END_OF_STREAM;

		if (loop)
			buffer.LoopCount = XAUDIO2_INVALID_OPSET;
		else if (!loop)
			buffer.LoopCount = XAUDIO2_NO_LOOP_REGION;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		ret = m_source_voice->SubmitSourceBuffer(&buffer);
		if (FAILED(ret))
			return ret;

		ret = m_source_voice->SetVolume(m_volume);
		if (FAILED(ret))
			return ret;

		// �Đ�
		return m_source_voice->Start(0);
	}

	HRESULT AudioData::ReStart(bool loop)
	{
		if (m_source_voice == nullptr)
			return E_NOTIMPL;

		HRESULT ret;
		XAUDIO2_BUFFER buffer;

		memset(&buffer, 0, sizeof(buffer));

		// �o�b�t�@�̒l�ݒ�
		buffer.AudioBytes = m_audio_bytes;
		buffer.pAudioData = m_audio_data;
		buffer.Flags = XAUDIO2_END_OF_STREAM;

		if (loop)
			buffer.LoopCount = XAUDIO2_INVALID_OPSET;
		else if (!loop)
			buffer.LoopCount = XAUDIO2_NO_LOOP_REGION;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		ret = m_source_voice->SubmitSourceBuffer(&buffer);
		if (FAILED(ret))
			return ret;

		ret = m_source_voice->SetVolume(m_volume);
		if (FAILED(ret))
			return ret;

		// �Đ�
		return m_source_voice->Start(0);
	}

	void AudioData::Stop()
	{
		if (m_source_voice == nullptr)
			return;

		XAUDIO2_VOICE_STATE xa2state;

		// ��Ԏ擾
		m_source_voice->GetState(&xa2state);

		// �Đ����ł͂Ȃ�
		if (xa2state.BuffersQueued == 0)
			return;

		// �ꎞ��~
		m_source_voice->Stop(0);
	}

	void AudioData::End()
	{
		if (m_source_voice == nullptr)
			return;

		XAUDIO2_VOICE_STATE xa2state;

		// ��Ԏ擾
		m_source_voice->GetState(&xa2state);

		// �Đ����ł͂Ȃ�
		if (xa2state.BuffersQueued == 0)
			return;

		// �ꎞ��~
		m_source_voice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_source_voice->FlushSourceBuffers();
	}

	HRESULT AudioData::ExitLoop()
	{
		if (m_source_voice == nullptr)
			return E_FAIL;
		return m_source_voice->ExitLoop(XAUDIO2_COMMIT_NOW);
	}

	void AudioData::StopEngine()
	{
		if (m_xaudio2 == nullptr)
			return;
		m_xaudio2->StopEngine();
	}

	HRESULT AudioData::StartEngine()
	{
		if (m_xaudio2 == nullptr)
			return E_FAIL;
		return m_xaudio2->StartEngine();
	}

	void AudioData::GUIAudio()
	{
#if defined(_MSLIB_DEBUG)
		if (m_source_voice == nullptr)
			return;
		imgui::Text(imgui::CreateText("Audio Name : %s", m_tag.c_str()));

		// �t�H�[�}�b�g�^�O
		switch (m_format.wFormatTag)
		{
		case WAVE_FORMAT_PCM:
			imgui::Text("Saving Format : PCM");
			break;
		case WAVE_FORMAT_UNKNOWN:
			imgui::Text("Saving Format : Unknown or invalid format tag");
			break;
		case WAVE_FORMAT_IEEE_FLOAT:
			imgui::Text("Saving Format : 32-bit floating-point");
			break;
		case WAVE_FORMAT_MPEGLAYER3:
			imgui::Text("Saving Format : ISO/MPEG Layer3");
			break;
		case WAVE_FORMAT_DOLBY_AC3_SPDIF:
			imgui::Text("Saving Format : Dolby Audio Codec 3 over S/PDIF");
			break;
		case WAVE_FORMAT_WMAUDIO2:
			imgui::Text("Saving Format : Windows Media Audio");
			break;
		case WAVE_FORMAT_WMAUDIO3:
			imgui::Text("Saving Format : Windows Media Audio Pro");
			break;
		case WAVE_FORMAT_WMASPDIF:
			imgui::Text("Saving Format : Windows Media Audio over S/PDIF");
			break;
		case WAVE_FORMAT_EXTENSIBLE:
			imgui::Text("Saving Format : All WAVEFORMATEXTENSIBLE formats");
			break;
		default:
			break;
		}

		// �`���l����
		switch (m_format.nChannels)
		{
		case 1:
			imgui::Text("Number of channels : mono");
			break;
		case 2:
			imgui::Text("Number of channels : stereo");
			break;
		case 4:
			imgui::Text("Number of channels : 4-channel stereo");
			break;
		case 6:
			imgui::Text("Number of channels : 5.1 channel");
			break;
		case 8:
			imgui::Text("Number of channels : 7.1 channel");
			break;
		default:
			break;
		}

		// �T���v�����O���g��
		imgui::Text(imgui::CreateText("Sampling frequency : %dHz", m_format.nSamplesPerSec));

		// �f�[�^�]����
		imgui::Text(imgui::CreateText("Data transfer rate per second : %d", m_format.nAvgBytesPerSec));

		// �u���b�N�A���C��
		imgui::Text(imgui::CreateText("Block alignment : %d", m_format.nBlockAlign));

		// �R���e�i�T�C�Y
		imgui::Text(imgui::CreateText("Container size : %d", m_format.wBitsPerSample));

		// �g���T�C�Y
		imgui::Text(imgui::CreateText("Extended size : %d", m_format.cbSize));

		imgui::Separator();
		imgui::Text("Sound menu");
		imgui::Separator();
		if (imgui::Button("Start"))
			Start();
		if (imgui::Button("ReStart"))
			ReStart();
		if (imgui::Button("Stop"))
			Stop();
		if (imgui::Button("End"))
			End();
		if (imgui::Button("ExitLoop"))
			ExitLoop();

		imgui::Separator();
		imgui::Text("Engine menu");
		imgui::Separator();
		if (imgui::Button("StartEngine"))
			StartEngine();
		if (imgui::Button("StopEngine"))
			StopEngine();

		imgui::Separator();
#endif
	}

	void AudioData::GUIAudioList()
	{
#if defined(_MSLIB_DEBUG)
		if (imgui::NewTreeNode("Audio GUI", false))
		{
			for (auto& itr : m_audios)
				if (itr->m_source_voice != nullptr)
					imgui::Checkbox(itr->GetTag(), itr->m_open);
			imgui::EndTreeNode();
		}

		for (auto& itr : m_audios)
		{
			if (!itr->m_open)
				continue;
			imgui::_Begin(itr->GetTag().c_str(), &itr->m_open, ImGuiWindowFlags_NoSavedSettings);
			itr->GUIAudio();
			imgui::EndWindow();
		}
#endif
	}

	AudioLoader::AudioDataInput::AudioDataInput()
	{
	}

	AudioLoader::AudioDataInput::AudioDataInput(
		IXAudio2* xaudio2,
		IXAudio2SourceVoice* SourceVoice,
		BYTE* AudioData,
		const DWORD& AudioBytes,
		WAVEFORMATEX& format,
		int64_t createID,
		const std::string& tag,
		resource_loader::LoaderReference loader
	)
	{
		m_xaudio2 = xaudio2;
		m_source_voice = SourceVoice;
		m_audio_data = AudioData;
		m_audio_bytes = AudioBytes;
		m_format = format;
		m_createID = createID;
		m_tag = tag;
		m_loader_ptr = loader;
	}

	AudioLoader::AudioDataInput::~AudioDataInput()
	{
	}
}
_MSLIB_END