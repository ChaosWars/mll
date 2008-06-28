#include "modelloader.h"

using namespace mll;

ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

Model* ModelLoader::LoadModel( const char *model_file )
{
}

Model* ModelLoader::CreateModel( const std::string &name,
				const float *vertices,
				const float *tex_coords,
				const float *normals,
				const int num_vertices,
				const int *vertex_idx,
				const int *tex_coord_idx,
				const int *normal_idx,
				const std::string &material_file )
{
}
