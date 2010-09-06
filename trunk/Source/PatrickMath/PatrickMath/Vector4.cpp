/*!
* \file Vector4.cpp
* \author Patrick Martin
* \date 2010
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