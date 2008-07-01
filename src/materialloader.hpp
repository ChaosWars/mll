#ifndef _MATERIALLOADER_H_
#define _MATERIALLOADER_H_

#include <vector>
#include "material.hpp"

using namespace std;

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
			*		The vector to store the materials in.
			*/
			virtual void LoadMaterials( const string &material_file, vector <Material*> &materials ) = 0;
	};
}

#endif	//_MATERIALLOADER_H_
