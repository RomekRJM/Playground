/* 
 * File:   main.h
 * Author: roman
 *
 * Created on 10 listopada 2015, 20:27
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

char* shift(const char* input);
char* substring(const char*, const char*, const char*);
bool is_separator(char c);
char* mix_typoglycemialy(char *input);


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

