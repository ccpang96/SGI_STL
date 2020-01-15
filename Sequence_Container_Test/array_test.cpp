/*https://en.cppreference.com/w/cpp/container/array*/

//template<class T,std::size_t N> struct array;

#include <array>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "array_test.h"

namespace array_test{

	void array_test_function() {

		size_t ASIZE = 10;
		std::cout << "\ntest_array()......\n";
		std::array<int, 3>a = { 1,2,3 };
		std::cout << a.at(1) << std::endl;  //at access specified element with bounds checking 
		std::cout << a[1] << std::endl;
	
	}

}
