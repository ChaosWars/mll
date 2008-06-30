#include <fstream>
#include <iostream>
#include <sstream>
#include "exception.h"
#include "material.h"
#include "objloader.h"
#include "objmaterialloader.h"

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
		throw FileOpenException(objfile);
	}

	string name, material_file;
	bool quad;

	/* Temporary data variables */
	int vi1, vi2, vi3, vi4;
	int ti1, ti2, ti3, ti4;
	int ni1, ni2, ni3, ni4;
	float n1, n2, n3;
	float v1, v2, v3;
	float t1, t2;

	/* Index arrays */
	vector<int> normal_idx;
	vector<int> vertex_idx;
	vector<int> tex_coord_idx;

	/* Data arrays */
	vector<float> normals;
	vector<float> vertices;
	vector<float> tex_coords;

	while( !file.eof() ){
		getline( file, buffer );

		if( buffer.substr( 0, 6 ) == "mtllib" ){
			int len = buffer.length() - 6;
			char *mf = new char[len];
			sscanf( buffer.c_str(), "mtllib %s", mf );
			mf[len] = '\0';
			material_file = mf;
		}else if( buffer.substr( 0, 2 ) == "vn" ){

			sscanf( buffer.c_str(),
					"vn %f %f %f",
	 				&n1, &n2, &n3 );

			normals.push_back(n1);
			normals.push_back(n2);
			normals.push_back(n3);

		}else if( buffer.substr( 0, 2 ) == "vt" ){

			sscanf( buffer.c_str(),
					"vt %f %f",
					&t1, &t2 );
			
			tex_coords.push_back(t1);
			tex_coords.push_back(t2);

		}else if( buffer.substr( 0, 1 ) == "f" ){
			/* Note on the syntax vector.pushback(--var):
			 * All index array values in OBJ files start counting at 1,
			 * so we decrement each value to compensate for our starting to count at 0. */

			/* First check if the file is only composed of vertice information */
			int read = sscanf( buffer.c_str(),
					   "f %d %d %d %d",
   					    &vi1, &vi2, &vi3, &vi4 );

			if( read == 3 ){ /* The model is triangulated */
				vertex_idx.push_back(--vi1);
			    vertex_idx.push_back(--vi2);
				vertex_idx.push_back(--vi3);
			}else if( read == 4 ){ /* The model is quadrangulated */
				vertex_idx.push_back(--vi1);
			    vertex_idx.push_back(--vi2);
				vertex_idx.push_back(--vi3);
				vertex_idx.push_back(--vi4);
			}

			/* If not, check to see if it contains normal information as well */
			if( read < 3 ){
				read = sscanf( buffer.c_str(),
     					       "f %d//%d %d//%d %d//%d %d//%d",
								&vi1, &ni1, &vi2, &ni2, &vi3, &ni3, &vi4, &ni4 );

				if( read == 6 ){
					vertex_idx.push_back(--vi1);
					normal_idx.push_back(--ni1);
    				vertex_idx.push_back(--vi2);
					normal_idx.push_back(--ni2);
					vertex_idx.push_back(--vi3);
					normal_idx.push_back(--ni3);
				}else if( read == 8 ){
					vertex_idx.push_back(--vi1);
					normal_idx.push_back(--ni1);
    				vertex_idx.push_back(--vi2);
					normal_idx.push_back(--ni2);
					vertex_idx.push_back(--vi3);
					normal_idx.push_back(--ni3);
					vertex_idx.push_back(--vi4);
					normal_idx.push_back(--ni4);
				}

			}else if( read < 6 ){ /* It could concievably contain vertice and texture information */
				read = sscanf( buffer.c_str(),
								"f %d/%d %d/%d %d/%d %d/%d",
								&vi1, &ti1, &vi2, &ti2, &vi3, &ti3, &vi4, &ti4 );

				if( read == 6 ){
					vertex_idx.push_back(--vi1);
					tex_coord_idx.push_back(--ti1);
    				vertex_idx.push_back(--vi2);
					tex_coord_idx.push_back(--ti2);
					vertex_idx.push_back(--vi3);
					tex_coord_idx.push_back(--ti3);
				}else if( read == 8 ){
					vertex_idx.push_back(--vi1);
					tex_coord_idx.push_back(--ti1);
					vertex_idx.push_back(--vi2);
					tex_coord_idx.push_back(--ti2);
					vertex_idx.push_back(--vi3);
					tex_coord_idx.push_back(--ti3);
					vertex_idx.push_back(--vi4);
					tex_coord_idx.push_back(--ti4);
				}

			}else if( read < 6 ){ /* Lastly, check to see if it contains vertice, texture and normal information */
				read = sscanf( buffer.c_str(),
     					       "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
						       &vi1, &ti1, &ni1, &vi2, &ti2, &ni2, &vi3, &ti3, &ni3, &vi4, &ti4, &ni4 );

				if( read == 9 ){
					vertex_idx.push_back(--vi1);
					tex_coord_idx.push_back(--ti1);
					normal_idx.push_back(--ni1);
					vertex_idx.push_back(--vi2);
					tex_coord_idx.push_back(--ti2);
					normal_idx.push_back(--ni2);
					vertex_idx.push_back(--vi3);
					tex_coord_idx.push_back(--ti3);
					normal_idx.push_back(--ni3);
				}else if( read == 12 ){
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
				}
			}
			
		}else if( buffer.substr( 0, 1 ) == "v" ){

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

	return CreateModel( name, quad, vertices, tex_coords, normals, vertex_idx,
						tex_coord_idx, normal_idx, material_file );
}

Model* OBJLoader::CreateModel( const string &name, bool quad, const vector<float> &vertices, const vector<float> &tex_coords,
							   const vector<float> &normals, const vector<int> &vertex_idx, const vector<int> &tex_coord_idx,
							   const vector<int> &normal_idx, const string &material_file )
{
	/*Here we fill the vertex, texture and normal arrays.
	  We use the index array to calculate the polygons, since we
	  want to return the arrays to be used in a non-indexed way */
	vector<float> n;
	vector<float> v;
	vector<float> tc;
	vector<Material*> m;

	/* Simple optimization resulting in N complexity, since this will generally be the case */
	if( normals.size() == vertices.size() && normals.size() == tex_coords.size() && vertices.size() == tex_coords.size() ){
		for( int i = 0; i < normals.size(); ++i ){
			n.push_back( normals.at( normal_idx.at(i) ) );
			v.push_back( vertices.at( vertex_idx.at(i) ) );
			tc.push_back( tex_coords.at( tex_coord_idx.at(i) ) );
		}
	}else{ /* Otherwise we have to do this with complexity N^3*/
		for( int i = 0; i < normals.size(); ++i ){
			n.push_back( normals.at( normal_idx.at(i) ) );
		}

		for( int i = 0; i < vertices.size(); ++i ){
			v.push_back( vertices.at( vertex_idx.at(i) ) );
		}

		for( int i = 0; i < tex_coords.size(); ++i ){
			tc.push_back( tex_coords.at( tex_coord_idx.at(i) ) );
		}
	}

	if( !material_file.empty() ){
		OBJMaterialLoader ml;

		try{
			ml.LoadMaterials( material_file, m );
		}catch( exception &e){
			cout << e.what() << endl;
		}	
	}

	return new Model( name, quad, n, v, tc, m );
}
