/*
 * builder.hpp
 *
 *  Created on: Aug 1, 2015
 *      Author: dubchak
 */

#ifndef BUILDER_HPP_
#define BUILDER_HPP_

template<typename T>
class Builder {
public:
	virtual ~Builder() {}

	virtual T build() {
		return T();
	}

protected:
	virtual T operator()() = 0;
};


#endif /* BUILDER_HPP_ */
