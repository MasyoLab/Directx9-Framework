//==========================================================================
// Effekseer [EffekseerDX.cpp]
// author : MasyoLab
//==========================================================================
#include "EffekseerDX.h"
#include "Camera.h"

_MSLIB_BEGIN

namespace effekseer_dx
{
	std::list<Renderer*> Renderer::m_renderers;

	Renderer::Renderer()
	{
		m_renderers.push_back(this);
	}

	Renderer::~Renderer()
	{
		// 先にエフェクト管理用インスタンスを破棄
		m_renderer.reset();

		// 次に音再生用インスタンスを破棄
		m_sound.reset();

		// 次に描画用インスタンスを破棄
		m_renderer.reset();

		auto itr = std::find(m_renderers.begin(), m_renderers.end(), this);
		if (itr != m_renderers.end())
			m_renderers.erase(itr);
	}

	void Renderer::UpdateAll()
	{
		for (auto& itr : m_renderers)
			if (itr->m_manager != nullptr)
				itr->m_manager->Update();
	}

	void Renderer::DrawAll()
	{
		auto view_camera = camera::Camera::GetCamera();
		if (view_camera == nullptr)
			return;

		auto vEye = view_camera->GetLook1().eye + view_camera->GetLook2().eye;
		auto vAt = view_camera->GetLook1().at + view_camera->GetLook2().at;
		auto vUp = view_camera->GetLook1().up;
		auto pProjection = view_camera->GetProjectionMatrix();
		auto projection44 = Effekseer::Matrix44();
		auto& values = projection44.Values;
		auto LookAtLH = Effekseer::Matrix44().LookAtLH(
			Effekseer::Vector3D(vEye.x, vEye.y, vEye.z),
			Effekseer::Vector3D(vAt.x, vAt.y, vAt.z),
			Effekseer::Vector3D(vUp.x, vUp.y, vUp.z));

		values[0][0] = pProjection->_11; values[0][1] = pProjection->_12; values[0][2] = pProjection->_13; values[0][3] = pProjection->_14;
		values[1][0] = pProjection->_21; values[1][1] = pProjection->_22; values[1][2] = pProjection->_23; values[1][3] = pProjection->_24;
		values[2][0] = pProjection->_31; values[2][1] = pProjection->_32; values[2][2] = pProjection->_33; values[2][3] = pProjection->_34;
		values[3][0] = pProjection->_41; values[3][1] = pProjection->_42; values[3][2] = pProjection->_43; values[3][3] = pProjection->_44;

		for (auto& itr : m_renderers)
		{
			if (itr->m_manager == nullptr || itr->m_renderer == nullptr)
				continue;

			// 投影行列を設定
			itr->m_renderer->SetProjectionMatrix(projection44);

			itr->m_renderer->SetCameraMatrix(LookAtLH);

			// エフェクトの描画開始処理を行う。
			if (itr->m_renderer->BeginRendering())
			{
				itr->m_manager->Draw();
				itr->m_renderer->EndRendering();
			}
		}
	}

	void Renderer::SetUpManager(LPDIRECT3DDEVICE9 _device, int32_t _squareMaxCount, int _instance_max, bool _autoFlip)
	{
		// 描画用インスタンスの生成
		if (m_renderer == nullptr)
			m_renderer = std::shared_ptr<EffekseerRendererDX9::Renderer>(
				EffekseerRendererDX9::Renderer::Create(_device, _squareMaxCount),
				[](EffekseerRendererDX9::Renderer* p) {
					// カスタムデリータ
					if (p != nullptr) {
						p->Destroy();
						p = nullptr;
					}
				});

		// エフェクト管理用インスタンスの生成
		if (m_manager == nullptr)
		{
			m_manager = std::shared_ptr<Effekseer::Manager>(
				Effekseer::Manager::Create(_instance_max, _autoFlip), 
				[](Effekseer::Manager* p) {
					// カスタムデリータ
					if (p != nullptr) {
						p->Destroy();
						p = nullptr;
					}
				});

			// 描画用インスタンスから描画機能を設定
			m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
			m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
			m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
			m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
			m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

			// 描画用インスタンスからテクスチャの読込機能を設定
			// 独自拡張可能、現在はファイルから読み込んでいる。
			m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
			m_manager->SetModelLoader(m_renderer->CreateModelLoader());
		}
	}

	void Renderer::SetUpSound(IXAudio2* _xaudio2, int32_t _num1chVoices, int32_t _num2chVoices)
	{
		if (m_sound == nullptr)
			m_sound = std::shared_ptr<EffekseerSound::Sound>(
				EffekseerSound::Sound::Create(_xaudio2, _num1chVoices, _num2chVoices),
				[](EffekseerSound::Sound* p) {
					// カスタムデリータ
					if (p != nullptr) {
						p->Destroy();
						p = nullptr;
					}
				});
	}

	EffekseerData::EffekseerData()
	{
	}

	EffekseerData::~EffekseerData()
	{
		// エフェクトの停止
		if (!m_manager.check())
			return;

		// 実行済みハンドルから、現在存在しているインスタンスを終了する
		for (auto& itr : m_handle_list)
			if (m_manager->Exists(itr))
				m_manager->StopEffect(itr);
	}

	reference::IReference<Effekseer::Manager> EffekseerData::GetManager()
	{
		return m_manager;
	}

	reference::IReference<EffekseerRendererDX9::Renderer> EffekseerData::GetRenderer()
	{
		return m_renderer;
	}

	reference::IReference<EffekseerSound::Sound> EffekseerData::GetSound()
	{
		return m_sound;
	}

	reference::IReference<Effekseer::Effect> EffekseerData::GetEffect()
	{
		return m_effect;
	}

	void EffekseerData::SetHandle(Effekseer::Handle _handle)
	{
		m_handle_list.push_back(_handle);
	}

	Effekseer::Handle EffekseerData::Play(D3DXVECTOR3 pos)
	{
		if (m_manager == nullptr || m_effect == nullptr)
			return (Effekseer::Handle) - 1;
		return m_manager->Play(&(*m_effect), pos.x, pos.y, pos.z);
	}

	Effekseer::Handle EffekseerData::Play(float x, float y, float z)
	{
		if (m_manager == nullptr || m_effect == nullptr)
			return (Effekseer::Handle) - 1;
		return m_manager->Play(&(*m_effect), x, y, z);
	}

	EffekseerLoader::EffekseerDataInput::EffekseerDataInput()
	{
	}

	EffekseerLoader::EffekseerDataInput::EffekseerDataInput(const std::string& _tag,
		reference::IReference<Effekseer::Manager> _manager,
		reference::IReference<EffekseerRendererDX9::Renderer> _renderer,
		reference::IReference<EffekseerSound::Sound> _sound,
		std::shared_ptr<Effekseer::Effect> _effect,
		resource_loader::LoaderReference _loader)
	{
		m_manager = _manager;
		m_renderer = _renderer;
		m_sound = _sound;
		m_effect = _effect;
		m_tag = _tag;
		m_loader_ptr = _loader;
	}

	EffekseerLoader::EffekseerDataInput::~EffekseerDataInput()
	{
	}

	EffekseerLoader::EffekseerLoader() :
		m_device(nullptr)
	{
		SetComponentName("EffekseerLoader");
	}

	EffekseerLoader::EffekseerLoader(LPDIRECT3DDEVICE9 device) :
		m_device(device)
	{
		SetComponentName("EffekseerLoader");
	}

	EffekseerLoader::~EffekseerLoader()
	{
	}

	void EffekseerLoader::InitManager(int32_t _squareMaxCount, int _instance_max, bool _autoFlip)
	{
		SetUpManager(m_device, _squareMaxCount, _instance_max, _autoFlip);
	}

	void EffekseerLoader::InitSound(IXAudio2* _xaudio2, int32_t _num1chVoices, int32_t _num2chVoices)
	{
		SetUpSound(_xaudio2, _num1chVoices, _num2chVoices);
	}

	EffekseerReference EffekseerLoader::Load(const EFK_CHAR* path, const std::string& effect_name)
	{
		if (m_manager == nullptr)
			return EffekseerReference();

		auto itr = m_resource_list.find(effect_name);
		if (itr != m_resource_list.end())
			return itr->second;
		return m_resource_list[effect_name] = EffekseerData::Create(new EffekseerDataInput(
			effect_name, m_manager, m_renderer, m_sound,
			std::shared_ptr<Effekseer::Effect>(Effekseer::Effect::Create(&(*m_manager), path),
				[](Effekseer::Effect* p) {
					// カスタムデリータ
					if (p != nullptr) {
						p->Release();
						p = nullptr;
					}}),
			ThisComponent<Loader>()));
	}

	CreateEffekseerLoader::CreateEffekseerLoader() :
		m_device(nullptr)
	{
		SetComponentName("CreateEffekseerLoader");
	}

	CreateEffekseerLoader::CreateEffekseerLoader(LPDIRECT3DDEVICE9 device) :
		m_device(device)
	{
		SetComponentName("CreateEffekseerLoader");
	}

	CreateEffekseerLoader::~CreateEffekseerLoader()
	{
	}

	EffekseerLoaderReference CreateEffekseerLoader::Create(const std::string& _str)
	{
		auto itr = m_resource_list.find(_str);
		if (itr != m_resource_list.end())
			return itr->second;
		return m_resource_list[_str] = EffekseerLoader::Create(new EffekseerLoaderInput(
			_str, ThisComponent<Loader>(), m_device));
	}

	SetEffekseer::SetEffekseer()
	{
	}

	SetEffekseer::~SetEffekseer()
	{
	}

	void SetEffekseer::SetEffekseerData(const EffekseerReference& effekseer)
	{
		m_effekseer_data = effekseer;
	}

	EffekseerReference SetEffekseer::GetEffekseerData()
	{
		return m_effekseer_data;
	}

	reference::IReference<Effekseer::Manager> SetEffekseer::GetManager()
	{
		return m_effekseer_data->GetManager();
	}

	reference::IReference<Effekseer::Effect> SetEffekseer::GetEffect()
	{
		return m_effekseer_data->GetEffect();
	}

	reference::IReference<EffekseerSound::Sound> SetEffekseer::GetSound()
	{
		return m_effekseer_data->GetSound();
	}

	CreateEffekseerLoader::EffekseerLoaderInput::EffekseerLoaderInput()
	{
	}

	CreateEffekseerLoader::EffekseerLoaderInput::EffekseerLoaderInput(const std::string& _tag, resource_loader::LoaderReference _loader, LPDIRECT3DDEVICE9 device)
		: EffekseerLoader(device)
	{
		m_tag = _tag;
		m_loader_ptr = _loader;
	}

	CreateEffekseerLoader::EffekseerLoaderInput::~EffekseerLoaderInput()
	{
	}
}

_MSLIB_END