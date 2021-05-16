#ifndef CGROTATIONOBJECT_H
#define CGROTATIONOBJECT_H

#include <vector>
#include <glm/glm.hpp>


#include "CgBase/CgBaseTriangleMesh.h"
#include "CgSceneGraph/CgPolyline.h"

class CgRotationObject : public CgBaseTriangleMesh
{

public:
    CgRotationObject();
    CgRotationObject(int id);
    CgRotationObject(int id, CgPolyline* polyLine,unsigned int grad);
    ~CgRotationObject();

    //inherited from CgBaseRenderableObject
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    //inherited from CgBaseTriangleMesh
    const std::vector<glm::vec3>& getVertices() const;
    const std::vector<glm::vec3>& getVertexNormals() const;
    const std::vector<glm::vec3>& getVertexColors() const;
    const std::vector<glm::vec2>& getVertexTexCoords() const;

    const std::vector<unsigned int>& getTriangleIndices() const;

    const std::vector<glm::vec3>& getFaceNormals() const;
    const std::vector<glm::vec3>& getFaceColors() const;

    //new
    unsigned int grad();


private:
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_vertex_normals;
    std::vector<glm::vec3> m_vertex_colors;
    std::vector<glm::vec2> m_tex_coords;

    std::vector<unsigned int>  m_triangle_indices;

    std::vector<glm::vec3> m_face_normals;
    std::vector<glm::vec3> m_face_colors;

    //new
    unsigned int m_grad;

    const Cg::ObjectType m_type;
    const unsigned int m_id;
};

inline Cg::ObjectType  CgRotationObject::getType() const {return m_type;}
inline unsigned int CgRotationObject::getID() const {return m_id;}

#endif // CGROTATIONOBJECT_H
