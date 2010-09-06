#pragma once

#include <limits>
#include "Vector4.h"
#include "XmmFloat.h"

__declspec(align(16))
class Quaternion
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
	Quaternion();
	Quaternion(const Quaternion &copy);
	Quaternion(const Container &container);
	Quaternion(const Vector4 &axis, const XmmFloat &angle);Quaternion(const Vector4 &axis, const XmmFloat &cosAngle, const XmmFloat &sinAngle);
	Quaternion(const Vector4::Container &axis, float angle);

	XmmFloat dotProduct(const Quaternion &rhs) const;
	Quaternion add(const Quaternion &rhs) const;
	Quaternion subtract(const Quaternion &rhs) const;
	Quaternion multiply(const Quaternion &rhs) const;
	Quaternion divide(const Quaternion &rhs) const;
	Quaternion conjugate() const;
	Quaternion normalize() const;
	Quaternion safeNormalize(const XmmFloat &epsilon = XmmFloat::EPSILON) const;
	Quaternion safeNormalizeSq(const XmmFloat &epsilonSq = XmmFloat::EPSILON_SQ) const;

	// do not confuse with normalize, this is the "norm" (length in R^3)
	XmmFloat norm() const;
	XmmFloat normSq() const;

	XmmBool isEqual(const Quaternion &rhs) const;
	XmmBool isEqual(const Quaternion &rhs, const XmmFloat &epsilon) const;

	Container &get(Container &destination) const;
	Quaternion &set(const Container &source);

	Vector4 applyRotation(const Vector4 &rhs) const;

public:
	static const Quaternion IDENTITY;
	static const Quaternion ZERO;

private:
	__m128 elements;
};

Quaternion::Quaternion()
{
	elements = IDENTITY.elements;
}

Quaternion::Quaternion(const Quaternion &copy)
{
	elements = copy.elements;
}
