#ifndef _MLL_EXCEPTION_
#define _MLL_EXCEPTION_

#include <exception>
#include <iostream>

using namespace std;

namespace mll{

	class FileOpenException : public exception{
		public:

			FileOpenException( const string &file ) : f(file){}

			virtual const char* what() const throw(){
				return f.c_str();
			}

		private:
			string f;

	};

}

#endif
