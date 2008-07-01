#include "exception.hpp"
#include "material.hpp"
#include "materialloader.hpp"
#include "model.hpp"
#include "modelloader.hpp"
#include "objloader.hpp"
#include "objmaterialloader.hpp"

namespace mll{

	typedef struct{
		int MAJOR;
		int MINOR;
	} MLLVersion;

	extern "C"{
		const MLLVersion* getMLLVersion();
	}

}
