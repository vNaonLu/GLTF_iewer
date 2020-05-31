#include <iostream>
#include <string>
#include <initializer_list>

namespace DEBUGConsole{ 

	using namespace std;

	template <class T>
	static void log(initializer_list<T> list) {
		for ( auto elem : list ) {
		
			cout << elem << ', ';

		}

		cout << endl;
	}

}