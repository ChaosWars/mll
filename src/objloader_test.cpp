#include <stdlib.h>
#include <iostream>
#include "mll.hpp"

using namespace mll;

void PrintModelGeometryInfo( Model &model )
{
	cout << "Geometry:" << endl;
	int nn = model.NumNormals();
	int nt = model.NumTextureCoords();
	int nv = model.NumVertices();
	cout << "Number of normals: " << nn << endl;
	cout << "Number of textures: " << nt << endl;
	cout << "Number of vertices: " << nv << endl << endl;

	vector<float> *normals = model.Normals();
	vector<float> *tex_coords = model.TextureCoords();
	vector<float> *vertices = model.Vertices();
	
	try{
		if( model.isQuad() ){ /* If the model is quadrangulated */
			if( nn == nt && nn == nv && nt == nv ){
				for(int i = 0; i < nn; i += 4){
					cout << "n: " << normals->at(i) << " " << normals->at(i+1) << " " << normals->at(i+2) << " " << normals->at(i+3) << endl;
					cout << "t: " << tex_coords->at(i) << " " << tex_coords->at(i+1) << " " << tex_coords->at(i+2) << " " << tex_coords->at(i+3) << endl;
					cout << "v: " << vertices->at(i) << " " << vertices->at(i+1) << " " << vertices->at(i+2) << " " << vertices->at(i+3)  << endl;
				}
			}else{
				for(int i = 0; i < nn; i += 4){
					cout << "n: " << normals->at(i) << " " << normals->at(i+1) << " " << normals->at(i+2) << " " << normals->at(i+3) << endl;
				}

				for(int i = 0; i < nt; i+= 4){
					cout << "t: " << tex_coords->at(i) << " " << tex_coords->at(i+1) << " " << tex_coords->at(i+2) << " " << tex_coords->at(i+3) << endl;
				}

				for(int i = 0; i < nv; i += 4){
					cout << "v: " << vertices->at(i) << " " << vertices->at(i+1) << " " << vertices->at(i+2) << " " << vertices->at(i+3) << endl;
				}

			}
		}else{ /* Otherwise the model is triangulated */
			if( nn == nt && nn == nv && nt == nv ){
				for(int i = 0; i < nn; i += 3){
					cout << "n: " << normals->at(i) << " " << normals->at(i+1) << " " << normals->at(i+2) << " " << endl;
					cout << "t: " << tex_coords->at(i) << " " << tex_coords->at(i+1) << " " << tex_coords->at(i+2) << " " << endl;
					cout << "v: " << vertices->at(i) << " " << vertices->at(i+1) << " " << vertices->at(i+2) << " " << endl;
				}
			}else{
				for(int i = 0; i < nn; i += 3){
					cout << "n: " << normals->at(i) << " " << normals->at(i+1) << " " << normals->at(i+2) << " " << endl;
				}

				for(int i = 0; i < nt; i+= 3){
					cout << "t: " << tex_coords->at(i) << " " << tex_coords->at(i+1) << " " << tex_coords->at(i+2) << " " << endl;
				}

				for(int i = 0; i < nv; i += 3){
					cout << "v: " << vertices->at(i) << " " << vertices->at(i+1) << " " << vertices->at(i+2) << " " << endl;
				}

			}
		}
	}catch(out_of_range &e){
		cout << e.what() << endl;
	}
}

void PrintModelMaterialInfo( const Model &model )
{
	cout << "Materials:" << endl;
}

int main(int argc, char **argv)
{
	if( argc < 2 ){
		cout << "This program requires an OBJ file as an argument." << endl;
		return EXIT_FAILURE;
	}

	OBJLoader *objloader = new OBJLoader();

	try{
		const MLLVersion *version = getMLLVersion();
		cout << "Using Model Loading Library Version " << version->MAJOR << "." << version->MINOR << endl << endl;
		Model *model = objloader->LoadModel( argv[1] );
		cout << "Model information:" << endl;
		cout << "Name: " << model->Name() << endl << endl;
		PrintModelGeometryInfo( *model );
		cout << endl;
		PrintModelMaterialInfo( *model );
		delete model;
		return EXIT_SUCCESS;
	}catch(FileOpenException &e){
		cout << "Failed to open file " << e.what() << endl;
		return EXIT_FAILURE;
	}
}

