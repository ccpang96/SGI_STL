#include <vector>
#include <stdexcept>
#include <cstdlib> //abort
#include <cstdio> //sprintf
#include <iostream> 
#include <ctime>
#include <algorithm> //sort
#include "vector_test.h"

namespace vector_test {

	void vector_test_function() {

		std::vector<int>v1(2, 4); 
		std::cout << v1.size() << std::endl;
		std::cout << v1.capacity() << std::endl;


		v1.push_back(10);

		auto it = v1.end();
		int j = 10;
		v1.insert(it, 10, std::move(j)); // insert(const_)
		for (auto it1 = v1.begin(); it1 != v1.end(); it1++)
			std::cout << *it1 << std::endl;


		printf("v1µÄÔªËØ %d \n ", v1.at(1));
		std::cout << v1.at(1) << std::endl;

		
	}
}
