/*
 * us_address.hpp
 *
 *  Created on: Jul 26, 2015
 *      Author: dubchak
 */

#ifndef US_ADDRESS_HPP_
#define US_ADDRESS_HPP_

#include <string>

#include "_address.hpp"
#include "_state_abbrev.hpp"
//#include "address.hpp"

class USAddress : public _address {
public:
	USAddress() :_state(StateAbbrev::AL) {}
	USAddress(const USAddress& rhs) : _address(rhs), _state(rhs._state), _zip(rhs._zip) {}
	USAddress(std::string s1,
			   std::string s2,
			   std::string c,
			   StateAbbrev s,
			   std::string z) : _address(s1, s2, c), _state(s), _zip(z) {}
	virtual ~USAddress() {}

	USAddress& operator=(const USAddress& rhs) {
		_address::operator=(rhs);

		if (&rhs != this) {
			_state = rhs._state;
			_zip = rhs._zip;
		}

		return *this;
	}

	StateAbbrev state() const { return _state; }
	std::string zip() const { return _zip; }

	std::string to_string() const override {
	  return "";
   }

private:
	StateAbbrev _state;
	std::string _zip;
};


#endif /* US_ADDRESS_HPP_ */
