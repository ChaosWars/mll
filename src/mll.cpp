#include "mll.hpp"

using namespace mll;

extern "C"{

	const MLLVersion* getMLLVersion()
	{
		MLLVersion *version = new MLLVersion();
		version->MAJOR = 0;
		version->MINOR = 1;
		return version;
	}

}
