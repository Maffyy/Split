#include <iostream>
#include <istream>
#include <sstream>
#include <utility>
#include <memory>
#include <tuple>
#include <type_traits>
#include <functional>


template<typename ... T>
class Pack {
public:
	std::istream stream;
	std::tuple<T...> tuple;
	Pack(std::tuple<T ...> && tup) : tup(tuple) {};
};

template<typename ... T>
class Pack<T...>  {
public:
	std::istream stream;

};

template<typename T>
void process_rvalue(T& elem) {
	if (std::is_rvalue_reference(elem)) {

	}
}
template<typename T>
void process_lvalue(T& elem) {

	if (std::is_lvalue_reference(elem)) {

	}
}

template<std::size_t I, typename ... T>
void parse(std::tuple<T...> & p) {

}


template<typename ... T>
Pack<T ...> split(T && ... params) {
	std::tuple<T ...>tuple(std::forward<T>(params) ...);
	parse<sizeof(tuple),T...>(tuple);
	Pack<T...> pack(tuple);

	return pack;
}



template<typename ... T>
std::istream& operator>>(std::istream& is,Pack<T ...> && pack) {
	is >> pack.stream;
	return is;
}

int main() {
	std::istringstream iss("alpha:=10/50.1");
	std::string x;
	int y;
	double z;
	iss >> split(x, ':', y, '/', z);
	std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
	return 0;
}