
#include <cassert>
#include <iostream>
#include <stdexcept>

#include "int_list.hpp"


void int_list() {
	IntList list;
	for (int i = 0; i < 10; ++i) {
		list.add(i);
	}

	std::cout << "Int list contains the following items:" << std::endl;

	for (int i = 0; i < list.size(); ++i) {
		std::cout << "list[" << i << "] = " << list.get(i) << std::endl;
	}
}


int main(int argc, char* argv[]) {
	
	int_list();
	
}
