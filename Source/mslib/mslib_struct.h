//==========================================================================
// mslib_struct.h [mslib_struct.h]
// author : MasyoLab
//==========================================================================
#pragma once

#include <Windows.h>
#include <cstddef> 

#include "mslib.hpp"

_MSLIB_BEGIN

namespace mslib_struct
{
	//==========================================================================
	// Declaration
	//==========================================================================

	//==========================================================================
	//
	// class : UV
	// Content : UV
	// how to use : UV<float>,UV<int>,UV<double>...
	//
	//==========================================================================
	template<typename types>
	class UV
	{
	public:
		UV() :
			u0(0), v0(0), u1(0), v1(0) {}
		UV(types _u0, types _v0, types _u1, types _v1) :
			u0(_u0), v0(_v0), u1(_u1), v1(_v1) {}
		UV(const UV& v) :
			u0(v.u0), v0(v.v0), u1(v.u1), v1(v.v1) {}
		~UV() {}

		// Member Selection
		const UV* operator->() const noexcept;
		// Member Selection
		UV* operator->() noexcept;

		// Compare
		bool operator<(const UV&);
		// Compare
		bool operator>(const UV&);
		// Compare
		bool operator<=(const UV&);
		// Compare
		bool operator>=(const UV&);
		// Equality Compare
		bool operator == (const UV&) const;
		// Equality Compare
		bool operator != (const UV&) const;

		// Compare
		bool operator<(const types);
		// Compare
		bool operator>(const types);
		// Compare
		bool operator<=(const types);
		// Compare
		bool operator>=(const types);
		// Equality Compare
		bool operator == (const types) const;
		// Equality Compare
		bool operator != (const types) const;

		// Unary Negation/Plus
		UV operator + () const;
		// Unary Negation/Plus
		UV operator - () const;

		// Prefix Increment / Decremrnt
		UV& operator ++();
		// Postfix Increment / Decrement
		UV operator ++(int);
		// Prefix Increment / Decremrnt
		UV& operator --();
		// Postfix Increment / Decrement
		UV operator --(int);

		UV operator +(const UV&);
		UV operator -(const UV&);
		UV operator *(const UV&);
		UV operator /(const UV&);

		UV& operator =(const UV&);
		UV& operator +=(const UV&);
		UV& operator -=(const UV&);
		UV& operator *=(const UV&);
		UV& operator /=(const UV&);

		UV operator + (const types) const;
		UV operator - (const types) const;
		UV operator * (const types) const;
		UV operator / (const types) const;

		UV& operator =(const types);
		UV& operator +=(const types);
		UV& operator -=(const types);
		UV& operator *=(const types);
		UV& operator /=(const types);

		// Array Subscript
		const UV& operator[](std::size_t) const &;
		// Array Subscript
		UV& operator[](std::size_t) &;
		// Array Subscript
		UV operator[](std::size_t) &&;
	public:
		types u0, v0, u1, v1;
	};

	//==========================================================================
	//
	// class : Texvec
	// Content : Texvec
	// how to use : Texvec<float>,Texvec<int>,Texvec<double>...
	//
	//==========================================================================
	template<typename types>
	class Texvec
	{
	public:
		Texvec() :
			x(0), y(0), w(0), h(0) {}
		Texvec(types _x, types _y, types _w, types _h) :
			x(_x), y(_y), w(_w), h(_h) {}
		Texvec(const Texvec& v) :
			x(v.x), y(v.y), w(v.w), h(v.h) {}
		~Texvec() {}

		// Member Selection
		const Texvec* operator->() const noexcept;
		// Member Selection
		Texvec* operator->() noexcept;

		// Compare
		bool operator<(const Texvec&);
		// Compare
		bool operator>(const Texvec&);
		// Compare
		bool operator<=(const Texvec&);
		// Compare
		bool operator>=(const Texvec&);
		// Equality Compare
		bool operator == (const Texvec&) const;
		// Equality Compare
		bool operator != (const Texvec&) const;

		// Compare
		bool operator<(const types);
		// Compare
		bool operator>(const types);
		// Compare
		bool operator<=(const types);
		// Compare
		bool operator>=(const types);
		// Equality Compare
		bool operator == (const types) const;
		// Equality Compare
		bool operator != (const types) const;

		// Unary Negation/Plus
		Texvec operator + () const;
		// Unary Negation/Plus
		Texvec operator - () const;

		// Prefix Increment / Decremrnt
		Texvec& operator ++();
		// Postfix Increment / Decrement
		Texvec operator ++(int);
		// Prefix Increment / Decremrnt
		Texvec& operator --();
		// Postfix Increment / Decrement
		Texvec operator --(int);

		Texvec operator +(const Texvec&);
		Texvec operator -(const Texvec&);
		Texvec operator *(const Texvec&);
		Texvec operator /(const Texvec&);

		Texvec& operator =(const Texvec&);
		Texvec& operator +=(const Texvec&);
		Texvec& operator -=(const Texvec&);
		Texvec& operator *=(const Texvec&);
		Texvec& operator /=(const Texvec&);

		Texvec operator + (const types) const;
		Texvec operator - (const types) const;
		Texvec operator * (const types) const;
		Texvec operator / (const types) const;

		Texvec& operator =(const types);
		Texvec& operator +=(const types);
		Texvec& operator -=(const types);
		Texvec& operator *=(const types);
		Texvec& operator /=(const types);

		// Array Subscript
		const Texvec& operator[](std::size_t) const &;
		// Array Subscript
		Texvec& operator[](std::size_t) &;
		// Array Subscript
		Texvec operator[](std::size_t) &&;
	public:
		types x, y, w, h;
	};

	//==========================================================================
	//
	// class : Color
	// Content : Color
	// how to use : Color<float>,Color<int>,Color<double>...
	//
	//==========================================================================
	template<typename types>
	class Color
	{
	public:
		Color() :
			r(0), g(0), b(0), a(0) {};
		Color(types _r, types _g, types _b, types _a) :
			r(_r), g(_g), b(_b), a(_a) {};
		Color(const Color& v) :
			r(v.r), g(v.g), b(v.b), a(v.a) {};
		~Color() {}

		// Member Selection
		const Color* operator->() const noexcept;
		// Member Selection
		Color* operator->() noexcept;

		// Compare
		bool operator<(const Color&);
		// Compare
		bool operator>(const Color&);
		// Compare
		bool operator<=(const Color&);
		// Compare
		bool operator>=(const Color&);
		// Equality Compare
		bool operator == (const Color&) const;
		// Equality Compare
		bool operator != (const Color&) const;

		// Compare
		bool operator<(const types);
		// Compare
		bool operator>(const types);
		// Compare
		bool operator<=(const types);
		// Compare
		bool operator>=(const types);
		// Equality Compare
		bool operator == (const types) const;
		// Equality Compare
		bool operator != (const types) const;

		// Unary Negation/Plus
		Color operator + () const;
		// Unary Negation/Plus
		Color operator - () const;

		// Prefix Increment / Decremrnt
		Color& operator ++();
		// Postfix Increment / Decrement
		Color operator ++(int);
		// Prefix Increment / Decremrnt
		Color& operator --();
		// Postfix Increment / Decrement
		Color operator --(int);

		Color operator +(const Color&);
		Color operator -(const Color&);
		Color operator *(const Color&);
		Color operator /(const Color&);

		Color& operator =(const Color&);
		Color& operator +=(const Color&);
		Color& operator -=(const Color&);
		Color& operator *=(const Color&);
		Color& operator /=(const Color&);

		Color operator + (const types) const;
		Color operator - (const types) const;
		Color operator * (const types) const;
		Color operator / (const types) const;

		Color& operator =(const types);
		Color& operator +=(const types);
		Color& operator -=(const types);
		Color& operator *=(const types);
		Color& operator /=(const types);

		// Array Subscript
		const Color& operator[](std::size_t) const &;
		// Array Subscript
		Color& operator[](std::size_t) &;
		// Array Subscript
		Color operator[](std::size_t) &&;
	public:
		types r, g, b, a;
	};

	//==========================================================================
	//
	// class : Vector4
	// Content : Vector4
	// how to use : Vector4<float>,Vector4<int>,Vector4<double>...
	//
	//==========================================================================
	template<typename types>
	class Vector4
	{
	public:
		Vector4() :
			x(0), y(0), z(0), w(0) {}
		Vector4(types _x, types _y) :
			x(_x), y(_y), z(0), w(0) {}
		Vector4(types _x, types _y, types _z) :
			x(_x), y(_y), z(_z), w(0) {}
		Vector4(types _x, types _y, types _z, types _w) :
			x(_x), y(_y), z(_z), w(_w) {}
		Vector4(const Vector4& v) :
			x(v.x), y(v.y), z(v.z), w(v.w) {}
		~Vector4() {}

		// Member Selection
		const Vector4* operator->() const noexcept;
		// Member Selection
		Vector4* operator->() noexcept;

		// Compare
		bool operator<(const Vector4&);
		// Compare
		bool operator>(const Vector4&);
		// Compare
		bool operator<=(const Vector4&);
		// Compare
		bool operator>=(const Vector4&);
		// Equality Compare
		bool operator == (const Vector4&) const;
		// Equality Compare
		bool operator != (const Vector4&) const;

		// Compare
		bool operator<(const types);
		// Compare
		bool operator>(const types);
		// Compare
		bool operator<=(const types);
		// Compare
		bool operator>=(const types);
		// Equality Compare
		bool operator == (const types) const;
		// Equality Compare
		bool operator != (const types) const;

		// Unary Negation/Plus
		Vector4 operator + () const;
		// Unary Negation/Plus
		Vector4 operator - () const;

		// Prefix Increment / Decremrnt
		Vector4& operator ++();
		// Postfix Increment / Decrement
		Vector4 operator ++(int);
		// Prefix Increment / Decremrnt
		Vector4& operator --();
		// Postfix Increment / Decrement
		Vector4 operator --(int);

		Vector4 operator +(const Vector4&);
		Vector4 operator -(const Vector4&);
		Vector4 operator *(const Vector4&);
		Vector4 operator /(const Vector4&);

		Vector4& operator =(const Vector4&);
		Vector4& operator +=(const Vector4&);
		Vector4& operator -=(const Vector4&);
		Vector4& operator *=(const Vector4&);
		Vector4& operator /=(const Vector4&);

		Vector4 operator + (const types) const;
		Vector4 operator - (const types) const;
		Vector4 operator * (const types) const;
		Vector4 operator / (const types) const;

		Vector4& operator =(const types);
		Vector4& operator +=(const types);
		Vector4& operator -=(const types);
		Vector4& operator *=(const types);
		Vector4& operator /=(const types);

		// Array Subscript
		const Vector4& operator[](std::size_t n) const &;
		// Array Subscript
		Vector4& operator[](std::size_t) &;
		// Array Subscript
		Vector4 operator[](std::size_t) &&;
	public:
		types x, y, z, w;
	};

	//==========================================================================
	//
	// class : Vector2
	// Content : Vector2
	// how to use : Vector2<float>,Vector2<int>,Vector2<double>...
	//
	//==========================================================================
	template<typename types>
	class Vector2
	{
	public:
		Vector2() :
			x(0), y(0) {}
		Vector2(types _x, types _y) :
			x(_x), y(_y) {}
		Vector2(const Vector2& v) :
			x(v.x), y(v.y) {}
		~Vector2() {}

		// Member Selection
		const Vector2* operator->() const noexcept;
		// Member Selection
		Vector2* operator->() noexcept;

		// Compare
		bool operator<(const Vector2&);
		// Compare
		bool operator>(const Vector2&);
		// Compare
		bool operator<=(const Vector2&);
		// Compare
		bool operator>=(const Vector2&);
		// Equality Compare
		bool operator == (const Vector2&) const;
		// Equality Compare
		bool operator != (const Vector2&) const;

		// Compare
		bool operator<(const types);
		// Compare
		bool operator>(const types);
		// Compare
		bool operator<=(const types);
		// Compare
		bool operator>=(const types);
		// Equality Compare
		bool operator == (const types) const;
		// Equality Compare
		bool operator != (const types) const;

		// Unary Negation/Plus
		Vector2 operator + () const;
		// Unary Negation/Plus
		Vector2 operator - () const;

		// Prefix Increment / Decremrnt
		Vector2& operator ++();
		// Postfix Increment / Decrement
		Vector2 operator ++(int);
		// Prefix Increment / Decremrnt
		Vector2& operator --();
		// Postfix Increment / Decrement
		Vector2 operator --(int);

		Vector2 operator +(const Vector2&);
		Vector2 operator -(const Vector2&);
		Vector2 operator *(const Vector2&);
		Vector2 operator /(const Vector2&);

		Vector2& operator =(const Vector2&);
		Vector2& operator +=(const Vector2&);
		Vector2& operator -=(const Vector2&);
		Vector2& operator *=(const Vector2&);
		Vector2& operator /=(const Vector2&);

		Vector2 operator + (const types) const;
		Vector2 operator - (const types) const;
		Vector2 operator * (const types) const;
		Vector2 operator / (const types) const;

		Vector2& operator =(const types);
		Vector2& operator +=(const types);
		Vector2& operator -=(const types);
		Vector2& operator *=(const types);
		Vector2& operator /=(const types);

		// Array Subscript
		const Vector2& operator[](std::size_t n) const &;
		// Array Subscript
		Vector2& operator[](std::size_t) &;
		// Array Subscript
		Vector2 operator[](std::size_t) &&;
	public:
		types x, y;
	};

	//==========================================================================
	//
	// class : Vector3
	// Content : Vector3
	// how to use : Vector3<float>,Vector3<int>,Vector3<double>...
	//
	//==========================================================================
	template<typename types>
	class Vector3
	{
	public:
		Vector3() :
			x(0), y(0), z(0) {}
		Vector3(types _x, types _y) :
			x(_x), y(_y), z(0) {}
		Vector3(types _x, types _y, types _z) :
			x(_x), y(_y), z(_z) {}
		Vector3(const Vector3& v) :
			x(v.x), y(v.y), z(v.z) {}
		~Vector3() {}

		// Member Selection
		const Vector3* operator->() const noexcept;
		// Member Selection
		Vector3* operator->() noexcept;

		// Compare
		bool operator<(const Vector3&);
		// Compare
		bool operator>(const Vector3&);
		// Compare
		bool operator<=(const Vector3&);
		// Compare
		bool operator>=(const Vector3&);
		// Equality Compare
		bool operator == (const Vector3&) const;
		// Equality Compare
		bool operator != (const Vector3&) const;

		// Compare
		bool operator<(const types);
		// Compare
		bool operator>(const types);
		// Compare
		bool operator<=(const types);
		// Compare
		bool operator>=(const types);
		// Equality Compare
		bool operator == (const types) const;
		// Equality Compare
		bool operator != (const types) const;

		// Unary Negation/Plus
		Vector3 operator + () const;
		// Unary Negation/Plus
		Vector3 operator - () const;

		// Prefix Increment / Decremrnt
		Vector3& operator ++();
		// Postfix Increment / Decrement
		Vector3 operator ++(int);
		// Prefix Increment / Decremrnt
		Vector3& operator --();
		// Postfix Increment / Decrement
		Vector3 operator --(int);

		Vector3 operator +(const Vector3&);
		Vector3 operator -(const Vector3&);
		Vector3 operator *(const Vector3&);
		Vector3 operator /(const Vector3&);

		Vector3& operator =(const Vector3&);
		Vector3& operator +=(const Vector3&);
		Vector3& operator -=(const Vector3&);
		Vector3& operator *=(const Vector3&);
		Vector3& operator /=(const Vector3&);

		Vector3 operator + (const types) const;
		Vector3 operator - (const types) const;
		Vector3 operator * (const types) const;
		Vector3 operator / (const types) const;

		Vector3& operator =(const types);
		Vector3& operator +=(const types);
		Vector3& operator -=(const types);
		Vector3& operator *=(const types);
		Vector3& operator /=(const types);

		// Array Subscript
		const Vector3& operator[](std::size_t n) const &;
		// Array Subscript
		Vector3& operator[](std::size_t) &;
		// Array Subscript
		Vector3 operator[](std::size_t) &&;
	public:
		types x, y, z;
	};

	//==========================================================================
	//
	// class : Material
	// Content : Material
	// how to use : Material<float>,Material<int>,Material<double>...
	//
	//==========================================================================
	template<typename types>
	class Material
	{
	public:
		Material() :Shininess(0) {}
		~Material() {}

		// Member Selection
		const Material* operator->() const noexcept;

		// Member Selection
		Material* operator->() noexcept;

		Material& operator =(const Material&);

		// Array Subscript
		const Material& operator[](std::size_t n) const &;
		// Array Subscript
		Material& operator[](std::size_t) &;
		// Array Subscript
		Material operator[](std::size_t) &&;
	public:
		Color<types> Ambient;
		Color<types> Diffuse;
		Color<types> Specular;
		Color<types> Emission;
		types Shininess;
	};

	//==========================================================================
	//
	// class : Vertex3D
	// Content : Vertex3D
	// how to use : Vertex3D<float>,Vertex3D<int>,Vertex3D<double>...
	//
	//==========================================================================
	template<typename types>
	class Vertex3D
	{
	public:
		Vertex3D() {}
		~Vertex3D() {}

		// Member Selection
		const Vertex3D* operator->() const noexcept;

		// Member Selection
		Vertex3D* operator->() noexcept;

		Vertex3D& operator =(const Vertex3D&);

		// Array Subscript
		const Vertex3D& operator[](std::size_t n) const &;
		// Array Subscript
		Vertex3D& operator[](std::size_t) &;
		// Array Subscript
		Vertex3D operator[](std::size_t) &&;
	public:
		Vector2<types> TexturePos;
		Color<types> Diffuse;
		Vector3<types> Normal;
		Vector3<types> Position;
	};

	//==========================================================================
	// Definition
	//==========================================================================

	//==========================================================================
	//
	// class : UV
	// Content : UV
	// how to use : UV<float>,UV<int>,UV<double>...
	//
	//==========================================================================

	// Member Selection
	template<typename types>
	inline const UV<types>* UV<types>::operator->() const noexcept
	{
		return this;
	}

	// Member Selection
	template<typename types>
	inline UV<types>* UV<types>::operator->() noexcept
	{
		return this;
	}

	// Compare
	template<typename types>
	inline bool UV<types>::operator<(const UV& v)
	{
		if (u0 < v.u0 && v0 < v.v0 && u1 < v.u1 && v1 < v.v1)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool UV<types>::operator>(const UV& v)
	{
		if (u0 > v.u0 && v0 > v.v0 && u1 > v.u1 && v1 > v.v1)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool UV<types>::operator<=(const UV& v)
	{
		if ((u0 <= v.u0) && (v0 <= v.v0) && (u1 <= v.u1) && (v1 <= v.v1))
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool UV<types>::operator>=(const UV& v)
	{
		if ((u0 >= v.u0) && (v0 >= v.v0) && (u1 >= v.u1) && (v1 >= v.v1))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool UV<types>::operator==(const UV& v) const
	{
		if ((u0 == v.u0) && (v0 == v.v0) && (u1 == v.u1) && (v1 == v.v1))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool UV<types>::operator!=(const UV& v) const
	{
		if ((u0 != v.u0) && (v0 != v.v0) && (u1 != v.u1) && (v1 != v.v1))
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool UV<types>::operator<(const types t)
	{
		if (u0 < t && v0 < t && u1 < t && v1 < t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool UV<types>::operator>(const types t)
	{
		if (u0 > t && v0 > t && u1 > t && v1 > t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool UV<types>::operator<=(const types t)
	{
		if ((u0 <= t) && (v0 <= t) && (u1 <= t) && (v1 <= t))
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool UV<types>::operator>=(const types t)
	{
		if ((u0 >= t) && (v0 >= t) && (u1 >= t) && (v1 >= t))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool UV<types>::operator==(const types t) const
	{
		if ((u0 == t) && (v0 == t) && (u1 == t) && (v1 == t))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool UV<types>::operator!=(const types t) const
	{
		if ((u0 != t) && (v0 != t) && (u1 != t) && (v1 != t))
			return true;
		return false;
	}

	// Unary Negation/Plus
	template<typename types>
	inline UV<types> UV<types>::operator+() const
	{
		return *this;
	}

	// Unary Negation/Plus
	template<typename types>
	inline UV<types> UV<types>::operator-() const
	{
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline UV<types>& UV<types>::operator++()
	{
		u0++;
		v0++;
		u1++;
		v1++;
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline UV<types> UV<types>::operator++(int)
	{
		auto out = *this;
		u0++;
		v0++;
		u1++;
		v1++;
		return out;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline UV<types>& UV<types>::operator--()
	{
		u0--;
		v0--;
		u1--;
		v1--;
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline UV<types> UV<types>::operator--(int)
	{
		auto out = *this;
		u0--;
		v0--;
		u1--;
		v1--;
		return out;
	}

	template<typename types>
	inline UV<types> UV<types>::operator+(const UV& v)
	{
		UV<types> out;
		out.u0 = u0 + v.u0;
		out.v0 = v0 + v.v0;
		out.u1 = u1 + v.u1;
		out.v1 = v1 + v.v1;
		return out;
	}

	template<typename types>
	inline UV<types> UV<types>::operator-(const UV& v)
	{
		UV<types> out;
		out.u0 = u0 - v.u0;
		out.v0 = v0 - v.v0;
		out.u1 = u1 - v.u1;
		out.v1 = v1 - v.v1;
		return out;
	}

	template<typename types>
	inline UV<types> UV<types>::operator*(const UV& v)
	{
		UV<types> out;
		out.u0 = u0 * v.u0;
		out.v0 = v0 * v.v0;
		out.u1 = u1 * v.u1;
		out.v1 = v1 * v.v1;
		return out;
	}

	template<typename types>
	inline UV<types> UV<types>::operator/(const UV& v)
	{
		UV<types> out;
		out.u0 = u0 / v.u0;
		out.v0 = v0 / v.v0;
		out.u1 = u1 / v.u1;
		out.v1 = v1 / v.v1;
		return out;
	}

	template<typename types>
	inline UV<types>& UV<types>::operator=(const UV& v)
	{
		u0 = v.u0;
		v0 = v.v0;
		u1 = v.u1;
		v1 = v.v1;
		return *this;
	}

	template<typename types>
	inline UV<types>& UV<types>::operator+=(const UV& v)
	{
		u0 += v.u0;
		v0 += v.v0;
		u1 += v.u1;
		v1 += v.v1;
		return *this;
	}

	template<typename types>
	inline UV<types>& UV<types>::operator-=(const UV& v)
	{
		u0 -= v.u0;
		v0 -= v.v0;
		u1 -= v.u1;
		v1 -= v.v1;
		return *this;
	}

	template<typename types>
	inline UV<types>& UV<types>::operator*=(const UV& v)
	{
		u0 *= v.u0;
		v0 *= v.v0;
		u1 *= v.u1;
		v1 *= v.v1;
		return *this;
	}

	template<typename types>
	inline UV<types>& UV<types>::operator/=(const UV& v)
	{
		u0 /= v.u0;
		v0 /= v.v0;
		u1 /= v.u1;
		v1 /= v.v1;
		return *this;
	}

	template<typename types>
	inline UV<types> UV<types>::operator+(const types t) const
	{
		return UV(u0 + t, v0 + t, u1 + t, v1 + t);
	}

	template<typename types>
	inline UV<types> UV<types>::operator-(const types t) const
	{
		return UV(u0 - t, v0 - t, u1 - t, v1 - t);
	}

	template<typename types>
	inline UV<types> UV<types>::operator*(const types t) const
	{
		return UV(u0 * t, v0 * t, u1 * t, v1 * t);
	}

	template<typename types>
	inline UV<types> UV<types>::operator/(const types t) const
	{
		types tInv = (types)1;
		tInv = tInv / t;
		return UV(u0 * tInv, v0 * tInv, u1 * tInv, v1 * tInv);
	}

	template<typename types>
	inline UV<types>& UV<types>::operator=(const types t)
	{
		u0 = t;
		v0 = t;
		u1 = t;
		v1 = t;
		return *this;
	}

	template<typename types>
	inline UV<types>& UV<types>::operator+=(const types t)
	{
		u0 += t;
		v0 += t;
		u1 += t;
		v1 += t;
		return *this;
	}

	template<typename types>
	inline UV<types>& UV<types>::operator-=(const types t)
	{
		u0 -= t;
		v0 -= t;
		u1 -= t;
		v1 -= t;
		return *this;
	}

	template<typename types>
	inline UV<types>& UV<types>::operator*=(const types t)
	{
		u0 *= t;
		v0 *= t;
		u1 *= t;
		v1 *= t;
		return *this;
	}

	template<typename types>
	inline UV<types>& UV<types>::operator/=(const types t)
	{
		u0 /= t;
		v0 /= t;
		u1 /= t;
		v1 /= t;
		return *this;
	}

	// Array Subscript
	template<typename types>
	inline const UV<types>& UV<types>::operator[](std::size_t n) const &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline UV<types>& UV<types>::operator[](std::size_t n) &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline UV<types> UV<types>::operator[](std::size_t n) &&
	{
		return std::move(this[n]);
	}

	//==========================================================================
	//
	// class  : Texvec
	// Content : Texvec
	// how to use : Texvec<float>,Texvec<int>,Texvec<double>...
	//
	//==========================================================================

	// Member Selection
	template<typename types>
	inline const Texvec<types>* Texvec<types>::operator->() const noexcept
	{
		return this;
	}

	// Member Selection
	template<typename types>
	inline Texvec<types>* Texvec<types>::operator->() noexcept
	{
		return this;
	}

	// Compare
	template<typename types>
	inline bool Texvec<types>::operator<(const Texvec& v)
	{
		if (x < v.x && y < v.y && w < v.w && h < v.h)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Texvec<types>::operator>(const Texvec& v)
	{
		if (x > v.x && y > v.y && w > v.w && h > v.h)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Texvec<types>::operator<=(const Texvec& v)
	{
		if (x <= v.x && y <= v.y && w <= v.w && h <= v.h)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Texvec<types>::operator>=(const Texvec& v)
	{
		if (x >= v.x && y >= v.y && w >= v.w && h >= v.h)
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Texvec<types>::operator==(const Texvec& v) const
	{
		if ((x == v.x) && (y == v.y) && (w == v.w) && (h == v.h))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Texvec<types>::operator!=(const Texvec& v) const
	{
		if ((x != v.x) && (y != v.y) && (w != v.w) && (h != v.h))
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Texvec<types>::operator<(const types t)
	{
		if (x < t && y < t && w < t && h < t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Texvec<types>::operator>(const types t)
	{
		if (x > t && y > t && w > t && h > t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Texvec<types>::operator<=(const types t)
	{
		if (x <= t && y <= t && w <= t && h <= t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Texvec<types>::operator>=(const types t)
	{
		if (x >= t && y >= t && w >= t && h >= t)
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Texvec<types>::operator==(const types t) const
	{
		if ((x == t) && (y == t) && (w == t) && (h == t))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Texvec<types>::operator!=(const types t) const
	{
		if ((x != t) && (y != t) && (w != t) && (h != t))
			return true;
		return false;
	}

	// Unary Negation/Plus
	template<typename types>
	inline Texvec<types> Texvec<types>::operator+() const
	{
		return *this;
	}

	// Unary Negation/Plus
	template<typename types>
	inline Texvec<types> Texvec<types>::operator-() const
	{
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Texvec<types>& Texvec<types>::operator++()
	{
		x++;
		y++;
		w++;
		h++;
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Texvec<types> Texvec<types>::operator++(int)
	{
		auto out = *this;
		x++;
		y++;
		w++;
		h++;
		return out;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Texvec<types>& Texvec<types>::operator--()
	{
		x--;
		y--;
		w--;
		h--;
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Texvec<types> Texvec<types>::operator--(int)
	{
		auto out = *this;
		x--;
		y--;
		w--;
		h--;
		return out;
	}

	template<typename types>
	inline Texvec<types> Texvec<types>::operator+(const Texvec& v)
	{
		Texvec<types> out;
		out.x = x + v.x;
		out.y = y + v.y;
		out.w = w + v.w;
		out.h = h + v.h;
		return out;
	}

	template<typename types>
	inline Texvec<types> Texvec<types>::operator-(const Texvec& v)
	{
		Texvec<types> out;
		out.x = x - v.x;
		out.y = y - v.y;
		out.w = w - v.w;
		out.h = h - v.h;
		return out;
	}

	template<typename types>
	inline Texvec<types> Texvec<types>::operator*(const Texvec& v)
	{
		Texvec<types> out;
		out.x = x * v.x;
		out.y = y * v.y;
		out.w = w * v.w;
		out.h = h * v.h;
		return out;
	}

	template<typename types>
	inline Texvec<types> Texvec<types>::operator/(const Texvec& v)
	{
		Texvec<types> out;
		out.x = x / v.x;
		out.y = y / v.y;
		out.w = w / v.w;
		out.h = h / v.h;
		return out;
	}

	template<typename types>
	inline Texvec<types>& Texvec<types>::operator=(const Texvec& v)
	{
		x = v.x;
		y = v.y;
		w = v.w;
		h = v.h;
		return *this;
	}

	template<typename types>
	inline Texvec<types>& Texvec<types>::operator+=(const Texvec& v)
	{
		x += v.x;
		y += v.y;
		w += v.w;
		h += v.h;
		return *this;
	}

	template<typename types>
	inline Texvec<types>& Texvec<types>::operator-=(const Texvec& v)
	{
		x -= v.x;
		y -= v.y;
		w -= v.w;
		h -= v.h;
		return *this;
	}

	template<typename types>
	inline Texvec<types>& Texvec<types>::operator*=(const Texvec& v)
	{
		x *= v.x;
		y *= v.y;
		w *= v.w;
		h *= v.h;
		return *this;
	}

	template<typename types>
	inline Texvec<types>& Texvec<types>::operator/=(const Texvec& v)
	{
		x /= v.x;
		y /= v.y;
		w /= v.w;
		h /= v.h;
		return *this;
	}

	template<typename types>
	inline Texvec<types> Texvec<types>::operator+(const types t) const
	{
		return Texvec(x + t, y + t, w + t, h + t);
	}

	template<typename types>
	inline Texvec<types> Texvec<types>::operator-(const types t) const
	{
		return Texvec(x - t, y - t, w - t, h - t);
	}

	template<typename types>
	inline Texvec<types> Texvec<types>::operator*(const types t) const
	{
		return Texvec(x * t, y * t, w * t, h * t);
	}

	template<typename types>
	inline Texvec<types> Texvec<types>::operator/(const types t) const
	{
		types tInv = (types)1;
		tInv = tInv / t;
		return Texvec(x * tInv, y * tInv, w * tInv, h * tInv);
	}

	template<typename types>
	inline Texvec<types>& Texvec<types>::operator=(const types t)
	{
		x = t;
		y = t;
		w = t;
		h = t;
		return *this;
	}

	template<typename types>
	inline Texvec<types>& Texvec<types>::operator+=(const types t)
	{
		x += t;
		y += t;
		w += t;
		h += t;
		return *this;
	}

	template<typename types>
	inline Texvec<types>& Texvec<types>::operator-=(const types t)
	{
		x -= t;
		y -= t;
		w -= t;
		h -= t;
		return *this;
	}

	template<typename types>
	inline Texvec<types>& Texvec<types>::operator*=(const types t)
	{
		x *= t;
		y *= t;
		w *= t;
		h *= t;
		return *this;
	}

	template<typename types>
	inline Texvec<types>& Texvec<types>::operator/=(const types t)
	{
		x /= t;
		y /= t;
		w /= t;
		h /= t;
		return *this;
	}

	// Array Subscript
	template<typename types>
	inline const Texvec<types>& Texvec<types>::operator[](std::size_t n) const &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Texvec<types>& Texvec<types>::operator[](std::size_t n) &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Texvec<types> Texvec<types>::operator[](std::size_t n) &&
	{
		return std::move(this[n]);
	}

	//==========================================================================
	//
	// class  : Color
	// Content : Color
	// how to use : Color<float>,Color<int>,Color<double>...
	//
	//==========================================================================

	// Member Selection
	template<typename types>
	inline const Color<types>* Color<types>::operator->() const noexcept
	{
		return this;
	}

	// Member Selection
	template<typename types>
	inline Color<types>* Color<types>::operator->() noexcept
	{
		return this;
	}

	// Compare
	template<typename types>
	inline bool Color<types>::operator<(const Color& v)
	{
		if (r < v.r && g < v.g && b < v.b && a < v.a)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Color<types>::operator>(const Color& v)
	{
		if (r > v.r && g > v.g && b > v.b && a > v.a)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Color<types>::operator<=(const Color& v)
	{
		if (r <= v.r && g <= v.g && b <= v.b && a <= v.a)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Color<types>::operator>=(const Color& v)
	{
		if (r >= v.r && g >= v.g && b >= v.b && a >= v.a)
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Color<types>::operator==(const Color& v) const
	{
		if ((r == v.r) && (g == v.g) && (b == v.b) && (a == v.a))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Color<types>::operator!=(const Color& v) const
	{
		if ((r != v.r) && (g != v.g) && (b != v.b) && (a != v.a))
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Color<types>::operator<(const types t)
	{
		if (r < t && g < t && b < t && a < t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Color<types>::operator>(const types t)
	{
		if (r > t && g > t && b > t && a > t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Color<types>::operator<=(const types t)
	{
		if (r <= t && g <= t && b <= t && a <= t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Color<types>::operator>=(const types t)
	{
		if (r >= t && g >= t && b >= t && a >= t)
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Color<types>::operator==(const types t) const
	{
		if ((r == t) && (g == t) && (b == t) && (a == t))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Color<types>::operator!=(const types t) const
	{
		if ((r != t) && (g != t) && (b != t) && (a != t))
			return true;
		return false;
	}

	// Unary Negation/Plus
	template<typename types>
	inline Color<types> Color<types>::operator+() const
	{
		return *this;
	}

	// Unary Negation/Plus
	template<typename types>
	inline Color<types> Color<types>::operator-() const
	{
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Color<types>& Color<types>::operator++()
	{
		r++;
		g++;
		b++;
		a++;
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Color<types> Color<types>::operator++(int)
	{
		auto out = *this;
		r++;
		g++;
		b++;
		a++;
		return out;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Color<types>& Color<types>::operator--()
	{
		r--;
		g--;
		b--;
		a--;
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Color<types> Color<types>::operator--(int)
	{
		auto out = *this;
		r--;
		g--;
		b--;
		a--;
		return out;
	}

	template<typename types>
	inline Color<types> Color<types>::operator+(const Color& v)
	{
		Color<types> out;
		out.r = r + v.r;
		out.g = g + v.g;
		out.b = b + v.b;
		out.a = a + v.a;
		return out;
	}

	template<typename types>
	inline Color<types> Color<types>::operator-(const Color& v)
	{
		Color<types> out;
		out.r = r - v.r;
		out.g = g - v.g;
		out.b = b - v.b;
		out.a = a - v.a;
		return out;
	}

	template<typename types>
	inline Color<types> Color<types>::operator*(const Color& v)
	{
		Color<types> out;
		out.r = r * v.r;
		out.g = g * v.g;
		out.b = b * v.b;
		out.a = a * v.a;
		return out;
	}

	template<typename types>
	inline Color<types> Color<types>::operator/(const Color& v)
	{
		Color<types> out;
		out.r = r / v.r;
		out.g = g / v.g;
		out.b = b / v.b;
		out.a = a / v.a;
		return out;
	}

	template<typename types>
	inline Color<types>& Color<types>::operator=(const Color& v)
	{
		r = v.r;
		g = v.g;
		b = v.b;
		a = v.a;
		return *this;
	}

	template<typename types>
	inline Color<types>& Color<types>::operator+=(const Color& v)
	{
		r += v.r;
		g += v.g;
		b += v.b;
		a += v.a;
		return *this;
	}

	template<typename types>
	inline Color<types>& Color<types>::operator-=(const Color& v)
	{
		r -= v.r;
		g -= v.g;
		b -= v.b;
		a -= v.a;
		return *this;
	}

	template<typename types>
	inline Color<types>& Color<types>::operator*=(const Color& v)
	{
		r *= v.r;
		g *= v.g;
		b *= v.b;
		a *= v.a;
		return *this;
	}

	template<typename types>
	inline Color<types>& Color<types>::operator/=(const Color& v)
	{
		r /= v.r;
		g /= v.g;
		b /= v.b;
		a /= v.a;
		return *this;
	}

	template<typename types>
	inline Color<types> Color<types>::operator+(const types t) const
	{
		return Color(r + t, g + t, b + t, a + t);
	}

	template<typename types>
	inline Color<types> Color<types>::operator-(const types t) const
	{
		return Color(r - t, g - t, b - t, a - t);
	}

	template<typename types>
	inline Color<types> Color<types>::operator*(const types t) const
	{
		return Color(r * t, g * t, b * t, a * t);
	}

	template<typename types>
	inline Color<types> Color<types>::operator/(const types t) const
	{
		types tInv = (types)1;
		tInv = tInv / t;
		return Color(r * tInv, g * tInv, b * tInv, a * tInv);
	}

	template<typename types>
	inline Color<types>& Color<types>::operator=(const types t)
	{
		r = t;
		g = t;
		b = t;
		a = t;
		return *this;
	}

	template<typename types>
	inline Color<types>& Color<types>::operator+=(const types t)
	{
		r += t;
		g += t;
		b += t;
		a += t;
		return *this;
	}

	template<typename types>
	inline Color<types>& Color<types>::operator-=(const types t)
	{
		r -= t;
		g -= t;
		b -= t;
		a -= t;
		return *this;
	}

	template<typename types>
	inline Color<types>& Color<types>::operator*=(const types t)
	{
		r *= t;
		g *= t;
		b *= t;
		a *= t;
		return *this;
	}

	template<typename types>
	inline Color<types>& Color<types>::operator/=(const types t)
	{
		r /= t;
		g /= t;
		b /= t;
		a /= t;
		return *this;
	}

	// Array Subscript
	template<typename types>
	inline const Color<types>& Color<types>::operator[](std::size_t n) const &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Color<types>& Color<types>::operator[](std::size_t n) &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Color<types> Color<types>::operator[](std::size_t n) &&
	{
		return std::move(this[n]);
	}

	//==========================================================================
	//
	// class  : Vector4
	// Content : Vector4
	// how to use : Vector4<float>,Vector4<int>,Vector4<double>...
	//
	//==========================================================================

	// Member Selection
	template<typename types>
	inline const Vector4<types>* Vector4<types>::operator->() const noexcept
	{
		return this;
	}

	// Member Selection
	template<typename types>
	inline Vector4<types>* Vector4<types>::operator->() noexcept
	{
		return this;
	}

	// Compare
	template<typename types>
	inline bool Vector4<types>::operator<(const Vector4& v)
	{
		if (x < v.x && y < v.y && z < v.z && w < v.w)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector4<types>::operator>(const Vector4& v)
	{
		if (x > v.x && y > v.y && z > v.z && w > v.w)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector4<types>::operator<=(const Vector4& v)
	{
		if (x <= v.x && y <= v.y && z <= v.z && w <= v.w)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector4<types>::operator>=(const Vector4& v)
	{
		if (x >= v.x && y >= v.y && z >= v.z && w >= v.w)
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Vector4<types>::operator==(const Vector4& v) const
	{
		if ((x == v.x) && (y == v.y) && (z == v.z) && (w == v.w))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Vector4<types>::operator!=(const Vector4& v) const
	{
		if ((x != v.x) && (y != v.y) && (z != v.z) && (w != v.w))
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector4<types>::operator<(const types t)
	{
		if (x < t && y < t && z < t && w < t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector4<types>::operator>(const types t)
	{
		if (x > t && y > t && z > t && w > t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector4<types>::operator<=(const types t)
	{
		if (x <= t && y <= t && z <= t && w <= t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector4<types>::operator>=(const types t)
	{
		if (x >= t && y >= t && z >= t && w >= t)
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Vector4<types>::operator==(const types t) const
	{
		if ((x == t) && (y == t) && (z == t) && (w == t))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Vector4<types>::operator!=(const types t) const
	{
		if ((x != t) && (y != t) && (z != t) && (w != t))
			return true;
		return false;
	}

	// Unary Negation/Plus
	template<typename types>
	inline Vector4<types> Vector4<types>::operator+() const
	{
		return *this;
	}

	// Unary Negation/Plus
	template<typename types>
	inline Vector4<types> Vector4<types>::operator-() const
	{
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Vector4<types>& Vector4<types>::operator++()
	{
		x++;
		y++;
		z++;
		w++;
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Vector4<types> Vector4<types>::operator++(int)
	{
		auto out = *this;
		x++;
		y++;
		z++;
		w++;
		return out;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Vector4<types>& Vector4<types>::operator--()
	{
		x--;
		y--;
		z--;
		w--;
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Vector4<types> Vector4<types>::operator--(int)
	{
		auto out = *this;
		x--;
		y--;
		z--;
		w--;
		return out;
	}

	template<typename types>
	inline Vector4<types> Vector4<types>::operator+(const Vector4& v)
	{
		Vector4<types> out;
		out.x = x + v.x;
		out.y = y + v.y;
		out.z = z + v.z;
		out.w = w + v.w;
		return out;
	}

	template<typename types>
	inline Vector4<types> Vector4<types>::operator-(const Vector4& v)
	{
		Vector4<types> out;
		out.x = x - v.x;
		out.y = y - v.y;
		out.z = z - v.z;
		out.w = w - v.w;
		return out;
	}

	template<typename types>
	inline Vector4<types> Vector4<types>::operator*(const Vector4& v)
	{
		Vector4<types> out;
		out.x = x * v.x;
		out.y = y * v.y;
		out.z = z * v.z;
		out.w = w * v.w;
		return out;
	}

	template<typename types>
	inline Vector4<types> Vector4<types>::operator/(const Vector4& v)
	{
		Vector4<types> out;
		out.x = x / v.x;
		out.y = y / v.y;
		out.z = z / v.z;
		out.w = w / v.w;
		return out;
	}

	template<typename types>
	inline Vector4<types>& Vector4<types>::operator=(const Vector4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}

	template<typename types>
	inline Vector4<types>& Vector4<types>::operator+=(const Vector4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	template<typename types>
	inline Vector4<types>& Vector4<types>::operator-=(const Vector4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	template<typename types>
	inline Vector4<types>& Vector4<types>::operator*=(const Vector4& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return *this;
	}

	template<typename types>
	inline Vector4<types>& Vector4<types>::operator/=(const Vector4& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}

	template<typename types>
	inline Vector4<types> Vector4<types>::operator+(const types t) const
	{
		return Vector4(x + t, y + t, z + t, w + t);
	}

	template<typename types>
	inline Vector4<types> Vector4<types>::operator-(const types t) const
	{
		return Vector4(x - t, y - t, z - t, w - t);
	}

	template<typename types>
	inline Vector4<types> Vector4<types>::operator*(const types t) const
	{
		return Vector4(x * t, y * t, z * t, w * t);
	}

	template<typename types>
	inline Vector4<types> Vector4<types>::operator/(const types t) const
	{
		types tInv = (types)1;
		tInv = tInv / t;
		return Vector4(x * tInv, y * tInv, z * tInv, w * tInv);
	}

	template<typename types>
	inline Vector4<types>& Vector4<types>::operator=(const types t)
	{
		x = t;
		y = t;
		z = t;
		w = t;
		return *this;
	}

	template<typename types>
	inline Vector4<types>& Vector4<types>::operator+=(const types t)
	{
		x += t;
		y += t;
		z += t;
		w += t;
		return *this;
	}

	template<typename types>
	inline Vector4<types>& Vector4<types>::operator-=(const types t)
	{
		x -= t;
		y -= t;
		z -= t;
		w -= t;
		return *this;
	}

	template<typename types>
	inline Vector4<types>& Vector4<types>::operator*=(const types t)
	{
		x *= t;
		y *= t;
		z *= t;
		w *= t;
		return *this;
	}

	template<typename types>
	inline Vector4<types>& Vector4<types>::operator/=(const types t)
	{
		x /= t;
		y /= t;
		z /= t;
		w /= t;
		return *this;
	}

	// Array Subscript
	template<typename types>
	inline const Vector4<types>& Vector4<types>::operator[](std::size_t n) const &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Vector4<types>& Vector4<types>::operator[](std::size_t n) &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Vector4<types> Vector4<types>::operator[](std::size_t n) &&
	{
		return std::move(this[n]);
	}

	//==========================================================================
	//
	// class  : Vector2
	// Content : Vector2
	// how to use : Vector2<float>,Vector2<int>,Vector2<double>...
	//
	//==========================================================================

	// Member Selection
	template<typename types>
	inline const Vector2<types>* Vector2<types>::operator->() const noexcept
	{
		return this;
	}

	// Member Selection
	template<typename types>
	inline Vector2<types>* Vector2<types>::operator->() noexcept
	{
		return this;
	}

	// Compare
	template<typename types>
	inline bool Vector2<types>::operator<(const Vector2& v)
	{
		if (x < v.x && y < v.y)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector2<types>::operator>(const Vector2& v)
	{
		if (x > v.x && y > v.y)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector2<types>::operator<=(const Vector2& v)
	{
		if (x <= v.x && y <= v.y)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector2<types>::operator>=(const Vector2& v)
	{
		if (x >= v.x && y >= v.y)
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Vector2<types>::operator==(const Vector2& v) const
	{
		if ((x == v.x) && (y == v.y))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Vector2<types>::operator!=(const Vector2& v) const
	{
		if ((x != v.x) && (y != v.y))
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector2<types>::operator<(const types t)
	{
		if (x < t && y < t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector2<types>::operator>(const types t)
	{
		if (x > t && y > t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector2<types>::operator<=(const types t)
	{
		if (x <= t && y <= t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector2<types>::operator>=(const types t)
	{
		if (x >= t && y >= t)
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Vector2<types>::operator==(const types t) const
	{
		if ((x == t) && (y == t))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Vector2<types>::operator!=(const types t) const
	{
		if ((x != t) && (y != t))
			return true;
		return false;
	}

	// Unary Negation/Plus
	template<typename types>
	inline Vector2<types> Vector2<types>::operator+() const
	{
		return *this;
	}

	// Unary Negation/Plus
	template<typename types>
	inline Vector2<types> Vector2<types>::operator-() const
	{
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Vector2<types>& Vector2<types>::operator++()
	{
		x++;
		y++;
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Vector2<types> Vector2<types>::operator++(int)
	{
		auto out = *this;
		x++;
		y++;
		return out;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Vector2<types>& Vector2<types>::operator--()
	{
		x--;
		y--;
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Vector2<types> Vector2<types>::operator--(int)
	{
		auto out = *this;
		x--;
		y--;
		return out;
	}

	template<typename types>
	inline Vector2<types> Vector2<types>::operator+(const Vector2& v)
	{
		Vector2<types> out;
		out.x = x + v.x;
		out.y = y + v.y;
		return out;
	}

	template<typename types>
	inline Vector2<types> Vector2<types>::operator-(const Vector2& v)
	{
		Vector2<types> out;
		out.x = x - v.x;
		out.y = y - v.y;
		return out;
	}

	template<typename types>
	inline Vector2<types> Vector2<types>::operator*(const Vector2& v)
	{
		Vector2<types> out;
		out.x = x * v.x;
		out.y = y * v.y;
		return out;
	}

	template<typename types>
	inline Vector2<types> Vector2<types>::operator/(const Vector2& v)
	{
		Vector2<types> out;
		out.x = x / v.x;
		out.y = y / v.y;
		return out;
	}

	template<typename types>
	inline Vector2<types>& Vector2<types>::operator=(const Vector2& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	template<typename types>
	inline Vector2<types>& Vector2<types>::operator+=(const Vector2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	template<typename types>
	inline Vector2<types>& Vector2<types>::operator-=(const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	template<typename types>
	inline Vector2<types>& Vector2<types>::operator*=(const Vector2& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	template<typename types>
	inline Vector2<types>& Vector2<types>::operator/=(const Vector2& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	template<typename types>
	inline Vector2<types> Vector2<types>::operator+(const types t) const
	{
		return Vector2(x + t, y + t);
	}

	template<typename types>
	inline Vector2<types> Vector2<types>::operator-(const types t) const
	{
		return Vector2(x - t, y - t);
	}

	template<typename types>
	inline Vector2<types> Vector2<types>::operator*(const types t) const
	{
		return Vector2(x * t, y * t);
	}

	template<typename types>
	inline Vector2<types> Vector2<types>::operator/(const types t) const
	{
		types tInv = (types)1;
		tInv = tInv / t;
		return Vector2(x * tInv, y * tInv);
	}

	template<typename types>
	inline Vector2<types>& Vector2<types>::operator=(const types t)
	{
		x = t;
		y = t;
		return *this;
	}

	template<typename types>
	inline Vector2<types>& Vector2<types>::operator+=(const types t)
	{
		x += t;
		y += t;
		return *this;
	}

	template<typename types>
	inline Vector2<types>& Vector2<types>::operator-=(const types t)
	{
		x -= t;
		y -= t;
		return *this;
	}

	template<typename types>
	inline Vector2<types>& Vector2<types>::operator*=(const types t)
	{
		x *= t;
		y *= t;
		return *this;
	}

	template<typename types>
	inline Vector2<types>& Vector2<types>::operator/=(const types t)
	{
		x /= t;
		y /= t;
		return *this;
	}

	// Array Subscript
	template<typename types>
	inline const Vector2<types>& Vector2<types>::operator[](std::size_t n) const &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Vector2<types>& Vector2<types>::operator[](std::size_t n) &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Vector2<types> Vector2<types>::operator[](std::size_t n) &&
	{
		return std::move(this[n]);
	}

	//==========================================================================
	//
	// class  : Vector3
	// Content : Vector3
	// how to use : Vector3<float>,Vector3<int>,Vector3<double>...
	//
	//==========================================================================

	// Member Selection
	template<typename types>
	inline const Vector3<types>* Vector3<types>::operator->() const noexcept
	{
		return this;
	}

	// Member Selection
	template<typename types>
	inline Vector3<types>* Vector3<types>::operator->() noexcept
	{
		return this;
	}

	// Compare
	template<typename types>
	inline bool Vector3<types>::operator<(const Vector3& v)
	{
		if (x < v.x && y < v.y && z < v.z)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector3<types>::operator>(const Vector3& v)
	{
		if (x > v.x && y > v.y && z > v.z)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector3<types>::operator<=(const Vector3& v)
	{
		if (x <= v.x && y <= v.y && z <= v.z)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector3<types>::operator>=(const Vector3& v)
	{
		if (x >= v.x && y >= v.y && z >= v.z)
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Vector3<types>::operator==(const Vector3& v) const
	{
		if ((x == v.x) && (y == v.y) && (z == v.z))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Vector3<types>::operator!=(const Vector3& v) const
	{
		if ((x != v.x) && (y != v.y) && (z != v.z))
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector3<types>::operator<(const types t)
	{
		if (x < t && y < t && z < t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector3<types>::operator>(const types t)
	{
		if (x > t && y > t && z > t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector3<types>::operator<=(const types t)
	{
		if (x <= t && y <= t && z <= t)
			return true;
		return false;
	}

	// Compare
	template<typename types>
	inline bool Vector3<types>::operator>=(const types t)
	{
		if (x >= t && y >= t && z >= t)
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Vector3<types>::operator==(const types t) const
	{
		if ((x == t) && (y == t) && (z == t))
			return true;
		return false;
	}

	// Equality Compare
	template<typename types>
	inline bool Vector3<types>::operator!=(const types t) const
	{
		if ((x != t) && (y != t) && (z != t))
			return true;
		return false;
	}

	// Unary Negation/Plus
	template<typename types>
	inline Vector3<types> Vector3<types>::operator+() const
	{
		return *this;
	}

	// Unary Negation/Plus
	template<typename types>
	inline Vector3<types> Vector3<types>::operator-() const
	{
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Vector3<types>& Vector3<types>::operator++()
	{
		x++;
		y++;
		z++;
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Vector3<types> Vector3<types>::operator++(int)
	{
		auto out = *this;
		x++;
		y++;
		z++;
		return out;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Vector3<types>& Vector3<types>::operator--()
	{
		x--;
		y--;
		z--;
		return *this;
	}

	// Postfix Increment / Decrement
	template<typename types>
	inline Vector3<types> Vector3<types>::operator--(int)
	{
		auto out = *this;
		x--;
		y--;
		z--;
		return out;
	}

	template<typename types>
	inline Vector3<types> Vector3<types>::operator+(const Vector3& v)
	{
		Vector3<types> out;
		out.x = x + v.x;
		out.y = y + v.y;
		out.z = z + v.z;
		return out;
	}

	template<typename types>
	inline Vector3<types> Vector3<types>::operator-(const Vector3& v)
	{
		Vector3<types> out;
		out.x = x - v.x;
		out.y = y - v.y;
		out.z = z - v.z;
		return out;
	}

	template<typename types>
	inline Vector3<types> Vector3<types>::operator*(const Vector3& v)
	{
		Vector3<types> out;
		out.x = x * v.x;
		out.y = y * v.y;
		out.z = z * v.z;
		return out;
	}

	template<typename types>
	inline Vector3<types> Vector3<types>::operator/(const Vector3& v)
	{
		Vector3<types> out;
		out.x = x / v.x;
		out.y = y / v.y;
		out.z = z / v.z;
		return out;
	}

	template<typename types>
	inline Vector3<types>& Vector3<types>::operator=(const Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	template<typename types>
	inline Vector3<types>& Vector3<types>::operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	template<typename types>
	inline Vector3<types>& Vector3<types>::operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	template<typename types>
	inline Vector3<types>& Vector3<types>::operator*=(const Vector3& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	template<typename types>
	inline Vector3<types>& Vector3<types>::operator/=(const Vector3& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	template<typename types>
	inline Vector3<types> Vector3<types>::operator+(const types t) const
	{
		return Vector3(x + t, y + t, z + t);
	}

	template<typename types>
	inline Vector3<types> Vector3<types>::operator-(const types t) const
	{
		return Vector3(x - t, y - t, z - t);
	}

	template<typename types>
	inline Vector3<types> Vector3<types>::operator*(const types t) const
	{
		return Vector3(x * t, y * t, z * t);
	}

	template<typename types>
	inline Vector3<types> Vector3<types>::operator/(const types t) const
	{
		types tInv = (types)1;
		tInv = tInv / t;
		return Vector3(x * tInv, y * tInv, z * tInv);
	}

	template<typename types>
	inline Vector3<types>& Vector3<types>::operator=(const types t)
	{
		x = t;
		y = t;
		z = t;
		return *this;
	}

	template<typename types>
	inline Vector3<types>& Vector3<types>::operator+=(const types t)
	{
		x += t;
		y += t;
		z += t;
		return *this;
	}

	template<typename types>
	inline Vector3<types>& Vector3<types>::operator-=(const types t)
	{
		x -= t;
		y -= t;
		z -= t;
		return *this;
	}

	template<typename types>
	inline Vector3<types>& Vector3<types>::operator*=(const types t)
	{
		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	template<typename types>
	inline Vector3<types>& Vector3<types>::operator/=(const types t)
	{
		x /= t;
		y /= t;
		z /= t;
		return *this;
	}

	// Array Subscript
	template<typename types>
	inline const Vector3<types>& Vector3<types>::operator[](std::size_t n) const &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Vector3<types>& Vector3<types>::operator[](std::size_t n) &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Vector3<types> Vector3<types>::operator[](std::size_t n) &&
	{
		return std::move(this[n]);
	}

	//==========================================================================
	//
	// class  : Material
	// Content : Material
	// how to use : Material<float>,Material<int>,Material<double>...
	//
	//==========================================================================

	// Member Selection
	template<typename types>
	inline const Material<types>* Material<types>::operator->() const noexcept
	{
		return this;
	}

	// Member Selection
	template<typename types>
	inline Material<types>* Material<types>::operator->() noexcept
	{
		return this;
	}

	template<typename types>
	inline Material<types>& Material<types>::operator=(const Material& v)
	{
		Ambient = v.Ambient;
		Diffuse = v.Diffuse;
		Specular = v.Specular;
		Emission = v.Emission;
		Shininess = v.Shininess;
		return *this;
	}

	// Array Subscript
	template<typename types>
	inline const Material<types>& Material<types>::operator[](std::size_t n) const &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Material<types>& Material<types>::operator[](std::size_t n) &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Material<types> Material<types>::operator[](std::size_t n) &&
	{
		return std::move(this[n]);
	}

	//==========================================================================
	//
	// class  : Vertex3D
	// Content : Vertex3D
	// how to use : Vertex3D<float>,Vertex3D<int>,Vertex3D<double>...
	//
	//==========================================================================

	// Member Selection
	template<typename types>
	inline const Vertex3D<types>* Vertex3D<types>::operator->() const noexcept
	{
		return this;
	}

	// Member Selection
	template<typename types>
	inline Vertex3D<types>* Vertex3D<types>::operator->() noexcept
	{
		return this;
	}

	template<typename types>
	inline Vertex3D<types>& Vertex3D<types>::operator=(const Vertex3D& v)
	{
		TexturePos = v.TexturePos;
		Normal = v.Normal;
		Position = v.Position;
		Diffuse = v.Diffuse;
		return *this;
	}

	// Array Subscript
	template<typename types>
	inline const Vertex3D<types>& Vertex3D<types>::operator[](std::size_t n) const &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Vertex3D<types>& Vertex3D<types>::operator[](std::size_t n) &
	{
		return this[n];
	}

	// Array Subscript
	template<typename types>
	inline Vertex3D<types> Vertex3D<types>::operator[](std::size_t n) &&
	{
		return std::move(this[n]);
	}
}
using int2 = mslib_struct::Vector2<int>;
using int3 = mslib_struct::Vector3<int>;
using int4 = mslib_struct::Vector4<int>;

using float2 = mslib_struct::Vector2<float>;
using float3 = mslib_struct::Vector3<float>;
using float4 = mslib_struct::Vector4<float>;

using bool2 = mslib_struct::Vector2<bool>;
using bool3 = mslib_struct::Vector3<bool>;
using bool4 = mslib_struct::Vector4<bool>;

using intVertex3D = mslib_struct::Vertex3D<int>;
using floatVertex3D = mslib_struct::Vertex3D<float>;

using intUV = mslib_struct::UV<int>;
using floatUV = mslib_struct::UV<float>;

using intTexvec = mslib_struct::Texvec<int>;
using floatTexvec = mslib_struct::Texvec<float>;

using intColor = mslib_struct::Color<int>;
using floatColor = mslib_struct::Color<float>;

using intMaterial = mslib_struct::Material<int>;
using floatMaterial = mslib_struct::Material<float>;

_MSLIB_END