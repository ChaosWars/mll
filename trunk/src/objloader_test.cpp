#include <stdlib.h>
#include <iostream>
#include "exception.h"
#include "objloader.h"

using namespace mll;

void PrintModelGeometryInfo( Model &model )
{
	cout << "Name: " << model.Name();
	int nn = cmodel.Normals()->size();
	int nt = model.TextureCoords()->size();
	int nv = model.Vertices()->size();
	cout << "Number of normals: " << nn << endl;
	cout << "Number of textures: " << nt << endl;
	cout << "Number of vertices: " << nv << endl << endl;
	cout << "Geometry:" << endl;

	vector<float> *normals = model.Normals();
	vector<float> *vertices = model.Vertices();
	vector<float> *tex_coords = model.TextureCoords();
	
	if( nn == nt && nn == nv && nt == nv ){
		for(int i = 0; i < nn; i++){
			count << "v: " << normals->at(i);

		}
	}
}

void PrintModelMaterialInfo( const Model &model )
{
}

int main(int argc, char **argv)
{
	if( argc < 2 ){
		cout << "This program requires an OBJ file as an argument." << endl;
		return EXIT_FAILURE;
	}

	OBJLoader *objloader = new OBJLoader();

	try{
		Model *model = objloader->LoadModel( argv[1] );
		cout << "Model loaded succesfully." << endl;
		cout << "Model geometry information:" << endl;
		PrintModelGeometryInfo( *model );
		cout << "Model material information:" << endl;
		PrintModelMaterialInfo( *model );
		delete model;
		return EXIT_SUCCESS;
	}catch(FileOpenException &e){
		cout << "Failed to open file " << e.what() << endl;
		return EXIT_FAILURE;
	}
}

