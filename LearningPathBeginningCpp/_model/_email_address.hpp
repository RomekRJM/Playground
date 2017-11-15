/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   _email_address.hpp
 * Author: roman.subik
 *
 * Created on 15 listopada 2017, 07:11
 */

#ifndef _EMAIL_ADDRESS_HPP
#define _EMAIL_ADDRESS_HPP

#include "_address.hpp"


class EmailAddress : _address {
public:        
    EmailAddress() {}
    EmailAddress(const EmailAddress& rhs) : _address(rhs), _email(rhs._email) {}
    EmailAddress(std::string e) : _email(e) {}
    virtual ~EmailAddress() {};
    
    EmailAddress& operator=(const EmailAddress& rhs) {
        _address::operator=(rhs);
        
        if (&rhs != this) {
            _email = rhs._email;
        }
        
        return *this;
    }
    
    std::string to_string() const override {
        return _email;
    }
    
private:
        std::string _email;
};

#endif /* _EMAIL_ADDRESS_HPP */

