#include <iostream>

template<std::size_t ... Indexes>
using index_sequence = /* just an empty class*/
template<std::size_t N>
using make_index_sequence = /*black magic*/;

/*
TO-DO:
	Prober:
		Traits
		Policy classes
		Funktory
		Tag classes
*/

template<typename T> class ftor {
public:
	template<typename T2> void ftor(T2 && p) : p_( std::forward<T2>(p)) {}
	void operator()(T & x) {x += p_; }
private:
	T p_;
};



int main() {


	return 0;
}
