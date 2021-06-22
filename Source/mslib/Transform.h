//==========================================================================
// トランスフォーム [Transform.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"
#include "Component.h"

_MSLIB_BEGIN

namespace transform
{
	//==========================================================================
	//
	// class : Look
	// Content : 視線ベクトル
	//
	//==========================================================================
	class Look
	{
	public:
		Look();
		Look(const Look& Input);
		Look(const D3DXVECTOR3& _eye, const D3DXVECTOR3& _at, const D3DXVECTOR3& _up);
		~Look();
		void Identity();
		Look GetIdentity();
		D3DXMATRIX* MatrixEyeAtUp(D3DXMATRIX& Out);
		D3DXMATRIX* MatrixEyeAtUpAxisFix(D3DXMATRIX& Out);
		Look* operator()();
		Look* operator()(const Look& Input);
		Look* operator()(const D3DXVECTOR3& _eye, const D3DXVECTOR3& _at, const D3DXVECTOR3& _up);
		Look operator+(const Look& v);
		Look operator-(const Look& v);
	public:
		D3DXVECTOR3 eye; // 視点
		D3DXVECTOR3 at; // 座標
		D3DXVECTOR3 up; // up
	};

	//==========================================================================
	//
	// class : Vector
	// Content : ベクトル
	//
	//==========================================================================
	class Vector
	{
	public:
		Vector();
		Vector(const Vector& Input);
		Vector(const D3DXVECTOR3& _front, const D3DXVECTOR3& _right, const D3DXVECTOR3& _up);
		~Vector();
		Vector* Normalize();
		Vector* TransformNormal(const D3DXMATRIX& pM);
		D3DXVECTOR3* CrossRight();
		D3DXVECTOR3* VectoeMultiply(D3DXVECTOR3& Out, const D3DXVECTOR3& V1);
		void Identity();
		Vector GetIdentity();
		D3DXMATRIX* MatrixVector(D3DXMATRIX& Out);
		Vector* operator()();
		Vector* operator()(const Vector& Input);
		Vector* operator()(const D3DXVECTOR3& _front, const D3DXVECTOR3& _right, const D3DXVECTOR3& _up);
		Vector operator+(const Vector& v);
		Vector operator-(const Vector& v);
	public:
		D3DXVECTOR3 up; // 上ベクトル
		D3DXVECTOR3 front; // 前ベクトル
		D3DXVECTOR3 right; //  右ベクトル
	};

	//==========================================================================
	//
	// class : Parameter
	// Content : 座標
	//
	//==========================================================================
	class Parameter
	{
	public:
		Parameter();
		Parameter(const Parameter& Input);
		Parameter(const D3DXVECTOR3& _position, const D3DXVECTOR3& _rotation, const D3DXVECTOR3& _scale);
		~Parameter();
		D3DXMATRIX* MatrixTranslation(D3DXMATRIX& Out);
		D3DXMATRIX* MatrixScaling(D3DXMATRIX& Out);
		void Identity();
		Parameter GetIdentity();
		Parameter* operator()();
		Parameter* operator()(const Parameter& Input);
		Parameter* operator()(const D3DXVECTOR3& _position, const D3DXVECTOR3& _rotation, const D3DXVECTOR3& _scale);
		Parameter operator+(const Parameter& v);
		Parameter operator-(const Parameter& v);
	public:
		D3DXVECTOR3 position; // 座標
		D3DXVECTOR3 rotation; // 回転
		D3DXVECTOR3 scale; // サイズ
	};

	//==========================================================================
	//
	// class : Transform
	// Content : トランスフォーム
	// Inheritance : public Component
	//
	//==========================================================================
	class Transform :
		virtual public component::Component
	{
	private:
		Transform(const Transform&) = delete;
		Transform(Transform&&) = delete;
		Transform& operator=(const Transform&) = delete;
		Transform& operator=(Transform&&) = delete;
	public:
		Transform();
		~Transform();

		/**
		@brief 初期化
		*/
		void Identity();

		/**
		@brief ワールド空間を基準とした時の姿勢
		@return マトリクス
		*/
		const D3DXMATRIX* GetWorldMatrix() const;

		/**
		@brief 自身の親空間を基準とした時の姿勢
		@return マトリクス
		*/
		const D3DXMATRIX* GetLocalMatrix() const;

		/**
		@brief ワールド空間を基準とした時の姿勢
		@param Input [in] マトリクス
		*/
		void SetWorldMatrix(const D3DXMATRIX& Input);

		/**
		@brief 自身の親空間を基準とした時の姿勢
		@param Input [in] マトリクス
		*/
		void SetLocalMatrix(const D3DXMATRIX& Input);

		/**
		@brief ビュー行列の取得
		@return ビュー行列
		*/
		const D3DXMATRIX* GetMatrixView() const;

		/**
		@brief ビュー行列の登録
		@param Input [in] ビュー行列
		*/
		void SetMatrixView(D3DXMATRIX* Input);

		/**
		@brief 視線ベクトルの登録
		@param Input [in] 視線ベクトル
		*/
		void SetLook(const Look& Input);

		/**
		@brief 向きベクトルの登録
		@param Input [in] 向きベクトル
		*/
		void SetVector(const Vector& Input);

		/**
		@brief パラメーターの登録
		@param Input [in] パラメーター
		*/
		void SetParameter(const Parameter& Input);

		/**
		@brief 視線ベクトルの取得
		@return 視線ベクトル
		*/
		Look& GetLook();

		/**
		@brief 向きベクトルの取得
		@return 向きベクトル
		*/
		Vector& GetVector();

		/**
		@brief パラメータの取得
		@return パラメータ
		*/
		Parameter& GetParameter();

		/**
		@brief 座標の取得
		@return 座標
		*/
		const D3DXVECTOR3& GetPosition() const;

		/**
		@brief 回転量の取得
		@return 回転量
		*/
		const D3DXVECTOR3& GetRotation();

		/**
		@brief サイズの取得
		@return サイズ
		*/
		const D3DXVECTOR3& GetScale() const;

		/**
		@brief 座標の登録
		@param x [in] x軸への移動値
		@param y [in] y軸への移動値
		*/
		void SetPosition(float x, float y);

		/**
		@brief 座標の登録
		@param x [in] x軸への移動値
		@param y [in] y軸への移動値
		@param z [in] z軸への移動値
		*/
		void SetPosition(float x, float y, float z);

		/**
		@brief 座標の登録
		@param position [in] x,y軸への移動値
		*/
		void SetPosition(const D3DXVECTOR2& position);

		/**
		@brief 座標の登録
		@param position [in] x,y,z軸への移動値
		*/
		void SetPosition(const D3DXVECTOR3& position);

		/**
		@brief 座標への加算
		@param x [in] x軸への移動値
		@param y [in] y軸への移動値
		*/
		void AddPosition(float x, float y);

		/**
		@brief 座標への加算
		@param x [in] x軸への移動値
		@param y [in] y軸への移動値
		@param z [in] z軸への移動値
		*/
		void AddPosition(float x, float y, float z);

		/**
		@brief 座標への加算
		@param position [in] x,y軸への移動値
		*/
		void AddPosition(const D3DXVECTOR2& position);

		/**
		@brief 座標への加算
		@param position [in] x,y,z軸への移動値
		*/
		void AddPosition(const D3DXVECTOR3& position);

		/**
		@brief サイズへの登録
		@param x [in] x軸サイズ
		@param y [in] y軸サイズ
		*/
		void SetScale(float x, float y);

		/**
		@brief サイズの登録
		@param x [in] x軸サイズ
		@param y [in] y軸サイズ
		@param z [in] z軸サイズ
		*/
		void SetScale(float x, float y, float z);

		/**
		@brief サイズの登録
		@param scale [in] x,y軸への移動値
		*/
		void SetScale(const D3DXVECTOR2& scale);

		/**
		@brief サイズの登録
		@param scale [in] x,y,z軸への移動値
		*/
		void SetScale(const D3DXVECTOR3& scale);

		/**
		@brief サイズへの加算
		@param x [in] x軸への加算値
		@param y [in] y軸への加算値
		*/
		void AddScale(float x, float y);

		/**
		@brief サイズへの加算
		@param x [in] x軸への加算値
		@param y [in] y軸への加算値
		@param z [in] z軸への加算値
		*/
		void AddScale(float x, float y, float z);

		/**
		@brief サイズへの加算
		@param scale [in] x,y軸への移動値
		*/
		void AddScale(const D3DXVECTOR2& scale);

		/**
		@brief サイズへの加算
		@param scale [in] x,y,z軸への移動値
		*/
		void AddScale(const D3DXVECTOR3& scale);

		/**
		@brief 回転の登録
		@param x [in] x軸への回転値
		@param y [in] y軸への回転値
		*/
		void SetRotation(float x, float y);

		/**
		@brief 回転の登録
		@param x [in] x軸への回転値
		@param y [in] y軸への回転値
		@param z [in] z軸への回転値
		*/
		void SetRotation(float x, float y, float z);

		/**
		@brief 回転の登録
		@param axis [in] x,y軸への回転値
		*/
		void SetRotation(const D3DXVECTOR2& axis);

		/**
		@brief 回転の登録
		@param axis [in] x,y,z軸への回転値
		*/
		void SetRotation(const D3DXVECTOR3& axis);

		/**
		@brief 回転軸への加算
		@param x [in] x軸への加算値
		@param y [in] y軸への加算値
		*/
		void AddRotation(float x, float y);

		/**
		@brief 回転軸への加算
		@param x [in] x軸への加算値
		@param y [in] y軸への加算値
		@param z [in] z軸への加算値
		*/
		void AddRotation(float x, float y, float z);

		/**
		@brief 回転軸への加算
		@param axis [in] x,y軸への加算値
		*/
		void AddRotation(const D3DXVECTOR2& axis);

		/**
		@brief 回転軸への加算
		@param axis [in] x,y,z軸への加算値
		*/
		void AddRotation(const D3DXVECTOR3& axis);

		/**
		@brief x軸回転への加算
		@param axis [in] x軸への指定向きベクトルの加算値
		*/
		void AddRotationX(const D3DXVECTOR2& axis);

		/**
		@brief x軸回転への加算
		@param axis [in] x軸への指定向きベクトルの加算値
		*/
		void AddRotationX(const D3DXVECTOR3& axis);

		/**
		@brief y軸回転への加算
		@param axis [in] y軸への指定向きベクトルの加算値
		*/
		void AddRotationY(const D3DXVECTOR2& axis);

		/**
		@brief y軸回転への加算
		@param axis [in] y軸への指定向きベクトルの加算値
		*/
		void AddRotationY(const D3DXVECTOR3& axis);

		/**
		@brief z軸回転への加算
		@param axis [in] z軸への指定向きベクトルの加算値
		*/
		void AddRotationZ(const D3DXVECTOR3& axis);

		/**
		@brief x軸回転への加算
		@param axis [in] x軸への指定向きベクトルの加算値
		@param angle [in] 回転量
		*/
		void AddRotationX(const D3DXVECTOR2& axis, float angle);

		/**
		@brief x軸回転への加算
		@param axis [in] x軸への指定向きベクトルの加算値
		@param angle [in] 回転量
		*/
		void AddRotationX(const D3DXVECTOR3& axis, float angle);

		/**
		@brief y軸回転への加算
		@param axis [in] y軸への指定向きベクトルの加算値
		@param angle [in] 回転量
		*/
		void AddRotationY(const D3DXVECTOR2& axis, float angle);

		/**
		@brief y軸回転への加算
		@param axis [in] y軸への指定向きベクトルの加算値
		@param angle [in] 回転量
		*/
		void AddRotationY(const D3DXVECTOR3& axis, float angle);

		/**
		@brief z軸回転への加算
		@param axis [in] z軸への指定向きベクトルの加算値
		@param angle [in] 回転量
		*/
		void AddRotationZ(const D3DXVECTOR3& axis, float angle);

		/**
		@brief x,y,z軸回転への加算
		@param axis [in] x,y,z軸への指定向きベクトルの加算値
		@param angle [in] 回転量
		*/
		void AddRotationXYZ(const D3DXVECTOR3& X, const D3DXVECTOR3& Y, const D3DXVECTOR3& Z, float angle);

		/**
		@brief x,y軸回転への加算
		@param axis [in] x,y軸への指定向きベクトルの加算値
		@param angle [in] 回転量
		*/
		void AddRotationXY(const D3DXVECTOR2& X, const D3DXVECTOR2& Y, float angle);

		/**
		@brief Y軸回転への加算(回転角度制限あり)
		@param y [in] y軸への加算値
		@param limit [in] 制限角度
		*/
		void AddRotationLimitY(float y, float limit);

		/**
		@brief ワールドマトリクスの生成
		@return マトリクス
		*/
		virtual D3DXMATRIX* CreateWorldMatrix();

		/**
		@brief ローカルマトリクスの生成
		@return マトリクス
		*/
		virtual D3DXMATRIX* CreateLocalMatrix();

		/**
		@brief グローバルマトリクスの生成
		@return マトリクス
		*/
		virtual D3DXMATRIX* CreateWorldViewMatrix();

		/**
		@brief ローカルマトリクスの生成
		@return マトリクス
		*/
		virtual D3DXMATRIX* CreateLocalViewMatrix();

		/**
		@brief Radian << Degree
		*/
		D3DXVECTOR3 ToRadian(const D3DXVECTOR3& degree);

		/**
		@brief Radian << Degree
		*/
		D3DXVECTOR3 ToRadian(float x, float y, float z);

		/**
		@brief Degree << Radian
		*/
		D3DXVECTOR3 ToDegree(const D3DXVECTOR3& radian);

		/**
		@brief Degree << Radian
		*/
		D3DXVECTOR3 ToDegree(float x, float y, float z);

		/**
		@brief 更新ロックを入力 trueで有効化
		*/
		void SetUpdateKey(bool _flag);

		/**
		@brief 更新キー
		*/
		bool GetUpdateKey();

		/**
		@brief 対象への向きベクトルを計算
		*/
		D3DXVECTOR3 ToSee(const D3DXMATRIX* _mat);

		/**
		@brief Transform のコピー
		*/
		void CopyTransform(reference::IReference<Transform> _trans);

		/**
		@brief 親のTransformを登録します
		*/
		void SetTransformParent();

		/**
		@brief オフセット値の取得
		*/
		D3DXVECTOR3 GetMatrixOffset();

		/**
		@brief スケール値の取得
		*/
		D3DXVECTOR3 GetMatrixScale();
	private:
		Transform* GetThisPtr();
	protected:
		void GUITransform();
		void InputDataTransform(std::ifstream& _ifstream);
		void OutputDataTransform(std::ofstream& _ofstream);
	protected:
		Look m_look; // Look
		Vector m_vector; // Vector
		Parameter m_parameter; // Parameter
		D3DXMATRIX m_world_matrix; // ワールド空間を基準とした時の姿勢
		D3DXMATRIX m_local_matrix; // 自身の親空間を基準とした時の姿勢
		D3DXMATRIX* m_view_matrix; // ビュー行列の登録
	private:
		bool m_update_flag; // 更新フラグ
		reference::IReference<Transform> m_transform_parent;
	};

	using TransformReference = reference::IReference<Transform>;
}

_MSLIB_END