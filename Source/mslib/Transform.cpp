//==========================================================================
// トランスフォーム [Transform.cpp]
// author : MasyoLab
//==========================================================================
#include "Transform.h"
#include "MsImGui.h"

_MSLIB_BEGIN

namespace transform
{
	Look::Look()
	{
		*this = Look(D3DXVECTOR3(0, 0, -1), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0));
	}

	Look::Look(const Look& Input)
	{
		*this = Input;
	}

	Look::Look(const D3DXVECTOR3& _eye, const D3DXVECTOR3& _at, const D3DXVECTOR3& _up)
	{
		eye = _eye;
		at = _at;
		up = _up;
	}

	Look::~Look()
	{
	}

	void Look::Identity()
	{
		*this = Look();
	}

	Look Look::GetIdentity()
	{
		return Look();
	}

	D3DXMATRIX* Look::MatrixEyeAtUp(D3DXMATRIX& Out)
	{
		D3DXVECTOR3 X, Y, Z;

		D3DXVec3Normalize(&Z, &eye);
		D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, &up), &Z);
		D3DXVec3Normalize(&X, &X);
		D3DXVec3Normalize(&Y, D3DXVec3Cross(&Y, &Z, &X));

		Out._11 = X.x; Out._12 = X.y; Out._13 = X.z; Out._14 = 0;
		Out._21 = Y.x; Out._22 = Y.y; Out._23 = Y.z; Out._24 = 0;
		Out._31 = Z.x; Out._32 = Z.y; Out._33 = Z.z; Out._34 = 0;
		Out._41 = 0.0f; Out._42 = 0.0f; Out._43 = 0.0f; Out._44 = 1.0f;

		return &Out;
	}

	D3DXMATRIX* Look::MatrixEyeAtUpAxisFix(D3DXMATRIX& Out)
	{
		D3DXVECTOR3 X, Y, Z, D;
		D3DXVec3Normalize(&D, &eye);
		D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, &up), &D);
		D3DXVec3Normalize(&X, &X);
		D3DXVec3Normalize(&Z, D3DXVec3Cross(&Z, &X, &Y));

		Out._11 = X.x; Out._12 = X.y; Out._13 = X.z; Out._14 = 0;
		Out._21 = Y.x; Out._22 = Y.y; Out._23 = Y.z; Out._24 = 0;
		Out._31 = Z.x; Out._32 = Z.y; Out._33 = Z.z; Out._34 = 0;
		Out._41 = 0; Out._42 = 0; Out._43 = 0; Out._44 = 0;

		return &Out;
	}

	Look* Look::operator()()
	{
		*this = Look();
		return this;
	}

	Look* Look::operator()(const Look& Input)
	{
		*this = Look(Input);
		return this;
	}

	Look* Look::operator()(const D3DXVECTOR3& _eye, const D3DXVECTOR3& _at, const D3DXVECTOR3& _up)
	{
		*this = Look(_eye, _at, _up);
		return this;
	}

	Look Look::operator+(const Look& v)
	{
		Look lock;

		lock.eye = eye + v.eye;
		lock.at = at + v.at;
		lock.up = up + v.up;

		return lock;
	}

	Look Look::operator-(const Look& v)
	{
		Look lock;

		lock.eye = eye - v.eye;
		lock.at = at - v.at;
		lock.up = up - v.up;

		return lock;
	}

	Vector::Vector()
	{
		*this = Vector(D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(1, 0, 0), D3DXVECTOR3(0, 1, 0));
	}

	Vector::Vector(const Vector& Input)
	{
		D3DXVec3Normalize(&front, &Input.front);
		D3DXVec3Normalize(&right, &Input.right);
		D3DXVec3Normalize(&up, &Input.up);
	}

	Vector::Vector(const D3DXVECTOR3& _front, const D3DXVECTOR3& _right, const D3DXVECTOR3& _up)
	{
		D3DXVec3Normalize(&front, &_front);
		D3DXVec3Normalize(&right, &_right);
		D3DXVec3Normalize(&up, &_up);
	}

	Vector::~Vector()
	{
	}

	Vector* Vector::Normalize()
	{
		D3DXVec3Normalize(&front, &front);
		D3DXVec3Normalize(&right, &right);
		D3DXVec3Normalize(&up, &up);

		return this;
	}

	Vector* Vector::TransformNormal(const D3DXMATRIX& pM)
	{
		D3DXVec3TransformNormal(&front, &front, &pM);
		D3DXVec3TransformNormal(&right, &right, &pM);
		D3DXVec3TransformNormal(&up, &up, &pM);
		return this;
	}

	D3DXVECTOR3* Vector::CrossRight()
	{
		return D3DXVec3Cross(&right, &up, &front);
	}

	D3DXVECTOR3* Vector::VectoeMultiply(D3DXVECTOR3& Out, const D3DXVECTOR3& V1)
	{
		Out += right * V1.x;
		Out += up * V1.y;
		Out += front * V1.z;

		return &Out;
	}

	void Vector::Identity()
	{
		*this = Vector();
	}

	Vector Vector::GetIdentity()
	{
		return Vector();
	}

	D3DXMATRIX* Vector::MatrixVector(D3DXMATRIX& Out)
	{
		Normalize();

		Out._11 = right.x; Out._12 = right.y; Out._13 = right.z; Out._14 = 0;
		Out._21 = up.x; Out._22 = up.y; Out._23 = up.z; Out._24 = 0;
		Out._31 = front.x; Out._32 = front.y; Out._33 = front.z; Out._34 = 0;
		Out._41 = 0.0f; Out._42 = 0.0f; Out._43 = 0.0f; Out._44 = 1.0f;

		return &Out;
	}

	Vector* Vector::operator()()
	{
		*this = Vector();
		return this;
	}

	Vector* Vector::operator()(const Vector& Input)
	{
		*this = Vector(Input);
		return this;
	}

	Vector* Vector::operator()(const D3DXVECTOR3& _front, const D3DXVECTOR3& _right, const D3DXVECTOR3& _up)
	{
		*this = Vector(_front, _right, _up);
		return this;
	}

	Vector Vector::operator+(const Vector& v)
	{
		Vector vector;

		vector.front = front + v.front;
		vector.right = right + v.right;
		vector.up = up + v.up;

		return vector;
	}

	Vector Vector::operator-(const Vector& v)
	{
		Vector vector;

		vector.front = front - v.front;
		vector.right = right - v.right;
		vector.up = up - v.up;

		return vector;
	}

	Parameter::Parameter()
	{
		*this = Parameter(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1));
	}

	Parameter::Parameter(const Parameter& Input)
	{
		*this = Input;
	}

	Parameter::Parameter(const D3DXVECTOR3& _position, const D3DXVECTOR3& _rotation, const D3DXVECTOR3& _scale)
	{
		position = _position;
		rotation = _rotation;
		scale = _scale;
	}

	Parameter::~Parameter()
	{
	}

	D3DXMATRIX* Parameter::MatrixTranslation(D3DXMATRIX& Out)
	{
		return D3DXMatrixTranslation(&Out, position.x, position.y, position.z);
	}

	D3DXMATRIX* Parameter::MatrixScaling(D3DXMATRIX& Out)
	{
		return D3DXMatrixScaling(&Out, scale.x, scale.y, scale.z);
	}

	void Parameter::Identity()
	{
		*this = Parameter();
	}

	Parameter Parameter::GetIdentity()
	{
		return Parameter();
	}

	Parameter* Parameter::operator()()
	{
		*this = Parameter();
		return this;
	}

	Parameter* Parameter::operator()(const Parameter& Input)
	{
		*this = Parameter(Input);
		return this;
	}

	Parameter* Parameter::operator()(const D3DXVECTOR3& _position, const D3DXVECTOR3& _rotation, const D3DXVECTOR3& _scale)
	{
		*this = Parameter(_position, _rotation, _scale);
		return this;
	}

	Parameter Parameter::operator+(const Parameter& v)
	{
		Parameter param;

		param.position = position + v.position;
		param.rotation = rotation + v.rotation;
		param.scale = scale + v.scale;

		return param;
	}

	Parameter Parameter::operator-(const Parameter& v)
	{
		Parameter param;

		param.position = position - v.position;
		param.rotation = rotation - v.rotation;
		param.scale = scale - v.scale;

		return param;
	}

	Transform::Transform() :
		Component("Transform"), m_view_matrix(nullptr), m_update_flag(true)
	{
		Identity();
	}

	Transform::~Transform()
	{
	}

	void Transform::Identity()
	{
		D3DXMatrixIdentity(&m_local_matrix);
		D3DXMatrixIdentity(&m_world_matrix);
		m_look.Identity();
		m_vector.Identity();
		m_parameter.Identity();
	}

	const D3DXMATRIX* Transform::GetWorldMatrix() const
	{
		return &m_world_matrix;
	}

	const D3DXMATRIX* Transform::GetLocalMatrix() const
	{
		return &m_local_matrix;
	}

	void Transform::SetWorldMatrix(const D3DXMATRIX& Input)
	{
		m_update_flag = true;
		m_world_matrix = Input;
	}

	void Transform::SetLocalMatrix(const D3DXMATRIX& Input)
	{
		m_local_matrix = Input;
	}

	const D3DXMATRIX* Transform::GetMatrixView()const
	{
		return m_view_matrix;
	}

	void Transform::SetMatrixView(D3DXMATRIX* Input)
	{
		m_update_flag = true;
		m_view_matrix = Input;
	}

	void Transform::SetLook(const Look& Input)
	{
		m_update_flag = true;
		m_look = Input;
	}

	void Transform::SetVector(const Vector& Input)
	{
		m_update_flag = true;
		m_vector = Input;
	}

	void Transform::SetParameter(const Parameter& Input)
	{
		m_update_flag = true;
		SetPosition(Input.position);
		SetRotation(Input.rotation);
		SetScale(Input.scale);
	}

	Look& Transform::GetLook()
	{
		return m_look;
	}

	Vector& Transform::GetVector()
	{
		return m_vector;
	}

	Parameter& Transform::GetParameter()
	{
		return m_parameter;
	}

	const D3DXVECTOR3& Transform::GetPosition() const
	{
		return m_parameter.position;
	}

	const D3DXVECTOR3& Transform::GetRotation()
	{
		return m_parameter.rotation;
	}

	const D3DXVECTOR3& Transform::GetScale() const
	{
		return m_parameter.scale;
	}

	void Transform::AddScale(float x, float y)
	{
		AddScale(D3DXVECTOR3(x, y, 0));
	}

	void Transform::AddScale(float x, float y, float z)
	{
		AddScale(D3DXVECTOR3(x, y, z));
	}

	void Transform::AddScale(const D3DXVECTOR2& scale)
	{
		AddScale(D3DXVECTOR3(scale.x, scale.y, 0));
	}

	void Transform::AddScale(const D3DXVECTOR3& scale)
	{
		m_update_flag = true;
		m_parameter.scale += scale;
	}

	void Transform::SetRotation(float x, float y)
	{
		SetRotation(D3DXVECTOR2(x, y));
	}

	void Transform::SetRotation(float x, float y, float z)
	{
		SetRotation(D3DXVECTOR3(x, y, z));
	}

	void Transform::SetRotation(const D3DXVECTOR2& axis)
	{
		m_update_flag = true;
		m_parameter.rotation = D3DXVECTOR3(axis.x, axis.y, 0);
	}

	void Transform::SetRotation(const D3DXVECTOR3& axis)
	{
		m_look.Identity();
		m_vector.Identity();
		m_parameter.rotation = D3DXVECTOR3(0, 0, 0);
		AddRotation(axis);
	}

	void Transform::SetScale(float x, float y)
	{
		SetScale(D3DXVECTOR2(x, y));
	}

	void Transform::SetScale(float x, float y, float z)
	{
		SetScale(D3DXVECTOR3(x, y, z));
	}

	void Transform::SetScale(const D3DXVECTOR2& scale)
	{
		m_update_flag = true;
		m_parameter.scale = D3DXVECTOR3(scale.x, scale.y, 1);
	}

	void Transform::SetScale(const D3DXVECTOR3& scale)
	{
		m_update_flag = true;
		m_parameter.scale = scale;
	}

	void Transform::SetPosition(float x, float y)
	{
		SetPosition(D3DXVECTOR2(x, y));
	}

	void Transform::SetPosition(float x, float y, float z)
	{
		SetPosition(D3DXVECTOR3(x, y, z));
	}

	void Transform::SetPosition(const D3DXVECTOR2& position)
	{
		m_update_flag = true;
		m_parameter.position = D3DXVECTOR3(position.x, position.y, m_parameter.position.z);
	}

	void Transform::SetPosition(const D3DXVECTOR3& position)
	{
		m_update_flag = true;
		m_parameter.position = position;
	}

	void Transform::AddPosition(float x, float y)
	{
		AddPosition(D3DXVECTOR3(x, y, 0));
	}

	void Transform::AddPosition(float x, float y, float z)
	{
		AddPosition(D3DXVECTOR3(x, y, z));
	}

	void Transform::AddPosition(const D3DXVECTOR2& position)
	{
		AddPosition(D3DXVECTOR3(position.x, position.y, 0));
	}

	void Transform::AddPosition(const D3DXVECTOR3& position)
	{
		// 正規化します
		m_vector.Normalize();

		// ベクトルを利用して動かします
		m_vector.VectoeMultiply(m_parameter.position, position);

		m_update_flag = true;
	}

	void Transform::AddRotation(float x, float y)
	{
		AddRotation(D3DXVECTOR3(x, y, 0));
	}

	void Transform::AddRotation(float x, float y, float z)
	{
		AddRotation(D3DXVECTOR3(x, y, z));
	}

	void Transform::AddRotation(const D3DXVECTOR2& axis)
	{
		AddRotation(D3DXVECTOR3(axis.x, axis.y, 0));
	}

	void Transform::AddRotation(const D3DXVECTOR3& axis)
	{
		D3DXMATRIX Matrix, AddMatrix; //回転行列

		m_parameter.rotation += axis;

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

		// 視線ベクトルを更新します
		m_look.up = m_vector.up;
		m_look.eye = -m_vector.front;

		m_update_flag = true;
	}

	void Transform::AddRotationX(const D3DXVECTOR2& axis)
	{
		AddRotationX(axis, 1);
	}

	void Transform::AddRotationX(const D3DXVECTOR3& axis)
	{
		AddRotationX(axis, 1);
	}

	void Transform::AddRotationY(const D3DXVECTOR2& axis)
	{
		AddRotationY(axis, 1);
	}

	void Transform::AddRotationY(const D3DXVECTOR3& axis)
	{
		AddRotationY(axis, 1);
	}

	void Transform::AddRotationZ(const D3DXVECTOR3& axis)
	{
		AddRotationZ(axis, 1);
	}

	void Transform::AddRotationX(const D3DXVECTOR2& axis, float angle)
	{
		AddRotationX(D3DXVECTOR3(axis.x, axis.y, 0), angle);
	}

	void Transform::AddRotationX(const D3DXVECTOR3& axis, float angle)
	{
		D3DXVECTOR3 vecAxis;

		// 外積を求めます
		m_vector.CrossRight();

		// 角度を求める
		float fVec3Dot = atanf(D3DXVec3Dot(&m_vector.right, D3DXVec3Normalize(&vecAxis, &axis)));

		AddRotation(D3DXVECTOR3(fVec3Dot * angle, 0, 0));
	}

	void Transform::AddRotationY(const D3DXVECTOR2& axis, float angle)
	{
		AddRotationY(D3DXVECTOR3(axis.x, axis.y, 0), angle);
	}

	void Transform::AddRotationY(const D3DXVECTOR3& axis, float angle)
	{
		D3DXVECTOR3 vecAxis;

		// 外積を求めます
		m_vector.CrossRight();

		// 角度を求める
		float fVec3Dot = atanf(D3DXVec3Dot(&m_vector.right, D3DXVec3Normalize(&vecAxis, &axis)));

		AddRotation(D3DXVECTOR3(0, fVec3Dot * angle, 0));
	}

	void Transform::AddRotationZ(const D3DXVECTOR3& axis, float angle)
	{
		D3DXVECTOR3 vecAxis;

		// 外積を求めます
		m_vector.CrossRight();

		// 角度を求める
		float fVec3Dot = atanf(D3DXVec3Dot(&m_vector.front, D3DXVec3Normalize(&vecAxis, &axis)));

		AddRotation(D3DXVECTOR3(0, 0, fVec3Dot * angle));
	}

	void Transform::AddRotationXYZ(const D3DXVECTOR3& X, const D3DXVECTOR3& Y, const D3DXVECTOR3& Z, float angle)
	{
		D3DXVECTOR3 vecAxis, rotation;

		// 外積を求めます
		m_vector.CrossRight();

		// 角度を求める
		rotation.x = atanf(D3DXVec3Dot(&m_vector.right, D3DXVec3Normalize(&vecAxis, &X)));
		rotation.y = atanf(D3DXVec3Dot(&m_vector.right, D3DXVec3Normalize(&vecAxis, &Y)));
		rotation.z = atanf(D3DXVec3Dot(&m_vector.front, D3DXVec3Normalize(&vecAxis, &Z)));

		AddRotation(rotation * angle);
	}

	void Transform::AddRotationXY(const D3DXVECTOR2& X, const D3DXVECTOR2& Y, float angle)
	{
		AddRotationXYZ(D3DXVECTOR3(X.x, X.y, 0), D3DXVECTOR3(Y.x, Y.y, 0), D3DXVECTOR3(0, 0, 0), angle);
	}

	void Transform::AddRotationLimitY(float y, float limit)
	{
		D3DXMATRIX Rot;
		D3DXVECTOR3 Vec, dir = D3DXVECTOR3(0, 1.0f, 0);

		D3DXMatrixRotationAxis(&Rot, m_vector.CrossRight(), limit);
		D3DXVec3TransformNormal(&Vec, &m_vector.front, &Rot);
		float fVec3Dot = atanf(D3DXVec3Dot(&Vec, &dir));

		if (-limit < fVec3Dot && limit>fVec3Dot)
		{
			AddRotation(D3DXVECTOR3(0, y, 0));
		}
	}

	D3DXMATRIX* Transform::CreateWorldMatrix()
	{
		if (m_transform_parent == nullptr)
		{
			m_transform_parent = GetComponentParent<Transform>();
			if (m_transform_parent == nullptr)
				m_transform_parent = ThisComponent<Transform>();
		}

		if (m_transform_parent->GetThisPtr() == this) {
			if (!m_update_flag)
				return &m_world_matrix;
		}
		else {
			if (!m_update_flag && !m_transform_parent->m_update_flag)
				return &m_world_matrix;
		}

		CreateLocalMatrix();

		// 親オブジェクトと合成
		if (m_transform_parent->GetThisPtr() != this)
		{
			// 自身のローカル姿勢と親のワールド変換行列の掛け算
			m_world_matrix = m_local_matrix * m_transform_parent->m_world_matrix;

			// 合成後に、値が反転するため再度反転
			m_world_matrix._11 = -m_world_matrix._11;
			m_world_matrix._12 = -m_world_matrix._12;
			m_world_matrix._13 = -m_world_matrix._13;
			m_world_matrix._31 = -m_world_matrix._31;
			m_world_matrix._32 = -m_world_matrix._32;
			m_world_matrix._33 = -m_world_matrix._33;
		}

		m_update_flag = true;

		return &m_world_matrix;
	}

	D3DXMATRIX* Transform::CreateLocalMatrix()
	{
		if (!m_update_flag)
			return &m_local_matrix;

		D3DXMATRIX MatRot;

		m_look.MatrixEyeAtUp(MatRot);

		m_local_matrix._11 = m_parameter.scale.x * MatRot._11;
		m_local_matrix._12 = m_parameter.scale.x * MatRot._12;
		m_local_matrix._13 = m_parameter.scale.x * MatRot._13;

		m_local_matrix._21 = m_parameter.scale.y * MatRot._21;
		m_local_matrix._22 = m_parameter.scale.y * MatRot._22;
		m_local_matrix._23 = m_parameter.scale.y * MatRot._23;

		m_local_matrix._31 = m_parameter.scale.z * MatRot._31;
		m_local_matrix._32 = m_parameter.scale.z * MatRot._32;
		m_local_matrix._33 = m_parameter.scale.z * MatRot._33;

		m_local_matrix._41 = m_parameter.position.x;
		m_local_matrix._42 = m_parameter.position.y;
		m_local_matrix._43 = m_parameter.position.z;

		m_local_matrix._14 = m_local_matrix._24 = m_local_matrix._34 = 0.0f;
		m_local_matrix._44 = 1.0f;

		m_world_matrix = m_local_matrix;

		return &m_world_matrix;
	}

	D3DXMATRIX* Transform::CreateWorldViewMatrix()
	{
		if (!m_update_flag)
			return &m_world_matrix;

		if (m_view_matrix == nullptr)
			return CreateWorldMatrix();

		D3DXMATRIX MtxView;

		D3DXMatrixTranspose(&MtxView, m_view_matrix);
		MtxView._14 = 0.0f;
		MtxView._24 = 0.0f;
		MtxView._34 = 0.0f;

		CreateWorldMatrix();

		// 合成後に、値が反転するため再度反転
		m_world_matrix._11 = -m_world_matrix._11;
		m_world_matrix._12 = -m_world_matrix._12;
		m_world_matrix._13 = -m_world_matrix._13;
		m_world_matrix._31 = -m_world_matrix._31;
		m_world_matrix._32 = -m_world_matrix._32;
		m_world_matrix._33 = -m_world_matrix._33;

		m_world_matrix = MtxView * m_world_matrix;

		return &m_world_matrix;
	}

	D3DXMATRIX* Transform::CreateLocalViewMatrix()
	{
		if (!m_update_flag)
			return &m_local_matrix;

		if (m_view_matrix == nullptr)
			return CreateLocalMatrix();

		D3DXMATRIX MtxView;

		D3DXMatrixTranspose(&MtxView, m_view_matrix);
		MtxView._14 = 0.0f;
		MtxView._24 = 0.0f;
		MtxView._34 = 0.0f;

		CreateLocalMatrix();

		m_local_matrix = MtxView * m_local_matrix;

		return &m_local_matrix; // 行列の合成
	}

	void Transform::SetUpdateKey(bool _flag)
	{
		m_update_flag = _flag;
	}

	bool Transform::GetUpdateKey()
	{
		return m_update_flag;
	}

	D3DXVECTOR3 Transform::ToSee(const D3DXMATRIX* _mat)
	{
		CreateWorldMatrix();
		return D3DXVECTOR3(_mat->_41, _mat->_42, _mat->_43) -
			D3DXVECTOR3(m_world_matrix._41, m_world_matrix._42, m_world_matrix._43);
	}

	D3DXVECTOR3 Transform::ToRadian(const D3DXVECTOR3& degree)
	{
		return D3DXVECTOR3(D3DXToRadian(degree.x), D3DXToRadian(degree.y), D3DXToRadian(degree.z));
	}

	D3DXVECTOR3 Transform::ToRadian(float x, float y, float z)
	{
		return ToRadian(D3DXVECTOR3(x, y, z));
	}

	D3DXVECTOR3 Transform::ToDegree(const D3DXVECTOR3& radian)
	{
		return D3DXVECTOR3(D3DXToDegree(radian.x), D3DXToDegree(radian.y), D3DXToDegree(radian.z));
	}

	D3DXVECTOR3 Transform::ToDegree(float x, float y, float z)
	{
		return ToDegree(D3DXVECTOR3(x, y, z));
	}

	void Transform::CopyTransform(reference::IReference<Transform> _trans)
	{
		if (_trans == nullptr)
			return;

		m_look = _trans->m_look;
		m_vector = _trans->m_vector;
		m_parameter = _trans->m_parameter;
	}

	void Transform::SetTransformParent()
	{
		m_transform_parent.clear();
	}

	D3DXVECTOR3 Transform::GetMatrixOffset()
	{
		return D3DXVECTOR3(m_world_matrix._41, m_world_matrix._42, m_world_matrix._43);
	}

	D3DXVECTOR3 Transform::GetMatrixScale()
	{
		D3DXVECTOR3 sX = D3DXVECTOR3(m_world_matrix._11, m_world_matrix._12, m_world_matrix._13);
		D3DXVECTOR3 sY = D3DXVECTOR3(m_world_matrix._21, m_world_matrix._22, m_world_matrix._23);
		D3DXVECTOR3 sZ = D3DXVECTOR3(m_world_matrix._31, m_world_matrix._32, m_world_matrix._33);
		return D3DXVECTOR3(D3DXVec3Length(&sX), D3DXVec3Length(&sY), D3DXVec3Length(&sZ));
	}

	Transform* Transform::GetThisPtr()
	{
		return this;
	}

	void Transform::GUITransform()
	{
#if defined(_MSLIB_DEBUG)
		if (!imgui::NewTreeNode("Transform", false))
			return;

		constexpr float move_buff = 0.1f;
		float float3x3[3][3] = { 0.0f };
		
		auto pos_slider = imgui::CreateText("Slider : Position");
		auto rot_slider = imgui::CreateText("Slider : Rotation");
		auto sca_slider = imgui::CreateText("Slider : Scale");
		auto pos_input = imgui::CreateText("Input : Position");
		auto rot_input = imgui::CreateText("Input : Rotation");
		auto sca_input = imgui::CreateText("Input : Scale");

		imgui::Separator();

		if (imgui::_SliderFloat3(pos_slider.c_str(), float3x3[0], -move_buff, move_buff))
			AddPosition(D3DXVECTOR3(float3x3[0][0], float3x3[0][1], float3x3[0][2]));
		if (imgui::_SliderFloat3(rot_slider.c_str(), float3x3[1], -move_buff, move_buff))
			AddRotation(D3DXVECTOR3(float3x3[1][0], float3x3[1][1], float3x3[1][2]));
		if (imgui::_SliderFloat3(sca_slider.c_str(), float3x3[2], -move_buff, move_buff))
			AddScale(D3DXVECTOR3(float3x3[2][0], float3x3[2][1], float3x3[2][2]));

		float3x3[0][0] = m_parameter.position.x;
		float3x3[0][1] = m_parameter.position.y;
		float3x3[0][2] = m_parameter.position.z;
		float3x3[1][0] = mslib::ToDegree(m_parameter.rotation.x);
		float3x3[1][1] = mslib::ToDegree(m_parameter.rotation.y);
		float3x3[1][2] = mslib::ToDegree(m_parameter.rotation.z);
		float3x3[2][0] = m_parameter.scale.x;
		float3x3[2][1] = m_parameter.scale.y;
		float3x3[2][2] = m_parameter.scale.z;

		if (imgui::_InputFloat3(pos_input.c_str(), float3x3[0], ImGuiInputTextFlags_EnterReturnsTrue))
			SetPosition(D3DXVECTOR3(float3x3[0][0], float3x3[0][1], float3x3[0][2]));
		if (imgui::_InputFloat3(rot_input.c_str(), float3x3[1], ImGuiInputTextFlags_EnterReturnsTrue))
			SetRotation(D3DXVECTOR3(mslib::ToRadian(float3x3[1][0]), mslib::ToRadian(float3x3[1][1]), mslib::ToRadian(float3x3[1][2])));
		if (imgui::_InputFloat3(sca_input.c_str(), float3x3[2], ImGuiInputTextFlags_EnterReturnsTrue))
			SetScale(D3DXVECTOR3(float3x3[2][0], float3x3[2][1], float3x3[2][2]));

		// パラメーターの表示
		if (imgui::NewTreeNode("Info", false))
		{
			auto pos_text = imgui::CreateText("Position : X[%.2f],Y[%.2f],Z[%.2f]", float3x3[0][0], float3x3[0][1], float3x3[0][2]);
			auto rot_text = imgui::CreateText("Rotation : X[%.2f],Y[%.2f],Z[%.2f]", mslib::ToRadian(float3x3[1][0]), mslib::ToRadian(float3x3[1][1]), mslib::ToRadian(float3x3[1][2]));
			auto sca_text = imgui::CreateText("Scale : X[%.2f],Y[%.2f],Z[%.2f]", float3x3[2][0], float3x3[2][1], float3x3[2][2]);

			auto mat_w_1 = imgui::CreateText("11[%.2f],12[%.2f],13[%.2f],14[%.2f]", m_world_matrix._11, m_world_matrix._12, m_world_matrix._13, m_world_matrix._14);
			auto mat_w_2 = imgui::CreateText("21[%.2f],22[%.2f],23[%.2f],24[%.2f]", m_world_matrix._21, m_world_matrix._22, m_world_matrix._23, m_world_matrix._24);
			auto mat_w_3 = imgui::CreateText("31[%.2f],32[%.2f],33[%.2f],34[%.2f]", m_world_matrix._31, m_world_matrix._32, m_world_matrix._33, m_world_matrix._34);
			auto mat_w_4 = imgui::CreateText("41[%.2f],42[%.2f],43[%.2f],44[%.2f]", m_world_matrix._41, m_world_matrix._42, m_world_matrix._43, m_world_matrix._44);

			auto mat_l_1 = imgui::CreateText("11[%.2f],12[%.2f],13[%.2f],14[%.2f]", m_local_matrix._11, m_local_matrix._12, m_local_matrix._13, m_local_matrix._14);
			auto mat_l_2 = imgui::CreateText("21[%.2f],22[%.2f],23[%.2f],24[%.2f]", m_local_matrix._21, m_local_matrix._22, m_local_matrix._23, m_local_matrix._24);
			auto mat_l_3 = imgui::CreateText("31[%.2f],32[%.2f],33[%.2f],34[%.2f]", m_local_matrix._31, m_local_matrix._32, m_local_matrix._33, m_local_matrix._34);
			auto mat_l_4 = imgui::CreateText("41[%.2f],42[%.2f],43[%.2f],44[%.2f]", m_local_matrix._41, m_local_matrix._42, m_local_matrix._43, m_local_matrix._44);

			imgui::Separator();
			imgui::Text("Parameter");
			imgui::Separator();
			imgui::Text(pos_text);
			imgui::Text(rot_text);
			imgui::Text(sca_text);
			imgui::Separator();
			imgui::Text("World Matrix");
			imgui::Separator();
			imgui::Text(mat_w_1);
			imgui::Text(mat_w_2);
			imgui::Text(mat_w_3);
			imgui::Text(mat_w_4);
			imgui::Separator();
			imgui::Text("Local Matrix");
			imgui::Separator();
			imgui::Text(mat_l_1);
			imgui::Text(mat_l_2);
			imgui::Text(mat_l_3);
			imgui::Text(mat_l_4);
			imgui::EndTreeNode();
		}
		imgui::Separator();
		imgui::EndTreeNode();
#endif
	}

	void Transform::InputDataTransform(std::ifstream& _ifstream)
	{
		std::vector<float> i_position;
		std::vector<float> i_rotation;
		std::vector<float> i_scale;
		std::string line_str;
		float ftemp;

		// 開始位置に
		_ifstream.clear();
		_ifstream.seekg(0, std::ios_base::beg);

		// 列ごとの読み取り
		while (std::getline(_ifstream, line_str))
		{
			// #はコメント
			if (line_str[0] == '#')
				continue;
			// 入力命令
			if (line_str.find('=') == std::string::npos)
				continue;

			std::stringstream ss_str(line_str);
			std::string name_str;

			ss_str >> name_str;
			ss_str.ignore(line_str.size(), '=');

			if (name_str == "Transform_Position")
			{
				while (ss_str >> ftemp)
					i_position.push_back(ftemp);
			}
			else if (name_str == "Transform_Rotation")
			{
				while (ss_str >> ftemp)
					i_rotation.push_back(ftemp);
			}
			else if (name_str == "Transform_Scale")
			{
				while (ss_str >> ftemp)
					i_scale.push_back(ftemp);
			}
		}

		if ((int)i_position.size() == 0)
			return;

		// 読み取ったデータを反映
		SetPosition(i_position[0], i_position[1], i_position[2]);
		SetRotation(i_rotation[0], i_rotation[1], i_rotation[2]);
		SetScale(i_scale[0], i_scale[1], i_scale[2]);
	}

	void Transform::OutputDataTransform(std::ofstream& _ofstream)
	{
		auto& p3 = m_parameter.position;
		auto& r3 = m_parameter.rotation;
		auto& s3 = m_parameter.scale;

		auto pos_str = std::string("Transform_Position =") + " " + std::to_string(p3.x) + " " + std::to_string(p3.y) + " " + std::to_string(p3.z);
		auto rot_str = std::string("Transform_Rotation =") + " " + std::to_string(r3.x) + " " + std::to_string(r3.y) + " " + std::to_string(r3.z);
		auto sca_str = std::string("Transform_Scale =") + " " + std::to_string(s3.x) + " " + std::to_string(s3.y) + " " + std::to_string(s3.z);

		_ofstream << std::string("#Set Transform_Position") << std::endl;
		_ofstream << pos_str << std::endl;
		_ofstream << std::string("#Set Transform_Rotation") << std::endl;
		_ofstream << rot_str << std::endl;
		_ofstream << std::string("#Set Transform_Scale") << std::endl;
		_ofstream << sca_str << std::endl;
	}
}

_MSLIB_END