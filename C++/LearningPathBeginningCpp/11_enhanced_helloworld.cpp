/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: roman (off sick)
 *
 * Created on 20 May 2016, 18:40
 */

#include <iostream>

using namespace std;

/*
 * 
 */
int main11(int argc, char** argv) {
    
    if (argc < 6) {
        std::cerr << "Not enough arguments - at least 5 required" << endl;
        return 1;
    }
    
    std::cout << "Total arguments: " << argc << endl;
    
    for (int i = 0; i < argc; ++i)
    {
        std::cout << "arg[" << i << "]=" << argv[i] << endl;
    }
    return 0;
}

