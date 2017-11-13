/*
 * utils.hpp
 *
 *  Created on: Nov 4, 2013
 *      Author: dubchak
 */

#ifndef MEMORY_UTILS_HPP_
#define MEMORY_UTILS_HPP_

#include <algorithm>

namespace std {
	template<typename T, typename... Args>
	std::unique_ptr<T> make_unique(Args&&... args) {
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}
}

template<typename T, typename Iter>
inline void my_copy(Iter beg, Iter end, T& target) {
	target.erase();
	std::copy(beg, end, std::back_inserter(target));
}

namespace std {

	//inline std::string as_string(std::chrono::high_resolution_clock::time_point& tp) {
	inline std::string as_string(std::chrono::system_clock::time_point& tp) {
		// convert to system time:
		std::time_t t = std::chrono::system_clock::to_time_t(tp);
		std::string ts = std::asctime(gmtime(&t));
		ts.resize(ts.size() - 1);
		return ts;
	}
}

template<class T>
inline bool is_type_of(T& t) {
	return typeid(T)==typeid(t);
}

template<typename T>
inline double to_double(T val) {
    return (double) val;
}

template<typename T, typename U>
inline double to_double(T numer, U denom) {
    return (double) numer / (double) denom;
}

inline int to_int(std::string s) {
	std::stringstream ss(s);
	int result;
	return ss >> result ? result : 0;
}


template<typename T, typename U>
inline bool in(const T& container, U item) {
	auto res = std::find_if(std::begin(container), std::end(container), [=] (const U t) { return t == item; });
	return res != std::end(container);
}

template<>
inline bool in(const std::vector<std::string>& container, std::string item) {
	auto res = std::find_if(std::begin(container), std::end(container), [=] (const std::string& t) { return t == item; });
	return res != std::end(container);
}

template<>
inline bool in(const std::vector<std::string>& container, const char* item) {
	std::string c_item{item};
	auto res = std::find_if(std::begin(container), std::end(container), [=] (const std::string& t) { return t == c_item; });
	return res != std::end(container);
}

template<typename T>
inline bool to_boolean(T arg) {
	return arg;
}

template<>
inline bool to_boolean(std::string arg) {
	std::string val = arg;
	std::transform (std::begin(val), std::end(val), std::begin(val), ::tolower);
	return val == "true";
}

template<>
inline bool to_boolean(const char* arg) {
	return to_boolean(std::string{arg});
}

template<>
inline bool to_boolean(long arg) {
	return arg == 1;
}

template<>
inline bool to_boolean(double arg) {
	return arg == 1.0;
}

template<typename T>
inline T within(T result, bool exit_on_error = false) {
	if (result < 0) {
		std::cerr << "Failed opening file: {" << result << "} -> '" << strerror(errno) << "'" << std::endl;
		if (exit_on_error)
			exit(EXIT_FAILURE);
	}

	return result;
}

#endif /* MEMORY_UTILS_HPP_ */
