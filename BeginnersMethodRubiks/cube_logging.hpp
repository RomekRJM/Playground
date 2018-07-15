/* 
 * File:   cube_logging.hpp
 * Author: roman.subik
 *
 * Created on 15 July 2018, 06:46
 */

#ifndef CUBE_LOGGING_HPP
#define CUBE_LOGGING_HPP
#include <iostream>

const int DEBUG = 0;
const int INFO = 1;
const int ERROR = 2;
const int LOGGING_LEVEL = DEBUG;

class Logger {
public:
  Logger(int l) : level(l) { };
  
  template <class T>
  Logger& operator<<(T const& t) {
    if(level >= LOGGING_LEVEL) {
        std::cout << t << std::endl;
    }
    return *this;
  }

private:
    int level;
};

#endif /* CUBE_LOGGING_HPP */

