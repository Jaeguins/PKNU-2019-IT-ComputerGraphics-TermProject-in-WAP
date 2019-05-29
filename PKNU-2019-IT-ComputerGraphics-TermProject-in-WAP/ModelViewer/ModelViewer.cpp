#include "ModelViewer.hpp"
#include <fstream>
#include <string>
#include <sstream>

namespace std {
    vector<string> split(string str, char delimiter) {
        vector<string> internal;
        stringstream ss(str);
        string temp;

        while (getline(ss, temp, delimiter)) {
            internal.push_back(temp);
        }

        return internal;
    }
}
namespace ModelViewer
{
    using namespace std;
    obj_reader::obj_reader(char* path)
    {
        this->load(path);
    }

    bool obj_reader::load(char* path)
    {
        this->path = path;
        vector<GlVec3f> temp_vertices, temp_normals;
        vector<GlVec2f> temp_uvs;
        vector<GlFace> temp_faces;
        ifstream file(path);
        if (!file.is_open())
        {
            return false;
        }
        while (true)
        {
            string line;
            if (!getline(file, line))
                break;
            vector<string>word = split(line, ' ');
            if (word[0] == "v") {
                GlVec3f vertex;
                vertex.x = stoi(word[1]);
                vertex.y = stoi(word[2]);
                vertex.z = stoi(word[3]);
                temp_vertices.push_back(vertex);
            }
            else if (word[0] == "vt") {
                GlVec2f uv;
                uv.x = stoi(word[1]);
                uv.y = stoi(word[2]);
                temp_uvs.push_back(uv);
            }
            else if (word[0] == "vn") {
                GlVec3f normal;
                normal.x = stoi(word[1]);
                normal.y = stoi(word[2]);
                normal.z = stoi(word[3]);
                temp_normals.push_back(normal);
            }
            else if (word[0] == "f") {
                GlFace face;
                if (word.size() != 4) {
                    return false;
                }
                vector<string> t_vertex;
                for (int i = 0; i < 3; i++) {
                    t_vertex = split(word[i+1], '/');
                    face.vertices[0] = GlVec3f(temp_vertices[stoi(t_vertex[0])]);
                    face.uvs[0] = GlVec2f(temp_uvs[stoi(t_vertex[1])]);
                    face.normals[0] = GlVec3f(temp_normals[stoi(t_vertex[2])]);
                }
                temp_faces.push_back(face);

                vertices=temp_vertices;
                uvs=temp_uvs;
                normals=temp_normals;
            }
            return true;
        }
    }

}