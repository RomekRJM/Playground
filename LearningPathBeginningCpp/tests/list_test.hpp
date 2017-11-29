/*
 * list_test.hpp
 *
 *  Created on: Jul 30, 2015
 *      Author: dubchak
 */

#ifndef LIST_TEST_HPP_
#define LIST_TEST_HPP_

#include "gtest/gtest.h"
#include "list.hpp"

TEST(ListIntTest, createListOfIntsDefaultCapacity) {
	List<int> list;

	EXPECT_EQ(list.capacity(), 100);
}

TEST(ListIntTest, createListOfIntsCustomCapacity) {
	List<int> list(225);

	EXPECT_EQ(list.capacity(), 225);
}

TEST(ListIntTest, createListOfIntsCustomCapacityAndLoad) {

	List<int> list(225);
	for (int i = 0; i < 225; ++i) {
		list.add(i);
	}

	EXPECT_EQ(list.size(), 225);
}

TEST(ListIntTest, createListOfInts) {
	List<int> list;
	for (int i = 0; i < 100; ++i) {
		list.add(i);
	}

	try {
		list.add(55757);
		FAIL();
	} catch (const std::out_of_range& expected) {
		std::cerr << expected.what() << std::endl;
	}
}

TEST(ListIntTest, createListOfIntsFillAndReset) {

	List<int> list;
	for (int i = 0; i < 100; ++i) {
		list.add(i);
	}

	EXPECT_EQ(list.size(), 100);

	list.reset();
	EXPECT_EQ(list.size(), 0);
}

#endif /* LIST_TEST_HPP_ */
