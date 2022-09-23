#ifndef _MODEL_H_
#define _MODEL_H_

#include "material.hpp"
#include <string>
#include <vector>

using namespace std;

namespace mll {

/**
 * @brief The Model class provides an interface to data needed by 3D graphics
 * API's, layed out in a way suitable for direct use OpenGL without the need to
 * convert the data.
 */
class Model {
  public:
    /**
     * Creates a Model.
     *
     * @param name
     *		The name of the model.
     *
     * @param quad
     *		True if the model is quadrangulate, false if the model is
     *triangulated
     */
    Model(const string &name, bool quad, const vector<float> &normals,
          const vector<float> &tex_coords, const vector<float> &vertices,
          const vector<Material *> &materials);

    /**
     * Destroys the Model
     */
    ~Model();

    /**
     * @returns
     *		The name of the model.
     */
    const string &Name() const;

    /**
     * @returns
     *		True if the model is quadrangulate, false if the model is
     *triangulated
     */
    bool isQuad();

    /**
     * @returns
     * 		The number of normals in the model.
     */
    int NumNormals();

    /**
     * @returns
     * 		The number of texture coordinates in the model.
     */
    int NumTextureCoords();

    /**
     * @returns
     * 		The number of vertices in the model.
     */
    int NumVertices();

    /**
     * @returns
     *		The normal data for the model.
     */
    vector<float> *Normals();

    /**
     * @returns
     *		The texture coordinate data for the model.
     */
    vector<float> *TextureCoords();

    /**
     * @returns
     *		The vertex data for the model.
     */
    vector<float> *Vertices();

    /**
     * @returns
     *		An array of Material containing the materials
     *		used by the model.
     */
    vector<Material *> *Materials();

  private:
    bool q;
    string n;
    vector<float> vn;
    vector<float> tc;
    vector<float> v;
    vector<Material *> m;
};

} // namespace mll

#endif //_MODEL_H_
