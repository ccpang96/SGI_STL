#pragma once
#include <exception>
namespace memory_primitives_test {
	void memory_primitives_test_function();

	//重载载类内的operator new和operator delete
	class Foo {
	public:
		int _id;
		long _data;
		std::string _st;
	public:
		Foo() : _id(0) { std::cout << "default cotr. this = " << this << "   id=" << _id << std::endl; }
		Foo(int i) :_id(i) { std::cout << "default cotr. this = " << this << "   id=" << _id << std::endl;  }
		
		~Foo() { std::cout << "dtor. this= " << this << "  id= " << _id << std::endl; }

		static void *operator new(size_t size);
		static void operator delete(void* pdead, size_t size);
		static void *operator new[](size_t size);
		static void operator delete[](void*pdead, size_t size);

		//重载new()和delete()
		void *operator new(size_t size, void *start);
		void *operator new(size_t size, long extra);
		void *operator new(size_t size, long extra, char init);

		//如果调用构造函数失败，才会调用如下的构造函数
		//void operator delete (void*, size_t);
		void operator delete(void*, void*);
		void operator delete(void*, long);
		void operator delete(void*, long, char);
	};
}
