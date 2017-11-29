/*
 * list_string_test.hpp
 *
 *  Created on: Aug 1, 2015
 *      Author: dubchak
 */

#ifndef LIST_STRING_TEST_HPP_
#define LIST_STRING_TEST_HPP_

#include <string>

#include "gtest/gtest.h"
#include "list.hpp"


TEST(ListStringTest, createListOfStringsDefaultCapacity) {
	List<std::string> list;

	EXPECT_EQ(list.capacity(), 100);
}

TEST(ListStringTest, createListOfStringsCustomCapacity) {
	List<std::string> list(225);

	EXPECT_EQ(list.capacity(), 225);
}

TEST(ListStringTest, createListOfStringsCustomCapacityAndLoad) {

	List<std::string> list(225);
	for (int i = 0; i < 225; ++i) {
		list.add(" ");
	}

	EXPECT_EQ(list.size(), 225);
}

TEST(ListStringTest, createListOfStrings) {
	List<std::string> list;
	for (int i = 0; i < 100; ++i) {
		list.add(" ");
	}

	try {
		list.add(" ");
		FAIL();
	} catch (const std::logic_error& execpted) {}
}

TEST(ListStringTest, createListOfStringsFillAndReset) {

	List<std::string> list;

	list.add("one");
	list.add("two");
	list.add("three");
	list.add("four");
	list.add("five");

	EXPECT_EQ(list.size(), 5);

	list.reset();
	EXPECT_EQ(list.size(), 0);
}

#endif /* LIST_STRING_TEST_HPP_ */
