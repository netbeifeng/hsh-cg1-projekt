#include "CgRotationMitVierObject.h"
#include "CgBase/CgEnums.h"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#define PI 3.1415
#include <glm/gtx/transform.hpp>
#include <cmath>
#include <algorithm>
#include <iterator>

CgRotationMitVierObject::CgRotationMitVierObject():
m_type(Cg::PolygonalMesh),
m_id(139)
{

}

CgRotationMitVierObject::CgRotationMitVierObject(unsigned int id):
m_type(Cg::PolygonalMesh),
m_id(id)
{

}

CgRotationMitVierObject::CgRotationMitVierObject(unsigned int id, CgPolyline* polyLine,unsigned int grad):
m_type(Cg::PolygonalMesh),
m_id(id),
m_grad(grad)
{
    float step = (2 * PI) / m_grad;
    std::vector<glm::vec3> polyLine_Vertices = polyLine->getVertices();
    bool sign = false;

    for(unsigned int i = 0; i < polyLine_Vertices.size(); i++) {
        float x = polyLine_Vertices[i].x;
        float y = polyLine_Vertices[i].y;
        float z = polyLine_Vertices[i].z;
        float angle = 0.0f;
        if(x==0&&z==0&&y!=0){
            sign = true;
            m_vertices.push_back(glm::vec3(x,y,z));
        } else {
            for(unsigned int j = 0; j < m_grad; j++) {
                float _x = z * sin(angle) + x * cos(angle);
                float _y = y;
                float _z = z * cos(angle) - x * sin(angle);
                m_vertices.push_back(glm::vec3(_x,_y,_z));
                angle += step;
            }
        }
    }

    if(sign){
        std::cout<<"Check!"<<std::endl;
        for(unsigned int h = 0; h < m_grad ; h++) {
            if(h == m_grad -1) {
                std::vector<unsigned int> header = {0,h+1,(h+2)-m_grad};
                std::cout << 0 << " " << h+1 << " " << (h+2)-m_grad << std::endl;
                m_polygon_indices.push_back(header);
            } else {
                std::vector<unsigned int> header = {0,h+1,(h+2)};
                std::cout << 0 << " " << h+1 << " " << (h+2) << std::endl;
                m_polygon_indices.push_back(header);
            }

        }
        for(unsigned int x = 0; x < (polyLine_Vertices.size()-3) * m_grad; x = x + m_grad) {
            for(unsigned int y = 0; y < m_grad; y++) {
                if(y == m_grad -1) {
                    std::vector<unsigned int> indices = {(x)+y+1,(x)+(y+1)-m_grad+1,(x)+(y+m_grad+1)-m_grad+1,(x)+(y+m_grad)+1};
                    std::cout << (x)+y+1 << " " << (x)+(y+1)-m_grad+1 << " " << (x)+(y+m_grad+1)-m_grad+1 << " " << (x)+(y+m_grad)+1 << std::endl;
                    m_polygon_indices.push_back(indices);
                } else {
                    std::vector<unsigned int> indices = {(x)+y+1,(x)+(y+1)+1,(x)+(y+m_grad+1)+1,(x)+(y+m_grad)+1};
                    std::cout << (x)+y+1 << " " << (x)+(y+1)+1 << " " << (x)+(y+m_grad+1)+1 << " " << (x)+(y+m_grad)+1 << std::endl;
                    m_polygon_indices.push_back(indices);
                }
            }
        }
        for(unsigned int f = 0; f < m_grad ; f++) {
            unsigned int top = m_vertices.size()-1;
            if(f == m_grad -1) {
                std::vector<unsigned int> footer = {top-m_grad+f,top-2*m_grad+1+f,top};
                std::cout << top-m_grad+f << " " << top-2*m_grad+1+f << " " << top << std::endl;
                m_polygon_indices.push_back(footer);
            } else {
                std::vector<unsigned int> footer = {top-m_grad+f,top-m_grad+1+f,top};
                std::cout << top-m_grad+f << " " << top-m_grad+1+f << " " << top << std::endl;
                m_polygon_indices.push_back(footer);
            }
        }

    } else {
        for(unsigned int x = 0; x < (polyLine_Vertices.size()-1) * m_grad; x = x + m_grad) {
            for(unsigned int y = 0; y < m_grad; y++) {
                if(y == m_grad -1) {
                    std::vector<unsigned int> indices = {(x)+y,(x)+(y+1)-m_grad,(x)+(y+m_grad+1)-m_grad,(x)+(y+m_grad)};
                    m_polygon_indices.push_back(indices);
                } else {
                    std::vector<unsigned int> indices = {(x)+y,(x)+(y+1),(x)+(y+m_grad+1),(x)+(y+m_grad)};
                    m_polygon_indices.push_back(indices);
                }
            }
        }
    }
}

CgRotationMitVierObject::~CgRotationMitVierObject()
{
    m_vertices.clear();
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_polygon_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();
}

const void CgRotationMitVierObject::printAll() const
{
    std::cout << "-----------------" << std::endl;
    for(int i = 0; i < m_polygon_indices.size(); i++) {
        for(int j = 0; j < m_polygon_indices[i].size(); j++) {
            std::cout << m_polygon_indices[i][j] << " ";
        }
        std::cout << "" << std::endl;
    }
}

const std::vector<glm::vec3>& CgRotationMitVierObject::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgRotationMitVierObject::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgRotationMitVierObject::getVertexColors() const
{
     return m_vertex_colors;
}

const std::vector<glm::vec2>& CgRotationMitVierObject:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<std::vector<unsigned int>> & CgRotationMitVierObject::getPolygonIndices() const
{
    return m_polygon_indices;
}

const std::vector<glm::vec3>& CgRotationMitVierObject::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgRotationMitVierObject::getFaceColors() const
{
    return m_face_colors;
}

