//==========================================================================
// dx9math [dx9math.cpp]
// Content : math types and functions
// author : MasyoLab
//==========================================================================
#include "dx9math.h"

_MSLIB_BEGIN

namespace math
{
	Vector2::Vector2()
	{
		x = y = 0.0f;
	}
	Vector2::~Vector2() {}
	Vector2& Vector2::operator+=(const D3DXVECTOR2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2& Vector2::operator-=(const D3DXVECTOR2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vector2 Vector2::operator+() const
	{
		return *this;
	}
	Vector2 Vector2::operator-() const
	{
		return Vector2(-x, -y);
	}
	void Vector2::operator()()
	{
		x = y = 0.0f;
	}
	void Vector2::operator()(const FLOAT* f)
	{
		*this = Vector2(f);
	}
	void Vector2::operator()(const D3DXFLOAT16* m)
	{
		*this = Vector2(m);
	}
	void Vector2::operator()(FLOAT fx, FLOAT fy)
	{
		*this = Vector2(fx, fy);
	}
	void Vector2::operator()(D3DXVECTOR2& v)
	{
		*this = Vector2(v.x, v.y);
	}
	Vector2& Vector2::operator++()
	{
		x++;
		y++;
		return *this;
	}
	Vector2& Vector2::operator--()
	{
		x--;
		y--;
		return *this;
	}
	Vector2 Vector2::operator++(int)
	{
		auto out = *this;
		++* this;
		return out;
	}
	Vector2 Vector2::operator--(int)
	{
		auto out = *this;
		--* this;
		return out;
	}
	D3DXVECTOR2& Vector2::operator=(const Vector2& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	Vector2& Vector2::operator=(const D3DXVECTOR2& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	Vector2& Vector2::operator=(const float f)
	{
		x = y = f;
		return *this;
	}
	Vector3::Vector3()
	{
		x = y = z = 0.0f;
	}
	Vector3::~Vector3() {}
	Vector3& Vector3::operator+=(const D3DXVECTOR3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vector3& Vector3::operator-=(const D3DXVECTOR3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	void Vector3::operator()()
	{
		x = y = z = 0.0f;
	}
	void Vector3::operator()(const FLOAT* f)
	{
		*this = Vector3(f);
	}
	void Vector3::operator()(const D3DVECTOR& v)
	{
		*this = Vector3(v);
	}
	void Vector3::operator()(const D3DXFLOAT16* m)
	{
		*this = Vector3(m);
	}
	void Vector3::operator()(FLOAT fx, FLOAT fy, FLOAT fz)
	{
		*this = Vector3(fx, fy, fz);
	}
	void Vector3::operator()(D3DXVECTOR3& v)
	{
		*this = Vector3(v.x, v.y, v.z);
	}
	Vector3 Vector3::operator+() const
	{
		return *this;
	}
	Vector3 Vector3::operator-() const
	{
		return D3DXVECTOR3(-x, -y, -z);
	}
	Vector3& Vector3::operator++()
	{
		x++;
		y++;
		z++;
		return *this;
	}
	Vector3& Vector3::operator--()
	{
		x--;
		y--;
		z--;
		return *this;
	}
	Vector3 Vector3::operator++(int)
	{
		auto out = *this;
		++* this;
		return out;
	}
	Vector3 Vector3::operator--(int)
	{
		auto out = *this;
		--* this;
		return out;
	}
	Vector3& Vector3::operator=(const Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	Vector3& Vector3::operator=(const D3DXVECTOR3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	Vector3& Vector3::operator=(const float f)
	{
		x = y = z = f;
		return *this;
	}
	Vector4::Vector4()
	{
		x = y = z = w = 0.0f;
	}
	Vector4::~Vector4() {}
	Vector4& Vector4::operator+=(const D3DXVECTOR4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	Vector4& Vector4::operator-=(const D3DXVECTOR4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	void Vector4::operator()()
	{
		x = y = z = w = 0.0f;
	}
	void Vector4::operator()(const FLOAT* f)
	{
		*this = Vector4(f);
	}
	void Vector4::operator()(const D3DXFLOAT16* f)
	{
		*this = Vector4(f);
	}
	void Vector4::operator()(const D3DVECTOR& xyz, FLOAT fw)
	{
		*this = Vector4(xyz, fw);
	}
	void Vector4::operator()(FLOAT fx, FLOAT fy, FLOAT fz, FLOAT fw)
	{
		*this = Vector4(fx, fy, fz, fw);
	}
	void Vector4::operator()(D3DXVECTOR4& v)
	{
		*this = Vector4(v.x, v.y, v.z, v.w);
	}
	Vector4 Vector4::operator+() const
	{
		return *this;
	}
	Vector4 Vector4::operator-() const
	{
		return Vector4(-x, -y, -z, -w);
	}
	Vector4& Vector4::operator++()
	{
		x++;
		y++;
		z++;
		w++;
		return *this;
	}
	Vector4& Vector4::operator--()
	{
		x--;
		y--;
		z--;
		w--;
		return *this;
	}
	Vector4 Vector4::operator++(int)
	{
		auto out = *this;
		++* this;
		return out;
	}
	Vector4 Vector4::operator--(int)
	{
		auto out = *this;
		--* this;
		return out;
	}
	Vector4& Vector4::operator=(const Vector4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}
	Vector4& Vector4::operator=(const D3DXVECTOR4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}
	Vector4& Vector4::operator=(const float f)
	{
		x = y = z = w = f;
		return *this;
	}
	Matrix::Matrix()
	{
		D3DXMatrixIdentity(this);
	}
	Matrix::~Matrix() {}
	Matrix& Matrix::operator+=(const D3DXMATRIX& mat)
	{
		_11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
		_21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
		_31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
		_41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;
		return *this;
	}
	Matrix& Matrix::operator-=(const D3DXMATRIX& mat)
	{
		_11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
		_21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
		_31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
		_41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;
		return *this;
	}
	Matrix& Matrix::operator*=(const D3DXMATRIX& mat)
	{
		D3DXMatrixMultiply(this, this, &mat);
		return *this;
	}
	void Matrix::operator()()
	{
		D3DXMatrixIdentity(this);
	}
	void Matrix::operator()(const FLOAT* f)
	{
		*this = Matrix(f);
	}
	void Matrix::operator()(const D3DMATRIX& mat)
	{
		*this = Matrix(mat);
	}
	void Matrix::operator()(const D3DXFLOAT16* f)
	{
		*this = Matrix(f);
	}
	void Matrix::operator()(FLOAT f11, FLOAT f12, FLOAT f13, FLOAT f14, FLOAT f21, FLOAT f22, FLOAT f23, FLOAT f24, FLOAT f31, FLOAT f32, FLOAT f33, FLOAT f34, FLOAT f41, FLOAT f42, FLOAT f43, FLOAT f44)
	{
		*this = Matrix(
			f11, f12, f13, f14,
			f21, f22, f23, f24,
			f31, f32, f33, f34,
			f41, f42, f43, f44);
	}
	void Matrix::operator()(D3DXMATRIX& mat)
	{
		_11 = mat._11; _12 = mat._12; _13 = mat._13; _14 = mat._14;
		_21 = mat._21; _22 = mat._22; _23 = mat._23; _24 = mat._24;
		_31 = mat._31; _32 = mat._32; _33 = mat._33; _34 = mat._34;
		_41 = mat._41; _42 = mat._42; _43 = mat._43; _44 = mat._44;
	}
	Matrix Matrix::operator+() const
	{
		return *this;
	}
	Matrix Matrix::operator-() const
	{
		return Matrix(
			-_11, -_12, -_13, -_14,
			-_21, -_22, -_23, -_24,
			-_31, -_32, -_33, -_34,
			-_41, -_42, -_43, -_44);
	}
	Matrix& Matrix::operator=(const Matrix& mat)
	{
		_11 = mat._11; _12 = mat._12; _13 = mat._13; _14 = mat._14;
		_21 = mat._21; _22 = mat._22; _23 = mat._23; _24 = mat._24;
		_31 = mat._31; _32 = mat._32; _33 = mat._33; _34 = mat._34;
		_41 = mat._41; _42 = mat._42; _43 = mat._43; _44 = mat._44;
		return *this;
	}
	Matrix& Matrix::operator=(const D3DXMATRIX& mat)
	{
		_11 = mat._11; _12 = mat._12; _13 = mat._13; _14 = mat._14;
		_21 = mat._21; _22 = mat._22; _23 = mat._23; _24 = mat._24;
		_31 = mat._31; _32 = mat._32; _33 = mat._33; _34 = mat._34;
		_41 = mat._41; _42 = mat._42; _43 = mat._43; _44 = mat._44;
		return *this;
	}
	Matrix& Matrix::operator=(const float f)
	{
		_11 = f; _12 = f; _13 = f; _14 = f;
		_21 = f; _22 = f; _23 = f; _24 = f;
		_31 = f; _32 = f; _33 = f; _34 = f;
		_41 = f; _42 = f; _43 = f; _44 = f;
		return *this;
	}
	Quaternion::Quaternion()
	{
		D3DXQuaternionIdentity(this);
	}
	Quaternion::~Quaternion()
	{
	}
	Quaternion& Quaternion::operator+=(const D3DXQUATERNION& q)
	{
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;
		return *this;
	}
	Quaternion& Quaternion::operator-=(const D3DXQUATERNION& q)
	{
		x -= q.x;
		y -= q.y;
		z -= q.z;
		w -= q.w;
		return *this;
	}
	Quaternion& Quaternion::operator*=(const D3DXQUATERNION& q)
	{
		D3DXQuaternionMultiply(this, this, &q);
		return *this;
	}
	void Quaternion::operator()()
	{
		D3DXQuaternionIdentity(this);
	}
	void Quaternion::operator()(const FLOAT* f)
	{
		*this = Quaternion(f);
	}
	void Quaternion::operator()(const D3DXFLOAT16* f)
	{
		*this = Quaternion(f);
	}
	void Quaternion::operator()(FLOAT fx, FLOAT fy, FLOAT fz, FLOAT fw)
	{
		*this = Quaternion(fx, fy, fz, fw);
	}
	void Quaternion::operator()(D3DXQUATERNION& q)
	{
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
	}
	Quaternion Quaternion::operator+() const
	{
		return *this;
	}
	Quaternion Quaternion::operator-() const
	{
		return Quaternion(-x, -y, -z, -w);
	}
	Quaternion& Quaternion::operator=(const Quaternion& q)
	{
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
		return *this;
	}
	Quaternion& Quaternion::operator=(const D3DXQUATERNION& q)
	{
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;
		return *this;
	}
	Quaternion& Quaternion::operator=(const float f)
	{
		x = y = z = w = f;
		return *this;
	}
	Plane::Plane()
	{
		a = b = c = d = 0.0f;
	}
	Plane::~Plane()
	{
	}
	void Plane::operator()()
	{
		a = b = c = d = 0.0f;
	}
	void Plane::operator()(const FLOAT* f)
	{
		*this = Plane(f);
	}
	void Plane::operator()(const D3DXFLOAT16* f)
	{
		*this = Plane(f);
	}
	void Plane::operator()(FLOAT fa, FLOAT fb, FLOAT fc, FLOAT fd)
	{
		*this = Plane(fa, fb, fc, fd);
	}
	void Plane::operator()(D3DXPLANE& p)
	{
		a = p.a;
		b = p.b;
		c = p.c;
		d = p.d;
	}
	Plane Plane::operator+() const
	{
		return *this;
	}
	Plane Plane::operator-() const
	{
		return Plane(-a, -b, -c, -d);
	}
	Plane& Plane::operator=(const Plane& p)
	{
		a = p.a;
		b = p.b;
		c = p.c;
		d = p.d;
		return *this;
	}
	Plane& Plane::operator=(const D3DXPLANE& p)
	{
		a = p.a;
		b = p.b;
		c = p.c;
		d = p.d;
		return *this;
	}
	Plane& Plane::operator=(const float f)
	{
		a = f;
		b = f;
		c = f;
		d = f;
		return *this;
	}
	Color::Color()
	{
		r = g = b = a = 0.0f;
	}
	Color::~Color()
	{
	}
	Color& Color::operator+=(const D3DXCOLOR& c)
	{
		r += c.r;
		g += c.g;
		b += c.b;
		a += c.a;
		return *this;
	}
	Color& Color::operator-=(const D3DXCOLOR& c)
	{
		r -= c.r;
		g -= c.g;
		b -= c.b;
		a -= c.a;
		return *this;
	}
	void Color::operator()()
	{
		r = g = b = a = 0.0f;
	}
	void Color::operator()(DWORD argb)
	{
		*this = Color(argb);
	}
	void Color::operator()(const FLOAT* f)
	{
		*this = Color(f);
	}
	void Color::operator()(const D3DXFLOAT16* f)
	{
		*this = Color(f);
	}
	void Color::operator()(const D3DCOLORVALUE& c)
	{
		*this = Color(c);
	}
	void Color::operator()(FLOAT fr, FLOAT fg, FLOAT fb, FLOAT fa)
	{
		*this = Color(fr, fg, fb, fa);
	}
	void Color::operator()(D3DXCOLOR& c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
		a = c.a;
	}
	Color Color::operator+() const
	{
		return *this;
	}
	Color Color::operator-() const
	{
		return Color(-r, -g, -b, -a);
	}
	Color& Color::operator=(const Color& c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
		a = c.a;
		return *this;
	}
	Color& Color::operator=(const D3DXCOLOR& c)
	{
		r = c.r;
		g = c.g;
		b = c.b;
		a = c.a;
		return *this;
	}
	Color& Color::operator=(D3DXCOLOR&& c)
	{
		auto  c_ = std::move(c);
		r = c_.r;
		g = c_.g;
		b = c_.b;
		a = c_.a;
		return *this;
	}
}

_MSLIB_END