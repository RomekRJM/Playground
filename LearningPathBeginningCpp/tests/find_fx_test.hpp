
#ifndef FIND_FX_TEST_HPP_
#define FIND_FX_TEST_HPP_

#include <array>
#include <string>
#include <type_traits>

#include "gtest/gtest.h"

template<typename Iter, typename T>
Iter find(Iter beg, Iter end, const T& value) {

	Iter orig_end = end;
	while (beg < end) {
        auto mid = beg + (end - beg) / 2;
        if (*mid == value)
            return mid;
        else if (*mid < value)
            beg = mid + 1;
        else
            end = mid - 1;
    }

	return orig_end;
}

TEST(FindTemplateTest, createFindForIntArray) {
	int i[] = {12, 15, 23, 32, 75, 123, 247, 323};
	auto idx = find(i, i+8, 23);
	EXPECT_EQ(23, *idx);
}

TEST(FindTemplateTest, createFindForDoubleArray) {
	double d[] = {12.3, 15.8, 23.75, 32.12, 75.65, 123.22, 247.99, 323.55};
	auto idx = find(d, d+8, 75.65);
	ASSERT_TRUE(*idx == 75.65);
	EXPECT_EQ(75.65, *idx);
}

TEST(FindTemplateTest, searchUsingFindForDoubleArrayThatisNotFound) {
	double d[] = {12.3, 15.8, 23.75, 32.12, 75.65, 123.22, 247.99, 323.55};
	auto idx = find(d, d+8, 75.66);
	ASSERT_FALSE(*idx == 75.66);
}


#endif /* FIND_FX_TEST_HPP_ */
