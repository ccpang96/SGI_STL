#include <forward_list>
#include <iostream>
#include "forward_list_test.h"
#include <cstdio>
#include <ctime>  //time
#include <cstdlib> //rand() abort()
#include <string>
#include <exception>
#include <algorithm>
#include <iterator>


namespace forward_list_test {
	
	void forward_list_test_function() {
		std::forward_list<std::string>l1;
		char buf[10];
		long value = 32767;
		std::string target = "3245"; //����һ����forward_list�в���һ��Ԫ��

		std::cout << "\nlist_test " << std::endl;
		clock_t timeStart = clock(); 

		for (unsigned long i = 0; i < value; ++i) {
			try {
				//��try���п��ܻ�throwһ��wrong
				snprintf(buf, 10, "%d", i);
				l1.push_front(std::string(buf));
			}
			catch (std::exception& p) {
				std::cout << "i= " << i << " " << p.what() << std::endl;
				abort();
			}
		}

		std::cout << "forward_list push_front's time is :" << static_cast<float>(clock() - timeStart) / CLOCKS_PER_SEC << std::endl;

		std::forward_list<std::string>::iterator it; 
		//find�е���input iterator ,�������ԶԷ�Χ�ڵ�Ԫ�ؽ���һ�η���
		//input itearator �� only accessing, no assigning 
		it = std::find(l1.begin(), l1.end(), target); 
		if (it != l1.end()) {
			std::cout << "Ԫ��" << target << "found at position";
		}

	}
}