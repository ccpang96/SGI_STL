#pragma once
#include <string>
namespace static_allocator {
	
	//���allocator1��ȥ��װmalloc��delete
	class allocator1 {
	private:
		struct obj {
			struct obj*next; //Ƕ��ʽָ�� embedded pointer
		};

	public:
		void* allocate(size_t);
		void deallocate(void*, size_t);
	private:
		obj * freeStore = nullptr;
		const int CHUNK = 5; //СһЩ�Ա�۲�
	};
	
	
	//ʵ��Foo��ȥ���������allocator1��
	class Foo {
	public:
		long L;
		std::string str;
		static allocator1 myAlloc;
	public:
		Foo(long l) : L(l) {}
		
		//����Foo���operator new
		static void* operator new(size_t size) {
			return myAlloc.allocate(size);
		}
		//����Foo���operator delete
		static void operator delete(void* pdead, size_t size) {
			return myAlloc.deallocate(pdead, size);
		}
		
	};

	

	void static_allocator_function();


}