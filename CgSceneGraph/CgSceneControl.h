#ifndef CGSCENECONTROL_H
#define CGSCENECONTROL_H

#include "CgBase/CgObserver.h"
#include "CgBase/CgBaseSceneControl.h"
#include <glm/glm.hpp>
#include <vector>
#include "CgBase/CgBaseRenderableObject.h"

class CgBaseEvent;
class CgBaseRenderer;

class CgExampleTriangle;
class CgPolyline;
class CgCube;
class CgMesh;
class CgRotationObject;
class CgRotationMitVierObject;

class CgScenegraph;
class CgScenegraphEnity;


class CgSceneControl : public CgObserver, public CgBaseSceneControl
{
public:
    CgSceneControl();
    ~CgSceneControl();
    void handleEvent(CgBaseEvent* e);
    void setRenderer(CgBaseRenderer* r);

    void setColor(int r,int g,int b);

    void drawAxis(CgBaseRenderableObject* o);
    void clearAxis(CgBaseRenderableObject* o);
    void createNormaleOfCube();
    void renderObjects();
    void createCurve();
    void makeRisenfeldAlgo(int mittel);
    void resetCurve();
    void createSceneGraph();
private:

    CgBaseRenderer* m_renderer;

    CgExampleTriangle* m_triangle;
    CgPolyline* m_kurve;
    CgCube* m_cube;
    CgRotationObject* m_rotationObject;
    CgRotationMitVierObject* m_rotationMitVierObject;
    CgMesh* m_mesh;
    std::vector<CgPolyline*> m_polylines;

    CgScenegraph* m_scenegraph;
    CgScenegraphEnity* m_scenegraph_enity_root;

    unsigned int m_position_of_list_all_objects;
    std::vector<CgBaseRenderableObject*> m_list_of_all_objects;

    glm::mat4 m_current_transformation;
    glm::mat4 m_trackball_rotation;
    glm::mat4 m_lookAt_matrix;
    glm::mat4 m_proj_matrix;
    glm::mat4 mv_matrix;
    glm::vec4 m_color;

};

#endif // CGSCENECONTROL_H
