/*
 * int_list_test.hpp
 *
 *  Created on: Jul 30, 2015
 *      Author: dubchak
 */

#ifndef INT_LIST_TEST_HPP_
#define INT_LIST_TEST_HPP_

#include "gtest/gtest.h"
#include "int_list.hpp"

TEST(IntListTest, createListOfIntsDefaultCapacity) {
	IntList list;

	EXPECT_EQ(list.capacity(), 100);
}

TEST(IntListTest, createListOfIntsCustomCapacity) {
	IntList list(225);

	EXPECT_EQ(list.capacity(), 225);
}

TEST(IntListTest, createListOfIntsCustomCapacityAndLoad) {

	IntList list(225);
	for (int i = 0; i < 225; ++i) {
		list.add(i);
	}

	EXPECT_EQ(list.size(), 225);
}

TEST(IntListTest, createListOfInts) {
	IntList list;
	for (int i = 0; i < 100; ++i) {
		list.add(i);
	}

	EXPECT_EQ(list.add(55757), IntList::ERROR_VAL);
}

TEST(IntListTest, createListOfIntsFillAndReset) {

	IntList list;
	for (int i = 0; i < 100; ++i) {
		list.add(i);
	}

	EXPECT_EQ(list.size(), 100);

	list.reset();
	EXPECT_EQ(list.size(), 0);
}

#endif /* INT_LIST_TEST_HPP_ */
