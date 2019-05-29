#pragma once
#include <vector>
#include "gl_object.hpp"
#include <fstream>
#include <string>
#include <sstream>


namespace std {
    vector<string> split(string str, char delimiter);
}
namespace model_viewer
{
    using namespace advanced_gl;
    class obj_reader
    {
    public:
        obj_reader(char* path);
        bool load(char* path);
        char* path = nullptr;
        std::vector<gl_vec_3f>vertices;
        std::vector<gl_vec_2f>uvs;
        std::vector<gl_vec_3f>normals;
        std::vector<GlFace>faces;
    };

}
