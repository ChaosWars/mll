#ifndef _MODELLOADER_H_
#define _MODELLOADER_H_

#include <string>
#include "model.h"

namespace mll{

	/**
	* @brief The ModelLoader class is an abstract base class for
	* model loading classes.
	*/
	class ModelLoader
	{
		public:
			/**
			* Constructs a model loader.
			*/
			ModelLoader();

			/**
			* Destroys the model loader.
			*/
			virtual ~ModelLoader();

			/**
			* Loads a file from disk with the data describing the model.
			* After loading the file, it is parsed so that the information
			* contained in it is layed out in memory in arrays that can
			* easily be used by 3D API's.
			*
			* @param model_file
			*		A pointer to the file to load.
			*
			* @returns
			*		The data contained in the file.
			*/
			virtual Model* LoadModel( const string &model_file ) = 0;

		protected:

			/**
			* Helper function for creating a new Model object.
			*
			* @param name
			*		The name of the model.
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
			virtual Model* CreateModel( const string &name, bool quad, const vector<float> &vertices, const vector<float> &tex_coords,
										const vector<float> &normals, const vector<int> &vertex_idx, const vector<int> &tex_coord_idx,
										const vector<int> &normal_idx, const string &material_file ) = 0;

	};

}

#endif	//_MODELLOADER_H_
