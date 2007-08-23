#ifndef _MATERIALLOADER_H_
#define _MATERIALLOADER_H_

#include <vector>
#include "material.h"

namespace mll{

	/**
	* @brief The MaterialLoader class is an abstract base class that loades the
	*		materials assosiated with a model into memory.
	*/
	class MaterialLoader
	{
		public:

			/**
			* Creates a ModelLoader.
			*/
			MaterialLoader(){};

			/**
			* Destroys the ModelLoader.
			*/
			~MaterialLoader(){};

			/**
			* Loads a file containing the references to the materials. After
			* parsing the file, the data contained in the file is layed out in
			* memory in a manner that can easily be used by 3D API's.
			*
			* @param material_file
			*		The file to be loaded from disk.
			*
			* @returns
			*		The reference to the new Material object.
			*/
			virtual std::vector< Material* >* LoadMaterials( const char *material_file );
	};
}

#endif	//_MATERIALLOADER_H_
