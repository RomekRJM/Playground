/*
 * string_utils.hpp
 *
 *  Created on: Jan 5, 2014
 *      Author: dubchak
 */

#ifndef STRING_UTILS_HPP_
#define STRING_UTILS_HPP_

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <vector>

#include <cstring>

#include "utils.hpp"


inline std::string& to_lower(std::string& s) {
	std::transform(std::begin(s), std::end(s), std::begin(s), ::tolower);
	return s;
}

template<typename T>
inline bool is_space(T arg) {
	return false;
}

template<>
inline bool is_space(std::string::iterator arg) {
	return *arg == ' ';
}

template<>
inline bool is_space(char arg) {
	return arg == ' ';
}

template<>
inline bool is_space(char* arg) {
	return arg != nullptr &&
			strlen(arg) == 1 &&
			*arg == ' ';
}

template<>
inline bool is_space(const char* arg) {
	return arg != nullptr &&
			strlen(arg) == 1 &&
			*arg == ' ';
}

template<>
inline bool is_space(const std::string& arg) {
	return arg.length() == 1 && arg[0] == ' ';
}

template<typename T>
inline bool is_not_space(T arg) {
	return true;
}

template<>
inline bool is_not_space(char arg) {
	return !is_space(arg);
}

template<>
inline bool is_not_space(char& arg) {
	return !is_space(arg);
}

template<>
inline bool is_not_space(char* arg) {
	return !is_space(arg);
}

template<>
inline bool is_not_space(const char* arg) {
	return !is_space(arg);
}

template<>
inline bool is_not_space(const std::string& arg) {
	return !is_space(arg);
}


template<typename T>
inline std::size_t len(T arg) {
	return arg.length();
}

template<>
inline std::size_t len(const char* arg) {
	if (arg)
		return strlen(arg);

	return 0;
}

template<typename T>
inline std::string str(T a) {
	return std::string(a);
}

template<>
inline std::string str(int a) {
	return std::to_string(a);
}

template<>
inline std::string str(long a) {
	return std::to_string(a);
}

template<>
inline std::string str(char* a) {
	return std::string{a};
}

template<>
inline std::string str(const char* a) {
	return std::string{a};
}

inline std::string to_string(void) {
	return std::string{};
}

inline static
bool remove(std::string& target, const std::string& to_remove) {
    auto pos = target.find(to_remove);
    if (pos != std::string::npos)
        target.replace(pos, to_remove.size(), "");
    return pos != std::string::npos;
}

template<typename T>
inline std::string to_string(T arg) {
	return std::to_string(arg);
}

template<>
inline std::string to_string(std::thread::id thread_id) {
	std::stringstream ss;
	ss << thread_id;
	return ss.str();
}

template<>
inline std::string to_string(int& arg) {
	return std::to_string(arg);
}

template<>
inline std::string to_string(long& arg) {
	return std::to_string(arg);
}

template<>
inline std::string to_string(double& arg) {
	return std::to_string(arg);
}

template<typename... Args>
inline std::string to_string(std::string arg, Args&&... args) {
	return arg + to_string(std::forward<Args>(args)...);
}

template<typename... Args>
inline std::string to_string(typename std::remove_reference<char*>::type arg, Args&&... args) {
	return std::string{arg} + to_string(std::forward<Args>(args)...);
}

template<typename... Args>
inline std::string to_string(typename std::remove_reference<const char*>::type arg, Args&&... args) {
	return std::string{arg} + to_string(std::forward<Args>(args)...);
}

template<typename... Args>
inline std::string to_string(typename std::remove_reference<const char*>::type arg1, typename std::remove_reference<const char*>::type arg2, Args&&... args) {
	return std::string{arg1} + std::string{arg2} + to_string(std::forward<Args>(args)...);
}

template<typename T, typename... Args>
inline std::string to_string(T arg, Args&&... args) {
	return std::string{arg} + to_string(std::forward<Args>(args)...);
}

template<typename Func>
inline auto to_vec(const std::string& str, Func creator) -> std::vector<decltype(creator(str))> {

	std::vector<decltype(creator(str))> results;
	std::stringstream ss(str);
	std::string res;
	ss >> res;
	if (!ss.fail())
		results.push_back(creator(res));

	return results;
}

inline static
std::string substitute(const std::string& target, const std::string& to_find, const std::string& replacement) {

	std::string result;

	auto pos = target.find(to_find);
	if (pos != std::string::npos) {
		result = target.substr(0, pos);
		result += replacement;
		result += target.substr(pos + to_find.length());
	} else {
		result = target;
	}

	return result;
}

template<typename Iter, typename Predicate>
inline std::size_t iter_pos(Iter i, Predicate p) {
	std::size_t pos = -1;
	while (p(*i)) {
		if (pos == -1)
			pos = 0;
		pos += 1;
		++i;
	}

	return pos;
}


// trim from start
inline std::string& ltrim(std::string& s) {

	if (s.length() > 0)
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), is_not_space<char>));

	return s;
}

// trim from end
inline std::string& rtrim(std::string& s) {

	int pos = iter_pos(s.rbegin(), [](char& c) -> bool {
		return c == ' ';
	});

	if (pos > 0)
	s.erase(s.length() - pos);
	return s;
}

// trim from both ends
inline std::string& trim(std::string &s) {

	if (s.length() > 0)
		return ltrim(rtrim(s));

	return s;
}

inline std::vector<std::string> split(const std::string& t, const std::string& delim = ":", bool trim_vals = false) {

	std::vector<std::string> results;
	// Account for a special case where the delimeter is not in string
	if (t.find(delim) == std::string::npos) {
		results.push_back(t);
		return results;
	}

	auto start = std::begin(t);
	auto end = std::end(t);
	auto prev = start;

	std::string tmp;
	while (start != end) {
		if (std::string{*start} == delim) {
			my_copy(prev, start, tmp);
			if (trim_vals && tmp.length() > 0)
				trim(tmp);

			results.push_back(tmp);
			prev = start + delim.length();
		}
		++start;
	}

	if (prev != (start + delim.length()) && start == end)  {
		my_copy(prev, start, tmp);
		if (trim_vals)
			trim(tmp);

		results.push_back(tmp);
	}

	return results;
}

template<typename T>
inline T join(T t) {
	return t;
}

inline std::string join(char* t) {
	return std::string{t};
}

inline std::string join(const char* t) {
	return std::string{t};
}

inline std::string join(std::string t) {
	return t;
}

template<typename T, typename... Args>
inline T join(T t, Args&&... args) {
	return join(t, std::forward<Args>(args)...);
}

template<typename... Args>
inline std::string join(char* t, Args&&... args) {
	return std::string{t} + join(std::forward<Args>(args)...);
}

template<typename... Args>
inline std::string join(const char* t, Args&&... args) {
	return std::string{t} + join(std::forward<Args>(args)...);
}

template<typename... Args>
inline std::string join(std::string t, Args&&... args) {
	return t + join(std::forward<Args>(args)...);
}

template<typename Iter>
inline auto join(Iter beg, Iter end) -> typename std::remove_reference<decltype(*beg)>::type {

	using Type = typename std::remove_reference<decltype(*beg)>::type;
	Type val;

	while (beg != end) {
		val += (*beg);
		++beg;
	}

	return val;
}

template<typename Iter>
inline auto join(std::string d, Iter beg, Iter end) -> typename std::remove_reference<decltype(*beg)>::type {

	using Type = typename std::remove_reference<decltype(*beg)>::type;
	Type val;

	bool first = true;
	while (beg != end) {
		if (first) first = false;
		else val += d;

		val += (*beg);
		++beg;
	}

	return val;
}

template<typename T>
inline std::pair<T, T> to_pair(T arg1, T arg2) {
	return std::make_pair(arg1, arg2);
}

inline std::pair<std::string, std::string> to_pair(std::vector<std::string> elems) {
	return std::make_pair(elems[0], elems[1]);
}

#endif /* STRING_UTILS_HPP_ */
