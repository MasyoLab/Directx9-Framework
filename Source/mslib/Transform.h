//==========================================================================
// �g�����X�t�H�[�� [Transform.h]
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
	// Content : �����x�N�g��
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
		D3DXVECTOR3 eye; // ���_
		D3DXVECTOR3 at; // ���W
		D3DXVECTOR3 up; // up
	};

	//==========================================================================
	//
	// class : Vector
	// Content : �x�N�g��
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
		D3DXVECTOR3 up; // ��x�N�g��
		D3DXVECTOR3 front; // �O�x�N�g��
		D3DXVECTOR3 right; //  �E�x�N�g��
	};

	//==========================================================================
	//
	// class : Parameter
	// Content : ���W
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
		D3DXVECTOR3 position; // ���W
		D3DXVECTOR3 rotation; // ��]
		D3DXVECTOR3 scale; // �T�C�Y
	};

	//==========================================================================
	//
	// class : Transform
	// Content : �g�����X�t�H�[��
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
		@brief ������
		*/
		void Identity();

		/**
		@brief ���[���h��Ԃ���Ƃ������̎p��
		@return �}�g���N�X
		*/
		const D3DXMATRIX* GetWorldMatrix() const;

		/**
		@brief ���g�̐e��Ԃ���Ƃ������̎p��
		@return �}�g���N�X
		*/
		const D3DXMATRIX* GetLocalMatrix() const;

		/**
		@brief ���[���h��Ԃ���Ƃ������̎p��
		@param Input [in] �}�g���N�X
		*/
		void SetWorldMatrix(const D3DXMATRIX& Input);

		/**
		@brief ���g�̐e��Ԃ���Ƃ������̎p��
		@param Input [in] �}�g���N�X
		*/
		void SetLocalMatrix(const D3DXMATRIX& Input);

		/**
		@brief �r���[�s��̎擾
		@return �r���[�s��
		*/
		const D3DXMATRIX* GetMatrixView() const;

		/**
		@brief �r���[�s��̓o�^
		@param Input [in] �r���[�s��
		*/
		void SetMatrixView(D3DXMATRIX* Input);

		/**
		@brief �����x�N�g���̓o�^
		@param Input [in] �����x�N�g��
		*/
		void SetLook(const Look& Input);

		/**
		@brief �����x�N�g���̓o�^
		@param Input [in] �����x�N�g��
		*/
		void SetVector(const Vector& Input);

		/**
		@brief �p�����[�^�[�̓o�^
		@param Input [in] �p�����[�^�[
		*/
		void SetParameter(const Parameter& Input);

		/**
		@brief �����x�N�g���̎擾
		@return �����x�N�g��
		*/
		Look& GetLook();

		/**
		@brief �����x�N�g���̎擾
		@return �����x�N�g��
		*/
		Vector& GetVector();

		/**
		@brief �p�����[�^�̎擾
		@return �p�����[�^
		*/
		Parameter& GetParameter();

		/**
		@brief ���W�̎擾
		@return ���W
		*/
		const D3DXVECTOR3& GetPosition() const;

		/**
		@brief ��]�ʂ̎擾
		@return ��]��
		*/
		const D3DXVECTOR3& GetRotation();

		/**
		@brief �T�C�Y�̎擾
		@return �T�C�Y
		*/
		const D3DXVECTOR3& GetScale() const;

		/**
		@brief ���W�̓o�^
		@param x [in] x���ւ̈ړ��l
		@param y [in] y���ւ̈ړ��l
		*/
		void SetPosition(float x, float y);

		/**
		@brief ���W�̓o�^
		@param x [in] x���ւ̈ړ��l
		@param y [in] y���ւ̈ړ��l
		@param z [in] z���ւ̈ړ��l
		*/
		void SetPosition(float x, float y, float z);

		/**
		@brief ���W�̓o�^
		@param position [in] x,y���ւ̈ړ��l
		*/
		void SetPosition(const D3DXVECTOR2& position);

		/**
		@brief ���W�̓o�^
		@param position [in] x,y,z���ւ̈ړ��l
		*/
		void SetPosition(const D3DXVECTOR3& position);

		/**
		@brief ���W�ւ̉��Z
		@param x [in] x���ւ̈ړ��l
		@param y [in] y���ւ̈ړ��l
		*/
		void AddPosition(float x, float y);

		/**
		@brief ���W�ւ̉��Z
		@param x [in] x���ւ̈ړ��l
		@param y [in] y���ւ̈ړ��l
		@param z [in] z���ւ̈ړ��l
		*/
		void AddPosition(float x, float y, float z);

		/**
		@brief ���W�ւ̉��Z
		@param position [in] x,y���ւ̈ړ��l
		*/
		void AddPosition(const D3DXVECTOR2& position);

		/**
		@brief ���W�ւ̉��Z
		@param position [in] x,y,z���ւ̈ړ��l
		*/
		void AddPosition(const D3DXVECTOR3& position);

		/**
		@brief �T�C�Y�ւ̓o�^
		@param x [in] x���T�C�Y
		@param y [in] y���T�C�Y
		*/
		void SetScale(float x, float y);

		/**
		@brief �T�C�Y�̓o�^
		@param x [in] x���T�C�Y
		@param y [in] y���T�C�Y
		@param z [in] z���T�C�Y
		*/
		void SetScale(float x, float y, float z);

		/**
		@brief �T�C�Y�̓o�^
		@param scale [in] x,y���ւ̈ړ��l
		*/
		void SetScale(const D3DXVECTOR2& scale);

		/**
		@brief �T�C�Y�̓o�^
		@param scale [in] x,y,z���ւ̈ړ��l
		*/
		void SetScale(const D3DXVECTOR3& scale);

		/**
		@brief �T�C�Y�ւ̉��Z
		@param x [in] x���ւ̉��Z�l
		@param y [in] y���ւ̉��Z�l
		*/
		void AddScale(float x, float y);

		/**
		@brief �T�C�Y�ւ̉��Z
		@param x [in] x���ւ̉��Z�l
		@param y [in] y���ւ̉��Z�l
		@param z [in] z���ւ̉��Z�l
		*/
		void AddScale(float x, float y, float z);

		/**
		@brief �T�C�Y�ւ̉��Z
		@param scale [in] x,y���ւ̈ړ��l
		*/
		void AddScale(const D3DXVECTOR2& scale);

		/**
		@brief �T�C�Y�ւ̉��Z
		@param scale [in] x,y,z���ւ̈ړ��l
		*/
		void AddScale(const D3DXVECTOR3& scale);

		/**
		@brief ��]�̓o�^
		@param x [in] x���ւ̉�]�l
		@param y [in] y���ւ̉�]�l
		*/
		void SetRotation(float x, float y);

		/**
		@brief ��]�̓o�^
		@param x [in] x���ւ̉�]�l
		@param y [in] y���ւ̉�]�l
		@param z [in] z���ւ̉�]�l
		*/
		void SetRotation(float x, float y, float z);

		/**
		@brief ��]�̓o�^
		@param axis [in] x,y���ւ̉�]�l
		*/
		void SetRotation(const D3DXVECTOR2& axis);

		/**
		@brief ��]�̓o�^
		@param axis [in] x,y,z���ւ̉�]�l
		*/
		void SetRotation(const D3DXVECTOR3& axis);

		/**
		@brief ��]���ւ̉��Z
		@param x [in] x���ւ̉��Z�l
		@param y [in] y���ւ̉��Z�l
		*/
		void AddRotation(float x, float y);

		/**
		@brief ��]���ւ̉��Z
		@param x [in] x���ւ̉��Z�l
		@param y [in] y���ւ̉��Z�l
		@param z [in] z���ւ̉��Z�l
		*/
		void AddRotation(float x, float y, float z);

		/**
		@brief ��]���ւ̉��Z
		@param axis [in] x,y���ւ̉��Z�l
		*/
		void AddRotation(const D3DXVECTOR2& axis);

		/**
		@brief ��]���ւ̉��Z
		@param axis [in] x,y,z���ւ̉��Z�l
		*/
		void AddRotation(const D3DXVECTOR3& axis);

		/**
		@brief x����]�ւ̉��Z
		@param axis [in] x���ւ̎w������x�N�g���̉��Z�l
		*/
		void AddRotationX(const D3DXVECTOR2& axis);

		/**
		@brief x����]�ւ̉��Z
		@param axis [in] x���ւ̎w������x�N�g���̉��Z�l
		*/
		void AddRotationX(const D3DXVECTOR3& axis);

		/**
		@brief y����]�ւ̉��Z
		@param axis [in] y���ւ̎w������x�N�g���̉��Z�l
		*/
		void AddRotationY(const D3DXVECTOR2& axis);

		/**
		@brief y����]�ւ̉��Z
		@param axis [in] y���ւ̎w������x�N�g���̉��Z�l
		*/
		void AddRotationY(const D3DXVECTOR3& axis);

		/**
		@brief z����]�ւ̉��Z
		@param axis [in] z���ւ̎w������x�N�g���̉��Z�l
		*/
		void AddRotationZ(const D3DXVECTOR3& axis);

		/**
		@brief x����]�ւ̉��Z
		@param axis [in] x���ւ̎w������x�N�g���̉��Z�l
		@param angle [in] ��]��
		*/
		void AddRotationX(const D3DXVECTOR2& axis, float angle);

		/**
		@brief x����]�ւ̉��Z
		@param axis [in] x���ւ̎w������x�N�g���̉��Z�l
		@param angle [in] ��]��
		*/
		void AddRotationX(const D3DXVECTOR3& axis, float angle);

		/**
		@brief y����]�ւ̉��Z
		@param axis [in] y���ւ̎w������x�N�g���̉��Z�l
		@param angle [in] ��]��
		*/
		void AddRotationY(const D3DXVECTOR2& axis, float angle);

		/**
		@brief y����]�ւ̉��Z
		@param axis [in] y���ւ̎w������x�N�g���̉��Z�l
		@param angle [in] ��]��
		*/
		void AddRotationY(const D3DXVECTOR3& axis, float angle);

		/**
		@brief z����]�ւ̉��Z
		@param axis [in] z���ւ̎w������x�N�g���̉��Z�l
		@param angle [in] ��]��
		*/
		void AddRotationZ(const D3DXVECTOR3& axis, float angle);

		/**
		@brief x,y,z����]�ւ̉��Z
		@param axis [in] x,y,z���ւ̎w������x�N�g���̉��Z�l
		@param angle [in] ��]��
		*/
		void AddRotationXYZ(const D3DXVECTOR3& X, const D3DXVECTOR3& Y, const D3DXVECTOR3& Z, float angle);

		/**
		@brief x,y����]�ւ̉��Z
		@param axis [in] x,y���ւ̎w������x�N�g���̉��Z�l
		@param angle [in] ��]��
		*/
		void AddRotationXY(const D3DXVECTOR2& X, const D3DXVECTOR2& Y, float angle);

		/**
		@brief Y����]�ւ̉��Z(��]�p�x��������)
		@param y [in] y���ւ̉��Z�l
		@param limit [in] �����p�x
		*/
		void AddRotationLimitY(float y, float limit);

		/**
		@brief ���[���h�}�g���N�X�̐���
		@return �}�g���N�X
		*/
		virtual D3DXMATRIX* CreateWorldMatrix();

		/**
		@brief ���[�J���}�g���N�X�̐���
		@return �}�g���N�X
		*/
		virtual D3DXMATRIX* CreateLocalMatrix();

		/**
		@brief �O���[�o���}�g���N�X�̐���
		@return �}�g���N�X
		*/
		virtual D3DXMATRIX* CreateWorldViewMatrix();

		/**
		@brief ���[�J���}�g���N�X�̐���
		@return �}�g���N�X
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
		@brief �X�V���b�N����� true�ŗL����
		*/
		void SetUpdateKey(bool _flag);

		/**
		@brief �X�V�L�[
		*/
		bool GetUpdateKey();

		/**
		@brief �Ώۂւ̌����x�N�g�����v�Z
		*/
		D3DXVECTOR3 ToSee(const D3DXMATRIX* _mat);

		/**
		@brief Transform �̃R�s�[
		*/
		void CopyTransform(reference::IReference<Transform> _trans);

		/**
		@brief �e��Transform��o�^���܂�
		*/
		void SetTransformParent();

		/**
		@brief �I�t�Z�b�g�l�̎擾
		*/
		D3DXVECTOR3 GetMatrixOffset();

		/**
		@brief �X�P�[���l�̎擾
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
		D3DXMATRIX m_world_matrix; // ���[���h��Ԃ���Ƃ������̎p��
		D3DXMATRIX m_local_matrix; // ���g�̐e��Ԃ���Ƃ������̎p��
		D3DXMATRIX* m_view_matrix; // �r���[�s��̓o�^
	private:
		bool m_update_flag; // �X�V�t���O
		reference::IReference<Transform> m_transform_parent;
	};

	using TransformReference = reference::IReference<Transform>;
}

_MSLIB_END