/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <gtest/gtest.h>
#include <algorithm>
#include "30_handson_functions.hpp"

TEST(FindTest, findFindsValueInStringArray) {
    std::string fruits[] = { "apple", "banana", "strawbery", "orange"};
    std::string actual = find("banana", fruits, 0, 3);
    
    ASSERT_STREQ("banana", actual.c_str());
}

