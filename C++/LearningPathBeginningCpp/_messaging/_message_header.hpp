/*
 * _message_header.hpp
 *
 *  Created on: Aug 1, 2015
 *      Author: dubchak
 */

#ifndef _MESSAGE_HEADER_HPP_
#define _MESSAGE_HEADER_HPP_

class MessageHeader {
public:
	using value_type = std::string;

	MessageHeader() {}
	MessageHeader(const MessageHeader& rhs) : _key(rhs._key), _value(rhs._value) {}
	explicit MessageHeader(const std::string& key, const std::string& val) : _key(key), _value(val) {}
	virtual ~MessageHeader() {}

	MessageHeader& operator=(const MessageHeader& rhs) {
		if (&rhs != this) {
			_key = rhs._key;
			_value = rhs._value;
		}
		return *this;
	}

	bool operator==(const MessageHeader& rhs) {
		return (&rhs == this)
				|| (_key == rhs._key
				&& _value == rhs._value);
	}

	bool operator!=(const MessageHeader& rhs) {
		return (&rhs != this)
				||( _key != rhs._key)
				|| (_value != rhs._value);
	}

	std::string key() const { return _key; }
	std::string value() const { return _value; }

private:
	std::string _key;
	std::string _value;
};


#endif /* _MESSAGE_HEADER_HPP_ */
