#include <iostream>
#include <istream>
#include <sstream>
#include <utility>
#include <memory>
#include <tuple>
#include <type_traits>
#include <list>

template<class... T>
class Pack {
public:
	std::tuple<T...> tuple;
	Pack(std::tuple<T...> tup) : tuple(tup) {}
};




template<std::size_t I, typename ... T>
std::stringstream& process_args(std::istream& stream, std::tuple<T...> & param) {

	std::stringstream ss;
	auto current = std::get<I>(param);
	if (std::is_lvalue_reference(current)) {
		ss = process_args<I + 1>(stream, param);
		current = std::tie(ss);

	}
	else if (std::add_rvalue_reference(param) && std::_Is_character(param)) {
		char c;
		while (stream.get(c) != param) { ss << c; } 
	}

	return ss;

}



template<typename ... T>
std::istream& operator>>(std::istream& stream, std::tuple<T ...>&& param) {

	process_args<0>(stream,param);

	return stream;
}

template<typename ... T>
std::tuple<T ...> split(T ... param) {
	auto data = std::make_tuple(std::forward<T>(param) ...);
	return std::tuple<T ...>(std::move(data));
}

int main() {
	std::istringstream iss("alpha:=10/50.1");
	std::string x;
	int y;
	double z;
	iss >> split(x, ':', '=', y, '/', z);
	std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
	return 0;
}