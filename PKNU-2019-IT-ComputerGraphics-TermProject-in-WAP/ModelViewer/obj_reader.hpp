#pragma once
#ifndef CHILDH
#define CHILDH
#include <string>
#include <vector>
#include "gl_vectors.hpp"
#include "gl_object.hpp"

namespace model_viewer
{
    class viewport;
    using namespace advanced_gl;
    using namespace std;

    class obj_reader :public gl_object
    {
    public:
        float x_max,x_min,y_max,y_min,z_max,z_min;
        obj_reader(viewport* parent, const char* path);
        ~obj_reader();
        viewport* parent;
        void auto_magnify();
        bool load(string path);
        bool load_main_tex(string path);
        void auto_position();
        string path;
        GLuint main_tex=0xffffffff;
        std::vector<gl_vec_3f>vertices;
        std::vector<gl_vec_2f>uvs;
        std::vector<gl_vec_3f>normals;
        std::vector<gl_face>faces;
    };

}
#endif