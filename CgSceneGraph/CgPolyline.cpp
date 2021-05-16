#include "CgPolyline.h"
#include "CgBase/CgEnums.h"
#include <iostream>

CgPolyline::CgPolyline():
m_type(Cg::Polyline),
m_id(69)
{

}

CgPolyline::CgPolyline(glm::vec3 startPoint, glm::vec3 endPoint,int id):
m_type(Cg::Polyline),
m_id(id)
{

}

CgPolyline::CgPolyline(glm::vec3 startPoint, glm::vec3 endPoint,glm::vec3 color,unsigned int lineWidth,int id):
m_type(Cg::Polyline),
m_id(id),
m_lineWidth(lineWidth),
m_color(color)
{
    m_vertices.push_back(startPoint);
    m_vertices.push_back(endPoint);
}

CgPolyline::CgPolyline(std::vector<glm::vec3> pointList,glm::vec3 color,unsigned int lineWidth,int id):
m_type(Cg::Polyline),
m_id(id),
m_lineWidth(lineWidth),
m_color(color)
{
    m_vertices = pointList;
}


CgPolyline::~CgPolyline()
{
    m_vertices.clear();
//    m_color = glm::vec3(1,1,1);
//    m_lineWidth = 0;
}

const std::vector<glm::vec3>& CgPolyline::getVertices() const
{
    return m_vertices;
}

glm::vec3 CgPolyline::getColor() const
{
    return m_color;
}

unsigned int CgPolyline::getLineWidth() const
{
    return m_lineWidth;
}

glm::vec3 CgPolyline::getDirectionVector() const
{
    return m_vertices[1] - m_vertices[0];
}

void CgPolyline::setVertices(std::vector<glm::vec3> pointList) {
    m_vertices = pointList;
}

void CgPolyline::lane_Risenfeld_Algo(int mittel)
{
    m_vertices.resize(m_vertices.size()*2);
    if(mittel == 0) {
        return;
    } else if(mittel > m_vertices.size()-1) {
        //Fehler behandeln
        return;
    }

    for (int i = m_vertices.size() - 1;i >= 0; i=i-2) {
        m_vertices[i] = m_vertices[i/2];
        m_vertices[i-1] = m_vertices[i/2];
    }
    while (mittel>0) {
        std::cout << m_vertices.size() << std::endl;
        for (int i = 0; i < m_vertices.size(); i++) {
            float x = (m_vertices[i].x + m_vertices[i+1].x)/2;
            float y = (m_vertices[i].y + m_vertices[i+1].y)/2;
            float z = (m_vertices[i].z + m_vertices[i+1].z)/2;
            m_vertices[i] = glm::vec3(x,y,z);
        }
//                for (int i = 0; i < m_vertices.size(); i=i+2) {
//                    float qx = (0.75 * m_vertices[i].x + 0.25 * m_vertices[i+1].x);
//                    float qy = (0.75 * m_vertices[i].y + 0.25 * m_vertices[i+1].y);
//                    float qz = (0.75 * m_vertices[i].z + 0.25 * m_vertices[i+1].z);
//                    float rx = (0.25 * m_vertices[i].x + 0.75 * m_vertices[i+1].x);
//                    float ry = (0.25 * m_vertices[i].y + 0.75 * m_vertices[i+1].y);
//                    float rz = (0.25 * m_vertices[i].z + 0.75 * m_vertices[i+1].z);
//                    m_vertices[i] = glm::vec3(qx,qy,qz);
//                    m_vertices[i+1] = glm::vec3(rx,ry,rz);
//                }
        mittel--;
        m_vertices.pop_back();
//        std::cout << m_vertices.size() << std::endl;
//        for (int i = 0; i < m_vertices.size(); i++) {
//            std::cout << m_vertices[i].x << "," << m_vertices[i].y << "," << m_vertices[i].z << std::endl;
//        }
    }

}
