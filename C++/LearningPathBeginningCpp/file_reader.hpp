/*
 * file_reader.hpp
 *
 *  Created on: Jun 8, 2014
 *      Author: dubchak
 */

#ifndef FILE_READER_HPP_
#define FILE_READER_HPP_

#include <fstream>
#include <stdexcept>
#include <string>

#include <cstring>
#include <cerrno>

struct _file_reader_exception : public std::exception {

	using error_t = std::size_t;

	_file_reader_exception() : _code(-1) {}
	explicit _file_reader_exception(const std::string& m) : _code(-1), _message(m) {}
	explicit _file_reader_exception(const char* m) : _code(-1), _message(m) {}
	_file_reader_exception(std::string n, std::size_t c, std::string m) : _code(c), _name(n), _message(m) {}
	_file_reader_exception(const _file_reader_exception& rhs) : _name(rhs._name), _code(rhs._code), _message(rhs._message) {}
	virtual ~_file_reader_exception() {}

	_file_reader_exception& operator=(const _file_reader_exception& rhs) {
		if (&rhs != this) {
			_name = rhs._name;
			_code = rhs._code;
			_message = rhs._message;
		}
		return *this;
	}

	const char* what() const noexcept override { return _message.c_str(); }

	void message(const std::string& m) { _message = m; }

	void name(const std::string& n) { _name = n; }
	error_t error_code() const { return _code; }
	std::string name() const { return _name; }

private:
	std::string _name;
	error_t 	_code;
	std::string _message;
};

template<typename T>
struct file_reader {

	file_reader() : _count(0) {}
	file_reader(T name) : _file_name(name), _count(0) {
		_file.open(_file_name);
		if (!_file) {
			throw _file_reader_exception(name, errno, strerror(errno));
		}
	}

	virtual ~file_reader() noexcept {
		if (_file) {
			_file.close();
		}
	}

	/**
	 *
	 */
	void open(T file_name) {
		if (!_file) {
			throw _file_reader_exception(file_name, "Invalid operation - attempt to open file a second time");
		}

		_file.open(_file_name);
		if (!_file)
			throw _file_reader_exception(file_name, "Invalid file");
	}

	/**
	 *
	 */
	template<typename Func>
	void for_each (Func& callback) {
		T line;

		while (_file) {
			int row = 0;
			if (std::getline(_file, line)) {
				callback(++row, line);
			}
		}
	}

	operator bool() const { return (_file.good()); }
	bool operator!() const { return !(_file); }

private:
	std::ifstream	_file;
	T 				_file_name;
	std::size_t		_count;
};


namespace fs {
	template<typename T>
	using FileReader = file_reader<T>;

	using FileReaderException = _file_reader_exception;
}

#endif /* FILE_READER_HPP_ */
