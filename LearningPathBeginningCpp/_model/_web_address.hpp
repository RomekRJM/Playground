/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   _web_address.hpp
 * Author: roman.subik
 *
 * Created on 15 listopada 2017, 06:50
 */

#ifndef _WEB_ADDRESS_HPP
#define _WEB_ADDRESS_HPP

class WebAddress : public _address {
public:
    WebAddress () {}
    WebAddress (const WebAddress &rhs) : _address(rhs), _uri(rhs._uri) {}
    WebAddress (std::string e) : _uri(e) {}
    virtual ~WebAddress () {}
    
    WebAddress operator=(const WebAddress &rhs) {
        _address::operator=(rhs);
        
        if (&rhs != this) {
            _uri = rhs._uri;
        }
        return *this;
    }
    
    std::string to_string() const override { return _uri; }
    
private:
    std::string _uri;
    
};

#endif /* _WEB_ADDRESS_HPP */

