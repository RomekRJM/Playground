/*
 * find.hpp
 *
 *  Created on: Jul 19, 2015
 *      Author: dubchak
 */

#ifndef FIND_HPP_
#define FIND_HPP_

#include <string>

std::string __find(const std::string& value, std::string data[], std::size_t beg, std::size_t end) {

	while (beg <= end) {
        int mid = beg + (end - beg) / 2;
        if (data[mid] == value)
            return value;
        else if (data[mid] < value)
            beg = mid + 1;
        else
            end = mid - 1;
    }

    return ""; // Not found
}

namespace intro {
	// Creating a namespace alias to __find for intro::find
    std::string (*find)(const std::string& value, std::string data[], std::size_t beg, std::size_t end) = __find;
}
#endif /* FIND_HPP_ */
