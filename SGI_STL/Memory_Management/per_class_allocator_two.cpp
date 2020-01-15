#include "per_class_allocator_two.h"
#include <iostream>
namespace per_class_allocator_two {

	Airplane* Airplane::headOfFreeList;
	const int Airplane::BLOCK_SIZE = 512;
	
	//����Airplane��operator new
	void* Airplane::operator new(size_t size) {
		if (size != sizeof(Airplane))
			return ::operator new(size);
		
		Airplane* p = headOfFreeList;
		if (p) //���p��Ч���Ͱ�list��ͷ������һ��Ԫ��
			headOfFreeList = p->next;
		else {
			//free list �ѿգ��������һ������ڴ�
			Airplane* newBlock = static_cast<Airplane*>(::operator new(BLOCK_SIZE * sizeof(Airplane)));
			
			//�ٽ�ÿ��С�鴮��һ��free list,����Ҫ����#0,�������أ���Ϊ���γɹ�
			for (int i = 1; i < BLOCK_SIZE - 1; ++i)
				newBlock[i].next = &newBlock[i + 1];
			newBlock[BLOCK_SIZE - 1].next = 0; //����list
			p = newBlock;
			headOfFreeList = &newBlock[1];
		}
		return p;
	}

	//����Airplane���operator delete
	//��û�л�������ϵͳ���������������������
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
		//�������object�Ƿ�����
		p[1]->set(1000, 'A');
		p[5]->set(2000, 'B');
		p[8]->set(500000, 'C');

		//���10��pointers
		for (int i = 0; i < N; ++i)
			std::cout << p[i] << std::endl;
		for (int i = 0; i < N; ++i)
			delete p[i];
	}
}