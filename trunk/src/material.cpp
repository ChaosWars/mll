#include "material.hpp"

using namespace mll;

Material::Material( const string &name, const string &diffuse_map, const string &normal_map, const string &specular_map ) :
					_has_specular( false )
{
	_name = name;

	if( !diffuse_map.empty() ){
		ilGenImages( 1, &diffuse_tex );
		ilBindImage( diffuse_tex );
		ilLoadImage( diffuse_map.c_str() );
	}

	if( !normal_map.empty() ){
		ilGenImages( 1, &normal_tex );
		ilBindImage( normal_tex );
		ilLoadImage( normal_map.c_str() );
	}

	if( !specular_map.empty() ){
		ilGenImages( 1, &specular_tex );
		ilBindImage( specular_tex );
		ilLoadImage( specular_map.c_str() );
	}

	ambient_color.assign( 0.0 );
	diffuse_color.assign( 0.0 );
	specular_color.assign( 0.0 );
}

Material::~Material()
{
	if( diffuse_tex != 0 )
		ilDeleteImages( 1, &diffuse_tex );

	if( normal_tex != 0 )
		ilDeleteImages( 1, &normal_tex );

	if( specular_tex != 0 )
		ilDeleteImages( 1, &specular_tex );
}

string Material::Name()
{
	return _name;
}

ILuint* Material::DiffuseTexture()
{
	return &diffuse_tex;
}

ILuint* Material::NormalTexture()
{
	return &normal_tex;
}

ILuint* Material::SpecularTexture()
{
	return &specular_tex;
}

array< float, 3 >* Material::AmbientColor()
{
	return &ambient_color;
}

array< float, 3 >* Material::DiffuseColor()
{
	return &diffuse_color;
}

array< float, 3 >* Material::SpecularColor()
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

void Material::SetName( const string &name )
{
	_name = name;
}

void Material::SetDiffuseTexture( const string &diffuse_file )
{
	if( diffuse_tex != 0 )
		ilDeleteImages( 1, &diffuse_tex );

	ilGenImages( 1, &diffuse_tex );
	ilBindImage( diffuse_tex );
	ilLoadImage( diffuse_file.c_str() );
}

void Material::SetNormalTexture( const string &normal_file )
{
	if( &normal_tex != NULL )
		ilDeleteImages( 1, &normal_tex );

	ilGenImages( 1, &normal_tex );
	ilBindImage( normal_tex );
	ilLoadImage( normal_file.c_str() );
}

void Material::SetSpecularTexture( const string &specular_file )
{
	if( &specular_tex != NULL )
		ilDeleteImages( 1, &specular_tex );

	ilGenImages( 1, &specular_tex );
	ilBindImage( specular_tex );
	ilLoadImage( specular_file.c_str() );
}

void Material::SetAmbientColor( float red, float green, float blue )
{
	ambient_color[0] = red;
	ambient_color[1] = green;
	ambient_color[2] = blue;
}

void Material::SetDiffuseColor( float red, float green, float blue )
{
	diffuse_color[0] = red;
	diffuse_color[1] = green;
	diffuse_color[2] = blue;
}

void Material::SetSpecularColor( float red, float green, float blue )
{
	specular_color[0] = red;
	specular_color[1] = green;
	specular_color[2] = blue;
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
