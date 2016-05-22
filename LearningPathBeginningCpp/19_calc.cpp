/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <string>
#include <cmath>

int main(int argc, char *argv[]) 
{
    if(argc != 4)
    {
        std::cerr << "Program accepts 4 arguments" << std::endl;
        return 1;
    }
    
    double lhs = std::stod(argv[1]);
    std::string op = argv[2];
    double rhs = std::stod(argv[3]);
    
    if(op == "+") 
    {
        std::cout << "result= " << lhs + rhs << std::endl;
    } 
    else if (op == "-")
    {
        std::cout << "result= " << lhs - rhs << std::endl;
    }
    else if (op == "*" || op == "x")
    {
        std::cout << "result= " << lhs * rhs << std::endl;
    }
    else if (op == "/")
    {
        std::cout << "result= " << lhs / rhs << std::endl;
    }
    else if (op == "^")
    {
        std::cout << "result= " << std::pow(lhs, rhs) << std::endl;
    }
    else
    {
        std::cerr << "Op: " << op << " is not supported" << std::endl;
        return 1;
    }
    
}
