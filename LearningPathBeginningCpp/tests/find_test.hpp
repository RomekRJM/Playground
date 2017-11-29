
#ifndef FIND_TEST_HPP_
#define FIND_TEST_HPP_

#include "gtest/gtest.h"
#include <algorithm>
#include <cstring>
#include <string>

#include "find.hpp"

TEST(BinarySearchTest, findDoesNotFindValueInStringArray) {

	std::string fruits[] = {"apple", "banana", "cranberry", "orange"};
	std::string actual = find("tomato", fruits, 0, 3);
	ASSERT_STREQ("", actual.c_str());
}

TEST(BinarySearchTest, findFindsValueInStringArray) {

	std::string fruits[] = {"apple", "banana", "cranberry", "orange"};
	std::string actual = find("banana", fruits, 0, 3);
	ASSERT_STREQ("banana", actual.c_str());
}

TEST(BinarySearchTest, findSortedAlphabetFindsValueInStringArray) {

	std::string alphabet[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
	std::sort(std::begin(alphabet), std::end(alphabet));
	std::string actual = find("a", alphabet, 0, 25);
	ASSERT_STREQ("a", actual.c_str());

}

TEST(BinarySearchTest, sortUnsortedArrayfindFindsValueInStringArray) {

	std::string states[] = {"Texas", "North Dakota", "California", "Kentucky", "Alaska", "Colorado", "Minnesota", "Hawaii"};
	std::sort(std::begin(states), std::end(states));
	std::string actual = find("California", states, 0, 7);
	ASSERT_STREQ("California", actual.c_str());

}

TEST(BinarySearchTest, arrayTest) {

	int* items = new int[3];
	items[0] = 23;
	items[1] = 14;
	items[2] = 12;

	EXPECT_EQ(1, 2);

}

#endif /* FIND_TEST_HPP_ */
