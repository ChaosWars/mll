#ifndef _MLL_EXCEPTION_
#define _MLL_EXCEPTION_

#include <exception>
#include <iostream>

using namespace std;

namespace mll{

	class FileOpenException : public exception{
		public:

			FileOpenException( const string &file ) : f(file){}

			virtual ~FileOpenException() throw(){}

			virtual const char* what() const throw(){
				string *error = new string( "Failed to open file " );
				error->append(f);
				return error->c_str();
			}

		private:
			string f;

	};

}

#endif
