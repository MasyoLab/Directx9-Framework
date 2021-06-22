//==========================================================================
// カメラ [Camera.h]
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
	// Content : カメラ
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
		@brief 初期化
		*/
		void Init();

		/**
		@brief 初期化
		@param eye [in] 注視点
		@param at [in] 座標
		*/
		void Init(const D3DXVECTOR3& eye, const D3DXVECTOR3& at);

		/**
		@brief カメラが写す全ての物をテクスチャに反映します
		*/
		static void Rendering(LPDIRECT3DDEVICE9 device);

		/**
		@brief カメラのGUI
		*/
		static void GUICamera();

		/**
		@brief 現在メインで使用されているカメラのポインタを取得します
		@return カメラポインタ
		*/
		static reference::IReference<Camera> GetCamera();

		/**
		@brief ビュー行列の取得
		@return ビュー行列
		*/
		D3DXMATRIX* GetViewMatrix();

		/**
		@brief プロジェクション行列の取得
		@return プロジェクション行列
		*/
		D3DXMATRIX* GetProjectionMatrix();

		/**
		@brief プロジェクション行列の生成
		@return プロジェクション行列
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
		@brief 視点変更
		@param _distance [in] 入れた値が加算されます
		@return 視点とカメラの距離
		*/
		float DistanceFromView(float distance);

		/**
		@brief カメラY軸回転情報
		@return 内積
		*/
		float GetRestrictionY();

		/**
		@brief カメラX軸回転情報
		@return 内積
		*/
		float GetRestrictionX();

		/**
		@brief カメラZ軸回転情報
		@return 内積
		*/
		float GetRestrictionZ();

		/**
		@brief カメラ座標をセット
		@param Eye [in] 注視点
		@param At [in] カメラ座標
		@param Up [in] ベクター
		*/
		void SetCameraPos(const D3DXVECTOR3& eye, const D3DXVECTOR3& at, const D3DXVECTOR3& up);

		/**
		@brief カメラ座標
		@param At [in] カメラ座標
		*/
		void SetAt(const D3DXVECTOR3& at);

		/**
		@brief 注視点
		@param Eye [in] 注視点
		*/
		void SetEye(const D3DXVECTOR3& eye);

		const transform::Look& GetLook1() const;
		const transform::Look& GetLook2() const;
		const transform::Vector& GetVector() const;

		/**
		@brief メインカメラにします
		*/
		void IsMainCamera();

		/**
		@brief カメラが写したテクスチャを取得します
		@return TextureReference
		*/
		texture::TextureReference GetImage();

		/**
		@brief ファークリップの取得
		@return ファークリップ
		*/
		float GetFarClip();

		/**
		@brief ファークリップの登録
		*/
		void SetFarClip(float farClip);

		/**
		@brief ニアクリップの取得
		@return ニアクリップ
		*/
		float GetNearClip();

		/**
		@brief ニアクリップの登録
		*/
		void SetNearClip(float nearClip);
	private:
		/**
		@brief ビュー行列生成
		@return ビュー行列
		*/
		D3DXMATRIX* CreateView();

		/**
		@brief 視点変更
		@param vec [in] ベクトル
		@param out1 [out] 出力1
		@param out2 [out] 出力2
		@param speed [in] 移動速度
		@return 戻り値は 距離
		*/
		float ViewPos(D3DXVECTOR3& vec, D3DXVECTOR3& out1, const D3DXVECTOR3& out2, float speed);

		/**
		@brief 内積
		@param axis [in] 回転情報
		@param limit [in] 回転速度
		@return 移動可能範囲なら true
		*/
		bool Restriction(float axis, float limit);

		void GUICameraWindow();
	private:
		texture::TextureReference m_blur_texture; // 画面
		object::SpriteReference m_screen_renderer; // 画面描画機能
		LPDIRECT3DSURFACE9 m_surface; // テクスチャ1
		D3DXMATRIX m_projection; // プロジェクション行列
		D3DXMATRIX m_view; // ビュー行列
		transform::Look m_look1; // 視線ベクトル
		transform::Look m_look2; // 視線ベクトル
		transform::Vector m_vector; // 向きベクトル
		D3DXVECTOR2 m_win_size; // ウィンドウサイズ
		float m_far_clip; // ファークリップを行う距離
		float m_near_clip; // ニアクリップを行う距離
		reference::IReference<Camera> m_this;
		static std::list<Camera*> m_cameras; // 全てのカメラ
		static reference::IReference<Camera> m_main_camera; // メインのカメラ
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
//        D3DXMATRIX m_ProjectionMatrix; // プロジェクション行列
//        D3DXMATRIX m_ViewMatrix; // ビュー行列
//		component::IReference<transform::Transform> m_target; // 追従対象
//		component::IReference<transform::Transform> m_CameraPosition; // カメラ
//		component::IReference<transform::Transform> m_ViewingPosition; // 表示方向
//        static std::list<Camera*> m_AllCamera; // 全カメラ
//        static Camera * m_MainCamera; // メインのカメラ
//    };
//}
_MSLIB_END