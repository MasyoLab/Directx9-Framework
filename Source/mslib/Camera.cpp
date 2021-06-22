//==========================================================================
// カメラ [Camera.cpp]
// author : MasyoLab
//==========================================================================
#include "Camera.h"
#include "Renderer.h"
#include "MsImGui.h"
#include "string_encode.hpp"

_MSLIB_BEGIN

namespace camera
{
	std::list<Camera*> Camera::m_cameras; // 全てのカメラ
	reference::IReference<Camera> Camera::m_main_camera; // メインのカメラ

	Camera::Camera() :
		Component("Camera"), m_surface(nullptr), m_far_clip(1000), m_near_clip(1)
	{
		// 初期化
		D3DXMatrixIdentity(&m_view);
		D3DXMatrixIdentity(&m_projection);
		m_vector.Identity();
		m_vector.Normalize();

		m_win_size = GetDevice()->GetWindowsSize();
		m_this = ThisComponent<Camera>();

		// カメラ映像出力用のテクスチャ
		m_blur_texture = GetTextureLoader()->CreateTexture((int)m_win_size.x, (int)m_win_size.y, 1, D3DUSAGE_RENDERTARGET, D3DFMT_R8G8B8, D3DPOOL_DEFAULT);
		m_blur_texture->GetTexture()->GetSurfaceLevel(0, &m_surface);

		// スプライトを生成
		m_screen_renderer = AddComponent(new object::Sprite);
		m_screen_renderer->SetTextureData(m_blur_texture);
		m_screen_renderer->SetPriority(-9999999.f);
		m_screen_renderer->AddPosition(-0.5f, -0.5f, 0);
		m_screen_renderer->SetDefaultWindowSizeModel(false);
		m_screen_renderer->SetActivity(false);

		// デフォルトとして、ニアクリップとファークリップを設定
		CreateProjectionMatrix();

		// メインのカメラとして設定
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

		// メインのレンダーターゲットを保存
		device->GetRenderTarget(0, &buffer);

		// カメラの数だけ回す
		for (auto& itr : m_cameras)
		{
				// レンダーターゲットを指定
			device->SetRenderTarget(0, itr->m_surface);

			if (pdevice->DrawBegin())
			{
				// プロジェクション行列の作成
				// ズームイン、ズームアウトのような物
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

		// ビュー変換行列 ,(LH = 左手座標 ,LR = 右手座標)
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
		D3DXMATRIX Matrix, AddMatrix; //回転行列
		D3DXVECTOR3 Direction;

		// 外積を求めます
		m_vector.CrossRight();

		// マトリクスの初期化
		D3DXMatrixIdentity(&Matrix);

		// 生成した回転マトリクスを合成していきます
		D3DXMatrixMultiply(&Matrix, D3DXMatrixRotationY(&AddMatrix, axis.x), &Matrix);
		D3DXMatrixMultiply(&Matrix, D3DXMatrixRotationAxis(&AddMatrix, &m_vector.right, axis.y), &Matrix);
		D3DXMatrixMultiply(&Matrix, D3DXMatrixRotationAxis(&AddMatrix, &m_vector.front, axis.z), &Matrix);

		// 向きベクトルに合成します
		m_vector.TransformNormal(Matrix);

		Direction = m_look1.eye - m_look1.at;
		D3DXVec3TransformNormal(&Direction, &Direction, &Matrix);
		m_look1.eye = m_look1.at + Direction;
		m_look1.up = m_vector.up;
	}

	void Camera::AddCameraRotation(const D3DXVECTOR3& axis)
	{
		D3DXMATRIX Matrix, AddMatrix; //回転行列
		D3DXVECTOR3 Direction;

		// 外積を求めます
		m_vector.CrossRight();

		// マトリクスの初期化
		D3DXMatrixIdentity(&Matrix);

		// 生成した回転マトリクスを合成していきます
		D3DXMatrixMultiply(&Matrix, D3DXMatrixRotationY(&AddMatrix, axis.x), &Matrix);
		D3DXMatrixMultiply(&Matrix, D3DXMatrixRotationAxis(&AddMatrix, &m_vector.right, axis.y), &Matrix);
		D3DXMatrixMultiply(&Matrix, D3DXMatrixRotationAxis(&AddMatrix, &m_vector.front, axis.z), &Matrix);

		// 向きベクトルに合成します
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
		auto dir = D3DXVECTOR3(0, 1.0f, 0); // 単位ベクトル

		auto vector = m_vector;

		// ベクトルの座標変換
		vector.CrossRight();
		D3DXMatrixRotationAxis(&Rot, &vector.right, axis); // 回転
		vector.TransformNormal(Rot);
		float fVec3Dot = atanf(D3DXVec3Dot(&vector.front, &dir));

		// 内積
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
		auto dir1 = D3DXVECTOR3(0, 1.0f, 0); // 単位ベクトル
		auto dir2 = D3DXVECTOR3(0, m_vector.front.y, 0); // 単位ベクトル

		return atanf(D3DXVec3Dot(&dir2, &dir1)); // 内積
	}

	float Camera::GetRestrictionX()
	{
		auto dir1 = D3DXVECTOR3(1.0f, 0, 0); // 単位ベクトル
		auto dir2 = D3DXVECTOR3(m_vector.front.x, 0, 0); // 単位ベクトル

		return atanf(D3DXVec3Dot(&dir2, &dir1)); // 内積
	}

	float Camera::GetRestrictionZ()
	{
		auto dir1 = D3DXVECTOR3(0, 0, 1.0f); // 単位ベクトル
		auto dir2 = D3DXVECTOR3(0, 0, m_vector.front.z); // 単位ベクトル

		return atanf(D3DXVec3Dot(&dir2, &dir1)); // 内積
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
//    std::list<Camera*> Camera::m_AllCamera; // 全カメラ
//    Camera * Camera::m_main_camera = nullptr; // メインのカメラ
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
//        // プロジェクション行列の作成
//        // ズームイン、ズームアウトのような物
//        D3DXMatrixPerspectiveFovLH(&m_main_camera->m_ProjectionMatrix, D3DXToRadian(60)/*D3DX_PI/3*/, (float)win_size.x / (float)win_size.y, 0.1f/*ニヤ*/, 1000.0f/*ファー*/);
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
//        // ビューカメラの向きを更新
//        auto angle = m_CameraPosition->ToSee(*m_ViewingPosition);
//        m_ViewingPosition->GetLook()->eye = -angle;
//        m_ViewingPosition->GetVector()->front = angle;
//        m_ViewingPosition->GetVector()->Normalize();
//
//        // カメラの向きを更新
//        m_CameraPosition->GetLook()->eye = -angle;
//        m_CameraPosition->GetVector()->front = angle;
//        m_CameraPosition->GetVector()->Normalize();
//
//        // ビューカメラの更新フラグが有効
//        if (m_ViewingPosition->UpdateKey())
//        {
//            auto mat = m_ViewingPosition->GetWorldMatrix();
//            auto distance = collider::Distance(m_CameraPosition, m_ViewingPosition);
//
//            m_CameraPosition->SetPosition(mat->_41, mat->_42, mat->_43);
//            m_CameraPosition->AddPosition(0, 0, -distance);
//        }
//
//        // 全行列の更新
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
//        // 更新のロック
//        m_CameraPosition->LockUpdate();
//        m_ViewingPosition->LockUpdate();
//
//        // ビュー変換行列 ,(LH = 左手座標 ,LR = 右手座標)
//        return D3DXMatrixLookAtLH(&m_ViewMatrix, &eye, &at, &look->up);
//    }
//}
_MSLIB_END