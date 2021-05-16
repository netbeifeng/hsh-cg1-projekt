#include "CgScenegraphEnity.h"
#include "CgAppearance.h"
#include <iostream>
#include <algorithm>
#include "CgMesh.h"
CgScenegraphEnity::CgScenegraphEnity(std::vector<CgBaseRenderableObject*> list_of_objects,glm::mat4 current_transformation,CgAppearance* appearance,CgScenegraphEnity* parent,std::vector<CgScenegraphEnity*> children):
m_list_of_objects(list_of_objects),
m_current_transformation(current_transformation),
m_apperarance(appearance),
m_parent(parent),
m_children(children)
{
//    CgMesh* cgm = new CgMesh(12);

//    std::cout << cgm << std::endl;
//    list_of_objects.push_back(cgm);
}

CgScenegraphEnity::~CgScenegraphEnity()
{

}

const std::vector<CgBaseRenderableObject*> &CgScenegraphEnity::getListOfObjects() const {
    return m_list_of_objects;
}

const glm::mat4 &CgScenegraphEnity::getCurrentTransformation() const {
    return m_current_transformation;
}

const CgAppearance* CgScenegraphEnity::getAppearance() const {
    return m_apperarance;
}

const CgScenegraphEnity* CgScenegraphEnity::getParent() const {
    return m_parent;
}

const std::vector<CgScenegraphEnity*> &CgScenegraphEnity::getChildren() const {
    return m_children;
}

void CgScenegraphEnity::setCurrentTransformation(glm::mat4 current_transformation) {
    m_current_transformation = current_transformation;
}

void CgScenegraphEnity::addChildEnity(CgScenegraphEnity* e) {
    m_children.push_back(e);
}

void CgScenegraphEnity::deleteChildEnity(CgScenegraphEnity* e) {
    std::vector<CgScenegraphEnity*>::iterator itr = m_children.begin();

        while(itr != m_children.end()) {
            if(*itr == e) {
                itr = m_children.erase(itr);
            } else {
                ++itr;
            }
        }

}

void CgScenegraphEnity::addObject(CgBaseRenderableObject* o) {
//    CgMesh* cgm = new CgMesh(12);
    std::cout << o << std::endl;
//    std::cout << cgm << std::endl;
    this->m_list_of_objects.push_back(o);
}

CgBaseRenderableObject* CgScenegraphEnity::findObject(CgBaseRenderableObject* o) {
    std::vector<CgBaseRenderableObject*>::iterator f_object = find(m_list_of_objects.begin(),m_list_of_objects.end(),o);
    if(f_object != m_list_of_objects.end()) {
        return *f_object;
    } else {
        return NULL;
    }
}

void CgScenegraphEnity::deleteObject(CgBaseRenderableObject* o) {
    CgBaseRenderableObject* f_object = findObject(o);

    std::vector<CgBaseRenderableObject*>::iterator itr = m_list_of_objects.begin();
    if(f_object != NULL) {
        while(itr != m_list_of_objects.end()) {
            if(*itr == f_object) {
                itr = m_list_of_objects.erase(itr);
            } else {
                ++itr;
            }
        }
    }
}
