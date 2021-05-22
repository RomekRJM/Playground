/*
 * template_fx_test.hpp
 *
 *  Created on: Jul 29, 2015
 *      Author: dubchak
 */

#ifndef TEMPLATE_FX_TEST_HPP_
#define TEMPLATE_FX_TEST_HPP_

#include "gtest/gtest.h"

template<typename T>
T add(T lhs, T rhs) {
    return lhs + rhs;
}

// Class/typename are synonymous
template<class T>
T add_c(T lhs, T rhs) {
    return lhs + rhs;
}

TEST(AddTemplateTest, addTwoInts) {
	ASSERT_TRUE(add(2, 2) == 4);
}

TEST(AddTemplateTest, addCTwoInts) {
	ASSERT_TRUE(add_c(2, 2) == 4);
}

TEST(AddTemplateTest, addTwoStrings) {
	ASSERT_TRUE(add_c(std::string{"one "}, std::string{"two"}) == std::string{"one two"});
}

#endif /* TEMPLATE_FX_TEST_HPP_ */
