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
extern int loggingLevel;

class Logger {
public:
  Logger(int l) : level(l) { };
  
  template <class T>
  Logger& operator<<(T const& t) {
    if(level >= loggingLevel) {
        std::cout << t << std::endl;
    }
    return *this;
  }

private:
    int level;
};

extern Logger debug;
extern Logger info;
extern Logger error;

#endif /* CUBE_LOGGING_HPP */

