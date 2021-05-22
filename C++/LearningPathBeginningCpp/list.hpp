/*
 * list.hpp
 *
 *  Created on: Jul 30, 2015
 *      Author: dubchak
 */

#ifndef LIST_HPP_
#define LIST_HPP_

#include <stdexcept>

template<typename T>
class List {
public:

	List() : _size(0), _capacity(100), _data(alloc()) {}
	List(const List& rhs) : _size(rhs._size), _capacity(rhs._capacity), _data(rhs._data) {}
	List(std::size_t capacity) : _size(0), _capacity(capacity), _data(alloc()) {}
	virtual ~List() {
		if (_data) delete [] _data;
	}

	List& operator=(const List& rhs) {
		if (&rhs != this) {
			_size = rhs._size;
			_capacity = rhs._capacity;
			_data = rhs._data;
		}

		return *this;
	}

	const T& operator[](std::size_t idx) const { return _data[idx]; };
	T& operator[](std::size_t idx) { return _data[idx]; }

	std::size_t add(T val) {
		if (_size == _capacity) throw std::out_of_range("list full error");

		_data[_size++] = val;
		return _size;
	}

	T& get(std::size_t idx) {
		if (idx < 0 || idx >= _size) throw std::out_of_range("list full error");

		return _data[idx];
	}

	T replace(std::size_t idx, T val) {
		if (idx < 0 || idx >= _size) throw std::out_of_range("list full error");

		_data[idx] = val;
		return _data + (idx * sizeof(T));
	}

	std::size_t capacity() const { return _capacity; }
	std::size_t size() const { return _size; }
	bool is_empty() const { return _size == 0; }
	void reset() {
		delete [] _data;
		_data = alloc();
		_size = 0;
	}

private:
	std::size_t _size;
	std::size_t	_capacity;
	T* 			_data;

	T* alloc() {
		return new T[_capacity + 1];
	}
};

#endif /* LIST_HPP_ */
