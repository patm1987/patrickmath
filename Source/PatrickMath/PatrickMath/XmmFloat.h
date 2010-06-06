/*!
* \file XmmFloat.h
* \author Patrick Martin
* \date 2010
* \brief Floating point values represented via XMM registers.  Every 32 bits should be identical
* 
* This is a class for storing and operating on floating point values stored in SSE registers.  Every 32 bytes should be
* identical (as opposed to just maintaining the first one).  This is to accomondate fast operations with Vector4's.
*
* This project is governed by the MIT licence:
* 
*  Copyright (c) 2010 Patrick Martin
* 
*  Permission is hereby granted, free of charge, to any person
*  obtaining a copy of this software and associated documentation
*  files (the "Software"), to deal in the Software without
*  restriction, including without limitation the rights to use,
*  copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the
*  Software is furnished to do so, subject to the following
*  conditions:
* 
*  The above copyright notice and this permission notice shall be
*  included in all copies or substantial portions of the Software.
* 
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
*  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
*  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
*  OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <xmmintrin.h>

#include "XmmBool.h"

/*!
* \class XmmFloat
* \brief provides a wrapper for common floating point operations on sse registers
*
* This is a very shallow wrapper around SSE2 intrinsics.  Always assume that making any single function call from this
* class is faster than any two even if you think it will be cleaner using a provided operator.
*/
__declspec(align(16))
class XmmFloat
{
public:
	XmmFloat();
	XmmFloat(const XmmFloat &copy);
	XmmFloat(const __m128 &value);
	explicit XmmFloat(const float &value);

	// operator overloads
	inline XmmFloat operator-() const						{return negate();}
	inline XmmFloat operator+(const XmmFloat &rhs) const	{return add(rhs);}
	inline XmmFloat operator-(const XmmFloat &rhs) const	{return subtract(rhs);}
	inline XmmFloat operator/(const XmmFloat &rhs) const	{return divide(rhs);}
	inline XmmFloat operator*(const XmmFloat &rhs) const	{return multiply(rhs);}

	// caution: these logical operations do not return a value usable in an if statement (do not return a bool)
	inline XmmBool operator==(const XmmFloat &rhs) const	{return isEqual(rhs);}
	inline XmmBool operator >(const XmmFloat &rhs) const	{return isGreaterThan(rhs);}
	inline XmmBool operator>=(const XmmFloat &rhs) const	{return isGreaterThanOrEqual(rhs);}
	inline XmmBool operator <(const XmmFloat &rhs) const	{return isLessThan(rhs);}
	inline XmmBool operator<=(const XmmFloat &rhs) const	{return isLessThanOrEqual(rhs);}
	inline XmmBool operator!=(const XmmFloat &rhs) const	{return isNotEqual(rhs);}
	
	// named arithmetic operations
	XmmFloat sqrt() const;
	XmmFloat invSqrt() const;
	XmmFloat inverse() const;

	XmmFloat negate() const;
	XmmFloat add(const XmmFloat &rhs) const;
	XmmFloat subtract(const XmmFloat &rhs) const;
	XmmFloat divide(const XmmFloat &rhs) const;
	XmmFloat multiply(const XmmFloat &rhs) const;

	// logic operations
	XmmBool isEqual(const XmmFloat &cmp) const;
	XmmBool isLessThan(const XmmFloat &cmp) const;
	XmmBool isLessThanOrEqual(const XmmFloat &cmp) const;
	XmmBool isGreaterThan(const XmmFloat &cmp) const;
	XmmBool isGreaterThanOrEqual(const XmmFloat &cmp) const;
	XmmBool isNotEqual(const XmmFloat &cmp) const;
	XmmBool isNotLessThan(const XmmFloat &cmp) const;
	XmmBool isNotLessThanOrEqual(const XmmFloat &cmp) const;
	XmmBool isNotGreaterThan(const XmmFloat &cmp) const;
	XmmBool isNotGreaterThanOrEqual(const XmmFloat &cmp) const;

	static XmmFloat min(const XmmFloat &lhs, const XmmFloat &rhs);
	static XmmFloat max(const XmmFloat &lhs, const XmmFloat &rhs);

	// read/write
	float &get(float &destination) const;
	XmmFloat &set(float source);

	operator __m128 ();

	static const XmmFloat EPSILON;
	static const XmmFloat EPSILON_SQ;

private:
	__m128 m_value;
};

/*!
* Default constructor will initialize to 0
*/
inline XmmFloat::XmmFloat()
{
	_mm_setzero_ps();
}

inline XmmFloat::XmmFloat(const XmmFloat &copy)
{
	m_value = copy.m_value;
}

inline XmmFloat::XmmFloat(const __m128 &value)
{
	m_value = value;
}

/*!
* Require an explicit conversion from float, keep user informed that this is an expensive copy
* \param value the value to store, loads an __m128
*/
inline XmmFloat::XmmFloat(const float &value)
{
	set(value);
}

inline XmmFloat XmmFloat::sqrt() const
{
	return _mm_sqrt_ps(m_value);
}

inline XmmFloat XmmFloat::invSqrt() const
{
	return _mm_rsqrt_ps(m_value);
}

inline XmmFloat XmmFloat::inverse() const
{
	return _mm_rcp_ps(m_value);
}

inline XmmFloat XmmFloat::negate() const
{
	return _mm_sub_ps(_mm_setzero_ps(),m_value);
}

inline XmmFloat XmmFloat::add(const XmmFloat &rhs) const
{
	return _mm_add_ps(m_value, rhs.m_value);
}

inline XmmFloat XmmFloat::subtract(const XmmFloat &rhs) const
{
	return _mm_sub_ps(m_value, rhs.m_value);
}

inline XmmFloat XmmFloat::divide(const XmmFloat &rhs) const
{
	return _mm_div_ps(m_value, rhs.m_value);
}

inline XmmFloat XmmFloat::multiply(const XmmFloat &rhs) const
{
	return _mm_div_ps(m_value, rhs.m_value);
}

inline XmmBool XmmFloat::isEqual(const XmmFloat &cmp) const
{
	return _mm_cmpeq_ps(m_value, cmp.m_value);
}

inline XmmBool XmmFloat::isLessThan(const XmmFloat &cmp) const
{
	return _mm_cmplt_ps(m_value, cmp.m_value);
}

inline XmmBool XmmFloat::isLessThanOrEqual(const XmmFloat &cmp) const
{
	return _mm_cmple_ps(m_value, cmp.m_value);
}

inline XmmBool XmmFloat::isGreaterThan(const XmmFloat &cmp) const
{
	return _mm_cmpgt_ps(m_value, cmp.m_value);
}

inline XmmBool XmmFloat::isGreaterThanOrEqual(const XmmFloat &cmp) const
{
	return _mm_cmpge_ps(m_value, cmp.m_value);
}

inline XmmBool XmmFloat::isNotEqual(const XmmFloat &cmp) const
{
	return _mm_cmpneq_ps(m_value, cmp.m_value);
}

inline XmmBool XmmFloat::isNotLessThan(const XmmFloat &cmp) const
{
	return _mm_cmpnlt_ps(m_value, cmp.m_value);
}

inline XmmBool XmmFloat::isNotLessThanOrEqual(const XmmFloat &cmp) const
{
	return _mm_cmpnle_ps(m_value, cmp.m_value);
}

inline XmmBool XmmFloat::isNotGreaterThan(const XmmFloat &cmp) const
{
	return _mm_cmpngt_ps(m_value, cmp.m_value);
}

inline XmmBool XmmFloat::isNotGreaterThanOrEqual(const XmmFloat &cmp) const
{
	return _mm_cmpnge_ps(m_value, cmp.m_value);
}

inline XmmFloat XmmFloat::min(const XmmFloat &lhs, const XmmFloat &rhs)
{
	return _mm_min_ps(lhs.m_value, rhs.m_value);
}

inline XmmFloat XmmFloat::max(const XmmFloat &lhs, const XmmFloat &rhs)
{
	return _mm_max_ps(lhs.m_value, rhs.m_value);
}

inline float &XmmFloat::get(float &destination) const
{
	_mm_store_ss(&destination, m_value);
}

inline XmmFloat &XmmFloat::set(float source)
{
	m_value = _mm_load1_ps(&source);
}

/*!
* This is very bad C++ form, but it permits using the XmmFloat in intrinsics, on the other hand the only reason for
* this class is to provide useful functions on sse registers while maintaining a sharp perceived wall between SSE
* instructions and normal instructions.
* TODO: re-evaluate and see if it can be removed after ironing out other operations (this kills type safety to an
* extent)
* \return the __m128 representing this object
*/
XmmFloat::operator __m128 ()
{
	return m_value;
}
