#ifndef CGPOLYLINE_H
#define CGPOLYLINE_H

#include <vector>
#include <glm/glm.hpp>

#include "CgBase/CgBasePolyline.h"

class CgPolyline : public CgBasePolyline
{

public:
    CgPolyline();
    CgPolyline(glm::vec3 startPoint, glm::vec3 endPoint,int id);
    CgPolyline(glm::vec3 startPoint, glm::vec3 endPoint,glm::vec3 color,unsigned int lineWidth,int id);
    CgPolyline(std::vector<glm::vec3> pointList,glm::vec3 color,unsigned int lineWidth,int id);
    ~CgPolyline();

    Cg::ObjectType getType() const;
    unsigned int getID() const;

    //new
    void lane_Risenfeld_Algo(int mittel);

    //inherited from CgBasePolyline
    void setVertices(std::vector<glm::vec3> pointList);
    const std::vector<glm::vec3>& getVertices() const;
    glm::vec3 getColor() const;
    glm::vec3 getDirectionVector() const;
    unsigned int getLineWidth() const;

private:

    std::vector<glm::vec3> m_vertices;
    glm::vec3 m_color;
    unsigned int m_lineWidth;


    const Cg::ObjectType m_type;
    const unsigned int m_id;
};

inline Cg::ObjectType  CgPolyline::getType() const {return m_type;}
inline unsigned int CgPolyline::getID() const {return m_id;}

#endif // CGPOLYLINE_H
