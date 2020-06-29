#include <iostream>
#include <string>



//#include <Windows.h>


#ifndef __GL_FUNCTION_TRACKER__
#define __GL_FUNCTION_TRACKER__
#endif


#ifndef __CONSOLE_MESSAGE__
#define __CONSOLE_MESSAGE__
#endif


namespace _DebugTools_{ 
	using namespace std;

	static void Log(string str) {

#ifdef __CONSOLE_MESSAGE__
		cout << str << endl;
#endif

	}
}