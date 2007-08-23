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
			Model( std::string *name,
				   std::vector< float > *vertices = NULL,
				   std::vector< float > *tex_coords = NULL,
				   std::vector< float > *normals = NULL,
				   std::vector< Material* > *material = NULL );

			/**
			* Destroys the Model
			*/
			~Model();

			/**
			* @returns
			*		The name of the model.
			*/
			const std::string* Name();

			/**
			* @returns
			*		The vertex data for the model.
			*/
			const std::vector< float >* Vertices();

			/**
			* @returns
			*		The texture coordinate data for the model.
			*/
			const std::vector< float >* TextureCoords();

			/**
			* @returns
			*		The normal data for the model.
			*/
			const std::vector< float >* Normals();

			/**
			* @returns
			*		An array of Material containing the materials
			*		used by the model.
			*/
			const std::vector< Material*>* Materials();

		private:
			std::string *name;
			std::vector< float > *vertices;
			std::vector< float > *tex_coords;
			std::vector< float > *normals;
			std::vector< Material* > *materials;
	};

}

#endif	//_MODEL_H_
