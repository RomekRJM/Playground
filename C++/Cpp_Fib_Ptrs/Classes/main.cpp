/* 
 * File:   main.cpp
 * Author: roman
 *
 * Created on 3 listopada 2015, 19:58
 */

#include <iostream>

#include "main.h"

using namespace std;

Fib::Fib(){
    cout << "\nIn constructor\n";
};

void Fib::compute(int n){
    if (n<1) {
        cout << "Value needs to be greater or equal 1";
    }
    
    long *elements = new long[n];
    long *start = elements;
    long sum;
    
    for(int i=0; i<n; ++i) {
        *(elements++) = 1;
    }
    
    elements=start;
    
    for(int i=0; i<n-2; ++i) {
        *(elements+2)=*elements + *(elements+1);
        ++elements;
    }
    
    elements=start;
    
    for(int i=0; i<n; ++i) {
        cout << *(elements++) << ", ";
    }
    
    delete start;
};

int main(int argc, char** argv) {
    Fib *dupa = new Fib();
    dupa->compute(17);
    delete dupa;
}

