#ifndef _OBJMATERIALLOADER_H_
#define _OBJMATERIALLOADER_H_

#include <vector>
#include "materialloader.h"
#include "material.h"

namespace mll{

	class OBJMaterialLoader : MaterialLoader
	{
		public:
			OBJMaterialLoader();
			~OBJMaterialLoader();
			std::vector< Material* >* LoadMaterials( const char *material_file );
	};

}
#endif	//_OBJMATERIALLOADER_H_
