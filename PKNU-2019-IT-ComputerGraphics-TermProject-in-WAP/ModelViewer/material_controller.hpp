#pragma once
#include "gl_vectors.hpp"
#include <string>
#include <vector>
using namespace advanced_gl;
using namespace std;
struct material {
    string name;
    gl_vec_3f ambient, diffuse, specular;
};
class material_controller {
public:
    vector<material> materials;
    material get_material(string name);
    string tex_diffuse, tex_specular, tex_ambient, tex_bump;
    void load(string path);
};
