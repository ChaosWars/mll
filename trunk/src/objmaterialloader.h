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
			 * @param materials
			 *		The array to store the materials in. This is an array of pointers
			 *		to objects of the type Material. This variable will be dynamically allocated,
			 *		therefor it should not point to anything valid when passed to this function.
			 *
			 * @returns
			 *		The number of Materials read.
			 */
			int LoadMaterials( const char *material_file, Material **materials );
	};

}
#endif	//_OBJMATERIALLOADER_H_
