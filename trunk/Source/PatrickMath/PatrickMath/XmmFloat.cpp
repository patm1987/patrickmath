#include "stdafx.h"

#include "XmmFloat.h"
#include <limits>

const XmmFloat XmmFloat::EPSILON = XmmFloat(std::numeric_limits<float>::epsilon());
const XmmFloat XmmFloat::EPSILON_SQ = XmmFloat::EPSILON * XmmFloat::EPSILON;