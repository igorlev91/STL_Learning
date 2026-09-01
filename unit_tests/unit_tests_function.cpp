#include "xrstl/fixed_function.h"

#include <functional>

#include <stdio.h>

int DummyA = 4;

void DummyVoidFunction()
{
	printf("Hello %d\n", DummyA);
}

int DummyIntFunction(int value)
{
	printf("DummyIntFunction %d\n", value);
	return -1;
}

int DummyIntFunction2(int value)
{
	printf("DummyIntFunction2 %d\n", value);
	return -1;
}

void FunctionPassByReferenceTest(const xrstl::fixed_function<void(int), 8>& myFunction, int k)
{
	myFunction(k);
}

struct OperatorStruct
{
	OperatorStruct() {}

	void operator()(void) const
	{

	}
};

void RunUnitTestsFunction()
{
	int a = 3;

	std::function<void()> stdVoidFunction;

	std::function<void()> stdVoidFunction2 = []()
	{
		printf("stdVoidFunction2\n");
	};

	std::function<void()> stdVoidFunction3 = [a]()
	{
		printf("stdVoidFunction3 %d\n", a);
	};

	std::function<void(int)> stdIntFunction;

	stdIntFunction = &DummyIntFunction;

	xrstl::fixed_function<void(), 8> crVoidFunction;
	
	xrstl::fixed_function<void(), 16> crVoidFunction2 = []()
	{
		printf("crVoidFunction2\n");
	};

	xrstl::fixed_function<void(), 8> crVoidFunction3 = [a]()
	{
		printf("crVoidFunction3 %d\n", a);
	};
	
	xrstl::fixed_function<void(), 8> crVoidFunction4 = &DummyVoidFunction;

	xrstl::fixed_function<int(int), 8> crIntFunction = &DummyIntFunction;

	xrstl::fixed_function<int(int), 8> crIntFunctionNonConst = &DummyIntFunction2;

	const xrstl::fixed_function<int(int), 8> crIntFunctionConst = &DummyIntFunction2;

	const xrstl::fixed_function<void(void), 8> crMoveOnlyFunction = OperatorStruct();

	crIntFunction = crIntFunctionNonConst;
	xrstl::fixed_function<int(int), 8> crIntFunctionCopy1(crIntFunctionNonConst);
	xrstl::fixed_function<int(int), 8> crIntFunctionCopy2(crIntFunctionConst);
	xrstl::fixed_function<int(int), 8> crIntFunctionMove(std::move(crIntFunctionNonConst));

	crIntFunctionConst(5);

	// Call functions

	if (stdVoidFunction)
	{
		stdVoidFunction();
	}

	if (crVoidFunction)
	{
		crVoidFunction();
	}

	stdVoidFunction2();
	crVoidFunction2();
	
	stdVoidFunction3();
	crVoidFunction3();
	
	//stdVoidFunction4();
	crVoidFunction4();

	int i = crIntFunction(4);
	printf("IntFunction %d", i);

	//printf("Hello\n");
	//printf("Hello %d\n", a);
}