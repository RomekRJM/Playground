/*
 * main.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: dubchak
 */

#include <iostream>
#include "gtest/gtest.h"

#include "find_fx_test.hpp"
#include "generic_builder_test.hpp"
#include "int_list_test.hpp"
#include "list_double_test.hpp"
#include "list_string_test.hpp"
#include "list_test.hpp"
#include "template_fx_test.hpp"

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
