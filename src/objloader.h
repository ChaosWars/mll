#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include <string>
#include <stdio.h>
#include "modelloader.h"
#include "model.h"

namespace mll{

	/**
	* \brief This class loads a Wavefront *.obj file and parses both the
	* model data in the file as well as the material data in the
	* corresponding *.mtl file.
	*/
	class OBJLoader : ModelLoader
	{
		public:

			/**
			* Construct a *.obj model loader
			*/
			OBJLoader();

			/**
			* Destroy the *.obj loader
			*/
			~OBJLoader();

			/**
			*	Load a *.obj file into memory.
			*
			*	@param objfile
			*		The *.obj file
			*
			*	@returns
			*		The model data.
			*/
			Model* LoadModel( const char *objfile );

		private:

			/**
			* Helper function that reorganises the the data
			* loaded from the *.obj file into a format expected
			* by model.h
			*/
			Model* CreateModel( const std::string &name,
								const float *vertices,
								const float *tex_coords,
								const float *normals,
								const int num_polygons,
								const int *vertex_idx,
								const int *tex_coord_idx,
								const int *normal_idx,
								const std::string &material_file );

	};

}

#endif	//_OBJLOADER_H_
