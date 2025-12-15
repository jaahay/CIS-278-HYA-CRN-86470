#include "FunctionArg.h"
#include <iostream>

static int FnArgVariableRet(int i) {
	std::cout << "FnArgVariable i: " << i << std::endl;
	return i;
}

static void FnArgVariable() {
	std::cout << "FnArgVariable top" << std::endl;
	int a = 1;
	int ret_a = FnArgVariableRet(a);
	std::cout << "a: " << a << " ret_a: " << ret_a << std::endl;
	int b = 2;
	int* ptr_to_ref_b = &b;
	int ptr_ptr_to_ref_b = *ptr_to_ref_b;
	int ret_b = FnArgVariableRet(ptr_ptr_to_ref_b);
	std::cout << "b: " << b << " ret_b: " << ret_b << std::endl;
	std::cout << "FnArgVariable bottom" << std::endl;
}

static void FnArgPointer() {

}

static void FnArgReference() {

}

//static void FnArgConstVariable() {}
//static void FnArgConstPointer() {}
//static void FnArgConstReference() {}

int FnArgMain() {
	FnArgVariable();
	FnArgPointer();
	FnArgReference();
	//FnArgConstVariable();
	//FnArgConstPointer();
	//FnArgConstReference();
	return 0;
}