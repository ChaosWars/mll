#include <string>
#include "model.h"

using namespace mll;

Model::Model( const string &name, bool quad, const vector<float> &vertices, const vector<float> &tex_coords,
			 const vector<float> &normals, const vector<Material*> &materials )
: n(name), v(vertices), tc(tex_coords), vn(normals), m(materials)
{
}

Model::~Model()
{
}

const string& Model::Name() const
{
	return n;
}

bool Model::Quad()
{
	return q;
}

int Model::NumNormals()
{
	return vn.size();
}

int Model::NumTextureCoords()
{
	return tc.size();
}

int Model::NumVertices()
{
	return v.size();
}

const vector<float>* Model::Vertices()
{
	return const_cast< vector<float>* >( &v );
}

const vector<float>* Model::TextureCoords()
{
	return const_cast< vector<float>* >( &tc );
}

const vector<float>* Model::Normals()
{
	return const_cast< vector<float>* >( &vn );
}

const vector<Material*>* Model::Materials()
{
	return const_cast< vector<Material*>* >( &m );
}
