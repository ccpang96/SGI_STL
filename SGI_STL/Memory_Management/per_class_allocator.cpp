#include "per_class_allocator.h"
#include <cstddef>
#include <iostream>

using namespace std;
using namespace per_class_allocator;
namespace per_class_allocator {
	Screen* Screen::freeStore = 0;
	const int Screen::screenChunk = 24;
	
	//重载Screen类的operator new
	void* Screen::operator new(size_t size) {
		Screen *p;
		if (!freeStore) {
			//linked list是空的，所以申请一大块
			size_t chunk = screenChunk * size;
			freeStore = p = reinterpret_cast<Screen*>(new char[chunk]);
			//将一大块分割片片，当做linked list串接起来
			for (; p = &freeStore[screenChunk - 1]; ++p)
				p->next = p + 1;
			p->next = 0;
		}
		p = freeStore;
		freeStore = freeStore->next;
		return p;
	}

	//重载Screen类的operator delete
	void Screen::operator delete(void *p, size_t) {
		//将deleted object插回free list前端
		(static_cast<Screen*>(p))->next = freeStore;
		freeStore = static_cast<Screen*>(p);
	}

	//开始测试
	void per_class_allocator_function() {
		std::cout << sizeof(Screen) << std::endl; //8
		size_t const N = 10;
		Screen* p[N];

		for (int i = 0; i < N; ++i)
			p[i] = new Screen(i);

		//输出前10个pointers，比较其间隔
		for (int i = 0; i < 10; ++i)
			std::cout << p[i] << std::endl;

		for (int i = 0; i < N; ++i)
			delete p[i];
	}

}