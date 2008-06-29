#ifndef _MATERIALLOADER_H_
#define _MATERIALLOADER_H_

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
			MaterialLoader();

			/**
			* Destroys the ModelLoader.
			*/
			virtual ~MaterialLoader();

			/**
			* Loads a file containing the references to the materials. After
			* parsing the file, the data contained in the file is layed out in
			* memory in a manner that can easily be used by 3D API's.
			*
			* @param material_file
			*		The file to be loaded from disk.
			*
			* @param materials
			*		The array to store the materials in. This is an array of pointers
			*		to objects of the type Material. This variable will be dynamically allocated,
			*		therefor it should not point to anything valid when passed to this function.
			*
			* @returns
			*		The number of Materials read.
			*/
			virtual int LoadMaterials( const char *&material_file, Material **&materials ) = 0;
	};
}

#endif	//_MATERIALLOADER_H_
