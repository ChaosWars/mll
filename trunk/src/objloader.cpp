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

	printf( "Read %d normals\n", num_normals );
	printf( "Read %d texture coordinates\n", num_tex_coords );
	printf( "Read %d vertices\n", num_indexed_vertices );
	printf( "Read %d faces\n", num_faces );
	printf( "material_file : %s\n", material_file->c_str() );
	printf( "name : %s\n", name->c_str() );

	//Allocate the memory for the data
	int *normal_indices = NULL;
	int *tex_coord_indices = NULL;
	int *vertex_indices = NULL;
	float *normals = NULL;
	float *tex_coords = NULL;
	float *vertices = NULL;
	num_vertices = num_faces * 3;
	
	if( num_normals > 0 ){
		normals = new float[ num_normals * 3 ];
		normal_indices = new int[ num_vertices ];
	}

	if( num_tex_coords > 0 ){
		tex_coords = new float[ num_tex_coords * 2 ] ;
		tex_coord_indices = new int[ num_vertices ];
	}

	if( num_indexed_vertices > 0 ){
		vertices = new float[ num_indexed_vertices * 3 ];
		vertex_indices = new int[ num_vertices ];
	}

	//Rewind file pointer in preperation for the second pass.
	file.clear();
	file.seekg( std::ifstream::beg );

	//Index variables for data arrays
	int vertex_index = 0;
	int tex_coord_index = 0;
	int normal_index = 0;
	int face_index = 0;
	int v1, v2, v3, v4;
	int t1, t2, t3, t4;
	int n1, n2, n3, n4;

	//second pass
	while( !file.eof() ){
		getline( file, buffer );
		//printf( "%s\n", buffer.c_str() );

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

			/* First check if the file is only composed of vertice information */
			int read = sscanf( buffer.c_str(),
					   "f %d %d %d %d",
   					    &v1, &v2, &v3, &v4 );

			if( read == 3 ){ /* The model is triangulated */
				vertex_indices[ face_index ] = v1;
			        vertex_indices[ face_index + 1 ] = v2;
   				vertex_indices[ face_index + 2 ] = v3;
		
				/* The vertex index array values start counting at 1,
				 * so we decrement each value to compensate for our
				 * starting to count at 0. */
				vertex_indices[ face_index ]--;
				vertex_indices[ face_index + 1 ]--;
				vertex_indices[ face_index + 2 ]--;
			}else if( read == 4 ){ /* The model is quadrangulated */
				vertex_indices[ face_index ] = v1;
			        vertex_indices[ face_index + 1 ] = v2;
   				vertex_indices[ face_index + 2 ] = v3;
				vertex_indices[ face_index + 3 ] = v4;
				vertex_indices[ face_index ]--;
				vertex_indices[ face_index + 1 ]--;
				vertex_indices[ face_index + 2 ]--;
				vertex_indices[ face_index + 3 ]--;
			}

			/* If not, check to see if it contains normal information as well */
			if( read < 3 ){
				read = sscanf( buffer.c_str(),
     					       "f %d//%d %d//%d %d//%d %d//%d",
					       &v1, &n1, &v2, &n2, &v3, &n3, &v4, &n4 );

				if( read == 6 ){
					vertex_indices[ face_index ] = v1;
    					normal_indices[ face_index ] = n1;
    					vertex_indices[ face_index + 1 ] = v2;
    					normal_indices[ face_index + 1 ] = n2;
    					vertex_indices[ face_index + 2 ] = v3;
    					normal_indices[ face_index + 2 ] = n3;
					vertex_indices[ face_index ]--;
					normal_indices[ face_index ]--;
					vertex_indices[ face_index + 1 ]--;
					normal_indices[ face_index + 1 ]--;
					vertex_indices[ face_index + 2 ]--;
					normal_indices[ face_index + 2 ]--;
				}else if( read == 8 ){
					vertex_indices[ face_index ] = v1;
    					normal_indices[ face_index ] = n1;
    					vertex_indices[ face_index + 1 ] = v2;
    					normal_indices[ face_index + 1 ] = n2;
    					vertex_indices[ face_index + 2 ] = v3;
    					normal_indices[ face_index + 2 ] = n3;
					vertex_indices[ face_index + 3 ] = v4;
    					normal_indices[ face_index + 3 ] = n4;
					vertex_indices[ face_index ]--;
					normal_indices[ face_index ]--;
					vertex_indices[ face_index + 1 ]--;
					normal_indices[ face_index + 1 ]--;
					vertex_indices[ face_index + 2 ]--;
					normal_indices[ face_index + 2 ]--;
					vertex_indices[ face_index + 3 ]--;
					normal_indices[ face_index + 3 ]--;
				}

			}else if( read < 6 ){ /* It could concievably contain vertice and texture information */
				read = sscanf( buffer.c_str(),
     					       "f %d/%d %d/%d %d/%d %d/%d",
					       &v1, &t1, &v2, &t2, &v3, &t3, &v4, &t4 );

				if( read == 6 ){
					vertex_indices[ face_index ] = v1;
    					tex_coord_indices[ face_index ] = t1;
    					vertex_indices[ face_index + 1 ] = v2;
    					tex_coord_indices[ face_index + 1 ] = t2;
    					vertex_indices[ face_index + 2 ] = v3;
    					tex_coord_indices[ face_index + 2 ] = t3;
					vertex_indices[ face_index ]--;
					tex_coord_indices[ face_index ]--;
					vertex_indices[ face_index + 1 ]--;
					tex_coord_indices[ face_index + 1 ]--;
					vertex_indices[ face_index + 2 ]--;
					tex_coord_indices[ face_index + 2 ]--;
				}else if( read == 8 ){
					vertex_indices[ face_index ] = v1;
    					tex_coord_indices[ face_index ] = t1;
    					vertex_indices[ face_index + 1 ] = v2;
    					tex_coord_indices[ face_index + 1 ] = t2;
    					vertex_indices[ face_index + 2 ] = v3;
    					tex_coord_indices[ face_index + 2 ] = t3;
					vertex_indices[ face_index + 3 ] = v4;
    					tex_coord_indices[ face_index + 3 ] = t4;
					vertex_indices[ face_index ]--;
					tex_coord_indices[ face_index ]--;
					vertex_indices[ face_index + 1 ]--;
					tex_coord_indices[ face_index + 1 ]--;
					vertex_indices[ face_index + 2 ]--;
					tex_coord_indices[ face_index + 2 ]--;
					vertex_indices[ face_index + 3 ]--;
					tex_coord_indices[ face_index + 3 ]--;
				}

			}else if( read < 6 ){ /* Lastly, check to see if it contains vertice, texture and normal information */
				read = sscanf( buffer.c_str(),
     					       "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
					       &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3, &v4, &t4, &n4 );

				if( read == 9 ){
					vertex_indices[ face_index ] = v1;
    					tex_coord_indices[ face_index ] = t1;
    					normal_indices[ face_index ] = n1;
					vertex_indices[ face_index + 1 ] = v2;
					tex_coord_indices[ face_index + 1 ] = t2;
					normal_indices[ face_index + 1 ] = n2;
					vertex_indices[ face_index + 2 ] = v3;
					tex_coord_indices[ face_index + 2 ] = t3;
					normal_indices[ face_index + 2 ] = n3;
					vertex_indices[ face_index ]--;
					tex_coord_indices[ face_index ]--;
					normal_indices[ face_index ]--;
					vertex_indices[ face_index + 1 ]--;
					tex_coord_indices[ face_index + 1 ]--;
					normal_indices[ face_index + 1 ]--;
					vertex_indices[ face_index + 2 ]--;
					tex_coord_indices[ face_index + 2 ]--;
					normal_indices[ face_index + 2 ]--;
				}else if( read == 12 ){
					vertex_indices[ face_index ] = v1;
    					tex_coord_indices[ face_index ] = t1;
    					normal_indices[ face_index ] = n1;
					vertex_indices[ face_index + 1 ] = v2;
					tex_coord_indices[ face_index + 1 ] = t2;
					normal_indices[ face_index + 1 ] = n2;
					vertex_indices[ face_index + 2 ] = v3;
					tex_coord_indices[ face_index + 2 ] = t3;
					normal_indices[ face_index + 2 ] = n3;
					vertex_indices[ face_index + 3 ] = v4;
					tex_coord_indices[ face_index + 3 ] = t4;
					normal_indices[ face_index + 3 ] = n4;
					vertex_indices[ face_index ]--;
					tex_coord_indices[ face_index ]--;
					normal_indices[ face_index ]--;
					vertex_indices[ face_index + 1 ]--;
					tex_coord_indices[ face_index + 1 ]--;
					normal_indices[ face_index + 1 ]--;
					vertex_indices[ face_index + 2 ]--;
					tex_coord_indices[ face_index + 2 ]--;
					normal_indices[ face_index + 2 ]--;
					vertex_indices[ face_index + 3 ]--;
					tex_coord_indices[ face_index + 3 ]--;
					normal_indices[ face_index + 3 ]--;
				}
			}

			printf( "sscanf returned %d\n", read );

 			/* printf( "vertex %d\n",vertex_indices[ face_index ] );
 			printf( "texture %d\n", tex_coord_indices[ face_index ] );
 			printf( "normal %d\n", normal_indices[ face_index ] );
 			printf( "vertex %d\n", vertex_indices[ face_index + 1 ] );
 			printf( "texture %d\n", tex_coord_indices[ face_index + 1 ] );
 			printf( "normal %d\n", normal_indices[ face_index + 1 ] );
 			printf( "vertex %d\n", vertex_indices[ face_index + 2 ] );
 			printf( "texture %d\n", tex_coord_indices[ face_index + 2 ] );
 			printf( "normal %d\n", normal_indices[ face_index + 2 ] ); */

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
	printf( "File closed.\n" );

	model = CreateModel( *name, vertices, tex_coords, normals, num_vertices, vertex_indices,
			     tex_coord_indices, normal_indices, *material_file );

	printf( "Created model.\n" );

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
	printf( "Beginning model creation.\n" );
	Model *model;
	char *_name = new char[name.size() + 1];
	strcpy( _name, name.c_str() );
	float *_vertices = new float[num_vertices];
	float *_tex_coords = new float[num_vertices];
	float *_normals = new float[num_vertices];

	printf( "Setup complete. Filling arrays.\n" );

	/*Here we fill the vertex, texture and normal arrays.
	  We use the index array to calculate the polygons, since we
	  want to return the arrays to be used in a non-indexed way */
	for( int i = 0; i < num_vertices; ++i ){
		if( normal_idx != NULL ){
			printf( "normal_idx[%d] = %d\n", i,  normal_idx[ i ] );

			if( normals != NULL ){
				printf( "normals[normal_idx[%d]] = %f\n",  normal_idx[ i ], normals[ normal_idx[ i ] ] );
				_normals[i] = normals[ normal_idx[ i ] ];
			}
		}		

		if( tex_coord_idx != NULL ){
			printf( "text_coord_idx[%d] = %d\n", i, tex_coord_idx[ i ] );

			if( tex_coords != NULL ){
				printf( "tex_coords[tex_coord_idx[%d]] = %f\n", tex_coord_idx[i], tex_coords[ tex_coord_idx[ i ] ] );
				_tex_coords[i] = tex_coords[ tex_coord_idx[ i ] ];
			}
		}

		if( vertex_idx != NULL ){
			printf( "vertex_idx[%d] = %d\n", i, vertex_idx[ i ] );

			if( vertices != NULL ){
				printf( "vertices[vertex_idx[%d]] = %f\n", vertex_idx[i], vertices[ vertex_idx[ i ] ] );
				_vertices[i] = vertices[ vertex_idx[ i ] ];
			}
		}
		
	}

	printf( "Arrays filled.\n" );

	if( &material_file != NULL ){
		printf( "Reading materials.\n" );
		OBJMaterialLoader *ml = new OBJMaterialLoader();
		Material **materials = ml->LoadMaterials( material_file.c_str() );
		printf( "Creating model.\n" );
		model = new Model( _name, _vertices, _tex_coords, _normals, materials );
	}else{
		printf( "Creating model.\n" );
		model = new Model(  _name, _vertices, _tex_coords, _normals );
	}

	return model;
}
