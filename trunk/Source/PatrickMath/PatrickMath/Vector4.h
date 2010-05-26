#pragma once

#include <xmmintrin.h>

__declspec(align(16))
class Vector4
{
public:
	__declspec(align(16))
	struct Container
	{
		union
		{
			struct { float x, y, z, w; };
			float elements [4];
		};
	};

public:
	// constructors
	Vector4 ();
	Vector4 (const Vector4 &copy);
	Vector4 (const Container &container);

	// assignment operators
	Vector4 &operator=(const Vector4 &copy);
	Vector4 &operator=(const Container &copy);

	// fast operations

	// named
	__m128 dotProduct(const Vector4 &rhs);
	Vector4 &add(const Vector4 &rhs);
	Vector4 &subtract(const Vector4 &rhs);
	Vector4 &negate();
	Vector4 &crossProduct(const Vector4 &rhs);
	Vector4 &normalize();

	// operators
	inline __m128 operator* (const Vector4 &rhs)	{return dotProduct(rhs);}
	inline Vector4 &operator+ (const Vector4 &rhs)	{return add(rhs);}
	inline Vector4 &operator- (const Vector4 &rhs)	{return subtract(rhs);}
	inline Vector4 &operator- ()					{return negate();}
	inline Vector4 &operator^ (const Vector4 &rhs)	{return crossProduct(rhs);}
	inline Vector4 &operator~ ()					{return normalize();}

	// reads
	Container &write(Container &destination) const;

	// writes
	Vector4 &set(const Container &source);

	/*
	* TODO:
	*	equality operator (==)
	*	equality with epsilon
	*	safe normalize (epsilon for 0)
	*	override new and delete for _aligned_malloc and free, everything must lie on 16 byte boundaries
	*	create a FLOAT shell type (for dot product) holding an __m128 indicating a single float (either in the first index or all 4 indicies)
	*/

public:
	static const Vector4 ZERO;
	static const Vector4 ZERO_VECTOR;
	static const Vector4 ZERO_POINT;
	static const Vector4 UNIT_X;
	static const Vector4 UNIT_Y;
	static const Vector4 UNIT_Z;
	static const Vector4 UNIT_W;
	
private:
	__m128 elements;
};

inline Vector4::Vector4()
{
	elements = _mm_setzero_ps();
}

/*!
* Initializes a Vector4 with another Vector4
*/
inline Vector4::Vector4(const Vector4 &copy)
{
	elements = copy.elements;
}

/*!
* Initializes a Vector4 with a Vector4::Container holding the initial data to load to the SSE registers
* \param container the container containing four floats to load the SSE registers
*/
inline Vector4::Vector4(const Vector4::Container &container)
{
	set(container);
}

/*!
* Assignment operator
* \param copy the Vector4 to copy
* \return a reference to this Vector4
*/
inline Vector4 &Vector4::operator=(const Vector4 &copy)
{
	elements = copy.elements;
	return *this;
}

/*!
* Performs an assignment to a container, caution this is slow
* \param copy the container to load
* \return a reference to this
*/
inline Vector4 &Vector4::operator=(const Vector4::Container &copy)
{
	set(copy);
	return *this;
}

/*!
* Perform the dot product between two vector4's
* \param rhs the right hand side of the dot product
* \return a __m128 where every 32 bits is a float indicating the dot product
*/
inline __m128 Vector4::dotProduct(const Vector4 &rhs)
{
	__m128 r0, r1;
	r0 = _mm_mul_ps(elements, rhs.elements); // l0*r0, l1*r1, l2*r2, l3*r3; 0, 1, 2, 3
	r1 = _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(0,1,2,3)); // 3, 2, 1, 0
	r0 = _mm_add_ps(r0, r1); // 0+3, 1+2, 1+2, 0+3
	r1 = _mm_shuffle_ps(r0, r0, _MM_SHUFFLE(1,0,3,2)); // 1+2, 0+3, 1+3, 0+3
	
	return _mm_add_ps(r0, r1);
}

/*!
* Adds two Vector4's
* \param rhs the right hand side of the equation
* \return a reference to this Vector4
*/
inline Vector4 &Vector4::add(const Vector4 &rhs)
{
	elements = _mm_add_ps(elements, rhs.elements);
	return *this;
}

/*!
* Subtract's two Vector4's
* \param rhs the right hand side of the equation
* \return a reference to this Vector4
*/
inline Vector4 &Vector4::subtract(const Vector4 &rhs)
{
	elements = _mm_sub_ps(elements, rhs.elements);
	return *this;
}

/*!
* Negate this Vector4
* \return a reference to this Vector4
*/
inline Vector4 &Vector4::negate()
{
	elements = _mm_sub_ps(_mm_setzero_ps(), elements);
	return *this;
}

/*!
* Cross two Vector4's, assume the first 3 elements of each are properly filled and the final element is 0
* \param rhs the right hand side of the equation
* \return a reference to this Vector4
*/
inline Vector4 &Vector4::crossProduct(const Vector4 &rhs)
{
	__m128 temp1 = _mm_shuffle_ps(elements, elements, _MM_SHUFFLE(3,0,2,1));
	__m128 temp2 = _mm_shuffle_ps(rhs.elements, rhs.elements, _MM_SHUFFLE(3,1,0,2));
	__m128 mult1 = _mm_mul_ps(temp1, temp2);

	temp1 = _mm_shuffle_ps(elements, elements, _MM_SHUFFLE(3, 1, 0, 2));
	temp2 = _mm_shuffle_ps(rhs.elements, rhs.elements, _MM_SHUFFLE(3,0,2,1));
	__m128 mult2 = _mm_mul_ps(temp1, temp2);

	// TODO: I can knock this down to 3 variables, but does that gain me any speed benefits (it sure would kill readability)?

	elements = _mm_sub_ps(mult1, mult2);

	return *this;
}

/*!
* Normalizes a Vector4, does not perform a divide by zero check, does not verify that the 4th elment (w) is 0
* Normalizing a point has no value, so I choose to ignore this.  Also could be useful if extended to a Quaternion class
* \return a reference to this Vector4
*/
inline Vector4 &Vector4::normalize()
{
	__m128 length = _mm_sqrt_ps(dotProduct(*this));
	elements = _mm_div_ps(elements, length);

	return *this;
}

/*!
* Writes the elements out to a Container (slow: reading from SSE registers)
* \param destination the Container to store the result
* \return a reference to the Container filled
*/
inline Vector4::Container &Vector4::write(Vector4::Container &destination) const
{
	_mm_store_ps(destination.elements, elements);
	return destination;
}

/*!
* Sets this Vector4 given a Container
* \param source the source container to set from
* \return a reference to this Vector4
*/
inline Vector4 &Vector4::set(const Vector4::Container &source)
{
	elements = _mm_load_ps(source.elements);
	return *this;
}