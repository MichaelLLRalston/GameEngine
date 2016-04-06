#include <iostream>
#include <cassert>

#include "Vector2.h"
#include "Matrix3.h"
#include "Vector3.h"

int main()
{
	std::cout << "Testing math functions..." << std::endl;

	// unit tests

	// have test subjects
	Matrix3 example;
	example.c[0] = { 0,1,2 };
	example.c[1] = { 3,4,5 };
	example.c[2] = { 6,7,8 };

	//float result = example.determinant();	// perform the function being tested
	//float expected = 0.0f;	// provide the expected result

	//// this should not fail
	//assert(abs(result - expected) < FLT_EPSILON);		// compare to see if we get our expected result

	example.print(); 
	cout << "\n\n";
	example.determinant();
	example.print();

	system("pause");

	return 0;
}