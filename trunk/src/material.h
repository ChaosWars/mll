#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <IL/il.h>
#include <string>

namespace mll{

	/**
	* \brief The Material class contains the materials used by a Model.
	*/
	class Material
	{
		public:

			/**
			* Default constructor.
			*
			* @param name
			* 			The name of the material.
			*
			* @param diffuse_file
			* 		The path of the diffuse map of the material.
			*
			* @param normal_file
			* 		The path of normal map of the model.
			*
			* @param specular_file
			* 		The path of specular map of the model.
			*/
			Material( const std::string &name = NULL,
					  char *diffuse_file = NULL,
					  char *normal_file = NULL,
					  char *specular_file = NULL );

			/**
			* Destroy the material.
			*/
			~Material();

			/**
			 * Assign an instance of Material to this material.
			 *
			 * @param material
			 * 		The material to be assigned to this material.
			 *
			 * @returns
			 * 		A reference to the new material.
			 */
// 			Material& operator= ( Material &material );

			/**
			* Get the models name.
			*
			* @return
			* 		The models name.
			*/
			const std::string* Name();

			/**
			* Get the diffuse texture for the model.
			*
			* @return
			* 		The diffuse texture for the model.
			*/
			const ILuint* DiffuseTexture();

			/**
			* Get the normal texture for the model.
			*
			* @return
			* 		The normal texture for the model.
			*/
			const ILuint* NormalTexture();

			/**
			* Get the specular texture for the model.
			*
			* @return
			*		The specular texture for the model.
			*/
			const ILuint* SpecularTexture();

			/**
			* Set the name for the model.
			*
			* @param name
			* 		The new name for the model.
			*/
			void SetName( const std::string &name );

			/**
			* Set the diffuse texture for the model.
			*
			* @param diffuse_file
			* 		The location of the new diffuse texture for the model.
			*/
			void SetDiffuseTexture( char *diffuse_file );

			/**
			* Set the normal texture for the model.
			*
			* @param normal_file
			* 		The location of the new normal texture for the model.
			*/
			void SetNormalTexture( char *normal_file );

			/**
			* Set the specular texure for the file.
			*
			* @param specular_file
			* 		The location of the new specular texture for the model.
			*/
			void SetSpecularTexture( char *specular_file );

		private:
			std::string *name;
			ILuint diffuse_tex;
			ILuint normal_tex;
			ILuint specular_tex;
	};
}

#endif
