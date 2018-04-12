#include <iostream>
#include <istream>
#include <sstream>
#include <utility>
#include <memory>
#include <tuple>
#include <type_traits>
#include <list>
#include "Splitter.h"

using namespace splitter;

int main() {
	std::istringstream iss("alpha:=10/50.1");
	std::string x = "";
	int y = 0;
	double z = 0;
	iss >> split(x, ':', '=', y, '/', z);
	std::cout << "x = " << x << ", y = " << y << ", z = " << z << std::endl;
	for(;;);
	return 0;
}