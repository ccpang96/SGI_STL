#include "per_class_allocator.h"
#include <cstddef>
#include <iostream>

using namespace std;
using namespace per_class_allocator;
namespace per_class_allocator {
	Screen* Screen::freeStore = 0;
	const int Screen::screenChunk = 24;
	
	//����Screen���operator new
	void* Screen::operator new(size_t size) {
		Screen *p;
		if (!freeStore) {
			//linked list�ǿյģ���������һ���
			size_t chunk = screenChunk * size;
			freeStore = p = reinterpret_cast<Screen*>(new char[chunk]);
			//��һ���ָ�ƬƬ������linked list��������
			for (; p = &freeStore[screenChunk - 1]; ++p)
				p->next = p + 1;
			p->next = 0;
		}
		p = freeStore;
		freeStore = freeStore->next;
		return p;
	}

	//����Screen���operator delete
	void Screen::operator delete(void *p, size_t) {
		//��deleted object���free listǰ��
		(static_cast<Screen*>(p))->next = freeStore;
		freeStore = static_cast<Screen*>(p);
	}

	//��ʼ����
	void per_class_allocator_function() {
		std::cout << sizeof(Screen) << std::endl; //8
		size_t const N = 10;
		Screen* p[N];

		for (int i = 0; i < N; ++i)
			p[i] = new Screen(i);

		//���ǰ10��pointers���Ƚ�����
		for (int i = 0; i < 10; ++i)
			std::cout << p[i] << std::endl;

		for (int i = 0; i < N; ++i)
			delete p[i];
	}

}