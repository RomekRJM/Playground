/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   _site.hpp
 * Author: roman.subik
 *
 * Created on 15 listopada 2017, 06:41
 */

#ifndef _SITE_HPP
#define _SITE_HPP

class Site {
public:
    Site() : _id(1) {};
    Site(long id, std::string name, WebAddress uri, USAddress postal)
        : _id(id), _name(name), _uri(uri), _postal(postal) {};
    virtual ~Site() {};
    
    std::string to_string() const { return _name + ": " + _uri.to_string(); }
    
private:
    int _id;
    std::string _name;
    WebAddress _uri;
    USAddress _postal;
};

#endif /* _SITE_HPP */

