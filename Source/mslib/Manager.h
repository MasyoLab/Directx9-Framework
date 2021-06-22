//==========================================================================
// マネージャー [Manager.h]
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
		@brief 親コンポーネントを設定する
		@param pComponent [in] 親となるコンポーネント
		*/
		static void SetManagerComponent(const component::ComponentReference& _ipa);

		/**
		@brief テクスチャ読込クラスを取得する。
		*/
		static texture::TextureLoaderReference GetTextureLoader();

		/**
		@brief Xモデル読込クラスを取得する。
		*/
		static xmodel::XModelLoaderReference GetXModelLoader();

		/**
		@brief キューブの生成クラスを取得する。
		*/
		static cube::CreateCubeReference GetCreateCube();

		/**
		@brief 球体の生成クラスを取得する。
		*/
		static sphere::CreateSphereReference GetCreateSphere();

		/**
		@brief ビルボードの生成クラスを取得する。
		*/
		static billboard::CreateBillboardReference GetCreateBillboard();

		/**
		@brief メッシュの生成クラスを取得する。
		*/
		static mesh::CreateMeshReference GetCreateMesh();

		/**
		@brief エフェクト読み込みクラスを取得する。
		*/
		static effect::EffectLoaderReference GetEffectLoader();

		/**
		@brief デバイスを取得する。
		*/
		static device::DeviceReference GetDevice();

		/**
		@brief DirectInputコントローラーを取得する。
		*/
		static dinput_controller::ControllerReference GetDInputController();

		/**
		@brief DirectInputキーボードを取得する。
		*/
		static dinput_keyboard::KeyboardReference GetDInputKeyboard();

		/**
		@brief DirectInputマウスを取得する。
		*/
		static dinput_mouse::MouseReference GetDInputMouse();

		/**
		@brief XAudio2Deviceを取得する。
		*/
		static audio::AudioLoaderReference GetAudioLoader();

		/**
		@brief エフェクシア読み込み機能を取得する
		*/
		static effekseer_dx::CreateEffekseerLoaderReference GetCreateEffekseerLoader();

		/**
		@brief シーンマネージャーを取得する
		*/
		static scene_manager::SceneManagerReference GetSceneManager();

		/**
		@brief マネージャーの更新
		*/
		static void UpdateManager();

		/**
		@brief マネージャーでの一括描画
		*/
		static bool DrawManager();

		/**
		@brief マネージャーデータの破棄
		*/
		static void ReleaseManager();
	public:
		using KeyboardButton = dinput_keyboard::Button;
		using ControllerPS4Button = dinput_controller::PS4Button;
		using ControllerCrossKey = dinput_controller::CrossKey;
		using MouseButton = dinput_mouse::Button;
	private:
		static component::ComponentReference m_manager_component; // デバイス
		static device::DeviceReference m_manager_device; // デバイス
		static std::unordered_map<size_t, component::ComponentReference> m_manager_component_list; // コンポーネント
	};
}

_MSLIB_END