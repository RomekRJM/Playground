/*
 * list_double_test.hpp
 *
 *  Created on: Aug 1, 2015
 *      Author: dubchak
 */

#ifndef LIST_DOUBLE_TEST_HPP_
#define LIST_DOUBLE_TEST_HPP_

#include "gtest/gtest.h"
#include "list.hpp"


TEST(ListTest, createListOfDoublesDefaultCapacity) {
	List<double> list;

	EXPECT_EQ(list.capacity(), 100);
}

TEST(ListTest, createListOfDoublesCustomCapacity) {
	List<double> list(225);

	EXPECT_EQ(list.capacity(), 225);
}

TEST(ListTest, createListOfDoublesCustomCapacityAndLoad) {

	List<double> list(225);
	for (int i = 0; i < 225; ++i) {
		list.add(i);
	}

	EXPECT_EQ(list.size(), 225);
}

TEST(ListTest, createListOfDoubles) {
	List<double> list;
	for (int i = 0; i < 100; ++i) {
		list.add(i);
	}

	try {
		list.add(55757.0);
		FAIL();
	} catch (const std::logic_error& execpted) {}
}

TEST(ListTest, createListOfDoublesFillAndReset) {

	List<double> list;
	for (int i = 0; i < 100; ++i) {
		list.add(i);
	}

	EXPECT_EQ(list.size(), 100);

	list.reset();
	EXPECT_EQ(list.size(), 0);
}


#endif /* LIST_DOUBLE_TEST_HPP_ */
