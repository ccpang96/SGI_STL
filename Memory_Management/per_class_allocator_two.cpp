#include "per_class_allocator_two.h"
#include <iostream>
namespace per_class_allocator_two {

	Airplane* Airplane::headOfFreeList;
	const int Airplane::BLOCK_SIZE = 512;
	
	//重载Airplane的operator new
	void* Airplane::operator new(size_t size) {
		if (size != sizeof(Airplane))
			return ::operator new(size);
		
		Airplane* p = headOfFreeList;
		if (p) //如果p有效，就把list的头部下移一个元素
			headOfFreeList = p->next;
		else {
			//free list 已空，申请分配一个大块内存
			Airplane* newBlock = static_cast<Airplane*>(::operator new(BLOCK_SIZE * sizeof(Airplane)));
			
			//再将每个小块串成一个free list,但是要跳过#0,它被传回，作为本次成果
			for (int i = 1; i < BLOCK_SIZE - 1; ++i)
				newBlock[i].next = &newBlock[i + 1];
			newBlock[BLOCK_SIZE - 1].next = 0; //结束list
			p = newBlock;
			headOfFreeList = &newBlock[1];
		}
		return p;
	}

	//重载Airplane类的operator delete
	//并没有还给操作系统，还是在这个自由链表中
	void Airplane::operator delete(void* deadObject, size_t size) { 
		if (deadObject == 0) return;
		if (size != sizeof(Airplane)) {
			::operator delete(deadObject);
			return;
		}
		Airplane* carcass = static_cast<Airplane*>(deadObject);
		carcass->next = headOfFreeList;
		headOfFreeList = carcass;
	}

	void per_class_allocator_two_function() {
		std::cout  << sizeof(Airplane) << std::endl;
		size_t const N = 10;
		Airplane* p[N];

		for (int i = 0; i < N; ++i)
			p[i] = new Airplane;
		//随机测试object是否正常
		p[1]->set(1000, 'A');
		p[5]->set(2000, 'B');
		p[8]->set(500000, 'C');

		//输出10个pointers
		for (int i = 0; i < N; ++i)
			std::cout << p[i] << std::endl;
		for (int i = 0; i < N; ++i)
			delete p[i];
	}
}