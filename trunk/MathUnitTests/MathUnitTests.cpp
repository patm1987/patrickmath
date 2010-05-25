// MathUnitTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../MathLib/Vector4.h"

#include <iostream>

bool testAdd()
{
	Vector4::Container container0 = {1,2,3,4};
	Vector4::Container container1 = {1,1,1,1};

	Vector4 vec0 (container0);
	Vector4 vec1 (container1);
	Vector4 result = vec0 + vec1;

	Vector4::Container resultContainer;
	result.write(resultContainer);

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
	result.write(resultContainer);

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
	result.write(resultContainer);

	return resultContainer.x == -1 &&
		resultContainer.y == -2 &&
		resultContainer.z == -3 &&
		resultContainer.w == -4 ;
}

bool testDot()
{
	return false;
}

bool testCross()
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

