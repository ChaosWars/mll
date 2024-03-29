#include <fstream>
#include <iostream>
#include <sstream>
#include <IL/ilut.h>
#include "exception.hpp"
#include "objmaterialloader.hpp"

using namespace mll;

OBJMaterialLoader::OBJMaterialLoader()
{
}

OBJMaterialLoader::~OBJMaterialLoader()
{
}

void OBJMaterialLoader::LoadMaterials( const string &material_file, vector<Material*> &materials )
{
	ifstream file;
	string buffer;

	file.open( material_file.c_str(), ifstream::in );

	if ( !file.is_open() ){
		throw FileOpenException(material_file);
	}

	string name, diffuse_map, normal_map, specular_map;
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

	while( !file.eof() ){
		getline( file, buffer );

		while( buffer.substr( 0, 6 ) != "newmtl" ){
			getline( file, buffer );
		}

		int len = buffer.length() - 6;
		char *n = new char[len];
		sscanf( buffer.c_str(), "newmtl %s", n );
		n[len] = '\0';
		name = n;
		getline( file, buffer );

		while( buffer.substr( 0, 6 ) != "newmtl" && !file.eof() ){

			if( buffer.substr( 0, 6 ) == "map_Kd" ){
				int len = buffer.length() - 6;
				char *d = new char[len];
				sscanf( buffer.c_str(), "map_Kd %s", d );
				d[len] = '\0';
				diffuse_map = d;
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

		materials.push_back( new Material( name, diffuse_map, normal_map, specular_map ) );
		materials.back()->SetAmbientColor( ambient_red, ambient_green, ambient_blue );
		materials.back()->SetDiffuseColor( diffuse_red, diffuse_green, diffuse_blue );

		if( has_specular ){
			materials.back()->SetHasSpecular( true );
			materials.back()->SetSpecularColor( specular_red, specular_green, specular_blue );
		}

		materials.back()->SetAlpha( alpha );
		materials.back()->SetShininess( shininess );

		name.clear();
		diffuse_map.clear();
		normal_map.clear();
		specular_map.clear();
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
	}

	file.close();
}
