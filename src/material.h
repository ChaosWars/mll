#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <IL/il.h>
#include <string>
#include <boost/array.hpp>

using namespace std;
using namespace boost;

namespace mll{

	/**
	* @brief The Material class contains the materials used by a Model.
	*/
	class Material
	{
		public:

			/**
			* Default constructor.
			*
			* @param name
			*		The name of the material.
			*
			* @param diffuse_file
			*		The path of the diffuse map of the material.
			*
			* @param normal_file
			*		The path of normal map of the material.
			*
			* @param specular_file
			*		The path of specular map of the material.
			*/
			Material( const string &name, const string &diffuse_file, const string &normal_file, const string &specular_file );

			/**
			* Destroy the material.
			*/
			~Material();

			/**
			* Get the materials name.
			*
			* @return
			*		The materials name.
			*/
			const string Name() const;

			/**
			* Get the diffuse texture for the material.
			*
			* @return
			*		The diffuse texture for the material.
			*/
			const ILuint* DiffuseTexture();

			/**
			* Get the normal texture for the material.
			*
			* @return
			*		The normal texture for the material.
			*/
			const ILuint* NormalTexture();

			/**
			* Get the specular texture for the material.
			*
			* @return
			*		The specular texture for the material.
			*/
			const ILuint* SpecularTexture();

			/**
			 * Get the ambient color for the material.
			 *
			 * @returns
			 *		An array containing the ambient color.
			 */
			const array< float, 3 >* AmbientColor();

			/**
			 * Get the diffuse color for the material.
			 *
			 * @returns
			 *		An array containing the diffuse color.
			 */
			const array< float, 3 >* DiffuseColor();

			/**
			 * Get the specular color for the material.
			 *
			 * @returns
			 *		An array containing the specular color.
			 */
			const array< float, 3 >* SpecularColor();

			/**
			 * Get the alpha value of the material.
			 *
			 * @returns
			 *		The alpha value of the material.
			 */
			const float Alpha() const;

			/**
			 * Get the shininess of the material.
			 *
			 * @returns
			 *		The shininess value of the material.
			 */
			const float Shininess() const;

			/**
			 * If the materials specular values and map should be used.
			 *
			 * @returns
			 *		If the material has specular highlights.
			 */
			const bool HasSpecular() const;

			/**
			* Set the name for the material.
			*
			* @param name
			*		The new name for the material.
			*/
			void SetName( const string &name );

			/**
			* Set the diffuse texture for the material.
			*
			* @param diffuse_file
			*		The location of the new diffuse texture for the material.
			*/
			void SetDiffuseTexture( const string &diffuse_file );

			/**
			* Set the normal texture for the material.
			*
			* @param normal_file
			*		The location of the new normal texture for the material.
			*/
			void SetNormalTexture( const string &normal_file );

			/**
			* Set the specular texure for the file.
			*
			* @param specular_file
			*		The location of the new specular texture for the material.
			*/
			void SetSpecularTexture( const string &specular_file );

			/**
			 * Set the ambient color for the material.
			 *
			 * @param red
			 *		The red ambient channel of the material.
			 *
			 * @param blue
			 * 		The blue ambient channel of the material.
			 *
			 * @param green
			 *		The green ambient channel of the material.
			 */
			void SetAmbientColor( float red, float green, float blue );

			/**
			 * Set the diffuse color for the material.
			 *
			 * @param red
			 *		The red diffuse channel of the material.
			 *
			 * @param blue
			 *		The blue diffuse channel of the material.
			 *
			 * @param green
			 *		The green diffuse channel of the material.
			 */
			void SetDiffuseColor( float red, float green, float blue );

			/**
			 * Set the specular color for the material.
			 *
			 * @param red
			 *		The red specular channel of the material.
			 *
			 * @param blue
			 *		The blue specular channel of the material.
			 *
			 * @param green
			 *		The green specular channel of the material.
			 */
			void SetSpecularColor( float red, float green, float blue );

			/**
			 * Set the alpha value of the material.
			 *
			 * @param alpha
			 *		The new alpha value of the material.
			 */
			void SetAlpha( float alpha );

			/**
			 * Set the shininess value of the material.
			 *
			 * @param shininess
			 *		The new shininess value of the material.
			 */
			void SetShininess( float shininess );

			/**
			 * Turn the specular values on or off.
			 *
			 * @param has_specular
			 *		Engage/disengage the specular values of the material.
			 */
			void SetHasSpecular( bool has_specular );

		private:
			string _name;
			ILuint diffuse_tex;
			ILuint normal_tex;
			ILuint specular_tex;
			boost::array< float, 3 > ambient_color;
			boost::array< float, 3 > diffuse_color;
			boost::array< float, 3 > specular_color;
			float _alpha;
			float _shininess;
			bool _has_specular;
	};
}

#endif
