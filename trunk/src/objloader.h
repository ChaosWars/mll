#ifndef _OBJLOADER_H_
#define _OBJLOADER_H_

#include <string>
#include <stdio.h>
#include "modelloader.h"
#include "model.h"

using namespace std;

namespace mll{

	/**
	* @brief This class loads a Wavefront *.obj file and parses both the
	*		 model data in the file as well as the material data in the
	* 		 corresponding *.mtl file.
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
			Model* LoadModel( const string &objfile );

		protected:

			/**
			* Helper function that reorganises the the data
			* loaded from the *.obj file into a format expected
			* by model.h
			*
			* @param name
			*		The name of the model.
			*
			* @param quad
			*		True if the model is quadrangulate, false if the model is triangulated
			*
			* @param vertices
			*		Indexed array containing the vertex data of the model.
			*
			* @param tex_coords
			*		Indexed array containing the texture coordinate data
			*		of the model.
			*
			* @param normals
			*		Indexed array containing the normal data of the model.
			*
			* @param num_vertices
			*		Number of unique vertices in the model.
			*
			* @param vertex_idx
			*		Index array of the vertex array.
			*
			* @param tex_coord_idx
			*		Index array of the texture coordinate array.
			*
			* @param normal_idx
			*		Index array of the normal array.
			*
			* @param material_file
			*		The location of the file containing the material data.
			*
			* @returns
			*		A pointer to the data contained in the model.
			*/
			Model* CreateModel( const string &name, bool quad, const vector<float> &normals, const vector<float> &tex_coords,
								const vector<float> &vertices, const vector<int> &normal_idx, const vector<int> &tex_coord_idx,
								const vector<int> &vertex_idx, const string &material_file );

	};

}

#endif	//_OBJLOADER_H_
