/*
 * int_list.hpp
 *
 *  Created on: Jul 26, 2015
 *      Author: dubchak
 */

#ifndef INTLIST_HPP_
#define INTLIST_HPP_

#include <memory>
#include <climits>

class IntList {
public:

	static int ERROR_VAL;

	IntList() : _size(0), _capacity(100), _data(alloc()) {}
	IntList(const IntList& rhs) : _size(rhs._size), _capacity(rhs._capacity), _data(rhs._data) {}
	IntList(std::size_t capacity) : _size(0), _capacity(capacity), _data(alloc()) {}
	virtual ~IntList() {
		if (_data) delete [] _data;
	}

	IntList& operator=(const IntList& rhs) {
		if (&rhs != this) {
			_size = rhs._size;
			_capacity = rhs._capacity;
			_data = rhs._data;
		}

		return *this;
	}

	int add(int val) {
		if (_size == _capacity) return ERROR_VAL;

		_data[_size++] = val;
		return _size - 1;
	}

	int get(int idx) {
		if (idx < 0 || idx >= _size) return ERROR_VAL;

		return _data[idx];
	}

int replace(int idx, int val) {
	if (idx < 0 || idx >= _size) return ERROR_VAL;

	_data[idx] = val;
	return _data[idx];
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
	std::size_t 	_size;
	std::size_t		_capacity;
	int* 			_data;

	int* alloc() {
		return new int[_capacity + 1];
	}
};

int IntList::ERROR_VAL = INT_MIN;

#endif /* INTLIST_HPP_ */
