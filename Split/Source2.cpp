//template<class ... Us> void f(Us... pargs) {}
//template<class ... Ts> void g(Ts... args) {
//	f(&args...);
//}
//


int main() {
	/*g(1,0.2,"a");*/
	return 0;
}






//
//
//template<typename ...> struct Tuple {};
//template<typename T1, typename T2> struct Pair {};
//
//template<class ...Args1> struct zip {
//	template<class ...Args2> struct with {
//		typedef Tuple<Pair<Args1, Args2>...> type;
//	};
//};
//
//typedef zip<short, int>::with<unsigned short, unsigned>::type T1;
//
//typedef zip<short>::with<unsigned short, unsigned>::type T2;
//
//template<class ...Args>
//	void g(Args... args) {
//		f(const_cast<const Args*>(&args)...);
//
//		
//	}







