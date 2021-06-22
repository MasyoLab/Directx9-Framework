//==========================================================================
// �J���� [Camera.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "mslib.hpp"
#include "Manager.h"
#include "Component.h"
#include "Transform.h"
#include "Texture.h"
#include "Sprite.h"

_MSLIB_BEGIN

namespace camera
{
	//==========================================================================
	//
	// class : Camera
	// Content : �J����
	//
	//==========================================================================
	class Camera :
		public component::Component,
		public manager::Manager
	{
	private:
		Camera(const Camera&) = delete;
		Camera(Camera&&) = delete;
		Camera& operator=(const Camera&) = delete;
		Camera& operator=(Camera&&) = delete;
	public:
		Camera();
		virtual ~Camera();

		/**
		@brief ������
		*/
		void Init();

		/**
		@brief ������
		@param eye [in] �����_
		@param at [in] ���W
		*/
		void Init(const D3DXVECTOR3& eye, const D3DXVECTOR3& at);

		/**
		@brief �J�������ʂ��S�Ă̕����e�N�X�`���ɔ��f���܂�
		*/
		static void Rendering(LPDIRECT3DDEVICE9 device);

		/**
		@brief �J������GUI
		*/
		static void GUICamera();

		/**
		@brief ���݃��C���Ŏg�p����Ă���J�����̃|�C���^���擾���܂�
		@return �J�����|�C���^
		*/
		static reference::IReference<Camera> GetCamera();

		/**
		@brief �r���[�s��̎擾
		@return �r���[�s��
		*/
		D3DXMATRIX* GetViewMatrix();

		/**
		@brief �v���W�F�N�V�����s��̎擾
		@return �v���W�F�N�V�����s��
		*/
		D3DXMATRIX* GetProjectionMatrix();

		/**
		@brief �v���W�F�N�V�����s��̐���
		@return �v���W�F�N�V�����s��
		*/
		D3DXMATRIX* CreateProjectionMatrix();

		void AddViewRotation(const D3DXVECTOR3& axis);

		void AddCameraRotation(const D3DXVECTOR3& axis);

		void AddViewRotation(float x, float y, float z);

		void AddCameraRotation(float x, float y, float z);

		void AddViewRotationY(float y);

		void AddCameraRotationY(float y);

		void AddViewRotationY(float y, float limit);

		void AddCameraRotationY(float y, float limit);

		void AddPosition(const D3DXVECTOR3& position);

		void AddPosition(float x, float y, float z);

		/**
		@brief ���_�ύX
		@param _distance [in] ���ꂽ�l�����Z����܂�
		@return ���_�ƃJ�����̋���
		*/
		float DistanceFromView(float distance);

		/**
		@brief �J����Y����]���
		@return ����
		*/
		float GetRestrictionY();

		/**
		@brief �J����X����]���
		@return ����
		*/
		float GetRestrictionX();

		/**
		@brief �J����Z����]���
		@return ����
		*/
		float GetRestrictionZ();

		/**
		@brief �J�������W���Z�b�g
		@param Eye [in] �����_
		@param At [in] �J�������W
		@param Up [in] �x�N�^�[
		*/
		void SetCameraPos(const D3DXVECTOR3& eye, const D3DXVECTOR3& at, const D3DXVECTOR3& up);

		/**
		@brief �J�������W
		@param At [in] �J�������W
		*/
		void SetAt(const D3DXVECTOR3& at);

		/**
		@brief �����_
		@param Eye [in] �����_
		*/
		void SetEye(const D3DXVECTOR3& eye);

		const transform::Look& GetLook1() const;
		const transform::Look& GetLook2() const;
		const transform::Vector& GetVector() const;

		/**
		@brief ���C���J�����ɂ��܂�
		*/
		void IsMainCamera();

		/**
		@brief �J�������ʂ����e�N�X�`�����擾���܂�
		@return TextureReference
		*/
		texture::TextureReference GetImage();

		/**
		@brief �t�@�[�N���b�v�̎擾
		@return �t�@�[�N���b�v
		*/
		float GetFarClip();

		/**
		@brief �t�@�[�N���b�v�̓o�^
		*/
		void SetFarClip(float farClip);

		/**
		@brief �j�A�N���b�v�̎擾
		@return �j�A�N���b�v
		*/
		float GetNearClip();

		/**
		@brief �j�A�N���b�v�̓o�^
		*/
		void SetNearClip(float nearClip);
	private:
		/**
		@brief �r���[�s�񐶐�
		@return �r���[�s��
		*/
		D3DXMATRIX* CreateView();

		/**
		@brief ���_�ύX
		@param vec [in] �x�N�g��
		@param out1 [out] �o��1
		@param out2 [out] �o��2
		@param speed [in] �ړ����x
		@return �߂�l�� ����
		*/
		float ViewPos(D3DXVECTOR3& vec, D3DXVECTOR3& out1, const D3DXVECTOR3& out2, float speed);

		/**
		@brief ����
		@param axis [in] ��]���
		@param limit [in] ��]���x
		@return �ړ��\�͈͂Ȃ� true
		*/
		bool Restriction(float axis, float limit);

		void GUICameraWindow();
	private:
		texture::TextureReference m_blur_texture; // ���
		object::SpriteReference m_screen_renderer; // ��ʕ`��@�\
		LPDIRECT3DSURFACE9 m_surface; // �e�N�X�`��1
		D3DXMATRIX m_projection; // �v���W�F�N�V�����s��
		D3DXMATRIX m_view; // �r���[�s��
		transform::Look m_look1; // �����x�N�g��
		transform::Look m_look2; // �����x�N�g��
		transform::Vector m_vector; // �����x�N�g��
		D3DXVECTOR2 m_win_size; // �E�B���h�E�T�C�Y
		float m_far_clip; // �t�@�[�N���b�v���s������
		float m_near_clip; // �j�A�N���b�v���s������
		reference::IReference<Camera> m_this;
		static std::list<Camera*> m_cameras; // �S�ẴJ����
		static reference::IReference<Camera> m_main_camera; // ���C���̃J����
#if defined(_MSLIB_DEBUG)
		bool m_flag_window;
#endif	
	};

	using CameraReference = reference::IReference<Camera>;
}
//namespace camera_develop
//{
//    class Camera : public component::Component
//    {
//    public:
//        Camera();
//        ~Camera();
//        transform::Transform & CameraPosition();
//        transform::Transform & ViewingPosition();
//        static void UpdateAll(const int2 & win_size, LPDIRECT3DDEVICE9 device);
//        void IsMainCamera();
//        D3DXMATRIX * GetViewMatrix();
//        D3DXMATRIX * GetProjectionMatrix();
//        void LockOn(transform::Transform * obj);
//    protected:
//        D3DXMATRIX * CreateView();
//    protected:
//        D3DXMATRIX m_ProjectionMatrix; // �v���W�F�N�V�����s��
//        D3DXMATRIX m_ViewMatrix; // �r���[�s��
//		component::IReference<transform::Transform> m_target; // �Ǐ]�Ώ�
//		component::IReference<transform::Transform> m_CameraPosition; // �J����
//		component::IReference<transform::Transform> m_ViewingPosition; // �\������
//        static std::list<Camera*> m_AllCamera; // �S�J����
//        static Camera * m_MainCamera; // ���C���̃J����
//    };
//}
_MSLIB_END