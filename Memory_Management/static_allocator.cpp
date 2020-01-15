#include "static_allocator.h"
#include <cstdlib>
#include <iostream>
namespace static_allocator {


	//allocate的实现 类似于new
	void* allocator1::allocate(size_t size) {
		obj* p;
		if (!freeStore) {
			
			//linklist为空，申请一大块内存
			size_t chunk = CHUNK * size;
			freeStore = p = (obj*)malloc(chunk);
			
			//将分配得到的一大块当做linked list般，小块小块串接起来
			for (int i = 0; i < CHUNK - 1; ++i) {
				p->next = (obj*)((char*)p + size);
				p = p->next;
			}
			p->next = nullptr; //last node
		}
		p = freeStore;
		freeStore = freeStore->next;
		return p;
	}

	//allocator1的deallocate的首先
	void allocator1::deallocate(void*p, size_t size) {
		//将*p 收回插入到free list
		((obj*)p)->next = freeStore;
		freeStore = (obj*)p;
	}

	allocator1 Foo::myAlloc;

	void static_allocator_function() {

		
		Foo *p[100]; //这里只是定义100个指针，并没有new分配内存
		std::cout << "sizeof(Foo)= " << sizeof(Foo) << std::endl;

		for (int i = 0; i < 23; ++i) {
			p[i] = new Foo(i);
			std::cout << p[i] << " " << p[i]->L << std::endl;
		}
		for (int i = 0; i < 23; ++i)
			delete p[i];

	}

}