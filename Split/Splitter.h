#include <iostream>
#include <tuple>
#include <type_traits>
#include <fstream>
#include <sstream>
#include <utility>


namespace splitter
{
	template<class... T>
	class Pack {
	public:
		std::tuple<T...> tuple;
		Pack(std::tuple<T...> tup) : tuple(tup) {}
	};


	/* Recursion - process arguments functions */

	template<typename ... T>
	void process_args(std::istream& stream, char first, T && ... rest) {

		char c;
		stream.get(c);
		if (c != first || stream.fail()) {
			throw std::logic_error("invalid input");
		}
		process_args(stream, std::forward<T>(rest) ...);
	}


	void process_args(std::istream& stream, char last) {

		char c;
		stream.get(c);
		if (c != last || stream.fail()) {
			throw std::logic_error("invalid input");
		}
	}

	template<typename ... T>
	void process_args(std::istream& stream, char& first, char second, T && ... rest) {

		char c;
		std::stringstream is;
		while (stream.get(c) && c != second && !stream.fail()) { is << c; }
		is >> first;
		if (is.fail()) {
			throw std::logic_error("invalid input");
		}
		process_args(stream, std::forward<T>(rest)...);
	}

	template<typename F, typename ... T>
	void process_args(std::istream& stream, F& first, char second, T && ... rest) {

		char c;
		std::stringstream is;
		while (stream.get(c) && c != second && !stream.fail()) { is << c; }

		is >> first;
		if (is.fail()) {
			throw std::logic_error("invalid input");
		}

		process_args(stream, std::forward<T>(rest)...);
	}

	template<typename T>
	void process_args(std::istream& stream, T& first) {

		char c;
		std::stringstream is;
		while (stream.get(c) && (c != '\n' || !stream.fail())) { is << c; }

		is >> first;
		if (is.fail()) {
			throw std::logic_error("invalid input");
		}
	}

	void process_args(std::istream& stream) {}

	/**/
	
	template<typename T1>
	void check_errors(T1 && first) {
		static_assert(!std::is_rvalue_reference<T1>() || std::is_same<T1, char>(), "error char");
	}

	template<typename T1, typename ... T>
	void check_errors(T1 && first, T && ... rest) {
		static_assert(!std::is_rvalue_reference<T1>() || std::is_same<T1, char>(), "error char");
		check_errors(std::forward(rest)...);
	}

	/*Static assert*/
	template<typename T1, typename T2, typename ... T>
	void check_errors(T1 && first, T2 && second, T && ... rest) {

		static_assert(!(std::is_lvalue_reference<T1>() && std::is_lvalue_reference<T2>()), "two lvalues");
		static_assert(!std::is_rvalue_reference<T1>() || std::is_same<T1, char>(), "error char");
		static_assert(!std::is_rvalue_reference<T2>() || std::is_same<T2, char>(), "error char");

		check_errors(std::forward<T2>(second), std::forward<T>(rest)...);

	}

	/**/

	template<size_t ... I, typename ... T>
	void preprocess(std::istream& stream, std::tuple<T ...>& param, std::index_sequence<I...>) {
		process_args(stream, std::get<I>(param)...);
	}


	template<typename ... T>
	std::istream& operator>>(std::istream& stream, std::tuple<T ...>& param) {
		preprocess(stream, param, std::make_index_sequence<sizeof...(T)>());
		return stream;
	}

	template<typename ... T>
	std::istream& operator>>(std::istream& stream, std::tuple<T ...>&& param) {
		preprocess(stream, param, std::make_index_sequence<sizeof...(T)>());
		return stream;
	}

	template<typename ... T>
	std::tuple<T ...> split(T && ... param) {

		check_errors(std::forward<T>(param)...);

		return std::tuple<T ...>(param ...);

	}
}
