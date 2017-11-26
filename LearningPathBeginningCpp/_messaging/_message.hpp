/*
 * _message.hpp
 *
 *  Created on: Jul 30, 2015
 *      Author: dubchak
 */

#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include <algorithm>
#include <map>
#include <string>


class Message {

	using Key = std::string;
	using Map = std::map<Key, MessageHeader>;

public:
	Message() {}
	Message(const Message& rhs) : _message(rhs._message), _headers(rhs._headers) {}
	explicit Message(std::string m) : _message(m) {}
	virtual ~Message() {}

	Message& operator=(const Message& rhs) {
		if (&rhs != this) {
			_message = rhs._message;
			_headers = rhs._headers;
		}
		return *this;
	}

	void message(const std::string& m) { _message = m; }
	std::string message() const { return _message; }

	bool contains_header(const Key& key) {
		return _headers.find(key) != std::end(_headers);
	}

	std::string get(const Key& key) const {
		const std::string result = _headers.find(key)->second.value();
		return result;
	}

	void add(Map& headers) {
		_headers.insert(std::begin(headers), std::end(headers));
	}

private:
	Key _message;
	Map _headers;
};


#endif /* _MESSAGE_HPP_ */
