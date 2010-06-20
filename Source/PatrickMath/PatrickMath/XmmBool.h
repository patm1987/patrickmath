/*!
* \file XmmBool.h
* \author Patrick Martin
* \date 2010
* \brief Boolean values and logic represented via XMM registers.  Every 32 bits should be identical
* 
* This is a class for storing and operating on boolean values stored in SSE registers.  Every 32 bytes should be
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

/*!
* An XmmBool stores the result of a logical operation.  You cannot use this in a traditional granch unless you read the
* value into a traditional bool (or int).  Correct values are only all bits 0 or all bit 1, in this way an XmmBool can
* provide basic logic operation without requiring a branch (which would require a read back into normal registers)
*/
class XmmBool
{
	// TODO: finish
public:
	XmmBool();
	XmmBool(const XmmBool &copy);
	XmmBool(const __m128 &copy);
	explicit XmmBool(bool copy);

	bool getValue() const;

	operator __m128() const;
private:
	__m128 m_value;
};

inline XmmBool::XmmBool()
{
	m_value = _mm_setzero_ps();
}

inline XmmBool::XmmBool(const XmmBool &copy)
{
	m_value = copy.m_value;
}

inline XmmBool::XmmBool(const __m128 &copy)
{
	m_value = copy;
}

inline bool XmmBool::getValue() const
{
	float destination;
	_mm_store_ss(&destination, m_value);

	return destination != 0.f;
}

/*!
* TODO: finish writing boolean operations so this isn't necessary
*/
inline XmmBool::operator __m128 () const
{
	return m_value;
}
