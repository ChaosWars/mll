#ifndef _OBJMATERIALLOADER_H_
#define _OBJMATERIALLOADER_H_

#include "materialloader.h"
#include "material.h"

namespace mll{

	/**
	 * @brief The OBJMaterialLoader class loads the materials from a *.mtl file
	 *		  associated with a *.obj file.
	 */
	class OBJMaterialLoader : MaterialLoader
	{
		public:

			/**
			 * Construct an OBJMaterialLLoader.
			 */
			OBJMaterialLoader();

			/**
			 * Desroy the OBJMaterialLoader.
			 */
			~OBJMaterialLoader();

			/**
			 * Load the materials from a *.mtl file.
			 *
			 * @param material_file
			 *		The name of the material file to load.
			 *
			 * @returns
			 *		A vector containing pointers to the loaded materials.
			 */
			Material** LoadMaterials( const char *material_file );
	};

}
#endif	//_OBJMATERIALLOADER_H_
