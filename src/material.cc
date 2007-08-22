#include "material.h"

using namespace mll;

Material::Material( const std::string &name, char *diffuse_file,
	 				char *normal_file, char *specular_file ) :
					_has_specular( false )
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

	ambient_color.assign( 0.0 );
	diffuse_color.assign( 0.0 );
	specular_color.assign( 0.0 );
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

const boost::array< float, 3 >* Material::AmbientColor()
{
	return &ambient_color;
}

const boost::array< float, 3 >* Material::DiffuseColor()
{
	return &diffuse_color;
}

const boost::array< float, 3 >* Material::SpecularColor()
{
	return &specular_color;
}

float Material::Alpha()
{
	return _alpha;
}

float Material::Shininess()
{
	return _shininess;
}

bool Material::HasSpecular()
{
	return _has_specular;
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

void Material::SetAmbientColor( float red, float blue, float green )
{
	ambient_color[ 0 ] = red;
	ambient_color[ 1 ] = blue;
	ambient_color[ 2 ] = green;
}

void Material::SetDiffuseColor( float red, float blue, float green )
{
	diffuse_color[ 0 ] = red;
	diffuse_color[ 1 ] = blue;
	diffuse_color[ 2 ] = green;
}

void Material::SetSpecularColor( float red, float blue, float green )
{
	specular_color[ 0 ] = red;
	specular_color[ 1 ] = blue;
	specular_color[ 2 ] = green;
}

void Material::SetAlpha( float alpha )
{
	_alpha = alpha;
}

void Material::SetShininess( float shininess )
{
	_shininess = shininess;
}

void Material::SetHasSpecular( bool has_specular )
{
	_has_specular = has_specular;
}
