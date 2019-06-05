
#include "obj_reader.hpp"
#include <fstream>
#include "string_split.h"
#include "viewport.hpp"
#include "gl_Camera.hpp"
#include <algorithm>


namespace model_viewer
{
    using namespace std;
    obj_reader::obj_reader(viewport* parent, const char* path) :gl_object::gl_object()
    {
        this->Scale = Scale / 10.f;
        this->parent = parent;
        draw = [](gl_object* obj)->void {
            obj_reader* read = (obj_reader*)obj;



            for (gl_face face : read->faces) {
                glFace(face);
            }
        };

        this->load(path);

        parent->components.push_back(this);
    }
    obj_reader::~obj_reader() {
        vector<gl_object*>::iterator itr = parent->components.begin();
        if (*itr == this) {
            itr = parent->components.erase(itr);
        }
        else itr++;
    }

    void obj_reader::auto_magnify()
    {
        float sizeX = x_max - x_min, sizeY = y_max - y_min,sizeZ=z_max-z_min;
        float max_size = max(max(sizeX, sizeY), sizeZ);
        max_size = floor( 1280/max_size)/20;
        printf("%.2f\n", max_size);
        parent->camera->magnify = max_size;
    }

    bool obj_reader::load(string path)
    {
        this->path = path;
        vector<gl_vec_3f> temp_vertices, temp_normals;
        vector<gl_vec_2f> temp_uvs;
        vector<gl_face> temp_faces;
        ifstream file(path);
        if (!file.is_open())
        {
            parent->log("File Not found.");
            return false;
        }
        while (true)
        {
            string line;
            if (!getline(file, line))
                break;
            if (line.size() < 1)continue;
            vector<string>word = split(line, ' ');
            if (word[0] == "v") {
                gl_vec_3f vertex;
                vertex.x = (GLfloat)stof(word[1]);
                if (x_max < vertex.x)x_max = vertex.x;
                if (x_min > vertex.x)x_min = vertex.x;
                vertex.y = (GLfloat)stof(word[2]);
                if (y_max < vertex.y)y_max = vertex.y;
                if (y_min > vertex.y)y_min = vertex.y;
                vertex.z = (GLfloat)stof(word[3]);
                if (z_max < vertex.z)z_max = vertex.z;
                if (z_min > vertex.z)z_min = vertex.z;
                temp_vertices.push_back(vertex);
            }


            else if (word[0] == "vt") {
                gl_vec_2f uv;
                uv.x = (GLfloat)stof(word[1]);
                uv.y = (GLfloat)stof(word[2]);
                temp_uvs.push_back(uv);
            }


            else if (word[0] == "vn") {
                gl_vec_3f normal;
                normal.x = (GLfloat)stof(word[1]);
                normal.y = (GLfloat)stof(word[2]);
                normal.z = (GLfloat)stof(word[3]);
                temp_normals.push_back(normal);
            }


            else if (word[0] == "f") {
                gl_face face;
                face.amount = (int)word.size() - 1;
                vector<string> t_vertex;
                for (int i = 0; i < face.amount; i++) {
                    t_vertex = split(word[i + 1], '/');
                    if (t_vertex.size() >= 1)
                        face.vertices[i] = gl_vec_3f(temp_vertices[stoi(t_vertex[0]) - 1]);
                    if (t_vertex.size() >= 2)
                        face.uvs[i] = gl_vec_2f(temp_uvs[stoi(t_vertex[1]) - 1]);
                    if (t_vertex.size() >= 3)
                        face.normals[i] = gl_vec_3f(temp_normals[stoi(t_vertex[2]) - 1]);
                }
                temp_faces.push_back(face);
            }

        }
        vertices = temp_vertices;
        uvs = temp_uvs;
        normals = temp_normals;
        faces = temp_faces;
        auto_position();
        auto_magnify();
        parent->log("Load done.");
        return true;
    }
    void obj_reader::auto_position()
    {
        parent->camera->Position = -gl_vec_3f((x_max + x_min) / 2 * Scale.x, (y_max + y_min) / 2 * Scale.y, (z_max + z_min) / 2 * Scale.z);
    }


}
