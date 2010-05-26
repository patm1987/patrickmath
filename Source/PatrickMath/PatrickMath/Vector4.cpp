#include "stdafx.h"
#include "Vector4.h"

const Vector4::Container unitX = {1,0,0,0};
const Vector4::Container unitY = {0,1,0,0};
const Vector4::Container unitZ = {0,0,1,0};
const Vector4::Container unitW = {0,0,0,1};

const Vector4 Vector4::ZERO = Vector4();
const Vector4 Vector4::ZERO_VECTOR = Vector4::ZERO;
const Vector4 Vector4::ZERO_POINT = Vector4::UNIT_W;
const Vector4 Vector4::UNIT_X = unitX;
const Vector4 Vector4::UNIT_Y = unitY;
const Vector4 Vector4::UNIT_Z = unitZ;
const Vector4 Vector4::UNIT_W = unitW;
