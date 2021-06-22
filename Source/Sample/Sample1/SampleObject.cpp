#include "SampleObject.h"
#include "resource_list.h"

namespace sample1
{
	SampleObject::SampleObject()
	{
		SetComponentName("SampleObject");

		m_sprite = AddComponent(new mslib::object::Sprite(true));
		m_sprite->SetPosition(GetDevice()->GetDefaultWindowsSize().x - (m_sprite->GetPolygonSize().x * 2), m_sprite->GetPolygonSize().y);
		m_sprite->SetComponentName("SampleSpriteObject");
		auto sprite = m_sprite->AddComponent(new mslib::object::Sprite(true));
		sprite->SetPosition(0, m_sprite->GetPolygonSize().y + (m_sprite->GetPolygonSize().y * 0.25f));
		sprite->SetRotation(0, 0, mslib::ToRadian(45.0f));
		sprite->SetComponentName("SampleSpriteChildObject");

		auto light = AddComponent(new mslib::object::Light(GetDevice()->Getd3ddevice(), true));
		light->Init();
		light->AddPosition(0, 5, 0);
		light->AddComponent(new mslib::debug::Debug3D)->SetActivity(true);
		light->SetComponentName("SampleLightObject");

		auto mesh = AddComponent(new mslib::object::MeshObject(true));
		mesh->SetMeshData(GetCreateMesh()->Create(5, 5));
		mesh->AddComponent(new mslib::debug::Debug3D)->SetActivity(true);
		mesh->SetComponentName("SampleMeshObject");

		auto xmodel = AddComponent(new mslib::object::XModelObject(true));
		xmodel->SetXModelData(GetXModelLoader()->Load(RESOURCE_Box_x));
		xmodel->AddPosition(-3, 2, 0);
		xmodel->AddComponent(new mslib::debug::Debug3D)->SetActivity(true);
		xmodel->SetComponentName("SampleXModelObject");

		auto sphere = AddComponent(new mslib::object::SphereObject(true));
		sphere->SetSphereData(GetCreateSphere()->Create(20));
		sphere->AddPosition(0, 2, 0);
		sphere->AddComponent(new mslib::debug::Debug3D)->SetActivity(true);
		sphere->SetComponentName("SampleSphereObject");

		auto cube = AddComponent(new mslib::object::CubeObject(true));
		cube->SetCubeData(GetCreateCube()->Create());
		cube->AddPosition(3, 2, 0);
		cube->AddComponent(new mslib::debug::Debug3D)->SetActivity(true);
		cube->SetComponentName("SampleCubeObject");

		auto billboard = AddComponent(new mslib::object::BillboardObject(true));
		billboard->SetBillboardData(GetCreateBillboard()->Create());
		billboard->AddPosition(-5, 2, 0);
		billboard->AddComponent(new mslib::debug::Debug3D)->SetActivity(true);
		billboard->SetComponentName("SampleBillboardObject");

		auto effekseer_loader = GetCreateEffekseerLoader()->Create("SampleObject‚ÌEffekseerLoader");
		effekseer_loader->InitManager(200, 1000);

		auto effeks = AddComponent(new mslib::object::EffekseerObject(true));
		effeks->SetEffekseerData(effekseer_loader->Load((const EFK_CHAR*)L"resource/Effekseer/GoldenEffect.efk", "GoldenEffect"));
		effeks->AddPosition(5, 2, 0);
		effeks->AddComponent(new mslib::debug::Debug3D)->SetActivity(true);
		effeks->Play();
		effeks->SetComponentName("SampleEffekseerObject");

		m_audio = GetAudioLoader()->Load(RESOURCE_st001_wav);
	}

	SampleObject::~SampleObject()
	{
	}

	void SampleObject::Init()
	{
	}

	void SampleObject::Update()
	{
		m_sprite->AddRotation(0.01f, 0.01f, 0.01f);
	}

	void SampleObject::UpdateMatrix()
	{
	}
	void SampleObject::GUISystem()
	{
		GUIGameObject();
		if (m_audio.check())
			m_audio->GUIAudio();
	}
}