#pragma once
#include <string>
namespace macro_static_allocator {

	//设计allocator1类去封装malloc和delete
	class allocator1 {
	private:
		struct obj {
			struct obj*next; //嵌入式指针 embedded pointer
		};
	public:
		void* allocate(size_t);
		void deallocate(void*, size_t);
	private:
		obj * freeStore = nullptr;
		const int CHUNK = 5; //小一些以便观察
	};

//将myAlloc.allocate转换为宏定义
	//DECLARE_POOL_ALLOC --used in class definition
	//用反斜杠来续行
#define DECLARE_POOL_ALLOC() \
public:\
	void* operator new(size_t size) { return myAlloc.allocate(size); } \
	void operator delete(void* p) { myAlloc.deallocate(p, 0); } \
protected: \
	static allocator1 myAlloc;

	//IMPLEMENT_POOL_ALLOC--used in class implementation file
#define IMPLEMENT_POOL_ALLOC(class_name) \
	allocator1 class_name::myAlloc;

	//定义用于测试的类 Foo
	class Foo {
		DECLARE_POOL_ALLOC()
	public:
		long L;
		std::string str;
	public:
		Foo(long l) :L(l) {}
	};


	void macro_static_allocator_function();
}