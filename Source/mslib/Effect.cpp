//==========================================================================
// エフェクト [Effect.cpp]
// author : MasyoLab
//==========================================================================
#include "Effect.h"

_MSLIB_BEGIN

namespace effect
{
	EffectData::EffectData() :
		m_createID(0), m_effect(nullptr)
	{
	}

	EffectData::~EffectData()
	{
		if (m_effect != nullptr)
			m_effect->Release();
		m_effect = nullptr;
	}

	int64_t EffectData::GetCreateID()
	{
		return m_createID;
	}

	const LPD3DXEFFECT EffectData::GetEffect() const
	{
		return m_effect;
	}

	EffectLoader::EffectLoader() :
		m_createIDCount(0), m_device(nullptr)
	{
		SetComponentName("EffectLoader");
	}

	EffectLoader::EffectLoader(LPDIRECT3DDEVICE9 _device) :
		m_createIDCount(0), m_device(_device)
	{
		SetComponentName("EffectLoader");
	}

	EffectLoader::~EffectLoader()
	{
	}

	EffectReference EffectLoader::Load(const std::string& _path)
	{
		auto itr = m_resource_list.find(_path);
		if (itr != m_resource_list.end())
			return itr->second;

		LPD3DXBUFFER error = nullptr;
		LPD3DXEFFECT peffect = nullptr; // エフェクト

		if (FAILED(D3DXCreateEffectFromFile(m_device, _path.c_str(), 0, 0, 0, 0, &peffect, &error)))
		{
			if (error == nullptr)
				return EffectReference();
			OutputDebugStringA((const char*)error->GetBufferPointer());
			if (peffect != nullptr)
			{
				peffect->Release();
				peffect = nullptr;
			}
			return EffectReference();
		}

		m_createIDCount++;
		return m_resource_list[_path] =
			EffectData::Create(new EffectDataInput(
				m_createIDCount, peffect, _path, ThisComponent<Loader>()));
	}

	SetEffect::SetEffect()
	{
	}

	SetEffect::~SetEffect()
	{
	}

	void SetEffect::SetEffectData(const EffectReference& _effect)
	{
		m_effect_data = _effect;
	}

	EffectReference SetEffect::GetEffectData()
	{
		return m_effect_data;
	}

	EffectLoader::EffectDataInput::EffectDataInput()
	{
	}

	EffectLoader::EffectDataInput::EffectDataInput(
		int64_t _id,
		LPD3DXEFFECT _effect,
		const std::string& _tag,
		resource_loader::LoaderReference _loader)
	{
		m_createID = _id;
		m_tag = _tag;
		m_loader_ptr = _loader;
		m_effect = _effect;
	}

	EffectLoader::EffectDataInput::~EffectDataInput()
	{
	}

}

_MSLIB_END