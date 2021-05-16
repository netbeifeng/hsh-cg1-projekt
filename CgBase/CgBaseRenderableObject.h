#ifndef CGBASERENDERABLEOBJECT
#define CGBASERENDERABLEOBJECT


#include "CgBase/CgEnums.h"
#include <glm/glm.hpp>


class CgBaseRenderableObject
{

    public:

    virtual ~CgBaseRenderableObject(){};


    virtual Cg::ObjectType getType() const  =0;
    virtual unsigned int getID() const  =0;
    void setTransformMatrix(glm::mat4 arg) {transform_matrix=arg;};
    glm::mat4 getTransformMatrix() {return transform_matrix;};
    void addAxe(CgBaseRenderableObject* o) {axis.push_back(o);};
    std::vector<CgBaseRenderableObject*> getAxis() {return axis;};
    void clearAxis() {axis.clear();};

protected:
    glm::mat4 transform_matrix = glm::mat4(1.);
    std::vector<CgBaseRenderableObject*> axis;
};




#endif // CGBASERENDERABLEOBJECT

