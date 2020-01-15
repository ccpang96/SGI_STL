#pragma once
#include <string>
namespace static_allocator {
	
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
	
	
	//实现Foo类去测试上面的allocator1类
	class Foo {
	public:
		long L;
		std::string str;
		static allocator1 myAlloc;
	public:
		Foo(long l) : L(l) {}
		
		//重载Foo类的operator new
		static void* operator new(size_t size) {
			return myAlloc.allocate(size);
		}
		//重载Foo类的operator delete
		static void operator delete(void* pdead, size_t size) {
			return myAlloc.deallocate(pdead, size);
		}
		
	};

	

	void static_allocator_function();


}