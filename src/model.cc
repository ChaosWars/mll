#include <string>
#include "model.h"

using namespace mll;

Model::Model( std::string *name,
			  std::vector< float > *vertices,
			  std::vector< float > *tex_coords,
			  std::vector< float > *normals,
			  std::vector< Material* > *materials )
{
	if( name != NULL )
		this->name = name;
	else
		this->name = NULL;

	if( vertices != NULL )
		this->vertices = vertices;
	else
		this->vertices = NULL;

	if( tex_coords != NULL )
		this->tex_coords = tex_coords;
	else
		this->tex_coords = NULL;

	if( normals != NULL )
		this->normals = normals;
	else
		this->normals = NULL;

	if( materials != NULL )
		this->materials = materials;
	else
		this->materials = NULL;
}

Model::~Model()
{
	if( name != NULL )
		delete name;

	if( vertices != NULL )
		delete vertices;

	if( tex_coords != NULL )
		delete tex_coords;

	if( normals != NULL )
		delete name;

	if( materials != NULL )
		delete materials;
}

const std::string* Model::Name()
{
	if( name != NULL )
		return const_cast< std::string* >( name );
	else
		return NULL;
}

const std::vector< float >* Model::Vertices()
{
	if( vertices != NULL )
		return const_cast< std::vector< float >* >( vertices );
	else
		return NULL;
}

const std::vector< float >* Model::TextureCoords()
{
	if( tex_coords != NULL)
		return const_cast< std::vector< float >* >( tex_coords );
	else
		return NULL;
}

const std::vector< float >* Model::Normals()
{
	if( normals != NULL )
		return const_cast< std::vector< float >* >( normals );
	else
		return NULL;
}

const std::vector< Material* >* Model::Materials()
{
	if( materials != NULL )
		return const_cast< std::vector< Material* >* >( materials );
	else
		return NULL;
}
