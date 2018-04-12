#include <iostream>
#include <tuple>
#include <type_traits>
#include <fstream>
#include <sstream>
#include <utility>

namespace splitter
{
	void process_args(std::istream&, char);
	template<typename ... T>
	void process_args(std::istream&, char&, char, T && ...);
	template<typename F, typename ... T>
	void process_args(std::istream&, F&, char, T && ...);
	template<typename ... T>
	void process_args(std::istream&, char&, char, T && ...);
	template<typename T>
	void process_args(std::istream&, T&);
	void process_args(std::istream&);

	template<typename ... T>
	class Pack {
	public:
		std::tuple<T...> tuple;
		Pack(std::tuple<T...> tup) : tuple(tup) {}
	};

	/* Recursion - process arguments functions */

	template<typename ... T>
	void process_args(std::istream& str, char first, T && ... rest) {

		char c;
		str >> c;
		if (c != first) {
			throw std::logic_error("Explicitly specified delimiter was not found in the input str!");
		}
		else if (str.fail()) {
			throw std::logic_error("Conversion of characters failed!");
		}
		process_args(str, std::forward<T>(rest) ...);
	}

	void process_args(std::istream& str, char last) {
		char c;
		str.get(c);
		if (c != last || str.fail()) {
			throw std::logic_error("str load failed, delimiter or newline was not reached!");
		}
	}

	template<typename ... T>
	void process_args(std::istream& str, char& first, char second, T && ... rest) {
		std::string s;
		std::getline(str, s, second);
		std::stringstream ss(s);
		ss >> first;
		if (ss.fail()) {
			throw std::logic_error("str load failed!");
		}
		process_args(str, std::forward<T>(rest)...);
	}

	template<typename F, typename ... T>
	void process_args(std::istream& str, F& first, char second, T && ... rest) {

		std::string s;
		std::getline(str, s, second);
		std::stringstream ss(s);
		ss >> first;
		if (ss.fail()) {
			throw std::logic_error("str load failed!");
		}
		process_args(str, std::forward<T>(rest)...);
	}

	template<typename T>
	void process_args(std::istream& str, T& first) {

		std::string s;
		std::getline(str, s, '\n');
		std::stringstream ss(s);
		ss >> first;
		if (ss.fail()) {
			throw std::logic_error("str load failed!");
		}
	}

	void process_args(std::istream& str) {}

	/**/
	template<typename T1>
	void check_errors(T1 && first) {
		static_assert(!(std::is_rvalue_reference<T1>() && !std::is_same<T1, char>()), "A rvalue argument is of type different!");
	}
	/*Static assert*/
	template<typename T1, typename T2, typename ... T>
	void check_errors(T1 && first, T2 && second, T && ... rest) {
		static_assert(!(std::is_lvalue_reference<T1>() && std::is_lvalue_reference<T2>()), "Two lvalues argument are adjacent!");
		static_assert(!(std::is_rvalue_reference<T1>() && !std::is_same<T1, char>()), "A rvalue argument is of type different!");
		static_assert(!(std::is_rvalue_reference<T2>() && !std::is_same<T2, char>()), "A rvalue argument is of type different!");
		check_errors(std::forward<T2>(second), std::forward<T>(rest)...);
	}

	/**/

	template<size_t ... I, typename ... T>
	void preprocess(std::istream& str, Pack<T ...>& param, std::index_sequence<I...>) {
		process_args(str, std::get<I>(param.tuple)...);
	}


	template<typename ... T>
	std::istream& operator>>(std::istream& str, std::tuple<T ...>& param) {
		preprocess(str, param, std::make_index_sequence<sizeof...(T)>());
		return str;
	}

	template<typename ... T>
	std::istream& operator>>(std::istream& str, Pack<T ...>&& param) {
		preprocess(str, param, std::make_index_sequence<sizeof...(T)>());
		return str;
	}

	template<typename ... T>
	Pack<T ...> split(T && ... param) {
		Pack<T ...> pack(std::move(std::tuple<T...>(std::forward<T>(param) ...)));
		check_errors(std::forward<T>(param)...);
		return pack;
	}
}
