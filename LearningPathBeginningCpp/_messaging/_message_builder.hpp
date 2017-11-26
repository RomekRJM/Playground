/*
 * _message_builder.hpp
 *
 *  Created on: Jul 30, 2015
 *      Author: dubchak
 */

#ifndef _MESSAGE_BUILDER_HPP_
#define _MESSAGE_BUILDER_HPP_

#include <functional>
#include <map>
#include <string>

#include "builder.hpp"
#include "_message_header.hpp"
#include "_message.hpp"

class MessageBuilder : public Builder<Message> {
public:
	using value_type = Message;

	MessageBuilder() {}
	MessageBuilder(const MessageBuilder& rhs) : _message(rhs._message), _headers(rhs._headers) {}
	explicit MessageBuilder(std::string m) : _message(m) {}
	virtual ~MessageBuilder() {}

	MessageBuilder& operator=(const MessageBuilder& rhs) {
		if (&rhs != this) {
			_message = rhs._message;
			_headers = rhs._headers;
		}
		return *this;
	}

	MessageBuilder& body(const std::string& m) {
		_message = m;
		return *this;
	}

	// Header overloads
	MessageBuilder& header(const std::string& key, const std::string& value) {
		_headers.insert(std::make_pair(key, MessageHeader(key, value)));
		return *this;
	}

	MessageBuilder& header(const MessageHeader& header) {
		_headers.insert(std::make_pair(header.key(), header));
		return *this;
	}

protected:
	Message operator()() override {
		Message msg;
		msg.message(_message);
		msg.add(_headers);
		return msg;
	}

private:
	using Map = std::map<std::string, MessageHeader>;

	std::string _message;
	Map 		_headers;
};

template<>
struct NullAdapter<MessageBuilder> {
	void operator()(MessageBuilder& builder) {
		std::cout << "NullAdapter specialization for MessageBuilder" << std::endl;
	}
};

template<typename T>
struct MessageBuilderAdapter {
	MessageBuilder operator()(MessageBuilder& builder) {
		builder.body("A message adapter to customize the message body");
		return builder;
	}
};



#endif /* _MESSAGE_BUILDER_HPP_ */
