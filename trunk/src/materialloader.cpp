#include "materialloader.h"
#include "material.h"

using namespace mll;

MaterialLoader::MaterialLoader()
{
}

MaterialLoader::~MaterialLoader()
{
}

Material** MaterialLoader::LoadMaterials( const char *material_file )
{
	Material **material = new Material *[0];
	return material;
}
