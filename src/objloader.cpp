#include <fstream>
#include <iostream>
#include <sstream>
#include "exception.hpp"
#include "material.hpp"
#include "objloader.hpp"
#include "objmaterialloader.hpp"

using namespace mll;

OBJLoader::OBJLoader()
{
}

OBJLoader::~OBJLoader()
{
}

Model* OBJLoader::LoadModel( const string &objfile )
{
	ifstream file;
	string buffer;

	file.open( objfile.c_str(), ifstream::in );

	if ( !file.is_open() ){
<<<<<<< .mine
		cout << "Failed to open model file." << endl;
		return new Model();
=======
		throw FileOpenException(objfile);
>>>>>>> .r24
	}

	string name, material_file;
	bool quad = false;

	/* Temporary data variables */
	int vi1, vi2, vi3, vi4;
	int ti1, ti2, ti3, ti4;
	int ni1, ni2, ni3, ni4;
	float n1, n2, n3;
	float v1, v2, v3;
	float t1, t2;

<<<<<<< .mine
=======
	/* Index arrays */
	vector<int> normal_idx;
	vector<int> vertex_idx;
	vector<int> tex_coord_idx;

	/* Data arrays */
	vector<float> normals;
	vector<float> vertices;
	vector<float> tex_coords;

>>>>>>> .r24
	while( !file.eof() ){
		getline( file, buffer );

<<<<<<< .mine
		if( buffer.substr( 0, 2 ) == "vn" ){
=======
		if( buffer.substr( 0, 6 ) == "mtllib" ){
			int len = buffer.length() - 6;
			char *mf = new char[len];
			sscanf( buffer.c_str(), "mtllib %s", mf );
			mf[len] = '\0';
			material_file = mf;
		}else if( buffer.substr( 0, 2 ) == "vn" ){
>>>>>>> .r24

			sscanf( buffer.c_str(),
					"vn %f %f %f",
	 				&n1, &n2, &n3 );

			normals.push_back(n1);
			normals.push_back(n2);
			normals.push_back(n3);

<<<<<<< .mine
		} else if( buffer.substr( 0, 2 ) == "vt" ){
=======
		}else if( buffer.substr( 0, 2 ) == "vt" ){
>>>>>>> .r24

			sscanf( buffer.c_str(),
					"vt %f %f",
					&t1, &t2 );
			
			tex_coords.push_back(t1);
			tex_coords.push_back(t2);

		}else if( buffer.substr( 0, 1 ) == "f" ){
			/* Note on the syntax vector.pushback(--var):
			 * All index array values in OBJ files start counting at 1,
			 * so we decrement each value to compensate for our starting to count at 0. */

<<<<<<< .mine
		} else if( buffer.substr( 0, 1 ) == "f" ){

=======
>>>>>>> .r24
			/* First check if the file is only composed of vertice information */
			int read = sscanf( buffer.c_str(),
					   "f %d %d %d %d",
   					    &vi1, &vi2, &vi3, &vi4 );

			if( read == 3 ){ /* The model is triangulated */
<<<<<<< .mine
				//cout << "Read triangulated face with only vertex information." << endl;
				vertex_indices[ face_index ] = v1;
				vertex_indices[ face_index + 1 ] = v2;
				vertex_indices[ face_index + 2 ] = v3;
		
				/* The vertex index array values start counting at 1,
				 * so we decrement each value to compensate for our
				 * starting to count at 0. */
				vertex_indices[ face_index ]--;
				vertex_indices[ face_index + 1 ]--;
				vertex_indices[ face_index + 2 ]--;
=======
				vertex_idx.push_back(--vi1);
			    vertex_idx.push_back(--vi2);
				vertex_idx.push_back(--vi3);
>>>>>>> .r24
			}else if( read == 4 ){ /* The model is quadrangulated */
<<<<<<< .mine
				//cout << "Read quadrangulated face with only vertex information." << endl;
				vertex_indices[ face_index ] = v1;
			    vertex_indices[ face_index + 1 ] = v2;
   				vertex_indices[ face_index + 2 ] = v3;
				vertex_indices[ face_index + 3 ] = v4;
				vertex_indices[ face_index ]--;
				vertex_indices[ face_index + 1 ]--;
				vertex_indices[ face_index + 2 ]--;
				vertex_indices[ face_index + 3 ]--;
=======
				quad = true;
				vertex_idx.push_back(--vi1);
			    vertex_idx.push_back(--vi2);
				vertex_idx.push_back(--vi3);
				vertex_idx.push_back(--vi4);
>>>>>>> .r24
			}

			/* If not, check to see if it contains normal information as well */
			if( read < 3 ){
				read = sscanf( buffer.c_str(),
<<<<<<< .mine
								"f %d//%d %d//%d %d//%d %d//%d",
								&v1, &n1, &v2, &n2, &v3, &n3, &v4, &n4 );
=======
     					       "f %d//%d %d//%d %d//%d %d//%d",
								&vi1, &ni1, &vi2, &ni2, &vi3, &ni3, &vi4, &ni4 );
>>>>>>> .r24

				if( read == 6 ){
<<<<<<< .mine
					//cout << "Read triangulated face with vertex and normal information." << endl;
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
=======
					vertex_idx.push_back(--vi1);
					normal_idx.push_back(--ni1);
    				vertex_idx.push_back(--vi2);
					normal_idx.push_back(--ni2);
					vertex_idx.push_back(--vi3);
					normal_idx.push_back(--ni3);
>>>>>>> .r24
				}else if( read == 8 ){
<<<<<<< .mine
					//cout << "Read quadrangulated face with vertex and normal information." << endl;
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
=======
					quad = true;
					vertex_idx.push_back(--vi1);
					normal_idx.push_back(--ni1);
    				vertex_idx.push_back(--vi2);
					normal_idx.push_back(--ni2);
					vertex_idx.push_back(--vi3);
					normal_idx.push_back(--ni3);
					vertex_idx.push_back(--vi4);
					normal_idx.push_back(--ni4);
>>>>>>> .r24
				}

			}else if( read < 6 ){ /* It could concievably contain vertice and texture information */
				read = sscanf( buffer.c_str(),
<<<<<<< .mine
								"f %d/%d %d/%d %d/%d %d/%d",
								&v1, &t1, &v2, &t2, &v3, &t3, &v4, &t4 );
=======
								"f %d/%d %d/%d %d/%d %d/%d",
								&vi1, &ti1, &vi2, &ti2, &vi3, &ti3, &vi4, &ti4 );
>>>>>>> .r24

				if( read == 6 ){
<<<<<<< .mine
					//cout << "Read triangulated face with vertex and texture information." << endl;
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
=======
					vertex_idx.push_back(--vi1);
					tex_coord_idx.push_back(--ti1);
    				vertex_idx.push_back(--vi2);
					tex_coord_idx.push_back(--ti2);
					vertex_idx.push_back(--vi3);
					tex_coord_idx.push_back(--ti3);
>>>>>>> .r24
				}else if( read == 8 ){
<<<<<<< .mine
					//cout << "Read quadrangulated face with vertex and testure information." << endl;
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
=======
					quad = true;
					vertex_idx.push_back(--vi1);
					tex_coord_idx.push_back(--ti1);
					vertex_idx.push_back(--vi2);
					tex_coord_idx.push_back(--ti2);
					vertex_idx.push_back(--vi3);
					tex_coord_idx.push_back(--ti3);
					vertex_idx.push_back(--vi4);
					tex_coord_idx.push_back(--ti4);
>>>>>>> .r24
				}

			}else if( read < 6 ){ /* Lastly, check to see if it contains vertice, texture and normal information */
				read = sscanf( buffer.c_str(),
<<<<<<< .mine
								"f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
								&v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3, &v4, &t4, &n4 );
=======
     					       "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
						       &vi1, &ti1, &ni1, &vi2, &ti2, &ni2, &vi3, &ti3, &ni3, &vi4, &ti4, &ni4 );
>>>>>>> .r24

				if( read == 9 ){
<<<<<<< .mine
					//cout << "Read triangulated face with vertex, normal and texture information." << endl;
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
=======
					vertex_idx.push_back(--vi1);
					tex_coord_idx.push_back(--ti1);
					normal_idx.push_back(--ni1);
					vertex_idx.push_back(--vi2);
					tex_coord_idx.push_back(--ti2);
					normal_idx.push_back(--ni2);
					vertex_idx.push_back(--vi3);
					tex_coord_idx.push_back(--ti3);
					normal_idx.push_back(--ni3);
>>>>>>> .r24
				}else if( read == 12 ){
<<<<<<< .mine
					//cout << "Read quadrangulated face with vertex, normal and testure information." << endl;
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
=======
					quad = true;
					vertex_idx.push_back(--vi1);
					tex_coord_idx.push_back(--ti1);
					normal_idx.push_back(--ni1);
					vertex_idx.push_back(--vi2);
					tex_coord_idx.push_back(--ti2);
					normal_idx.push_back(--ni2);
					vertex_idx.push_back(--vi3);
					tex_coord_idx.push_back(--ti3);
					normal_idx.push_back(--ni3);
					vertex_idx.push_back(--vi4);
					tex_coord_idx.push_back(--ti4);
					normal_idx.push_back(--ni4);
>>>>>>> .r24
				}
			}
<<<<<<< .mine

			face_index += 3;
=======
>>>>>>> .r24
			
<<<<<<< .mine
		} else if( buffer.substr( 0, 1 ) == "v" ){
=======
		}else if( buffer.substr( 0, 1 ) == "v" ){
>>>>>>> .r24

			sscanf( buffer.c_str(),
					"v %f %f %f",
					&v1, &v2, &v3 );

			vertices.push_back(v1);
			vertices.push_back(v2);
			vertices.push_back(v3);

		}else if( buffer.substr( 0, 1 ) == "o" ){
			int len = buffer.length() - 1;
			char * n = new char[len];
			sscanf(buffer.c_str(), "o %s", n );
			n[len] = '\0';
			name = n;
		}
	}

	file.close();

<<<<<<< .mine
	Model *model = CreateModel( name, vertices, tex_coords, normals, num_vertices, vertex_indices,
			     tex_coord_indices, normal_indices, material_file );

	delete[] name ;
	delete[] material_file;
	delete[] vertices;
	delete[] tex_coords;
	delete[] normals;
	delete[] vertex_indices;
	delete[] tex_coord_indices;
	delete[] normal_indices;

	return model;
=======
	return CreateModel( name, quad, normals, tex_coords, vertices,
						normal_idx, tex_coord_idx, vertex_idx, material_file );
>>>>>>> .r24
}

Model* OBJLoader::CreateModel( const string &name, bool quad, const vector<float> &normals, const vector<float> &tex_coords,
							   const vector<float> &vertices, const vector<int> &normal_idx, const vector<int> &tex_coord_idx,
							   const vector<int> &vertex_idx, const string &material_file )
{
<<<<<<< .mine
	Model *model = NULL;
	float *_vertices = NULL;
	float *_tex_coords = NULL;
	float *_normals = NULL;
	char *_name = new char[strlen(name)];
	strcpy(_name, name);

	if(vertices != NULL)
		_vertices = new float[num_vertices];

	if(tex_coords != NULL)
		_tex_coords = new float[num_vertices];

	if(normals != NULL)
		_normals = new float[num_vertices];

=======
>>>>>>> .r24
	/*Here we fill the vertex, texture and normal arrays.
	  We use the index array to calculate the polygons, since we
	  want to return the arrays to be used in a non-indexed way */
<<<<<<< .mine
	for( int i = 0; i < num_vertices; ++i ){
		if( normal_idx != NULL ){
=======
	vector<float> n;
	vector<float> tc;
	vector<float> v;
	vector<Material*> m;
>>>>>>> .r24

<<<<<<< .mine
			if( normals != NULL ){
				_normals[i] = normals[ normal_idx[ i ] ];
			}
		}		
=======
	/* Simple optimization resulting in N complexity, since this will generally be the case */
	if( normal_idx.size() == vertex_idx.size() && normal_idx.size() == tex_coord_idx.size() && vertex_idx.size() == tex_coord_idx.size() ){
		for( int i = 0; i < normal_idx.size(); ++i ){
			n.push_back( normals.at( normal_idx.at(i) ) );
			tc.push_back( tex_coords.at( tex_coord_idx.at(i) ) );
			v.push_back( vertices.at( vertex_idx.at(i) ) );
		}
	}else{ /* Otherwise we have to do this with complexity N^3*/
		for( int i = 0; i < normal_idx.size(); ++i ){
			n.push_back( normals.at( normal_idx.at(i) ) );
		}
>>>>>>> .r24

<<<<<<< .mine
		if( tex_coord_idx != NULL ){
			
			if( tex_coords != NULL ){
				_tex_coords[i] = tex_coords[ tex_coord_idx[ i ] ];
			}
=======
		for( int i = 0; i < tex_coord_idx.size(); ++i ){
			tc.push_back( tex_coords.at( tex_coord_idx.at(i) ) );
>>>>>>> .r24
		}

<<<<<<< .mine
		if( vertex_idx != NULL ){

			if( vertices != NULL ){
				_vertices[i] = vertices[ vertex_idx[ i ] ];
			}
=======
		for( int i = 0; i < vertex_idx.size(); ++i ){
			v.push_back( vertices.at( vertex_idx.at(i) ) );
>>>>>>> .r24
		}
	}

<<<<<<< .mine
	if( material_file != NULL ){
=======
	if( !material_file.empty() ){
>>>>>>> .r24
		OBJMaterialLoader ml;
<<<<<<< .mine
		Material **materials = NULL;
		int num_materials = ml.LoadMaterials( material_file, materials );
		model = new Model( _name, _vertices, _tex_coords, _normals, num_vertices, num_materials, materials );
	}else{
		model = new Model(  _name, _vertices, _tex_coords, _normals, num_vertices );
=======

		try{
			ml.LoadMaterials( material_file, m );
		}catch( exception &e){
			cout << e.what() << endl;
		}	
>>>>>>> .r24
	}

	return new Model( name, quad, n, tc, v, m );
}
