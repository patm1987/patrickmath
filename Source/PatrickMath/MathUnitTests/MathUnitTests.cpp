// MathUnitTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../PatrickMath/Vector4.h"
#include "../PatrickMath/XmmFloat.h"

#include <iostream>

bool testAdd()
{
	Vector4::Container container0 = {1,2,3,4};
	Vector4::Container container1 = {1,1,1,1};

	Vector4 vec0 (container0);
	Vector4 vec1 (container1);
	Vector4 result = vec0 + vec1;

	Vector4::Container resultContainer;
	result.get(resultContainer);

	return resultContainer.x == 2 &&
		resultContainer.y == 3 &&
		resultContainer.z == 4 &&
		resultContainer.w == 5 ;
}

bool testSubtract()
{
	Vector4::Container container0 = {1,2,3,4};
	Vector4::Container container1 = {1,1,1,1};

	Vector4 vec0 (container0);
	Vector4 vec1 (container1);
	Vector4 result = vec0 - vec1;

	Vector4::Container resultContainer;
	result.get(resultContainer);

	return resultContainer.x == 0 &&
		resultContainer.y == 1 &&
		resultContainer.z == 2 &&
		resultContainer.w == 3 ;
}

bool testNegate()
{
	Vector4::Container container = {1,2,3,4};

	Vector4 vec (container);
	Vector4 result = -vec;

	Vector4::Container resultContainer;
	result.get(resultContainer);

	return resultContainer.x == -1 &&
		resultContainer.y == -2 &&
		resultContainer.z == -3 &&
		resultContainer.w == -4 ;
}

bool testDot()
{
	Vector4::Container load = {1,2,3,4};
	Vector4 test = Vector4(load);
	__declspec(align(16)) float resultContainer[4];
	
	__m128 result = test*Vector4::ZERO;
	_mm_store_ps(resultContainer, result);
	if ( resultContainer[0] != 0 )
	{
		return false;
	}
	
	result = test*Vector4::UNIT_X;
	_mm_store_ps(resultContainer, result);
	if ( resultContainer[0] != 1 )
	{
		return false;
	}
	
	result = test*Vector4::UNIT_Y;
	_mm_store_ps(resultContainer, result);
	if ( resultContainer[0] != 2 )
	{
		return false;
	}
	
	result = test*Vector4::UNIT_Z;
	_mm_store_ps(resultContainer, result);
	if ( resultContainer[0] != 3 )
	{
		return false;
	}
	
	result = test*Vector4::UNIT_W;
	_mm_store_ps(resultContainer, result);
	if ( resultContainer[0] != 4 )
	{
		return false;
	}

	// this is fun
	result = test * (Vector4::UNIT_X + Vector4::UNIT_Y + Vector4::UNIT_Z + Vector4::UNIT_W);
	_mm_store_ps(resultContainer, result);
	if ( resultContainer[0] != 10 )
	{
		return false;
	}

	return true;
}

bool testCross()
{
	// just basic test... I will need to be more thorough later
	Vector4 result = Vector4::UNIT_X ^ Vector4::UNIT_Y;
	Vector4::Container resultContainer;
	result.get(resultContainer);
	
	return resultContainer.x == 0 && resultContainer.y == 0 && resultContainer.z == 1 && resultContainer.w == 0;
}

bool testNormalize()
{
	return false;
}

bool testEquality()
{
	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Addition: " << testAdd() << std::endl;
	std::cout << "Subtraction: " << testSubtract() << std::endl;
	std::cout << "Negation: " << testNegate() << std::endl;
	std::cout << "Dot Product: " << testDot() << std::endl;
	std::cout << "Cross Product: " << testCross() << std::endl;
	return 0;
}

