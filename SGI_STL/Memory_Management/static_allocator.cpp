#include "static_allocator.h"
#include <cstdlib>
#include <iostream>
namespace static_allocator {


	//allocate��ʵ�� ������new
	void* allocator1::allocate(size_t size) {
		obj* p;
		if (!freeStore) {
			
			//linklistΪ�գ�����һ����ڴ�
			size_t chunk = CHUNK * size;
			freeStore = p = (obj*)malloc(chunk);
			
			//������õ���һ��鵱��linked list�㣬С��С�鴮������
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

	//allocator1��deallocate������
	void allocator1::deallocate(void*p, size_t size) {
		//��*p �ջز��뵽free list
		((obj*)p)->next = freeStore;
		freeStore = (obj*)p;
	}

	allocator1 Foo::myAlloc;

	void static_allocator_function() {

		
		Foo *p[100]; //����ֻ�Ƕ���100��ָ�룬��û��new�����ڴ�
		std::cout << "sizeof(Foo)= " << sizeof(Foo) << std::endl;

		for (int i = 0; i < 23; ++i) {
			p[i] = new Foo(i);
			std::cout << p[i] << " " << p[i]->L << std::endl;
		}
		for (int i = 0; i < 23; ++i)
			delete p[i];

	}

}