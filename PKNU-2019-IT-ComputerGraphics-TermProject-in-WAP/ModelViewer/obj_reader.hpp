#pragma once
#include <vector>
#include "gl_vectors.hpp"
#include "gl_object.hpp"


namespace model_viewer
{
    using namespace advanced_gl;
    class obj_reader:public gl_object
    {
    public:
        obj_reader(const char* path);
        bool load(const char* path);
        char* path = nullptr;
        std::vector<gl_vec_3f>vertices;
        std::vector<gl_vec_2f>uvs;
        std::vector<gl_vec_3f>normals;
        std::vector<gl_face>faces;
    };

}
