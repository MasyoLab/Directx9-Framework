//==========================================================================
// �J���� [Camera.cpp]
// author : MasyoLab
//==========================================================================
#include "Camera.h"
#include "Renderer.h"
#include "MsImGui.h"
#include "string_encode.hpp"

_MSLIB_BEGIN

namespace camera
{
	std::list<Camera*> Camera::m_cameras; // �S�ẴJ����
	reference::IReference<Camera> Camera::m_main_camera; // ���C���̃J����

	Camera::Camera() :
		Component("Camera"), m_surface(nullptr), m_far_clip(1000), m_near_clip(1)
	{
		// ������
		D3DXMatrixIdentity(&m_view);
		D3DXMatrixIdentity(&m_projection);
		m_vector.Identity();
		m_vector.Normalize();

		m_win_size = GetDevice()->GetWindowsSize();
		m_this = ThisComponent<Camera>();

		// �J�����f���o�͗p�̃e�N�X�`��
		m_blur_texture = GetTextureLoader()->CreateTexture((int)m_win_size.x, (int)m_win_size.y, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R8G8B8, D3DPOOL_DEFAULT);
		m_blur_texture->GetTexture()->GetSurfaceLevel(0, &m_surface);

		// �X�v���C�g�𐶐�
		m_screen_renderer = AddComponent(new object::Sprite);
		m_screen_renderer->SetTextureData(m_blur_texture);
		m_screen_renderer->SetPriority(-9999999.f);
		m_screen_renderer->AddPosition(-0.5f, -0.5f, 0);
		m_screen_renderer->SetDefaultWindowSizeModel(false);
		m_screen_renderer->SetActivity(false);

		// �f�t�H���g�Ƃ��āA�j�A�N���b�v�ƃt�@�[�N���b�v��ݒ�
		CreateProjectionMatrix();

		// ���C���̃J�����Ƃ��Đݒ�
		if (!m_main_camera.check())
			IsMainCamera();

		Init();
		m_cameras.push_back(this);
#if defined(_MSLIB_DEBUG)
		m_flag_window = false;
#endif
	}

	Camera::~Camera()
	{
		auto itr = std::find(m_cameras.begin(), m_cameras.end(), this);
		if (itr != m_cameras.end())
			m_cameras.erase(itr);

		if (m_main_camera == m_this)
			m_main_camera.clear();

		if (m_main_camera == nullptr)
		{
			auto itr = m_cameras.begin();
			if (itr != m_cameras.end())
				(*itr)->IsMainCamera();
		}

		if (m_blur_texture.check())
			m_blur_texture->GetLoader()->Unload(m_blur_texture);

		if (m_surface != nullptr)
			m_surface->Release();
		m_surface = nullptr;
	}

	void Camera::Init()
	{
		m_look1(D3DXVECTOR3(0.0f, 3.0f, -10.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		m_look2(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}

	void Camera::Init(const D3DXVECTOR3& eye, const D3DXVECTOR3& at)
	{
		m_look1(eye, at, D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		m_look2(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}

	void Camera::Rendering(LPDIRECT3DDEVICE9 device)
	{
		LPDIRECT3DSURFACE9 buffer = nullptr;
		auto pdevice = manager::Manager::GetDevice();

		// ���C���̃����_�[�^�[�Q�b�g��ۑ�
		device->GetRenderTarget(0, &buffer);

		// �J�����̐�������
		for (auto& itr : m_cameras)
		{
				// �����_�[�^�[�Q�b�g���w��
			device->SetRenderTarget(0, itr->m_surface);

			if (pdevice->DrawBegin())
			{
				// �v���W�F�N�V�����s��̍쐬
				// �Y�[���C���A�Y�[���A�E�g�̂悤�ȕ�
				device->SetTransform(D3DTS_VIEW, itr->CreateView());
				device->SetTransform(D3DTS_PROJECTION, &itr->m_projection);
				renderer::Renderer::DrawAll(device);
				device->EndScene();
			}
		}
		device->SetRenderTarget(0, buffer);
	}

	void Camera::GUICamera()
	{
#if defined(_MSLIB_DEBUG)
		if (imgui::NewTreeNode("Camera GUI", false))
		{
			for (auto& itr : m_cameras)
				itr->GUICameraWindow();
			imgui::EndTreeNode();
		}
#endif	
	}

	reference::IReference<Camera> Camera::GetCamera()
	{
		return m_main_camera;
	}

	D3DXMATRIX* Camera::CreateView()
	{
		auto look = m_look1 + m_look2;
		look.up = m_look1.up;

		// �r���[�ϊ��s�� ,(LH = ������W ,LR = �E����W)
		return D3DXMatrixLookAtLH(&m_view, &look.eye, &look.at, &look.up);
	}

	D3DXMATRIX* Camera::GetViewMatrix()
	{
		return &m_view;
	}

	D3DXMATRIX* Camera::GetProjectionMatrix()
	{
		return &m_projection;
	}

	D3DXMATRIX* Camera::CreateProjectionMatrix()
	{
		return D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(60), m_win_size.x / m_win_size.y, m_near_clip, m_far_clip);
	}

	void Camera::AddViewRotation(const D3DXVECTOR3& axis)
	{
		D3DXMATRIX Matrix, AddMatrix; //��]�s��
		D3DXVECTOR3 Direction;

		// �O�ς����߂܂�
		m_vector.CrossRight();

		// �}�g���N�X�̏�����
		D3DXMatrixIdentity(&Matrix);

		// ����������]�}�g���N�X���������Ă����܂�
		D3DXMatrixMultiply(&Matrix, D3DXMatrixRotationY(&AddMatrix, axis.x), &Matrix);
		D3DXMatrixMultiply(&Matrix, D3DXMatrixRotationAxis(&AddMatrix, &m_vector.right, axis.y), &Matrix);
		D3DXMatrixMultiply(&Matrix, D3DXMatrixRotationAxis(&AddMatrix, &m_vector.front, axis.z), &Matrix);

		// �����x�N�g���ɍ������܂�
		m_vector.TransformNormal(Matrix);

		Direction = m_look1.eye - m_look1.at;
		D3DXVec3TransformNormal(&Direction, &Direction, &Matrix);
		m_look1.eye = m_look1.at + Direction;
		m_look1.up = m_vector.up;
	}

	void Camera::AddCameraRotation(const D3DXVECTOR3& axis)
	{
		D3DXMATRIX Matrix, AddMatrix; //��]�s��
		D3DXVECTOR3 Direction;

		// �O�ς����߂܂�
		m_vector.CrossRight();

		// �}�g���N�X�̏�����
		D3DXMatrixIdentity(&Matrix);

		// ����������]�}�g���N�X���������Ă����܂�
		D3DXMatrixMultiply(&Matrix, D3DXMatrixRotationY(&AddMatrix, axis.x), &Matrix);
		D3DXMatrixMultiply(&Matrix, D3DXMatrixRotationAxis(&AddMatrix, &m_vector.right, axis.y), &Matrix);
		D3DXMatrixMultiply(&Matrix, D3DXMatrixRotationAxis(&AddMatrix, &m_vector.front, axis.z), &Matrix);

		// �����x�N�g���ɍ������܂�
		m_vector.TransformNormal(Matrix);

		Direction = m_look1.at - m_look1.eye;
		D3DXVec3TransformNormal(&Direction, &Direction, &Matrix);
		m_look1.at = m_look1.eye + Direction;
		m_look1.up = m_vector.up;
	}

	void Camera::AddViewRotation(float x, float y, float z)
	{
		AddViewRotation(D3DXVECTOR3(x, y, z));
	}

	void Camera::AddCameraRotation(float x, float y, float z)
	{
		AddCameraRotation(D3DXVECTOR3(x, y, z));
	}

	void Camera::AddViewRotationY(float y)
	{
		if (Restriction(y, 0.78f))
			AddViewRotation(D3DXVECTOR3(0, y, 0));
	}

	void Camera::AddCameraRotationY(float y)
	{
		if (Restriction(y, 0.78f))
			AddCameraRotation(D3DXVECTOR3(0, y, 0));
	}

	void Camera::AddViewRotationY(float y, float limit)
	{
		if (Restriction(y, limit))
			AddViewRotation(D3DXVECTOR3(0, y, 0));
	}

	void Camera::AddCameraRotationY(float y, float limit)
	{
		if (Restriction(y, limit))
			AddCameraRotation(D3DXVECTOR3(0, y, 0));
	}

	void Camera::AddPosition(const D3DXVECTOR3& position)
	{
		m_vector.Normalize();
		m_vector.VectoeMultiply(m_look1.eye, position);
		m_vector.VectoeMultiply(m_look1.at, position);
	}

	void Camera::AddPosition(float x, float y, float z)
	{
		AddPosition(D3DXVECTOR3(x, y, z));
	}

	float Camera::ViewPos(D3DXVECTOR3& vec, D3DXVECTOR3& out1, const D3DXVECTOR3& out2, float speed)
	{
		m_vector.CrossRight();
		D3DXVec3Normalize(&vec, &vec);
		out1 += vec * speed;

		return powf
		(
			out1.x - out2.x *
			out1.x - out2.x +
			out1.y - out2.y *
			out1.y - out2.y +
			out1.z - out2.z *
			out1.z - out2.z,
			0.5f
		);
	}

	bool Camera::Restriction(float axis, float limit)
	{
		D3DXMATRIX Rot;
		auto dir = D3DXVECTOR3(0, 1.0f, 0); // �P�ʃx�N�g��

		auto vector = m_vector;

		// �x�N�g���̍��W�ϊ�
		vector.CrossRight();
		D3DXMatrixRotationAxis(&Rot, &vector.right, axis); // ��]
		vector.TransformNormal(Rot);
		float fVec3Dot = atanf(D3DXVec3Dot(&vector.front, &dir));

		// ����
		return -limit<fVec3Dot && limit>fVec3Dot ? true : false;
	}

	void Camera::GUICameraWindow()
	{
#if defined(_MSLIB_DEBUG)
		auto label_str = GetComponentName() + " : " + imgui::CreateText("%p", this);
		bool bflag = (m_main_camera == m_this);

		if (imgui::Checkbox(label_str, bflag))
			IsMainCamera();
#endif	
	}

	float Camera::DistanceFromView(float distance)
	{
		auto vec = m_vector.front;

		return ViewPos(vec, m_look1.eye, m_look1.at, distance);
	}

	float Camera::GetRestrictionY()
	{
		auto dir1 = D3DXVECTOR3(0, 1.0f, 0); // �P�ʃx�N�g��
		auto dir2 = D3DXVECTOR3(0, m_vector.front.y, 0); // �P�ʃx�N�g��

		return atanf(D3DXVec3Dot(&dir2, &dir1)); // ����
	}

	float Camera::GetRestrictionX()
	{
		auto dir1 = D3DXVECTOR3(1.0f, 0, 0); // �P�ʃx�N�g��
		auto dir2 = D3DXVECTOR3(m_vector.front.x, 0, 0); // �P�ʃx�N�g��

		return atanf(D3DXVec3Dot(&dir2, &dir1)); // ����
	}

	float Camera::GetRestrictionZ()
	{
		auto dir1 = D3DXVECTOR3(0, 0, 1.0f); // �P�ʃx�N�g��
		auto dir2 = D3DXVECTOR3(0, 0, m_vector.front.z); // �P�ʃx�N�g��

		return atanf(D3DXVec3Dot(&dir2, &dir1)); // ����
	}

	void Camera::SetCameraPos(const D3DXVECTOR3& eye, const D3DXVECTOR3& at, const D3DXVECTOR3& up)
	{
		m_look1(eye, at, up);
	}

	void Camera::SetAt(const D3DXVECTOR3& at)
	{
		m_look2.at = at;
	}

	void Camera::SetEye(const D3DXVECTOR3& eye)
	{
		m_look2.eye = eye;
	}

	const transform::Look& Camera::GetLook1() const
	{
		return m_look1;
	}

	const transform::Look& Camera::GetLook2() const
	{
		return m_look2;
	}

	const transform::Vector& Camera::GetVector() const
	{
		return m_vector;
	}

	void Camera::IsMainCamera()
	{
		if (m_main_camera.check())
			m_main_camera->m_screen_renderer->SetActivity(false);
		m_main_camera = m_this;
		m_screen_renderer->SetActivity(true);
	}

	texture::TextureReference Camera::GetImage()
	{
		return m_blur_texture;
	}

	float Camera::GetFarClip()
	{
		return m_far_clip;
	}

	void Camera::SetFarClip(float farClip)
	{
		m_far_clip = farClip;
		CreateProjectionMatrix();
	}

	float Camera::GetNearClip()
	{
		return m_near_clip;
	}

	void Camera::SetNearClip(float nearClip)
	{
		m_near_clip = nearClip;
		CreateProjectionMatrix();
	}
}

//namespace camera_develop
//{
//    std::list<Camera*> Camera::m_AllCamera; // �S�J����
//    Camera * Camera::m_main_camera = nullptr; // ���C���̃J����
//
//    Camera::Camera()
//    {
//        SetComponentName("Camera");
//
//        m_CameraPosition = AddComponent<transform::Transform>();
//        m_ViewingPosition = m_CameraPosition->AddComponent<transform::Transform>();
//
//        m_CameraPosition->SetComponentName("CameraPosition");
//        m_ViewingPosition->SetComponentName("ViewingPosition");
//
//        D3DXMatrixIdentity(&m_ViewMatrix);
//        D3DXMatrixIdentity(&m_ProjectionMatrix);
//
//        m_CameraPosition->AddPosition(0.0f, 3.0f, -10.0f);
//        m_ViewingPosition->AddPosition(0.0f, 1.0f, 0.0f);
//
//        m_CameraPosition->CreateWorldMatrix();
//        m_ViewingPosition->CreateWorldMatrix();
//
//        m_target = nullptr;
//
//        m_AllCamera.push_back(this);
//    }
//    Camera::~Camera()
//    {
//        auto itr = std::find(m_AllCamera.begin(), m_AllCamera.end(), this);
//        if (itr != m_AllCamera.end())
//            m_AllCamera.erase(itr);
//
//        if (m_main_camera == this)
//            m_main_camera = nullptr;
//    }
//    transform::Transform & Camera::CameraPosition()
//    {
//        return *m_CameraPosition;
//    }
//    transform::Transform & Camera::ViewingPosition()
//    {
//        return *m_ViewingPosition;
//    }
//    void Camera::UpdateAll(const int2 & win_size, LPDIRECT3DDEVICE9 device)
//    {
//        if (m_main_camera == nullptr)return;
//
//        // �v���W�F�N�V�����s��̍쐬
//        // �Y�[���C���A�Y�[���A�E�g�̂悤�ȕ�
//        D3DXMatrixPerspectiveFovLH(&m_main_camera->m_ProjectionMatrix, D3DXToRadian(60)/*D3DX_PI/3*/, (float)win_size.x / (float)win_size.y, 0.1f/*�j��*/, 1000.0f/*�t�@�[*/);
//        device->SetTransform(D3DTS_VIEW, m_main_camera->CreateView());
//        device->SetTransform(D3DTS_PROJECTION, &m_main_camera->m_ProjectionMatrix);
//    }
//    void Camera::IsMainCamera()
//    {
//        m_main_camera = this;
//    }
//    D3DXMATRIX * Camera::GetViewMatrix()
//    {
//        return &m_ViewMatrix;
//    }
//    D3DXMATRIX * Camera::GetProjectionMatrix()
//    {
//        return &m_ProjectionMatrix;
//    }
//    void Camera::LockOn(transform::Transform * obj)
//    {
//        m_target = obj;
//    }
//    D3DXMATRIX * Camera::CreateView()
//    {
//        // �r���[�J�����̌������X�V
//        auto angle = m_CameraPosition->ToSee(*m_ViewingPosition);
//        m_ViewingPosition->GetLook()->eye = -angle;
//        m_ViewingPosition->GetVector()->front = angle;
//        m_ViewingPosition->GetVector()->Normalize();
//
//        // �J�����̌������X�V
//        m_CameraPosition->GetLook()->eye = -angle;
//        m_CameraPosition->GetVector()->front = angle;
//        m_CameraPosition->GetVector()->Normalize();
//
//        // �r���[�J�����̍X�V�t���O���L��
//        if (m_ViewingPosition->UpdateKey())
//        {
//            auto mat = m_ViewingPosition->GetWorldMatrix();
//            auto distance = collider::Distance(m_CameraPosition, m_ViewingPosition);
//
//            m_CameraPosition->SetPosition(mat->_41, mat->_42, mat->_43);
//            m_CameraPosition->AddPosition(0, 0, -distance);
//        }
//
//        // �S�s��̍X�V
//        auto mat1 = m_CameraPosition->GetWorldMatrix();
//        auto mat2 = m_ViewingPosition->GetWorldMatrix();
//        auto eye = D3DXVECTOR3(mat1->_41, mat1->_42, mat1->_43);
//        auto at = D3DXVECTOR3(mat2->_41, mat2->_42, mat2->_43);
//        auto look = m_CameraPosition->GetLook();
//
//        if (m_target != nullptr)
//        {
//            eye = eye + *m_target->GetPosition();
//        }
//
//        // �X�V�̃��b�N
//        m_CameraPosition->LockUpdate();
//        m_ViewingPosition->LockUpdate();
//
//        // �r���[�ϊ��s�� ,(LH = ������W ,LR = �E����W)
//        return D3DXMatrixLookAtLH(&m_ViewMatrix, &eye, &at, &look->up);
//    }
//}
_MSLIB_END