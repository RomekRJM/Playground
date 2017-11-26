#include <iostream>
#include <string>

#include "functions.hpp"

void generate_frequency_data(const std::string& file_name) {
    initialize();
    calculate(file_name);
    display();
}

int main37(int argc, char* argv[]) {
    std::string file_name = "2013_USDA_Farmers_Markets_Geographic_Data.csv";
    generate_frequency_data(file_name);
}
