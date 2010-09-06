#include "stdafx.h"

#include "XmmFloat.h"
#include <limits>
#include <stdint.h>

const XmmFloat XmmFloat::EPSILON = XmmFloat(std::numeric_limits<float>::epsilon());
const XmmFloat XmmFloat::EPSILON_SQ = XmmFloat::EPSILON * XmmFloat::EPSILON;

const XmmFloat XmmFloat::_PI = XmmFloat(3.14159265f);
const XmmFloat XmmFloat::_PI_2 = XmmFloat::_PI / XmmFloat(2.f);
const XmmFloat XmmFloat::_2PI = XmmFloat::_PI * XmmFloat(2.f);

union intfloat
{
	int32_t intPart;
	float floatPart;
} const floatMask = { 0x7FFFFFFF };
const XmmFloat XmmFloat::_FLOAT_ABS_MASK = XmmFloat(floatMask.floatPart);
