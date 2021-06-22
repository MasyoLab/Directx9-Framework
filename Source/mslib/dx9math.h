//==========================================================================
// dx9math [dx9math.h]
// Content : math types and functions
// author : MasyoLab
//==========================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "mslib.hpp"

_MSLIB_BEGIN

namespace math
{
	//==========================================================================
	//
	// class : Vector2
	//
	//==========================================================================
	class Vector2 :
		public D3DXVECTOR2
	{
	public:
		Vector2();
		~Vector2();

		// constructor
		using D3DXVECTOR2::D3DXVECTOR2;

		// casting
		using D3DXVECTOR2::operator const FLOAT*;
		using D3DXVECTOR2::operator FLOAT*;

		// assignment operators
		using D3DXVECTOR2::operator+=;
		using D3DXVECTOR2::operator-=;
		using D3DXVECTOR2::operator*=;
		using D3DXVECTOR2::operator/=;
		Vector2& operator += (const D3DXVECTOR2&);
		Vector2& operator -= (const D3DXVECTOR2&);

		// binary operators
		using D3DXVECTOR2::operator+;
		using D3DXVECTOR2::operator-;
		using D3DXVECTOR2::operator*;
		using D3DXVECTOR2::operator/;

		using D3DXVECTOR2::operator==;
		using D3DXVECTOR2::operator!=;

		// unary operators
		Vector2 operator + () const;
		Vector2 operator - () const;

		// initializer Operators
		void operator () ();
		void operator () (const FLOAT*);
		void operator () (const D3DXFLOAT16*);
		void operator () (FLOAT, FLOAT);
		void operator () (D3DXVECTOR2&);

		// Prefix Increment / Decremrnt
		Vector2& operator ++ ();
		Vector2& operator -- ();
		Vector2 operator ++ (int);
		Vector2 operator -- (int);

		// Assignment Operators
		D3DXVECTOR2& operator = (const Vector2&);
		Vector2& operator = (const D3DXVECTOR2&);
		Vector2& operator = (const float);
	};

	//==========================================================================
	//
	// class : Vector3
	//
	//==========================================================================
	class Vector3 :
		public D3DXVECTOR3
	{
	public:
		Vector3();
		~Vector3();

		// constructor
		using D3DXVECTOR3::D3DXVECTOR3;

		// casting
		using D3DXVECTOR3::operator const FLOAT*;
		using D3DXVECTOR3::operator FLOAT*;

		// assignment operators
		using D3DXVECTOR3::operator+=;
		using D3DXVECTOR3::operator-=;
		using D3DXVECTOR3::operator*=;
		using D3DXVECTOR3::operator/=;
		Vector3& operator += (const D3DXVECTOR3&);
		Vector3& operator -= (const D3DXVECTOR3&);

		// binary operators
		using D3DXVECTOR3::operator+;
		using D3DXVECTOR3::operator-;
		using D3DXVECTOR3::operator*;
		using D3DXVECTOR3::operator/;

		using D3DXVECTOR3::operator==;
		using D3DXVECTOR3::operator!=;

		// initializer Operators
		void operator () ();
		void operator () (const FLOAT*);
		void operator () (const D3DVECTOR&);
		void operator () (const D3DXFLOAT16*);
		void operator () (FLOAT, FLOAT, FLOAT);
		void operator () (D3DXVECTOR3&);

		// unary operators
		Vector3 operator + () const;
		Vector3 operator - () const;

		// Prefix Increment / Decremrnt
		Vector3& operator ++ ();
		Vector3& operator -- ();
		Vector3 operator ++ (int);
		Vector3 operator -- (int);

		// Assignment Operators
		Vector3& operator = (const Vector3&);
		Vector3& operator = (const D3DXVECTOR3&);
		Vector3& operator = (const float);
	};

	//==========================================================================
	//
	// class : Vector4
	//
	//==========================================================================
	class Vector4 :
		public D3DXVECTOR4
	{
	public:
		Vector4();
		~Vector4();

		// constructor
		using D3DXVECTOR4::D3DXVECTOR4;

		// casting
		using D3DXVECTOR4::operator const FLOAT*;
		using D3DXVECTOR4::operator FLOAT*;

		// assignment operators
		using D3DXVECTOR4::operator+=;
		using D3DXVECTOR4::operator-=;
		using D3DXVECTOR4::operator*=;
		using D3DXVECTOR4::operator/=;
		Vector4& operator += (const D3DXVECTOR4&);
		Vector4& operator -= (const D3DXVECTOR4&);

		// binary operators
		using D3DXVECTOR4::operator+;
		using D3DXVECTOR4::operator-;
		using D3DXVECTOR4::operator*;
		using D3DXVECTOR4::operator/;

		using D3DXVECTOR4::operator==;
		using D3DXVECTOR4::operator!=;

		// initializer Operators
		void operator () ();
		void operator () (const FLOAT*);
		void operator () (const D3DXFLOAT16*);
		void operator () (const D3DVECTOR&, FLOAT);
		void operator () (FLOAT, FLOAT, FLOAT, FLOAT);
		void operator () (D3DXVECTOR4&);

		// unary operators
		Vector4 operator + () const;
		Vector4 operator - () const;

		// Prefix Increment / Decremrnt
		Vector4& operator ++ ();
		Vector4& operator -- ();
		Vector4 operator ++ (int);
		Vector4 operator -- (int);

		// Assignment Operators
		Vector4& operator = (const Vector4&);
		Vector4& operator = (const D3DXVECTOR4&);
		Vector4& operator = (const float);
	};

	//==========================================================================
	//
	// class : Matrix
	//
	//==========================================================================
	class Matrix :
		public D3DXMATRIX
	{
	public:
		Matrix();
		~Matrix();

		// constructor
		using D3DXMATRIX::D3DXMATRIX;

		// access grants
		using D3DXMATRIX::operator();

		// casting operators
		using D3DXMATRIX::operator const FLOAT*;
		using D3DXMATRIX::operator FLOAT*;

		// assignment operators
		using D3DXMATRIX::operator+=;
		using D3DXMATRIX::operator-=;
		using D3DXMATRIX::operator*=;
		using D3DXMATRIX::operator/=;
		Matrix& operator += (const D3DXMATRIX&);
		Matrix& operator -= (const D3DXMATRIX&);
		Matrix& operator *= (const D3DXMATRIX&);

		// binary operators
		using D3DXMATRIX::operator+;
		using D3DXMATRIX::operator-;
		using D3DXMATRIX::operator*;
		using D3DXMATRIX::operator/;

		using D3DXMATRIX::operator==;
		using D3DXMATRIX::operator!=;

		// initializer Operators
		void operator () ();
		void operator () (const FLOAT*);
		void operator () (const D3DMATRIX&);
		void operator () (const D3DXFLOAT16*);
		void operator () (
			FLOAT, FLOAT, FLOAT, FLOAT,
			FLOAT, FLOAT, FLOAT, FLOAT,
			FLOAT, FLOAT, FLOAT, FLOAT,
			FLOAT, FLOAT, FLOAT, FLOAT);
		void operator () (D3DXMATRIX&);

		// unary operators
		Matrix operator + () const;
		Matrix operator - () const;

		// Assignment Operators
		Matrix& operator = (const Matrix&);
		Matrix& operator = (const D3DXMATRIX&);
		Matrix& operator = (const float);
	};

	//==========================================================================
	//
	// class : Quaternion
	//
	//==========================================================================
	class Quaternion :
		public D3DXQUATERNION
	{
	public:
		Quaternion();
		~Quaternion();

		// constructor
		using D3DXQUATERNION::D3DXQUATERNION;

		// casting
		using D3DXQUATERNION::operator const FLOAT*;
		using D3DXQUATERNION::operator FLOAT*;

		// assignment operators
		using D3DXQUATERNION::operator+=;
		using D3DXQUATERNION::operator-=;
		using D3DXQUATERNION::operator*=;
		using D3DXQUATERNION::operator/=;
		Quaternion& operator += (const D3DXQUATERNION&);
		Quaternion& operator -= (const D3DXQUATERNION&);
		Quaternion& operator *= (const D3DXQUATERNION&);

		// binary operators
		using D3DXQUATERNION::operator+;
		using D3DXQUATERNION::operator-;
		using D3DXQUATERNION::operator*;
		using D3DXQUATERNION::operator/;

		using D3DXQUATERNION::operator==;
		using D3DXQUATERNION::operator!=;

		// initializer Operators
		void operator () ();
		void operator () (const FLOAT*);
		void operator () (const D3DXFLOAT16*);
		void operator () (FLOAT, FLOAT, FLOAT, FLOAT);
		void operator () (D3DXQUATERNION&);

		// unary operators
		Quaternion operator + () const;
		Quaternion operator - () const;

		// Assignment Operators
		Quaternion& operator = (const Quaternion&);
		Quaternion& operator = (const D3DXQUATERNION&);
		Quaternion& operator = (const float);
	};

	//==========================================================================
	//
	// class : Planes
	//
	//==========================================================================
	class Plane :
		public D3DXPLANE
	{
	public:
		Plane();
		~Plane();

		// constructor
		using D3DXPLANE::D3DXPLANE;

		// casting
		using D3DXPLANE::operator const FLOAT*;
		using D3DXPLANE::operator FLOAT*;

		// assignment operators
		using D3DXPLANE::operator*=;
		using D3DXPLANE::operator/=;

		// binary operators
		using D3DXPLANE::operator+;
		using D3DXPLANE::operator-;
		using D3DXPLANE::operator*;
		using D3DXPLANE::operator/;
		using D3DXPLANE::operator==;
		using D3DXPLANE::operator!=;

		// initializer Operators
		void operator () ();
		void operator () (const FLOAT*);
		void operator () (const D3DXFLOAT16*);
		void operator () (FLOAT, FLOAT, FLOAT, FLOAT);
		void operator () (D3DXPLANE&);

		// unary operators
		Plane operator + () const;
		Plane operator - () const;

		// Assignment Operators
		Plane& operator = (const Plane&);
		Plane& operator = (const D3DXPLANE&);
		Plane& operator = (const float);
	};

	//==========================================================================
	//
	// class : Colors
	//
	//==========================================================================
	class Color :
		public D3DXCOLOR
	{
	public:
		Color();
		~Color();

		// constructor
		using D3DXCOLOR::D3DXCOLOR;

		// casting
		using D3DXCOLOR::operator const D3DCOLORVALUE &;
		using D3DXCOLOR::operator const D3DCOLORVALUE*;
		using D3DXCOLOR::operator const FLOAT*;
		using D3DXCOLOR::operator D3DCOLORVALUE &;
		using D3DXCOLOR::operator D3DCOLORVALUE*;
		using D3DXCOLOR::operator DWORD;
		using D3DXCOLOR::operator FLOAT*;

		// assignment operators
		using D3DXCOLOR::operator+=;
		using D3DXCOLOR::operator-=;
		using D3DXCOLOR::operator*=;
		using D3DXCOLOR::operator/=;
		Color& operator += (const D3DXCOLOR&);
		Color& operator -= (const D3DXCOLOR&);

		// binary operators
		using D3DXCOLOR::operator+;
		using D3DXCOLOR::operator-;
		using D3DXCOLOR::operator*;
		using D3DXCOLOR::operator/;

		using D3DXCOLOR::operator==;
		using D3DXCOLOR::operator!=;

		// initializer Operators
		void operator () ();
		void operator () (DWORD);
		void operator () (const FLOAT*);
		void operator () (const D3DXFLOAT16*);
		void operator () (const D3DCOLORVALUE&);
		void operator () (FLOAT, FLOAT, FLOAT, FLOAT);
		void operator () (D3DXCOLOR&);

		// unary operators
		Color operator + () const;
		Color operator - () const;

		// Assignment Operators
		Color& operator = (const Color&);
		Color& operator = (const D3DXCOLOR&);
		Color& operator = (D3DXCOLOR&&);
	};
}

_MSLIB_END