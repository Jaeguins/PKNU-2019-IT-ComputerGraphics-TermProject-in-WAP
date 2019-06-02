#include "obj_reader.hpp"
#include <fstream>
#include "string_split.h"
#include "viewport.hpp"
#include "gl_Camera.hpp"


namespace model_viewer
{
    using namespace std;
    obj_reader::obj_reader(viewport* parent, const char* path) :gl_object::gl_object()
    {
        this->Scale = Scale / 10.f;
        this->parent = parent;
        draw = [](gl_object* obj)->void {
            obj_reader* read = (obj_reader*)obj;

            
            glBegin(GL_TRIANGLES);
            for (gl_face face : read->faces) {
                glFace(face);
            }
            glEnd();
        };

        this->load(path);

        parent->components.push_back(this);
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
                vertex.x = stoi(word[1]);
                if(x_max<vertex.x)x_max=vertex.x;
                if(x_min>vertex.x)x_min=vertex.x;
                vertex.y = stoi(word[2]);
                if(y_max<vertex.y)y_max=vertex.y;
                if(y_min>vertex.y)y_min=vertex.y;
                vertex.z = stoi(word[3]);
                if(z_max<vertex.z)z_max=vertex.z;
                if(z_min>vertex.z)z_min=vertex.z;
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
                    face.vertices[i] = gl_vec_3f(temp_vertices[stoi(t_vertex[0]) - 1]);
                    face.uvs[i] = gl_vec_2f(temp_uvs[stoi(t_vertex[1]) - 1]);
                    face.normals[i] = gl_vec_3f(temp_normals[stoi(t_vertex[2]) - 1]);
                }
                temp_faces.push_back(face);
            }
        }
        vertices = temp_vertices;
        uvs = temp_uvs;
        normals = temp_normals;
        faces = temp_faces;
        parent->camera->Position=-gl_vec_3f((x_max+x_min)/2*Scale.x,(y_max+y_min)/2*Scale.y,(z_max+z_min)/2*Scale.z);
        parent->log("Load done.");
        return true;
    }
}
