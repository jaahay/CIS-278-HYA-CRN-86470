#include "FunctionLocal.h"
#include <iostream>

static void FnLocalVariable() {
	std::cout << "FnLocalVariable top" << std::endl;
	{
		int a = 1;
		std::cout << "a: " << a << std::endl; // 1
	}
	{
		int b = int{};
		std::cout << "b: " << b << std::endl; // 0
	}
	{
		int c = int{ 3 };
		std::cout << "c: " << c << std::endl; // 3
	}
	{
		int d = { 4 };
		std::cout << "d: " << d << std::endl; // 4
	}
	std::cout << "FnLocalVariable bottom" << std::endl;
}

static void FnLocalPointer() {
	std::cout << "FnLocalPointer top" << std::endl;
	{
		int a = 1;
		int* ref_a = &a;
		int ptr_ref_a = *ref_a;
		int** dbl_ref_a = &ref_a;
		int* ptr_dbl_ref_a = *dbl_ref_a;
		// a: 1 ref_a: 000000A3AD0FF4E4 ptr_ref_a: 1 dbl_ref_a: 000000A3AD0FF508 ptr_dbl_ref_a: 000000A3AD0FF4E4
		std::cout << "a: " << a << " ref_a: " << ref_a << " ptr_ref_a: " << ptr_ref_a << " dbl_ref_a: " << dbl_ref_a << " ptr_dbl_ref_a: " << ptr_dbl_ref_a << std::endl;
	}
	std::cout << "FnLocalPointer bottom" << std::endl;
}

static void FnLocalReference() {
	std::cout << "FnLocalReference top" << std::endl;
	{
		int a = 1;
		int& ref_a = a;
		std::cout << "a: " << a << " ref_a: " << ref_a << std::endl;
	}
	{
		int b = 2;
		int* ptr_to_ref_b = &b;
		// b: 2 ptr_to_ref_b : 00000021742FF6A4
		std::cout << "b: " << b << " ptr_to_ref_b: " << ptr_to_ref_b << std::endl;
	}
	{
		int c = 3;
		int* ptr_to_ref_c = &c;
		int** ptr_ptr_to_ptr_to_ref_c = &ptr_to_ref_c;
		// c: 3 ptr_to_ref_c : 00000021742FF6E4 ptr_ptr_to_ptr_to_ref_c : 00000021742FF708
		std::cout << "c: " << c << " ptr_to_ref_c: " << ptr_to_ref_c << " ref_dbl_c: " << ptr_ptr_to_ptr_to_ref_c << std::endl;
	}
	std::cout << "FnLocalReference bottom" << std::endl;
}

int FnLocalMain() {
	FnLocalVariable();
	FnLocalPointer();
	FnLocalReference();
	return 0;
}