#include <iostream>
#include <istream>
#include <sstream>
#include <utility>
#include <memory>
#include <tuple>
#include <type_traits>
#include <functional>


template<typename T1, typename ... TList>
class Pack {
public:
	std::istringstream stream;
};

template<typename T1,typename ... TList>
class Pack<T1,TList ...>  {
public:
	int a;
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


template<typename ... T>
Pack<T ...> split(T && ... p) {
	//using tuple1 = std:tuple<std::remove_reference_t<T> ... >;
	using tuple2 = std::tuple<T ...>;
	using tuple3 = std::tuple<T && ...>;

	
	auto data1 = std::make_tuple(std::forward<T>(p)...);
	parse(data1);
	auto data2 = std::tie(p ...);
	parse(data2);
}

template<std::size_t I, typename ... T>
void parse(std::tuple<T...> & p) {

}

template<typename ... TL>
std::istream& operator>>(std::istream& is,Pack<TL ...> && pack) {
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