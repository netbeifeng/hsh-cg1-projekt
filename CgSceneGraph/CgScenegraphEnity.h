#ifndef CGSCENEGRAPHENITY_H
#define CGSCENEGRAPHENITY_H

#include <vector>
#include "CgBase/CgBaseRenderableObject.h"
#include <glm/glm.hpp>

#include "CgAppearance.h"

class CgScenegraphEnity {

private:
    std::vector<CgBaseRenderableObject*> m_list_of_objects;
    glm::mat4 m_current_transformation;

    CgAppearance* m_apperarance;

    CgScenegraphEnity* m_parent;
    std::vector<CgScenegraphEnity*> m_children;

public:
    CgScenegraphEnity(std::vector<CgBaseRenderableObject*> list_of_objects,glm::mat4 current_transformation,CgAppearance* appearance,CgScenegraphEnity* parent,std::vector<CgScenegraphEnity*> children);
    ~CgScenegraphEnity();

    const std::vector<CgBaseRenderableObject*> &getListOfObjects() const;
    const glm::mat4 &getCurrentTransformation() const;

    const CgAppearance* getAppearance() const;
    const CgScenegraphEnity* getParent() const;
    const std::vector<CgScenegraphEnity*> &getChildren() const;

    void setCurrentTransformation(glm::mat4 current_transformation);

    void addChildEnity(CgScenegraphEnity* e);
    void deleteChildEnity(CgScenegraphEnity* e);

    void addObject(CgBaseRenderableObject* o);
    CgBaseRenderableObject* findObject(CgBaseRenderableObject* o);
    void deleteObject(CgBaseRenderableObject* o);
};

#endif // CGSCENEGRAPHENITY_H
