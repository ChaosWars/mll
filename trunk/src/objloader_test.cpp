#include <stdlib.h>
#include "objloader.h"

using namespace mll;

int main(int argc, char **argv)
{
	if( argc < 2 ){
		printf( "This program requires an OBJ file as an argument.\n" );
		return EXIT_FAILURE;
	}

	OBJLoader *objloader = new OBJLoader();
	Model *model = objloader->LoadModel( argv[1] );

	if( model != NULL ){
		printf( "Model loaded succesfully.\n" );
		//delete model;
		return EXIT_SUCCESS;
	}else{
		printf( "Model failed to load.\n" );
		return EXIT_FAILURE;
	}
}

