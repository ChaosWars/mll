#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>
#include <vector>
#include "material.h"

namespace mll{

	/**
	* @brief The Model class provides an interface to data needed by 3D graphics API's,
	* layed out in a way suitable for direct use OpenGL without the need to convert the
	* data.
	*/
	class  Model
	{
		public:

			/**
			* Creates a Model. The arguments in the constructor are
			* assigned to pointers maintained by the class and MUST NOT be
			* deleted by you! The class will delete them when it is destroyed.
			*/
			Model( char *name,
			       float *vertices = NULL,
			       float *tex_coords = NULL,
			       float *normals = NULL,
			       Material **material = NULL );

			/**
			* Destroys the Model
			*/
			~Model();

			/**
			* @returns
			*		The name of the model.
			*/
			const char* Name();

			/**
			 * @returns
			 * 		The number of normals in the model.
			 */
			int NumNormals();

			/**
			 * @returns
			 * 		The number of texture coordinates in the model.
			 */
			int NumTextureCoords();

			/**
			 * @returns
			 * 		The number of vertices in the model.
			 */
			int NumVertices();

			/**
			* @returns
			*		The normal data for the model.
			*/
			const float* Normals();
			
			/**
			* @returns
			*		The texture coordinate data for the model.
			*/
			const float* TextureCoords();
			
			/**
			* @returns
			*		The vertex data for the model.
			*/
			const float* Vertices();

			/**
			* @returns
			*		An array of Material containing the materials
			*		used by the model.
			*/
			Material** Materials();

		private:
			char *name;
			int num_normals;
			int num_texture_coords;
			int num_vertices;
			int num_materials;
			float *normals;
			float *tex_coords;
			float *vertices;
			Material **materials;
	};

}

#endif	//_MODEL_H_
