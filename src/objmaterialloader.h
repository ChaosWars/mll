#ifndef _OBJMATERIALLOADER_H_
#define _OBJMATERIALLOADER_H_

#include "materialloader.h"
#include "material.h"

using namespace std;

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
			 * Destroy the OBJMaterialLoader.
			 */
			~OBJMaterialLoader();

			/**
			 * Load the materials from a *.mtl file.
			 *
			 * @param material_file
			 *		The name of the material file to load.
			 *
			 * @param materials
			 *		The vector to store the materials in.
			 */
			void LoadMaterials( const string &material_file, vector<Material*> &materials );
	};

}
#endif	//_OBJMATERIALLOADER_H_
