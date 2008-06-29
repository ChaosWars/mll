#include <IL/ilut.h>
#include <fstream>
#include <sstream>
#include "objmaterialloader.h"

using namespace mll;

OBJMaterialLoader::OBJMaterialLoader()
{
}

OBJMaterialLoader::~OBJMaterialLoader()
{
}

Material** OBJMaterialLoader::LoadMaterials( const char *material_file )
{
	std::ifstream file;
	std::string buffer;
	Material **materials = NULL;

	file.open( material_file, std::ifstream::in );

	if ( !file.is_open() ){
		printf( "Failed to open material file.\n" );
		return materials;
	}

	//First pass established the number of materials
	int num_materials = 0;

	while( !file.eof() ){
		getline( file, buffer );

		if( buffer.substr( 0, 6 ) == "newmtl" )
			++num_materials;
	}

	printf( "%d materials in material file.\n", num_materials );
	materials = new Material *[num_materials];

	//Rewind file pointer in preperation for the second pass.
	file.clear();
	file.seekg( std::ifstream::beg );

	char *name = NULL;
	char *diffuse_map = NULL;
	float ambient_red = 0.0;
	float ambient_green = 0.0;
	float ambient_blue = 0.0;
	float diffuse_red = 0.0;
	float diffuse_green = 0.0;
	float diffuse_blue = 0.0;
	float specular_red = 0.0;
	float specular_green = 0.0;
	float specular_blue = 0.0;
	float shininess = 0.0;
	float alpha = 1.0;
	int specular = 1;
	bool has_specular = false;
	int material_idx = 0;
	int cur_material = 0;

	//Second pass reads the material properties
	while( !file.eof() ){
		getline( file, buffer );

		while( buffer.substr( 0, 6 ) != "newmtl" ){
			getline( file, buffer );
		}

		name = new char[buffer.length() - 7];
		sscanf( buffer.c_str(), "newmtl %s", name );

		printf( "name : %s\n", name );
		getline( file, buffer );

		while( buffer.substr( 0, 6 ) != "newmtl" && !file.eof() ){

			if( buffer.substr( 0, 6 ) == "map_Kd" ){

				diffuse_map = new char[buffer.length() - 7];
				sscanf( buffer.c_str(), "map_Kd %s", diffuse_map );
				printf( "diffuse_map : %s\n", diffuse_map );

			}else if( buffer.substr( 0, 4 ) == "illum" ){

				sscanf( buffer.c_str(), "illum %d", &specular );

				if( specular == 2 )
					has_specular = true;

			}else if( buffer.substr( 0, 2 ) == "Ka" ){

				sscanf( buffer.c_str(),
						"Ka %f %f %f",
						&ambient_red,
						&ambient_blue,
						&ambient_green );
				
			}else if( buffer.substr( 0, 2 ) == "Kd" ){

				sscanf( buffer.c_str(),
						"Kd %f %f %f",
						&diffuse_red,
						&diffuse_blue,
						&diffuse_green );
				
			}else if( buffer.substr( 0, 2 ) == "Ks" ){

				sscanf( buffer.c_str(),
						"Ks %f %f %f",
						&specular_red,
						&specular_blue,
						&specular_green );

			}else if( buffer.substr( 0, 2 ) == "Ns" ){

				sscanf( buffer.c_str(),
						"Ns %f",
						&shininess );

			}else if( buffer.substr( 0, 2 ) == "Tr" ){

				sscanf( buffer.c_str(), "Tr %f", &alpha );

			}else if( buffer.substr( 0, 1 ) == "d" ){

				sscanf( buffer.c_str(), "d %f", &alpha );

			}

			getline( file, buffer );
		}

		materials[cur_material] = new Material( name, const_cast< char* >( diffuse_map ) );
		materials[cur_material]->SetAmbientColor( ambient_red, ambient_green, ambient_blue );
		materials[cur_material]->SetDiffuseColor( diffuse_red, diffuse_green, diffuse_blue );

		if( has_specular ){
			materials[cur_material]->SetHasSpecular( true );
			materials[cur_material]->SetSpecularColor( specular_red, specular_green, specular_blue );
		}

		materials[cur_material]->SetAlpha( alpha );
		materials[cur_material]->SetShininess( shininess );

		if( diffuse_map != NULL ){
			delete diffuse_map;
			diffuse_map = NULL;
		}

		ambient_red = 0.0;
		ambient_green = 0.0;
		ambient_blue = 0.0;
		diffuse_red = 0.0;
		diffuse_green = 0.0;
		diffuse_blue = 0.0;
		specular_red = 0.0;
		specular_green = 0.0;
		specular_blue = 0.0;
		shininess = 0.0;
		alpha = 1.0;
		specular = 1;
		has_specular = false;
		
		++material_idx;
		++cur_material;
	}

	file.close();
	return materials;
}
