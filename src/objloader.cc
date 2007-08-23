#include <fstream>
#include <sstream>
#include "objloader.h"
#include "objmaterialloader.h"
#include "material.h"

using namespace mll;

OBJLoader::OBJLoader()
{
}

OBJLoader::~OBJLoader()
{
}

Model* OBJLoader::LoadModel( const char *objfile )
{
	std::ifstream file;
	std::string buffer;
	Model *model = NULL;

	file.open( objfile, std::ifstream::in );

	if ( !file.is_open() ){
		printf( "Failed to open model file.\n" );
		return model;
	}
	
	/*	We loop through the file twice.
		The first pass reads how much space to allocate
		for the model, the second pass reads the data. */
	std::string *name = NULL;
	std::string *material_file = NULL;
	int num_indexed_vertices = 0;
	int num_tex_coords = 0;
	int num_normals = 0;
	int num_faces = 0;
	int num_vertices = 0;

	//First pass
	while( !file.eof() ){
		getline( file, buffer );

		if( buffer.substr( 0, 6 ) == "mtllib" ){

		material_file = new std::string( buffer, 7, buffer.length() - 7 );

		} else if( buffer.substr( 0, 2 ) == "vn" ){
			++num_normals;
		} else if( buffer.substr( 0, 2 ) == "vt" ){
			++num_tex_coords;
		} else if( buffer.substr( 0, 1 ) == "f" ){
			++num_faces;
		} else if( buffer.substr( 0, 1 ) == "v" ){
			++num_indexed_vertices;
		} else if( buffer.substr( 0, 1 ) == "o" ){

		name = new std::string( buffer, 2, buffer.length() - 2 );
		}
	}

	printf( "Read %d vertices\n", num_indexed_vertices );
	printf( "Read %d normals\n", num_normals );
	printf( "Read %d texture coordinates\n", num_tex_coords );
	printf( "Read %d faces\n", num_faces );
	printf( "material_file : %s\n", material_file );
	printf( "name : %s\n", name );

	//Allocate the memory for the data
	float *vertices = new float[ num_indexed_vertices * 3 ];
	float *tex_coords = new float[ num_tex_coords * 2 ] ;
	float *normals = new float[ num_normals * 3 ];
	num_vertices = num_faces * 3;
	int *vertex_indices = new int[ num_vertices ];
	int *tex_coord_indices = new int[ num_vertices ];
	int *normal_indices = new int[ num_vertices ];

	//Rewind file pointer in preperation for the second pass.
	file.clear();
	file.seekg( std::ifstream::beg );

	//Index variables for data arrays
	int vertex_index = 0;
	int tex_coord_index = 0;
	int normal_index = 0;
	int face_index = 0;

	//second pass
	while( !file.eof() ){
		getline( file, buffer );

		if( buffer.substr( 0, 2 ) == "vn" ){
			//printf( "normal\n" );

			sscanf( buffer.c_str(),
					"vn %f %f %f",
	 				&normals[ normal_index ],
					&normals[ normal_index + 1 ],
					&normals[ normal_index + 2 ] );

			normal_index += 3;

		} else if( buffer.substr( 0, 2 ) == "vt" ){
			//printf( "texture coordinate\n" );

			sscanf( buffer.c_str(),
					"vt %f %f",
					&tex_coords[ tex_coord_index ],
					&tex_coords[ tex_coord_index + 1 ] );

			tex_coord_index += 2;

		} else if( buffer.substr( 0, 1 ) == "f" ){
 			//printf( "face\n" );

			sscanf( buffer.c_str(),
				"f %d/%d/%d %d/%d/%d %d/%d/%d",
				&vertex_indices[ face_index ],
				&tex_coord_indices[ face_index ],
				&normal_indices[ face_index ],
				&vertex_indices[ face_index + 1 ],
				&tex_coord_indices[ face_index + 1 ],
				&normal_indices[ face_index + 1 ],
				&vertex_indices[ face_index + 2 ],
				&tex_coord_indices[ face_index + 2 ],
				&normal_indices[ face_index + 2 ] );

			/*	The vertex index array values start counting at 1,
			 *	so we decrement each value to compensate for our
			 *	starting to count at 0.
			 */
			vertex_indices[ face_index ]--;
			tex_coord_indices[ face_index ]--;
			normal_indices[ face_index ]--;
			vertex_indices[ face_index + 1 ]--;
			tex_coord_indices[ face_index + 1 ]--;
			normal_indices[ face_index + 1 ]--;
			vertex_indices[ face_index + 2 ]--;
			tex_coord_indices[ face_index + 2 ]--;
			normal_indices[ face_index + 2 ]--;

// 			printf( "vertex %d\n",vertex_indices[ face_index ] );
// 			printf( "texture %d\n", tex_coord_indices[ face_index ] );
// 			printf( "normal %d\n", normal_indices[ face_index ] );
// 			printf( "vertex %d\n", vertex_indices[ face_index + 1 ] );
// 			printf( "texture %d\n", tex_coord_indices[ face_index + 1 ] );
// 			printf( "normal %d\n", normal_indices[ face_index + 1 ] );
// 			printf( "vertex %d\n", vertex_indices[ face_index + 2 ] );
// 			printf( "texture %d\n", tex_coord_indices[ face_index + 2 ] );
// 			printf( "normal %d\n", normal_indices[ face_index + 2 ] );

			face_index += 3;
			
		} else if( buffer.substr( 0, 1 ) == "v" ){
			//printf( "vertex\n" );

			sscanf( buffer.c_str(),
					"v %f %f %f",
					&vertices[ vertex_index ],
					&vertices[ vertex_index + 1 ],
					&vertices[ vertex_index + 2 ] );

			vertex_index += 3;

		}
	}

	file.close();

	model = CreateModel( *name,
						 vertices,
						 tex_coords,
						 normals,
						 num_vertices,
						 vertex_indices,
						 tex_coord_indices,
						 normal_indices,
						 *material_file );

	delete name ;
	delete material_file;
	delete[] vertices;
	delete[] tex_coords;
	delete[] normals;
	delete[] vertex_indices;
	delete[] tex_coord_indices;
	delete[] normal_indices;

	return model;
}

Model* OBJLoader::CreateModel( const std::string &name,
							   const float *vertices,
							   const float *tex_coords,
							   const float *normals,
							   const int num_vertices,
							   const int *vertex_idx,
							   const int *tex_coord_idx,
							   const int *normal_idx,
							   const std::string &material_file )
{
	Model *model;
	std::string *_name = new std::string( name );
	std::vector< float > *_vertices = new std::vector< float >( num_vertices );
	std::vector< float > *_tex_coords = new std::vector< float >( num_vertices );
	std::vector< float > *_normals = new std::vector< float >( num_vertices );

	/*Here we fill the vertex, texture and normal arrays.
	  We use the index array to calculate the polygons, since we
	  want to return the arrays to be used in a non-indexed way */
	for( int i = 0; i < num_vertices; ++i ){
		_vertices->at( i ) = vertices[ vertex_idx[ i ] ];
		_tex_coords->at( i ) = tex_coords[ tex_coord_idx[ i ] ];
		_normals->at( i ) = normals[ normal_idx[ i ] ];
	}

	if( &material_file != NULL ){
		OBJMaterialLoader *ml = new OBJMaterialLoader();
		std::vector< Material* > *materials = ml->LoadMaterials( material_file.c_str() );
		model = new Model( _name, _vertices, _tex_coords, _normals, materials );
	}else
		model = new Model(  _name, _vertices, _tex_coords, _normals );

	return model;
}
