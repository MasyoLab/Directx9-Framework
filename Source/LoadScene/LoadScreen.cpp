//==========================================================================
// ���[�h�X�N���[��[LoadScreen.cpp]
// author: MasyoLab
//==========================================================================
#include "resource_list.h"
#include "LoadScreen.h"

namespace load_screen
{
	LoadScreen::LoadScreen()
	{
		SetComponentName("LoadScreen");

		auto background = AddComponent(new mslib::object::Sprite(true));
		m_ring = AddComponent(new mslib::object::Sprite(true));
		m_font = AddComponent(new mslib::object::Sprite(true));

		background->SetComponentName("Background");
		m_ring->SetComponentName("Ring");
		m_font->SetComponentName("Font");

		// �w�i
		background->SetTextureData(GetTextureLoader()->Load(""));
		background->SetPriority(999999.1f);

		// �����O
		m_ring->SetTextureData(GetTextureLoader()->Load(RESOURCE_LoadTex_DDS));
		m_ring->SetPriority(999999.2f);

		// ���[�h�t�H���g
		m_paramload.m_Change = false;
		m_paramload.m_a = 100;
		m_font->SetTextureData(GetTextureLoader()->Load(RESOURCE_NowLoading_DDS));
		m_font->SetPriority(999999.3f);
	}

	LoadScreen::~LoadScreen()
	{
	}

	void LoadScreen::Init()
	{
	}

	void LoadScreen::Update()
	{
		// ���ݎ����̎擾
		m_NewTime = timeGetTime();

		// �O��Ƃ̍����擾
		DWORD dtime = m_NewTime - m_OldTime;

		//���ԓn��
		m_OldTime = m_NewTime;

		// ������]�͂ɕϊ�
		m_ring->AddRotation(0, 0, dtime * 0.0025f);

		Change((int)(dtime * 0.5f));

		auto& color = m_font->GetColor();
		m_font->SetColor(color.r, color.g, color.b, m_paramload.m_a / 255.0f);
	}

	void LoadScreen::Change(int Speed)
	{
		// �`�F���W�t���O
		if (m_paramload.m_Change)
		{
			m_paramload.m_a -= Speed;
			if (m_paramload.m_a <= 0)
			{
				m_paramload.m_a = 0;
				m_paramload.m_Change = false;
			}
		}
		else
		{
			m_paramload.m_a += Speed;
			if (255 <= m_paramload.m_a)
			{
				m_paramload.m_a = 255;
				m_paramload.m_Change = true;
			}
		}
	}
}