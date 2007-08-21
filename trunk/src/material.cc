#include "material.h"

using namespace mll;

Material::Material( const std::string &name, char *diffuse_file,
	 				char *normal_file, char *specular_file )
{
	if( &name != NULL )
		this->name = new std::string( name );
	else
		this->name = NULL;

	if( diffuse_file != NULL ){
		ilGenImages( 1, &diffuse_tex );
		ilBindImage( diffuse_tex );
		ilLoadImage( diffuse_file );
	}else
		this->diffuse_tex = NULL;

	if( normal_file != NULL ){
		ilGenImages( 1, &normal_tex );
		ilBindImage( normal_tex );
		ilLoadImage( normal_file );
	}else
		this->normal_tex = NULL;

	if( specular_file != NULL ){
		ilGenImages( 1, &specular_tex );
		ilBindImage( specular_tex );
		ilLoadImage( specular_file );
	}else
		this->specular_tex = NULL;
}

Material::~Material()
{
	if( name != NULL )
		delete name;

	if( diffuse_tex != 0 )
		ilDeleteImages( 1, &diffuse_tex );

	if( normal_tex != 0 )
		ilDeleteImages( 1, &normal_tex );

	if( specular_tex != 0 )
		ilDeleteImages( 1, &specular_tex );
}

// Material& Material::operator= ( Material &material )
// {
// 	if( this != &material ){
// 
// 		if( name != NULL ){
// 			delete name;
// 			name = NULL;
// 
// 			if( material.Name() != NULL )
// 				name = const_cast< std::string* >( material.Name() );
// 
// 		}
// 
// 		if( &diffuse_tex != NULL ){
// 			ilDeleteImages( 1, &diffuse_tex );
// 			diffuse_tex = NULL;
// 
// 			if( material.DiffuseTexture() != NULL )
// 				diffuse_tex = *const_cast< ILuint* >( material.DiffuseTexture() );
// 		}
// 
// 		if( &normal_tex != NULL ){
// 			ilDeleteImages( 1, &normal_tex );
// 			normal_tex = NULL;
// 
// 			if( material.NormalTexture() != NULL )
// 				normal_tex = *const_cast< ILuint* >( material.NormalTexture() );
// 		}
// 
// 		if( &specular_tex != NULL ){
// 			ilDeleteImages( 1, &specular_tex );
// 			specular_tex = NULL;
// 
// 			if( material.SpecularTexture() != NULL )
// 				specular_tex = *const_cast< ILuint* >( material.SpecularTexture() );
// 		}
// 	}
// 
// 	return *this;
// }

const std::string* Material::Name()
{
	if( name != NULL )
		return name;
	else
		return NULL;
}

const ILuint* Material::DiffuseTexture()
{
	if( &diffuse_tex != NULL )
		return &diffuse_tex;
	else
		return NULL;
}

const ILuint* Material::NormalTexture()
{
	if( &normal_tex != NULL )
		return &normal_tex;
	else
		return NULL;
}

const ILuint* Material::SpecularTexture()
{
	if( &specular_tex != NULL )
		return &specular_tex;
	else
		return NULL;	
}

void Material::SetName( const std::string &name )
{
	if( this->name != NULL ){
		delete this->name;
		this->name = NULL;
	}

	this->name = new std::string( name );
}

void Material::SetDiffuseTexture( char *diffuse_file )
{
	if( &diffuse_tex != NULL )
		ilDeleteImages( 1, &diffuse_tex );

	ilGenImages( 1, &diffuse_tex );
	ilBindImage( diffuse_tex );
	ilLoadImage( diffuse_file );
}

void Material::SetNormalTexture( char *normal_file )
{
	if( &normal_tex != NULL )
		ilDeleteImages( 1, &normal_tex );

	ilGenImages( 1, &normal_tex );
	ilBindImage( normal_tex );
	ilLoadImage( normal_file );
}

void Material::SetSpecularTexture( char *specular_file )
{
	if( &specular_tex != NULL )
		ilDeleteImages( 1, &specular_tex );

	ilGenImages( 1, &specular_tex );
	ilBindImage( specular_tex );
	ilLoadImage( specular_file );
}
