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

	//array_test::array_test_function(); //����array
	//vector_test::vector_test_function();  //����vector
	//forward_list_test::forward_list_test_function(); //����forward_list
	//memory_primitives_test::memory_primitives_test_function();  //����new��delete��
	//������������operator new��operator delete
	/*
	std::cout << "sizeof(Foo)" << sizeof(Foo) << std::endl;
	//����operator new��operator delete
	Foo *p = ::new Foo(7);
	::delete p;
	//����operator new[] ��operator delete[]
	Foo* pArray = ::new Foo[5];
	::delete[] pArray;
	*/
	//����placement new�Լ������캯���׳��쳣ʱ������delete

	//�����ڴ�����һ����
	//per_class_allocator::per_class_allocator_function();

	//�����ڴ����ڶ�����
	//per_class_allocator_two::per_class_allocator_two_function();

	//�����ڴ�������������װΪallocator1
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

