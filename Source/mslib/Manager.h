//==========================================================================
// �}�l�[�W���[ [Manager.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "mslib.hpp"
#include "Component.h"
#include "Device.h"
#include "Texture.h"
#include "XModel.h"
#include "Cube.h"
#include "Sphere.h"
#include "Billboard.h"
#include "Mesh.h"
//#include "MeshField.h"
#include "Effect.h"
#include "DinputController.h"
#include "DinputKeyboard.h"
#include "DinputMouse.h"
#include "Audio.h"
#include "EffekseerDX.h"
#include "SceneManager.h"

_MSLIB_BEGIN

namespace manager
{
	class Manager
	{
	private:
		Manager(const Manager&) = delete;
		Manager(Manager&&) = delete;
		Manager& operator=(const Manager&) = delete;
		Manager& operator=(Manager&&) = delete;
	public:
		Manager();
		~Manager();

		/**
		@brief �e�R���|�[�l���g��ݒ肷��
		@param pComponent [in] �e�ƂȂ�R���|�[�l���g
		*/
		static void SetManagerComponent(const component::ComponentReference& _ipa);

		/**
		@brief �e�N�X�`���Ǎ��N���X���擾����B
		*/
		static texture::TextureLoaderReference GetTextureLoader();

		/**
		@brief X���f���Ǎ��N���X���擾����B
		*/
		static xmodel::XModelLoaderReference GetXModelLoader();

		/**
		@brief �L���[�u�̐����N���X���擾����B
		*/
		static cube::CreateCubeReference GetCreateCube();

		/**
		@brief ���̂̐����N���X���擾����B
		*/
		static sphere::CreateSphereReference GetCreateSphere();

		/**
		@brief �r���{�[�h�̐����N���X���擾����B
		*/
		static billboard::CreateBillboardReference GetCreateBillboard();

		/**
		@brief ���b�V���̐����N���X���擾����B
		*/
		static mesh::CreateMeshReference GetCreateMesh();

		/**
		@brief �G�t�F�N�g�ǂݍ��݃N���X���擾����B
		*/
		static effect::EffectLoaderReference GetEffectLoader();

		/**
		@brief �f�o�C�X���擾����B
		*/
		static device::DeviceReference GetDevice();

		/**
		@brief DirectInput�R���g���[���[���擾����B
		*/
		static dinput_controller::ControllerReference GetDInputController();

		/**
		@brief DirectInput�L�[�{�[�h���擾����B
		*/
		static dinput_keyboard::KeyboardReference GetDInputKeyboard();

		/**
		@brief DirectInput�}�E�X���擾����B
		*/
		static dinput_mouse::MouseReference GetDInputMouse();

		/**
		@brief XAudio2Device���擾����B
		*/
		static audio::AudioLoaderReference GetAudioLoader();

		/**
		@brief �G�t�F�N�V�A�ǂݍ��݋@�\���擾����
		*/
		static effekseer_dx::CreateEffekseerLoaderReference GetCreateEffekseerLoader();

		/**
		@brief �V�[���}�l�[�W���[���擾����
		*/
		static scene_manager::SceneManagerReference GetSceneManager();

		/**
		@brief �}�l�[�W���[�̍X�V
		*/
		static void UpdateManager();

		/**
		@brief �}�l�[�W���[�ł̈ꊇ�`��
		*/
		static bool DrawManager();

		/**
		@brief �}�l�[�W���[�f�[�^�̔j��
		*/
		static void ReleaseManager();
	public:
		using KeyboardButton = dinput_keyboard::Button;
		using ControllerPS4Button = dinput_controller::PS4Button;
		using ControllerCrossKey = dinput_controller::CrossKey;
		using MouseButton = dinput_mouse::Button;
	private:
		static component::ComponentReference m_manager_component; // �f�o�C�X
		static device::DeviceReference m_manager_device; // �f�o�C�X
		static std::unordered_map<size_t, component::ComponentReference> m_manager_component_list; // �R���|�[�l���g
	};
}

_MSLIB_END