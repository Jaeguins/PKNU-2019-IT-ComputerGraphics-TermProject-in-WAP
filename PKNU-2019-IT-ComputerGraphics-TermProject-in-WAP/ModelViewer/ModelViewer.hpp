#pragma once
#include <iostream>
#include <vector>

namespace model_Viewer
{
    struct vec3
    {
        float x=0,y=0,z=0;
    };
    struct vec2
    {
        float x=0,y=0;
    };
    struct face
    {
        vec3 vertices[3];
        vec2 uvs[3];
        vec3 normals[3];
    };
    class obj_reader
    {
    public:
        obj_reader(char* path);
        bool load(char* path);
        char* path=nullptr;
        std::vector<vec3>vertices;
        std::vector<vec2>uvs;
        std::vector<vec3>normals;
        std::vector<face>faces;
        
    };
}