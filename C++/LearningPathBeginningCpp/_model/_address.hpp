/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   _address.hpp
 * Author: roman.subik
 *
 * Created on 15 listopada 2017, 07:00
 */

#ifndef _ADDRESS_HPP
#define _ADDRESS_HPP

class _address {

public:
    _address() {};
    _address(const _address& rhs) : _street1(rhs._street1), 
        _street2(rhs._street2), _city(rhs._city) {}
    _address(std::string s1, std::string s2, std::string c) : _street1(s1),
        _street2(s2), _city(c) {}
    virtual ~_address() {}
    
    _address& operator=(const _address& rhs) {
        if (&rhs != this) {
            _street1 = rhs._street1;
            _street2 = rhs._street2;
            _city = rhs._city;
        }
        
        return *this;
    }
    
    virtual std::string street1() const { return _street1; }
    virtual std::string street2() const { return _street2; }
    virtual std::string city() const { return _city; }
    
    virtual std::string to_string() const = 0;
    
private:
    std::string _street1;
    std::string _street2;
    std::string _city;
};


#endif /* _ADDRESS_HPP */

