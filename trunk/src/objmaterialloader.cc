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

std::vector< Material* >* OBJMaterialLoader::LoadMaterials( const char *material_file )
{
	std::ifstream file;
	std::string buffer;
	std::vector< Material* > *materials = NULL;

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
	materials = new std::vector< Material* >( num_materials );

	//Rewind file pointer in preperation for the second pass.
	file.clear();
	file.seekg( std::ifstream::beg );

	std::string *name = NULL;
	std::string *diffuse_map = NULL;
	int material_idx = 0;

	//Second pass reads the material properties
	while( !file.eof() ){
		getline( file, buffer );

		while( buffer.substr( 0, 6 ) != "newmtl" ){
			getline( file, buffer );
		}

		name = new std::string( buffer, 7, buffer.length() - 7 );
		sscanf( buffer.c_str(),
				"newmtl %s",
				name );

		printf( "name : %s\n", name );
		getline( file, buffer );

		while( buffer.substr( 0, 6 ) != "newmtl" && !file.eof() ){

			if( buffer.substr( 0, 6 ) == "map_Kd" ){

				diffuse_map = new std::string( buffer, 7, buffer.length() - 7 );
				sscanf( buffer.c_str(),
						"map_Kd %s",
						diffuse_map );
				printf( "diffuse_map : %s\n", diffuse_map->c_str() );

			}

			getline( file, buffer );
		}

// 		materials[ material_idx ] = new Material( *name );
		materials->push_back( new Material( *name ) );

		if( diffuse_map != NULL ){
			delete diffuse_map;
			diffuse_map = NULL;
		}
		
		++material_idx;
	}

	file.close();
	return materials;
}
