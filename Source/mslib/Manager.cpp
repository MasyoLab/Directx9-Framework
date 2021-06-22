//==========================================================================
// マネージャー [Manager.cpp]
// author : MasyoLab
//==========================================================================
#include "Manager.h"
#include "mslib_afx.h"

_MSLIB_BEGIN

namespace manager
{
	component::ComponentReference Manager::m_manager_component; // デバイス
	device::DeviceReference Manager::m_manager_device; // デバイス
	std::unordered_map<size_t, component::ComponentReference> Manager::m_manager_component_list; // コンポーネント

	template <typename _Ty1, typename _Ty2>
	reference::IReference<_Ty1> AddComponent(_Ty1* _ptr, reference::IReference<_Ty2>& _ref, std::unordered_map<size_t, component::ComponentReference>& management);
	template<typename _Ty1, typename _Ty2>
	reference::IReference<_Ty1> AddComponent(_Ty1* _ptr, reference::IReference<_Ty2>& _ref, std::unordered_map<size_t, component::ComponentReference>& management)
	{
		auto ref_new = management[typeid(_Ty1).hash_code()] = _ref->AddComponent(_ptr)->ThisComponent();
		return ref_new->ThisComponent<_Ty1>();
	}

	Manager::Manager()
	{
	}

	Manager::~Manager()
	{
	}

	void Manager::SetManagerComponent(const component::ComponentReference& _ipa)
	{
		if (m_manager_component == nullptr)
			m_manager_component = _ipa;
	}

	texture::TextureLoaderReference Manager::GetTextureLoader()
	{
		auto itr = m_manager_component_list.find(typeid(texture::TextureLoader).hash_code());
		if (itr == m_manager_component_list.end())
		{
			auto device = m_manager_device->Getd3ddevice();
			auto hwnd = m_manager_device->GetHwnd();
			return AddComponent(new texture::TextureLoader(device, hwnd), m_manager_device, m_manager_component_list);
		}
		return itr->second->ThisComponent<texture::TextureLoader>();
	}

	xmodel::XModelLoaderReference Manager::GetXModelLoader()
	{
		auto itr = m_manager_component_list.find(typeid(xmodel::XModelLoader).hash_code());
		if (itr == m_manager_component_list.end())
		{
			auto device = m_manager_device->Getd3ddevice();
			auto hwnd = m_manager_device->GetHwnd();
			return AddComponent(new xmodel::XModelLoader(device, hwnd, GetTextureLoader()), m_manager_device, m_manager_component_list);
		}
		return itr->second->ThisComponent<xmodel::XModelLoader>();
	}

	cube::CreateCubeReference Manager::GetCreateCube()
	{
		auto itr = m_manager_component_list.find(typeid(cube::CreateCube).hash_code());
		if (itr == m_manager_component_list.end())
		{
			auto device = m_manager_device->Getd3ddevice();
			auto hwnd = m_manager_device->GetHwnd();
			return AddComponent(new cube::CreateCube(device, hwnd), m_manager_device, m_manager_component_list);
		}
		return itr->second->ThisComponent<cube::CreateCube>();
	}

	sphere::CreateSphereReference Manager::GetCreateSphere()
	{
		auto itr = m_manager_component_list.find(typeid(sphere::CreateSphere).hash_code());
		if (itr == m_manager_component_list.end())
		{
			auto device = m_manager_device->Getd3ddevice();
			auto hwnd = m_manager_device->GetHwnd();
			return AddComponent(new sphere::CreateSphere(device, hwnd), m_manager_device, m_manager_component_list);
		}
		return itr->second->ThisComponent<sphere::CreateSphere>();
	}

	billboard::CreateBillboardReference Manager::GetCreateBillboard()
	{
		auto itr = m_manager_component_list.find(typeid(billboard::CreateBillboard).hash_code());
		if (itr == m_manager_component_list.end())
		{
			auto device = m_manager_device->Getd3ddevice();
			auto hwnd = m_manager_device->GetHwnd();
			return AddComponent(new billboard::CreateBillboard(device, hwnd), m_manager_device, m_manager_component_list);
		}
		return itr->second->ThisComponent<billboard::CreateBillboard>();
	}

	mesh::CreateMeshReference Manager::GetCreateMesh()
	{
		auto itr = m_manager_component_list.find(typeid(mesh::CreateMesh).hash_code());
		if (itr == m_manager_component_list.end())
		{
			auto device = m_manager_device->Getd3ddevice();
			auto hwnd = m_manager_device->GetHwnd();
			return AddComponent(new mesh::CreateMesh(device, hwnd), m_manager_device, m_manager_component_list);
		}
		return itr->second->ThisComponent<mesh::CreateMesh>();
	}

	effect::EffectLoaderReference Manager::GetEffectLoader()
	{
		auto itr = m_manager_component_list.find(typeid(effect::EffectLoader).hash_code());
		if (itr == m_manager_component_list.end())
			return AddComponent(new effect::EffectLoader(m_manager_device->Getd3ddevice()), m_manager_device, m_manager_component_list);
		return itr->second->ThisComponent<effect::EffectLoader>();
	}

	device::DeviceReference Manager::GetDevice()
	{
		if (m_manager_component != nullptr && m_manager_device == nullptr)
			return m_manager_device = m_manager_component->AddComponent(new device::Device);
		return m_manager_device;
	}

	dinput_controller::ControllerReference Manager::GetDInputController()
	{
		auto itr = m_manager_component_list.find(typeid(dinput_controller::Controller).hash_code());
		if (itr == m_manager_component_list.end())
			return AddComponent(new dinput_controller::Controller, m_manager_device, m_manager_component_list);
		return itr->second->ThisComponent<dinput_controller::Controller>();
	}

	dinput_keyboard::KeyboardReference Manager::GetDInputKeyboard()
	{
		auto itr = m_manager_component_list.find(typeid(dinput_keyboard::Keyboard).hash_code());
		if (itr == m_manager_component_list.end())
			return AddComponent(new dinput_keyboard::Keyboard, m_manager_device, m_manager_component_list);
		return itr->second->ThisComponent<dinput_keyboard::Keyboard>();
	}

	dinput_mouse::MouseReference Manager::GetDInputMouse()
	{
		auto itr = m_manager_component_list.find(typeid(dinput_mouse::Mouse).hash_code());
		if (itr == m_manager_component_list.end())
			return AddComponent(new dinput_mouse::Mouse, m_manager_device, m_manager_component_list);
		return itr->second->ThisComponent<dinput_mouse::Mouse>();
	}

	audio::AudioLoaderReference Manager::GetAudioLoader()
	{
		auto itr = m_manager_component_list.find(typeid(audio::AudioLoader).hash_code());
		if (itr == m_manager_component_list.end())
			return AddComponent(new audio::AudioLoader, m_manager_device, m_manager_component_list);
		return itr->second->ThisComponent<audio::AudioLoader>();
	}

	effekseer_dx::CreateEffekseerLoaderReference Manager::GetCreateEffekseerLoader()
	{
		auto itr = m_manager_component_list.find(typeid(effekseer_dx::CreateEffekseerLoader).hash_code());
		if (itr == m_manager_component_list.end())
			return AddComponent(new effekseer_dx::CreateEffekseerLoader(m_manager_device->Getd3ddevice()), m_manager_device, m_manager_component_list);
		return itr->second->ThisComponent<effekseer_dx::CreateEffekseerLoader>();
	}

	scene_manager::SceneManagerReference Manager::GetSceneManager()
	{
		auto itr = m_manager_component_list.find(typeid(scene_manager::SceneManager).hash_code());
		if (itr == m_manager_component_list.end())
			return AddComponent(new scene_manager::SceneManager, m_manager_device, m_manager_component_list);
		return itr->second->ThisComponent<scene_manager::SceneManager>();
	}

	void Manager::UpdateManager()
	{
#if defined(_MSLIB_DEBUG)
		imgui::Text("System GUI");
		imgui::Separator();
#endif	
		camera::Camera::GUICamera();
		texture::TextureData::GUITextureList();
		audio::AudioData::GUIAudioList();
#if defined(_MSLIB_DEBUG)
		imgui::Separator();
		imgui::Text("User GUI");
		imgui::Separator();
#endif	
		gui::GUI::GUIUpdateAll();
		direct_input::DirectInput::UpdateAll();
		initializer::Initializer::InitAll();
		//function::FunctionComponent::UpdateAll();
		object::GameObject::UpdateAll();
		effekseer_dx::EffekseerLoader::UpdateAll();
		collider::Collider::UpdateAll();
	}

	bool Manager::DrawManager()
	{
		auto device = m_manager_device->Getd3ddevice();
		camera::Camera::Rendering(device);
		auto flag = m_manager_device->DrawBegin();
		if (flag)
			object::Sprite::DrawAll(device);
		return flag;
	}

	void Manager::ReleaseManager()
	{
		m_manager_device = nullptr;
		m_manager_component = nullptr;
		m_manager_component_list.clear();
		object::Sprite::DeleteRenderer();
	}
}

_MSLIB_END