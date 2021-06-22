//==========================================================================
// �Q�[���I�u�W�F�N�g [GameObject.h]
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
	@brief �g���}�g���N�X�̎��
	*/
	enum class MatrixType
	{
		/// <summary>
		/// �`��@�\�ł������߂̍s�񂪎g�p����܂�
		/// </summary>
		Default = 0,
		/// <summary>
		/// ���[���h�s��𐶐����܂�
		/// </summary>
		World,
		/// <summary>
		/// ���[�J���s��𐶐����܂�
		/// </summary>
		Local,
		/// <summary>
		/// ���[���h�s��𐶐����܂�
		/// </summary>
		WorldView,
		/// <summary>
		/// ���[�J���s��𐶐����܂�
		/// </summary>
		LocalView,
	};

	using material::MaterialLighting;

	//==========================================================================
	//
	// class : GameObject
	// Content : �Q�[���I�u�W�F�N�g
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
		@brief �X�V���X�g����C�ɍX�V
		*/
		static void UpdateAll();
	protected:
		/**
		@brief ������
		*/
		virtual void Init() override;

		/**
		@brief �X�V
		*/
		virtual void Update();

		/**
		@brief �p���s��̍X�V
		*/
		virtual void UpdateMatrix();

		/**
		@brief GUI�ɕ\������@�\
		*/
		virtual void GUISystem() override;

		void GUIGameObject();
	public:
		/**
		@brief �g���}�g���N�X�̎��
		@param type [in] �}�g���N�X�̃^�C�v
		*/
		void SetMatrixType(MatrixType _type);

		/**
		@brief �g�p���̃}�g���N�X�̎��
		@return �}�g���N�X�̎��
		*/
		MatrixType GetMatrixType() const;
	private:
		MatrixType m_mat_type; // �}�g���N�X�̃^�C�v
		static std::list<GameObject*> m_objects; // �X�V�Ώ�
	};

	using GameObjectReference = reference::IReference<GameObject>;
}

_MSLIB_END