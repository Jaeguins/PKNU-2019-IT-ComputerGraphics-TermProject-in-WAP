#pragma once
#include <Gl/glut.h>
namespace advanced_gl
{
    struct gl_vec_3f {
        GLfloat x, y, z;
        gl_vec_3f(GLfloat x, GLfloat y, GLfloat z);
        gl_vec_3f operator+(gl_vec_3f t) const;
        gl_vec_3f operator-(gl_vec_3f t) const;
        //ũ�⸦ 1�� ��źȭ
        gl_vec_3f normalize() const;
        gl_vec_3f operator-() const;
        gl_vec_3f operator*(GLfloat t) const;
        gl_vec_3f operator/(GLfloat t) const;
        gl_vec_3f();
        //(0,0,0)
        static gl_vec_3f zero;
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
        static gl_vec_2f zero;
    };
    //�鿡 ���� ����ü
    struct GlFace
    {
        //������ ��
        gl_vec_3f vertices[3];
        //uv ��ǥ
        gl_vec_2f uvs[3];
        //��������
        gl_vec_3f normals[3];
        GlFace();
    };

    //ȸ�� ����ü
    struct Quaternion {
        gl_vec_3f vect = gl_vec_3f(0, 1, 0);
        float angle = 0.0f;
    };
}
    //3���� ���� ����ü
    
