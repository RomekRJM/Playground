/* 
 * File:   main.cpp
 * Author: roman
 *
 * Created on 10 listopada 2015, 20:25
 * 
 * https://www.reddit.com/r/dailyprogrammer/comments/3s4nyq/20151109_challenge_240_easy_typoglycemia/
 * 
 * Typoglicemia from daily programmers challange.
 * I overcomplicated this easy problem, to havily practice pointers.
 */

#include <cstdlib>
#include <iostream>
#include "main.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    shift("According to a research team at Cambridge University, it doesn't matter in what order the letters in a word are, " 
          "the only important thing is that the first and last letter be in the right place. "
          "The rest can be a total mess and you can still read it without a problem. "
          "This is because the human mind does not read every letter by itself, but the word as a whole." 
          "Such a condition is appropriately called Typoglycemia.");
    return 0;
}

char* shift(const char* input) {
    const char* last = input;
    const char* first = input;
    
    while(*input != '\0'){
        
        if(is_separator(*input)) {
            last = input+1;
            char *sub = substring(input, first, last);
            cout << mix_typoglycemialy(sub);
            first = last;
            
        }
        ++input;
    }
}

char* substring(const char *fullstring, const char *begin, const char *end) {
    char* substring = new char[end-begin];
    int diff = begin - fullstring;
    
    for(int i=0; i<end-begin; ++i) {
        *(substring+i) = *(fullstring+diff+i);
    }
    
    return substring;
}

bool is_separator(char c) {
    return c == '.' || c == ',' || c == '\''  || c == ' ';
}

char* mix_typoglycemialy(char* input) {
    char *begin = input;
    char *end = input;
    
    while(*end != '\0' && !is_separator(*end)) {
        ++end;
    }
    
    if(end-begin > 3) {
        char tmp = *(end-2);
        *(end-2) = *(begin+1);
        *(begin+1) = tmp;
    }
    
    return input;
}

