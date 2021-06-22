//==========================================================================
// ���C�g [Light.cpp]
// author : MasyoLab
//==========================================================================
#include "Light.h"

_MSLIB_BEGIN

namespace object
{
	std::list<int> Light::m_lights;

	LightData::LightData()
	{
		ZeroMemory(this, sizeof(*this));
	}

	LightData::~LightData()
	{
	}

	Light::Light(LPDIRECT3DDEVICE9 pDevice) :
		m_device(pDevice), m_label(0)
	{
		SetComponentName("Light");
		SetMatrixType(MatrixType::World);
		SetActivity(true);
		CreateLabel();
	}

	Light::Light(LPDIRECT3DDEVICE9 pDevice, bool _bInOutFunctionFlag) :
		InOutFunction(_bInOutFunctionFlag), m_device(pDevice), m_label(0)
	{
		SetComponentName("Light");
		SetMatrixType(MatrixType::World);
		SetActivity(true);
		CreateLabel();
	}

	Light::~Light()
	{
		auto itr = std::find(m_lights.begin(), m_lights.end(), m_label);
		if (itr != m_lights.end())
			m_lights.erase(itr);

		if (m_device != nullptr)
			m_device->LightEnable(m_label, false); // �g�p�̋���
	}

	void Light::Init()
	{
		Init(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
	}

	void Light::Init(const D3DXVECTOR3& aVecDir)
	{
		if (m_device == nullptr)
			return;

		// ���C�g�̐ݒ�
		ZeroMemory(&m_light, sizeof(m_light));
		D3DXVec3Normalize((D3DXVECTOR3*)& m_light.Direction, &aVecDir);

		m_light.Type = D3DLIGHT_DIRECTIONAL;
		m_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_light.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		m_light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
		m_light.Direction = D3DXVECTOR3(-5.0f, -1.0f, 1.0f);

		m_light.Range = 1000.0f;

		// ���C�g�̐ݒ�
		m_device->SetLight(m_label, &m_light); // ���C�g�̎��
		m_device->LightEnable(m_label, true); // �g�p�̋���
		m_device->SetRenderState(D3DRS_LIGHTING, true);
		m_device->SetRenderState(D3DRS_SPECULARENABLE, true);
		m_device->SetRenderState(D3DRS_AMBIENT, 0x00808080);
	}

	void Light::Update()
	{
		m_light.Position = m_parameter.position;
	}

	void Light::UpdateMatrix()
	{
		switch (GetMatrixType())
		{
		case MatrixType::Default:
			CreateWorldMatrix();
			break;
		case MatrixType::World:
			CreateWorldMatrix();
			break;
		case MatrixType::Local:
			CreateLocalMatrix();
			break;
		default:
			CreateWorldMatrix();
			break;
		}
	}
	void Light::GUISystem()
	{
		GUIGameObject();
		GUITransform();
	}
	void Light::InputDataFunction(std::ifstream& _ifstream)
	{
		InputDataTransform(_ifstream);
	}
	void Light::OutputDataFunction(std::ofstream& _ofstream)
	{
		OutputDataTransform(_ofstream);
	}
	void Light::CreateLabel()
	{
		for (m_label = 0;; m_label++)
		{
			auto itr = std::find(m_lights.begin(), m_lights.end(), m_label);
			// ���݂���ꍇ
			if (itr != m_lights.end())
				continue;
			// ���݂��Ȃ����
			m_lights.push_back(m_label);
			return;
		}
	}
}
_MSLIB_END
