#include <iostream>
#include "array_test.h"
#include "vector_test.h"
#include "forward_list_test.h"
#include "memory_primitives_test.h"
#include "per_class_allocator.h"
#include "per_class_allocator_two.h"
#include "static_allocator.h"

using namespace array_test;
using namespace vector_test;
using namespace memory_primitives_test;
using namespace per_class_allocator;
int main() {

	//array_test::array_test_function(); //测试array
	//vector_test::vector_test_function();  //测试vector
	//forward_list_test::forward_list_test_function(); //测试forward_list
	//memory_primitives_test::memory_primitives_test_function();  //测试new及delete等
	//测试类内重载operator new和operator delete
	/*
	std::cout << "sizeof(Foo)" << sizeof(Foo) << std::endl;
	//测试operator new和operator delete
	Foo *p = ::new Foo(7);
	::delete p;
	//测试operator new[] 和operator delete[]
	Foo* pArray = ::new Foo[5];
	::delete[] pArray;
	*/
	//测试placement new以及当构造函数抛出异常时，调用delete

	//迈出内存管理第一步：
	//per_class_allocator::per_class_allocator_function();

	//迈出内存管理第二步：
	//per_class_allocator_two::per_class_allocator_two_function();

	//迈出内存管理第三步：封装为allocator1
	static_allocator::static_allocator_function();
	/*
	try {
		throw 20;
	} catch (int e) {
		std::cout << "An exception occurred. Exception Nr. " << e << '\n';
	}
	*/

	system("pause");
	return 0;
	
}

