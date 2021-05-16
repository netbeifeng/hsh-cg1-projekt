#ifndef CGROTATIONMITVIEROBJECT_H
#define CGROTATIONMITVIEROBJECT_H
#include <vector>
#include <glm/glm.hpp>


#include "CgBase/CgBasePolygonMesh.h"
#include "CgSceneGraph/CgPolyline.h"

class CgRotationMitVierObject : public CgBasePolygonMesh
{

public:
    CgRotationMitVierObject();
    CgRotationMitVierObject(unsigned int id);
    CgRotationMitVierObject(unsigned int id, CgPolyline* polyLine,unsigned int grad);
    ~CgRotationMitVierObject();

    //inherited from CgBaseRenderableObject
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    //inherited from CgBaseTriangleMesh
    const std::vector<glm::vec3>& getVertices() const;
    const std::vector<glm::vec3>& getVertexNormals() const;
    const std::vector<glm::vec3>& getVertexColors() const;
    const std::vector<glm::vec2>& getVertexTexCoords() const;

    const std::vector<std::vector<unsigned int>>& getPolygonIndices() const;

    const std::vector<glm::vec3>& getFaceNormals() const;
    const std::vector<glm::vec3>& getFaceColors() const;

    //new
    unsigned int grad();
    const void printAll() const;

private:
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_vertex_normals;
    std::vector<glm::vec3> m_vertex_colors;
    std::vector<glm::vec2> m_tex_coords;

    std::vector<std::vector<unsigned int>>  m_polygon_indices;

    std::vector<glm::vec3> m_face_normals;
    std::vector<glm::vec3> m_face_colors;

    //new
    unsigned int m_grad;

    const Cg::ObjectType m_type;
    const unsigned int m_id;
};

inline Cg::ObjectType  CgRotationMitVierObject::getType() const {return m_type;}
inline unsigned int CgRotationMitVierObject::getID() const {return m_id;}

#endif // CGROTATIONMITVIEROBJECT_H
