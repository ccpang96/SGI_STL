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
		//2.new�Ĳ���
		std::cout << "new test start" << std::endl;
		std::vector<int>* p2 = new std::vector<int>;
		delete p2;
		std::cout << "new test is over" << std::endl;
		//new ����������ֳ����¼������裺
		


		std::cout << "operator new test start" << std::endl;
		void *p3 = ::operator new (512); //ֱ��ִ��ȫ���������е�operator new
		::operator delete(p3);
		std::cout << "operator new test is over" << std::endl;

		//����allocators,��ӿ���Ȼ�б�׼��񣬵��ǲ�ͬ�ĳ���ʵ���˲�ͬ�Ľӿ�	
		//һ�㲻��ͨ��������ֱ�����ڴ�
#ifdef _MSC_VER
		std::cout << "allocator test start" << std::endl;
		int *p4 = std::allocator<int>().allocate(3, (int*)0); //����3��ints
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

	//��������תΪ
		Complex *pc;
		try {
			void *mem = operator new(sizeof(Complex), buf);
			pc = static_cast<Complex*>(mem);
			pc->Complex::Complex(1, 2);
		}
		catch (std::bad_alloc)
		{
			//������ʧ�ܣ���ִ��constructor
		}*/
	}

	//Foo�ڵ�operator new
	void *Foo::operator new(size_t size) {
		Foo* p = (Foo*)malloc(size);
		std::cout << "Foo operator new" << std::endl;;
		return p;
	}
	//Foo�ڵ�operator delete
	void Foo::operator delete(void* pdead, size_t size) {
		std::cout << "Foo opeartor delete" << std::endl;
		free(pdead);
	}
	//Foo�ڵ�operator new[]
	void *Foo::operator new[](size_t size) {
		Foo* p = (Foo*)malloc(size);
		std::cout << "Foo operator new[]" << std::endl;;
		return p;
	}
	//Foo�ڵ�operator delete[]
	void Foo::operator delete[](void* pdead, size_t size) {
		std::cout << "Foo opeartor delete[]" << std::endl;
		free(pdead);
	}

	//����new()��delete()
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
	//������ù��캯��ʧ�ܣ��Ż�������µĹ��캯��
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
//����ȫ��::operator new /::operator delete /::operator new[] /::operator delete[]
void* myAlloc(size_t size) {
	return malloc(size); //����һ��ָ��ָ��malloc���ڴ�
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