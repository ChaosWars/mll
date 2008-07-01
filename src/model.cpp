#include <string>
#include "model.hpp"

using namespace mll;

<<<<<<< .mine
Model::Model( char *name,
		float *vertices,
		float *tex_coords,
		float *normals,
		int num_vertices,
		int num_materials,
		Material **materials )
=======
Model::Model( const string &name, bool quad, const vector<float> &normals, const vector<float> &tex_coords,
					const vector<float> &vertices, const vector<Material*> &materials )
: n(name), q(quad), vn(normals), tc(tex_coords), v(vertices), m(materials)
>>>>>>> .r24
{
<<<<<<< .mine
	this->name = new char[strlen(name)+1]
	this->name = name;
	this->vertices = vertices;
	this->tex_coords = tex_coords;
	this->normals = normals;
	num_texture_coords = num_normals = this->num_vertices = num_vertices;
	this->num_materials = num_materials;
	this->materials = materials;
=======
>>>>>>> .r24
}

Model::~Model()
{
<<<<<<< .mine
	delete[] name;
	delete[] vertices;
	delete[] tex_coords;
	delete[] normals;
=======
}
>>>>>>> .r24

<<<<<<< .mine
	if( materials != NULL ){
		for(int i = 0; i < num_materials; i++){
			delete materials[i];
		}

		delete[] materials;
	}
=======
const string& Model::Name() const
{
	return n;
}

bool Model::isQuad()
{
	return q;
}

int Model::NumNormals()
{
	return vn.size();
>>>>>>> .r24
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
