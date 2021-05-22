/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   30_handson_functions.hpp
 * Author: roman.subik
 *
 * Created on 2 listopada 2017, 06:58
 */

#ifndef HANDSON_FUNCTIONS_HPP
#define HANDSON_FUNCTIONS_HPP

#include <string>

std::string find(std::string to_find, std::string data[], int beg, int end) {
    
    while(beg <= end) {
        int mid = beg + (end - beg) / 2;
        if (data[mid] == to_find) {
            return to_find;
        } else if (data[mid] < to_find) {
            beg = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    
    return "";
}

constexpr auto aggregate = [&] (std::string line) {
    auto parts = split(line, "|", true);
}
#endif /* HANDSON_FUNCTIONS_HPP */

