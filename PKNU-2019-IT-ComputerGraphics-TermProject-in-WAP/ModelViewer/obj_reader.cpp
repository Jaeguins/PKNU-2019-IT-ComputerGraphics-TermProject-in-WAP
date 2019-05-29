#include "obj_reader.hpp"
#include <vector>
#include <fstream>
#include <string>
#include "string_split.h"
#include "gl_object.hpp"

namespace model_viewer
{
    using namespace std;
    obj_reader::obj_reader(const char* path)
    {
        this->load(path);
    }
    
    bool obj_reader::load(const char* path)
    {
        strcpy_s(this->path,strlen(path),path);
        vector<gl_vec_3f> temp_vertices, temp_normals;
        vector<gl_vec_2f> temp_uvs;
        vector<gl_face> temp_faces;
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
                gl_vec_3f vertex;
                vertex.x = stoi(word[1]);
                vertex.y = stoi(word[2]);
                vertex.z = stoi(word[3]);
                temp_vertices.push_back(vertex);
            }
            else if (word[0] == "vt") {
                gl_vec_2f uv;
                uv.x = stoi(word[1]);
                uv.y = stoi(word[2]);
                temp_uvs.push_back(uv);
            }
            else if (word[0] == "vn") {
                gl_vec_3f normal;
                normal.x = stoi(word[1]);
                normal.y = stoi(word[2]);
                normal.z = stoi(word[3]);
                temp_normals.push_back(normal);
            }
            else if (word[0] == "f") {
                gl_face face;
                if (word.size() != 4) {
                    return false;
                }
                vector<string> t_vertex;
                for (int i = 0; i < 3; i++) {
                    t_vertex = split(word[i + 1], '/');
                    face.vertices[0] = gl_vec_3f(temp_vertices[stoi(t_vertex[0])]);
                    face.uvs[0] = gl_vec_2f(temp_uvs[stoi(t_vertex[1])]);
                    face.normals[0] = gl_vec_3f(temp_normals[stoi(t_vertex[2])]);
                }
                temp_faces.push_back(face);

                vertices = temp_vertices;
                uvs = temp_uvs;
                normals = temp_normals;
            }
            return true;
        }
    }
}