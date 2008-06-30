#include <string>
#include "model.h"

using namespace mll;

Model::Model( const string &name, bool quad, const vector<float> &normals, const vector<float> &tex_coords,
					const vector<float> &vertices, const vector<Material*> &materials )
: n(name), vn(normals), tc(tex_coords), v(vertices), m(materials)
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

vector<float>* Model::Vertices()
{
	return &v;
}

vector<float>* Model::TextureCoords()
{
	return &tc;
}

vector<float>* Model::Normals()
{
	return &vn;
}

vector<Material*>* Model::Materials()
{
	return &m;
}
