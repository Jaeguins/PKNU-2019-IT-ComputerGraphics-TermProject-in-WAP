#pragma once
#include <vector>
#include "GlObject.hpp"
#include "Viewport.hpp"
namespace ModelViewer
{
    using namespace GlVector;
    using namespace viewport;

    class obj_reader
    {
    public:
        obj_reader(char* path);
        bool load(char* path);
        char* path = nullptr;
        std::vector<GlVec3f>vertices;
        std::vector<GlVec2f>uvs;
        std::vector<GlVec3f>normals;
        std::vector<GlFace>faces;
    };

    class obj_viewer
    {
    public:
        Viewport* viewport;
        obj_reader readed;
        GlObject converted;
        void Convert();
        void read(string filename);
        void clear();
        obj_viewer(int,char**);
    };
}