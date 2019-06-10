#pragma once
#include <GL/glut.h>

namespace advanced_gl
{
    //3���� ���� ����ü
    struct gl_vec_3f {
        GLfloat x, y, z;
        gl_vec_3f(GLfloat x, GLfloat y, GLfloat z);
        gl_vec_3f operator+(gl_vec_3f t) const;
        gl_vec_3f operator-(gl_vec_3f t) const;
        //ũ�⸦ 1�� ��źȭ
        gl_vec_3f normalize() const;
        //ũ�� ��ȯ
        float magnitude() const;
        gl_vec_3f operator-() const;
        gl_vec_3f operator*(GLfloat t) const;
        gl_vec_3f operator/(GLfloat t) const;
        gl_vec_3f operator%(gl_vec_3f t);
        gl_vec_3f();
        //(0,0,0)
        
    };
    
    //2���� ���� ����ü
    struct gl_vec_2f {
        GLfloat x, y;
        gl_vec_2f(GLfloat x, GLfloat y);
        gl_vec_2f operator+(gl_vec_2f t) const;
        gl_vec_2f operator-(gl_vec_2f t) const;
        //ũ�⸦ 1�� ��źȭ
        gl_vec_2f normalize() const;
        gl_vec_2f operator-() const;
        gl_vec_2f operator*(GLfloat t) const;
        gl_vec_2f operator/(GLfloat t) const;
        
        gl_vec_2f();
        //(0,0)
        
    };
    
    //�鿡 ���� ����ü
    struct gl_face
    {
        int amount;
        //������ ��
        gl_vec_3f vertices[5];
        //uv ��ǥ
        gl_vec_2f uvs[5];
        //��������
        gl_vec_3f normals[5];
    };
    
    void glVertexVector(gl_vec_3f);
    void glVertexVector(gl_vec_2f);
    void glFace(gl_face,GLuint);
    //ȸ�� ����ü
    struct Quaternion {
        gl_vec_3f vect = gl_vec_3f(0, 1, 0);
        float angle = 0.0f;
    };
    extern gl_vec_3f zero3f;
    extern gl_vec_2f zero2f;
}
