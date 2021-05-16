#include "CgRotationObject.h"
#include "CgBase/CgEnums.h"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#define PI 3.1415
#include <glm/gtx/transform.hpp>
#include <cmath>
CgRotationObject::CgRotationObject():
m_type(Cg::TriangleMesh),
m_id(133)
{

}

CgRotationObject::CgRotationObject(int id):
m_type(Cg::TriangleMesh),
m_id(id)
{

}

CgRotationObject::CgRotationObject(int id, CgPolyline* polyLine,unsigned int grad):
m_type(Cg::TriangleMesh),
m_id(id),
m_grad(grad)
{
    float step = (2 * PI) / m_grad;
    std::vector<glm::vec3> polyLine_Vertices = polyLine->getVertices();
//    std::cout << "polyLine_Vertices:" << polyLine_Vertices.size() << std::endl;
//    std::cout << "size: " << polyLine_Vertices.size() << std::endl;
//    int ss = 1;
//    int vertexIndex = 0;
//    int faceIndex = 0;
    for(int i = 0; i < polyLine_Vertices.size(); i++) {
        float x = polyLine_Vertices[i].x;
        float y = polyLine_Vertices[i].y;
        float z = polyLine_Vertices[i].z;
        float angle = 0.0f;
        for(int j = 0; j < m_grad; j++) {

            float _x = z * sin(angle) + x * cos(angle);
            float _y = y;
            float _z = z * cos(angle) - x * sin(angle);
            m_vertices.push_back(glm::vec3(_x,_y,_z));
            m_triangle_indices.push_back(m_grad * i + j);
            std::cout << "angle=" << angle << "i=" << i << " j=" << j <<std::endl;
            angle += step;
            if ( i == polyLine_Vertices.size() -1 ) {
                if ( j == m_grad -1 ) {
                    m_triangle_indices.push_back(m_grad * (i - 1) + j + 1);
                    m_triangle_indices.push_back(m_grad * (i - 1) + j);
                    std::cout << m_grad * i + j << "/" << m_grad * i + j + 1 << "/" << m_grad * (i - 1) + j << std::endl;
                } else {
                    m_triangle_indices.push_back(m_grad * i + j + 1);
                    m_triangle_indices.push_back(m_grad * (i - 1) + j);
                    std::cout << m_grad * i + j << "/" << m_grad * (i - 1) + j + 1 << "/" << m_grad * (i - 1) + j << std::endl;
                }
            } else {
                if ( j == m_grad -1 ) {
                    m_triangle_indices.push_back(m_grad * (i - 1) + j + 1);
                    m_triangle_indices.push_back(m_grad * i + j + 1);
                    std::cout << m_grad * i + j << "/" << m_grad * (i - 1) + j + 1 << "/" << m_grad * i + j + 1 << std::endl;
                } else {
                    m_triangle_indices.push_back(m_grad * i + j +1);
                    m_triangle_indices.push_back(m_grad * (i + 1) + j +1);
                    std::cout << m_grad * i + j << "/" << m_grad * i + j +1 << "/" << m_grad * (i + 1) + j +1 << std::endl;
                }
            }



//                if(m_triangle_indices.size() < m_grad * 20) {
//                    for(int i = 0; i < m_grad; i++) {
//                        m_triangle_indices.push_back(i+m_grad*index+vertexIndex);
//                        m_triangle_indices.push_back(i+m_grad*(index+1)+vertexIndex);
//                        if(i == m_grad -1) {
//                            m_triangle_indices.push_back(m_grad*index+vertexIndex);
//                            std::cout << i+m_grad*index << " " << i+m_grad*(index+1) << " " << i+m_grad*index << std::endl;
//                        } else {
//                            m_triangle_indices.push_back(i+(m_grad*(index+1)+1)+vertexIndex);
//                            std::cout << i+m_grad*index << " " << i+m_grad*(index+1) << " " << i+(m_grad*(index+1)+1) << std::endl;
//                        }

//                        m_triangle_indices.push_back(i+m_grad*index+vertexIndex);
//                        m_triangle_indices.push_back(i+m_grad*index+1+vertexIndex);
//                        if(i == m_grad - 1) {
//                            m_triangle_indices.push_back(i+m_grad*index+vertexIndex);
//                            std::cout << i+m_grad*index << " " << i+m_grad*index+1 << " " << i+m_grad*index << std::endl;
//                        } else {
//                            m_triangle_indices.push_back(i+(m_grad*(index+1)+1)+vertexIndex);
//                            std::cout << i+m_grad*index << " " << i+m_grad*index+1 << " " << i+(m_grad*(index+1)+1) << std::endl;
//                        }
//                    }
//                    index++;
//                }

                //std::cout << "_x:" << _x << " ,_y:" << _y << " ,_z:" << _z << std::endl;
//            }
        }

//                 ss++;
    }
//    m_triangle_indices = {
//      0,1,5,
//      1,2,6,
//      2,3,7,
//      3,0,4,

//      4,5,9,
//      5,6,10,
//      6,7,11,
//      7,4,8,

//      8,9,4,
//      10,9,5,
//      11,10,6,
//      11,8,7
//    };

//    m_triangle_indices = {
//        0,1,4,
//                          0,3,4,
//                          0,1,2,
//                          0,3,2,
//                          1,1+m_grad,1+(m_grad+1),
//                          2,2+m_grad,2+(m_grad+1),
//                          3,3+m_grad,3+(m_grad+1),
//                          4,4+m_grad,4*0+(m_grad+1),
//                          1+m_grad,1+2*m_grad,1+(2*m_grad+1),
//                          2+m_grad,2+2*m_grad,2+(2*m_grad+1),
//                          3+m_grad,3+2*m_grad,3+(2*m_grad+1),
//                          4+m_grad,4+2*m_grad,4*1+(m_grad+1)
//                         };

//        m_triangle_indices = {
//            0,1,2,

//            0,1,4,
////            0,3,4,
//            0,2,5,
//            0,3,5,
//            1,2,5,

//            3,4,5,

//            3,4,7,
//            3,5,8,
//            3,6,8,
//            4,5,8,

//            6,7,8};


//    m_triangle_indices.push_back(0);
//    m_triangle_indices.push_back(1);
//    m_triangle_indices.push_back(4);
//    m_triangle_indices.push_back(0);
//    m_triangle_indices.push_back(3);
//    m_triangle_indices.push_back(4);
//    m_triangle_indices.push_back(0);
//    m_triangle_indices.push_back(1);
//    m_triangle_indices.push_back(2);
//    m_triangle_indices.push_back(0);
//    m_triangle_indices.push_back(3);
//    m_triangle_indices.push_back(2);

//    m_triangle_indices.push_back(1);
//    m_triangle_indices.push_back(5);
//    m_triangle_indices.push_back(6);

//    m_triangle_indices.push_back(3);
//    m_triangle_indices.push_back(7);
//    m_triangle_indices.push_back(8);

//    m_triangle_indices.push_back(4);
//    m_triangle_indices.push_back(5);
//    m_triangle_indices.push_back(8);

//    m_triangle_indices.push_back(2);
//    m_triangle_indices.push_back(6);
//    m_triangle_indices.push_back(7);




//    for(glm::vec3 v : m_vertices) {
//        v = transform * glm::vec4(v,1.0f);
//        std::cout << "x:" << v.x << " ,y:" << v.y << " ,z:" << v.z << std::endl;
//    }

//    for(glm::vec3 v : m_vertices) {
//        std::cout << "x:" << v.x << " ,y:" << v.y << " ,z:" << v.z << std::endl;
//    }
}

CgRotationObject::~CgRotationObject()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}


const std::vector<glm::vec3>& CgRotationObject::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgRotationObject::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgRotationObject::getVertexColors() const
{
     return m_vertex_colors;
}

const std::vector<glm::vec2>& CgRotationObject:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int>& CgRotationObject::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3>& CgRotationObject::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgRotationObject::getFaceColors() const
{
    return m_face_colors;
}

