#include "CgCube.h"
#include "CgBase/CgEnums.h"
#include <iostream>

CgCube::CgCube():
m_type(Cg::TriangleMesh),
m_id(42)
{
    m_vertices.push_back(glm::vec3(-0.5,0.0,0.0));
    m_vertices.push_back(glm::vec3(0.5,-0.5,0.0));
    m_vertices.push_back(glm::vec3(0.0,0.5,0.0));

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);

    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
}

CgCube::CgCube(int id):
m_type(Cg::TriangleMesh),
m_id(id)
{
    // vertices 0.0
    m_vertices.push_back(glm::vec3(-0.5,0.0,0.0));
    m_vertices.push_back(glm::vec3(0.0,-0.5,0.0));
    m_vertices.push_back(glm::vec3(0.0,0.5,0.0));
    m_vertices.push_back(glm::vec3(0.5,0.0,0.0));

    // vertices 0.5
    m_vertices.push_back(glm::vec3(-0.5,0.0,0.5));
    m_vertices.push_back(glm::vec3(0.0,-0.5,0.5));
    m_vertices.push_back(glm::vec3(0.0,0.5,0.5));
    m_vertices.push_back(glm::vec3(0.5,0.0,0.5));

    m_vertex_colors.push_back(glm::vec3(255,1,1));
    m_vertex_colors.push_back(glm::vec3(255,1,1));
    m_vertex_colors.push_back(glm::vec3(255,1,1));
    m_vertex_colors.push_back(glm::vec3(255,1,1));
    m_vertex_colors.push_back(glm::vec3(255,1,1));
    m_vertex_colors.push_back(glm::vec3(255,1,1));
    m_vertex_colors.push_back(glm::vec3(255,1,1));
    m_vertex_colors.push_back(glm::vec3(255,1,1));

    //face 0
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);
    //face 1
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(3);
    //face 2
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(2);
    //face 3
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(2);
    //face 4
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(4);
    //face 5
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(1);
    //face 6
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(7);
    //face 7
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(5);
    //face 8
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(7);
    //face 9
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(6);
    //face 10
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(7);
    //face 11
    m_triangle_indices.push_back(7);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(4);

    //      4 - - - - - 5
    //     /|          /|
    //    / |         / |
    //   /  |        /  |
    //  6 - |- - - -7   |
    //  |   0 - - - | - 1
    //  |  /        |  /
    //  | /         | /
    //  |/          |/
    //  2 - - - - - 3

    //      * - - - - - *
    //     /|        5 /|
    //    / |         /7|
    //   /  |  4     /  |
    //  * - |- - - -*   |
    //  |3 2* - - - | - *
    //  |  /  0     |  /
    //  | /         |6/
    //  |/       1  |/
    //  * - - - - - *
//    std::cout << m_triangle_indices.size() << std::endl;

    for (unsigned int i = 0; i < m_triangle_indices.size(); i = i + 3) {
        unsigned int vertex_1 = m_triangle_indices[i];
        unsigned int vertex_2 = m_triangle_indices[i + 1];
        unsigned int vertex_3 = m_triangle_indices[i + 2];

        //std::cout << vertex_1 << " : " << vertex_2 << " : " << vertex_3 << std::endl;

        glm::vec3 v1 = m_vertices[vertex_3] - m_vertices[vertex_1];
        glm::vec3 v2 = m_vertices[vertex_2] - m_vertices[vertex_1];
        glm::vec3 normal;
        normal.x = (v2.y * v1.z) - (v2.z * v1.y);
        normal.y = (v2.z * v1.x) - (v2.x * v1.z);
        normal.z = (v2.x * v1.y) - (v1.x * v2.y);
        if(normal.x == -0) {
            normal.x = 0;
        } else if(normal.y == -0) {
            normal.y = 0;
        } else if(normal.z == -0) {
            normal.z = 0;
        }
        m_face_normals.push_back(normal);
        //m_face_normals.push_back(glm::normalize(glm::cross(v1,v2)));
    }

    for (unsigned int i = 0; i < m_face_normals.size(); i++) {
        std::cout << "Face_" << i << " , X:" << m_face_normals[i].x << ", Y:" << m_face_normals[i].y << ", Z:" << m_face_normals[i].z << std::endl;
        m_face_colors.push_back(glm::vec3(1,1,1));
    }


}

CgCube::~CgCube()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

const std::vector<glm::vec3>& CgCube::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgCube::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgCube::getVertexColors() const
{
     return m_vertex_colors;
}

const std::vector<glm::vec2>& CgCube:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int>& CgCube::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3>& CgCube::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgCube::getFaceColors() const
{
    return m_face_colors;
}
