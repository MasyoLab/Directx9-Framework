//==========================================================================
// ゲームオブジェクト [GameObject.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include "mslib.hpp"
#include "Activity.h"
#include "Manager.h"
#include "Initializer.h"
#include "Component.h"
#include "Reference.h"
#include "GUI.h"
#include "Material.h"

_MSLIB_BEGIN

namespace object
{
	/**
	@brief 使うマトリクスの種類
	*/
	enum class MatrixType
	{
		/// <summary>
		/// 描画機能でおすすめの行列が使用されます
		/// </summary>
		Default = 0,
		/// <summary>
		/// ワールド行列を生成します
		/// </summary>
		World,
		/// <summary>
		/// ローカル行列を生成します
		/// </summary>
		Local,
		/// <summary>
		/// ワールド行列を生成します
		/// </summary>
		WorldView,
		/// <summary>
		/// ローカル行列を生成します
		/// </summary>
		LocalView,
	};

	using material::MaterialLighting;

	//==========================================================================
	//
	// class : GameObject
	// Content : ゲームオブジェクト
	//
	//==========================================================================
	class GameObject :
		virtual public component::Component,
		virtual public activity::Activity,
		public gui::GUI,
		public manager::Manager,
		public initializer::Initializer
	{
	private:
		GameObject(const GameObject&) = delete;
		GameObject(GameObject&&) = delete;
		GameObject& operator=(const GameObject&) = delete;
		GameObject& operator=(GameObject&&) = delete;
	public:
		GameObject();
		virtual ~GameObject();

		/**
		@brief 更新リストを一気に更新
		*/
		static void UpdateAll();
	protected:
		/**
		@brief 初期化
		*/
		virtual void Init() override;

		/**
		@brief 更新
		*/
		virtual void Update();

		/**
		@brief 姿勢行列の更新
		*/
		virtual void UpdateMatrix();

		/**
		@brief GUIに表示する機能
		*/
		virtual void GUISystem() override;

		void GUIGameObject();
	public:
		/**
		@brief 使うマトリクスの種類
		@param type [in] マトリクスのタイプ
		*/
		void SetMatrixType(MatrixType _type);

		/**
		@brief 使用中のマトリクスの種類
		@return マトリクスの種類
		*/
		MatrixType GetMatrixType() const;
	private:
		MatrixType m_mat_type; // マトリクスのタイプ
		static std::list<GameObject*> m_objects; // 更新対象
	};

	using GameObjectReference = reference::IReference<GameObject>;
}

_MSLIB_END