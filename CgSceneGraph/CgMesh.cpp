#include "CgMesh.h"
#include "CgBase/CgEnums.h"
#include "CgUtils/ObjLoader.h"
#include <iostream>

CgMesh::CgMesh():
m_type(Cg::TriangleMesh),
m_id(42)
{
//    m_vertices.push_back(glm::vec3(-0.5,0.0,0.0));
//    m_vertices.push_back(glm::vec3(0.5,-0.5,0.0));
//    m_vertices.push_back(glm::vec3(0.0,0.5,0.0));

//    m_triangle_indices.push_back(0);
//    m_triangle_indices.push_back(1);
//    m_triangle_indices.push_back(2);

//    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
//    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
//    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));

}

CgMesh::CgMesh(int id):
m_type(Cg::TriangleMesh),
m_id(id)
{

//    m_vertices.push_back(glm::vec3(-0.5,0.0,0.0));
//    m_vertices.push_back(glm::vec3(0.0,-0.5,0.0));
//    m_vertices.push_back(glm::vec3(0.0,0.5,0.0));
//    m_vertices.push_back(glm::vec3(0.5,0.0,0.0));

//    m_triangle_indices.push_back(0);
//    m_triangle_indices.push_back(1);
//    m_triangle_indices.push_back(2);
//    m_triangle_indices.push_back(2);
//    m_triangle_indices.push_back(1);
//    m_triangle_indices.push_back(3);

//    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
//    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
//    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
//    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));

}



CgMesh::~CgMesh()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

void CgMesh::init( std::vector<glm::vec3> arg_verts,  std::vector<glm::vec3> arg_normals, std::vector<unsigned int> arg_triangle_indices)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();
    m_vertices=arg_verts;
    m_vertex_normals=arg_normals;
    m_triangle_indices=arg_triangle_indices;
}

void CgMesh::init(std::string filename)
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_triangle_indices.clear();

    ObjLoader loader;
    loader.load(filename);

    loader.getPositionData(m_vertices);
    loader.getNormalData(m_vertex_normals);
    loader.getFaceIndexData(m_triangle_indices);
    std::cout << m_vertex_normals.size() << std::endl;


}

void CgMesh::calcFaceNormal()
{
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
}

void CgMesh::calcVertexNormal()
{
    std::vector<glm::vec3> temp_vertex_normals(m_vertices.size());
    std::vector<unsigned int> temp_size(m_vertices.size());
//    for (unsigned int i = 0; i < m_triangle_indices.size(); i = i + 3) {
//        unsigned int vertex_1 = m_triangle_indices[i];
//        unsigned int vertex_2 = m_triangle_indices[i + 1];
//        unsigned int vertex_3 = m_triangle_indices[i + 2];

//        std::cout << vertex_1 << " " << vertex_2 << " " << vertex_3 << std::endl;
//    }
    for (unsigned int i = 0; i < m_triangle_indices.size(); i = i + 3) {
        unsigned int vertex_1 = m_triangle_indices[i];
        unsigned int vertex_2 = m_triangle_indices[i + 1];
        unsigned int vertex_3 = m_triangle_indices[i + 2];

        float x = m_face_normals[i/3].x;
        float y = m_face_normals[i/3].y;
        float z = m_face_normals[i/3].z;

        temp_vertex_normals[vertex_1].x += x;
        temp_vertex_normals[vertex_1].y += y;
        temp_vertex_normals[vertex_1].z += z;
        temp_size[vertex_1]++;

        temp_vertex_normals[vertex_2].x += x;
        temp_vertex_normals[vertex_2].y += y;
        temp_vertex_normals[vertex_2].z += z;
        temp_size[vertex_2]++;

        temp_vertex_normals[vertex_3].x += x;
        temp_vertex_normals[vertex_3].y += y;
        temp_vertex_normals[vertex_3].z += z;
        temp_size[vertex_3]++;
    }
    m_vertex_normals.resize(temp_vertex_normals.size());
    for(int i = 0; i < temp_vertex_normals.size(); i++) {
        float x = temp_vertex_normals[i].x / temp_size[i];
        float y = temp_vertex_normals[i].y / temp_size[i];
        float z = temp_vertex_normals[i].z / temp_size[i];
        m_vertex_normals[i] = glm::vec3(x,y,z);
    }
}

const std::vector<glm::vec3>& CgMesh::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgMesh::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgMesh::getVertexColors() const
{
     return m_vertex_colors;
}

const std::vector<glm::vec2>& CgMesh:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int>& CgMesh::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3>& CgMesh::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgMesh::getFaceColors() const
{
    return m_face_colors;
}
