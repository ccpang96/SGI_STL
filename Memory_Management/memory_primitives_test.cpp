#include <cstdlib>
#include <iostream>
#include "memory_primitives_test.h"
#include <vector>
#include <memory>
#include <new>
namespace memory_primitives_test {
	void memory_primitives_test_function() {

		std::cout << "malloc test start" << std::endl;
		void *p1 = malloc(512);  //512bytes
		free(p1);
		std::cout << "malloc test is over" << std::endl;
		//2.new的测试
		std::cout << "new test start" << std::endl;
		std::vector<int>* p2 = new std::vector<int>;
		delete p2;
		std::cout << "new test is over" << std::endl;
		//new 被编译器拆分成以下几个步骤：
		


		std::cout << "operator new test start" << std::endl;
		void *p3 = ::operator new (512); //直接执行全局作用域中的operator new
		::operator delete(p3);
		std::cout << "operator new test is over" << std::endl;

		//测试allocators,其接口虽然有标准规格，但是不同的厂商实现了不同的接口	
		//一般不会通过分配器直接拿内存
#ifdef _MSC_VER
		std::cout << "allocator test start" << std::endl;
		int *p4 = std::allocator<int>().allocate(3, (int*)0); //分配3个ints
		std::allocator<int>().deallocate(p4, 3);
		std::cout << "allocator test is over" << std::endl;
#endif

#ifdef __BORLANDC__
		int *p4 = allocator<int>().allocate(5);
		allocator<int>().deallocate(p4, 5);
#endif

#ifdef __GNUC__
		void *p4 = alloc::allocate(512);
		alloc::deallocate(p4, 512);
#endif


	//placement new
		/*
		char *buf = new char[sizeof(Complex) * 3];
		Complex *pc = new(buf)Complex(1,2);

		delete [] buf;

	//被编译器转为
		Complex *pc;
		try {
			void *mem = operator new(sizeof(Complex), buf);
			pc = static_cast<Complex*>(mem);
			pc->Complex::Complex(1, 2);
		}
		catch (std::bad_alloc)
		{
			//若分配失败，则不执行constructor
		}*/
	}

	//Foo内的operator new
	void *Foo::operator new(size_t size) {
		Foo* p = (Foo*)malloc(size);
		std::cout << "Foo operator new" << std::endl;;
		return p;
	}
	//Foo内的operator delete
	void Foo::operator delete(void* pdead, size_t size) {
		std::cout << "Foo opeartor delete" << std::endl;
		free(pdead);
	}
	//Foo内的operator new[]
	void *Foo::operator new[](size_t size) {
		Foo* p = (Foo*)malloc(size);
		std::cout << "Foo operator new[]" << std::endl;;
		return p;
	}
	//Foo内的operator delete[]
	void Foo::operator delete[](void* pdead, size_t size) {
		std::cout << "Foo opeartor delete[]" << std::endl;
		free(pdead);
	}

	//重载new()和delete()
	void* Foo::operator new(size_t size, void *start) {
		return start;
	}
	void* Foo::operator new(size_t size, long extra) {
		return malloc(size + extra);
	}
	void* Foo::operator new(size_t size, long extra, char init) {
		return malloc(size + extra);
	}

	/*
	//如果调用构造函数失败，才会调用如下的构造函数
	void Foo::operator delete (void*, size_t) {
		std::cout << "operator delete(void*,size_t)" << std::endl;
	}
	*/
	void Foo::operator delete(void*, void*) {
		std::cout << "operator delete(void*,void*)" << std::endl;
	}
	void Foo::operator delete(void*, long) {
		std::cout << "operator delete(void*,long)" << std::endl;
	}
	void Foo::operator delete(void*, long, char) {
		std::cout << "operator delete(void*,long,char)" << std::endl;
	}

}




/*
//重载全局::operator new /::operator delete /::operator new[] /::operator delete[]
void* myAlloc(size_t size) {
	return malloc(size); //返回一个指针指向malloc的内存
}

void myFree(void *ptr) {
	return free(ptr);
}

inline void * operator new(size_t size) {
	std::cout << "global new() \n ";
	return myAlloc(size);
}

inline void* operator new[](size_t size) {
	std::cout << "global new() \n";
	return myAlloc(size);
}

inline void operator delete(void* ptr) {
	std::cout << "global delete() \n";
	return myFree(ptr);
}

inline void operator delete[](void *ptr) {
	std::cout << "global delete [] \n";
	myFree(ptr);
}

*/