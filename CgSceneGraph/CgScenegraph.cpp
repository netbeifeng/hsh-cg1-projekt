#include "CgScenegraph.h"
#include "CgPolyline.h"
#include "CgCube.h"
#include <iostream>
#include <algorithm>

CgScenegraph::CgScenegraph(CgScenegraphEnity* rootNode,glm::mat4 init_matrix)
{
    m_root_node = rootNode;
    //glm::mat4 init_matrix = glm::mat4(1);
    m_modelview_matrix_stack.push(init_matrix);
}

CgScenegraph::CgScenegraph(CgScenegraphEnity* rootNode,std::stack<glm::mat4> modelview_matrix_stack):
m_root_node(rootNode),
m_modelview_matrix_stack(modelview_matrix_stack)
{

}


CgScenegraph::~CgScenegraph()
{
//    delete m_modelview_matrix_stack;
}

//void CgScenegraph::setMvMatrix(CgBaseRenderer *renderer) {
//    renderer->setUniformValue("modelviewMatrix",m_modelview_matrix_stack.top());
//}

void CgScenegraph::render(CgScenegraphEnity *enities,CgBaseRenderer *renderer,glm::mat4 current_transformation,glm::vec4 m_color) {
//    std::cout << "Render eingangen" << std::endl;
    if(enities->getChildren().size() >= 1) {
        pushMatrix();
        applyTransform(enities->getCurrentTransformation());
    }
    glm::mat4 mv_matrix = m_modelview_matrix_stack.top()*current_transformation;
//    renderer->setUniformValue("modelviewMatrix",mv_matrix);
    for(CgBaseRenderableObject* o : enities->getListOfObjects()) {
        if(o != NULL) {
//            std::cout << o << std::endl;
            renderer->setUniformValue("mycolor",m_color);
            renderer->setUniformValue("modelviewMatrix",mv_matrix*o->getTransformMatrix());
            renderer->init(o);
            renderer->render(o);
            for(CgBaseRenderableObject* po : o->getAxis()) {

                CgPolyline* pl = (CgPolyline*)po;
//                std::cout << pl->getColor().x << " " << pl->getColor().y << " " <<pl->getColor().z << std::endl;
                renderer->setUniformValue("mycolor",glm::vec4(pl->getColor(),1));
                renderer->render(pl);
            }
//            renderer->redraw();
        }
    }

//    std::cout << "Stage 2" << std::endl;

    if(enities->getChildren().size() >= 1) {
        for(CgScenegraphEnity* child_enity : enities->getChildren()) {
            render(child_enity,renderer,current_transformation,m_color);
        }
        popMatrix();
    }
//    std::cout << "Stage 3" << std::endl;
}

CgBaseRenderableObject* CgScenegraph::findObject(CgBaseRenderableObject* o, std::vector<CgBaseRenderableObject*> list_of_all_objects) {
    std::vector<CgBaseRenderableObject*>::iterator f_object = find(list_of_all_objects.begin(),list_of_all_objects.end(),o);
    if(f_object != list_of_all_objects.end()) {
        return *f_object;
    } else {
        return NULL;
    }
}

const std::vector<CgBaseRenderableObject*> CgScenegraph::getAllObjectsOfGraph() {
    std::stack<CgScenegraphEnity*> stack_of_enities;
    std::vector<CgBaseRenderableObject*> list_of_all_objects;
    stack_of_enities.push(m_root_node);
    while (!stack_of_enities.empty()) {
        CgScenegraphEnity* top = stack_of_enities.top();
        stack_of_enities.pop();
        for(CgBaseRenderableObject* o : top->getListOfObjects()) {
            if(findObject(o,list_of_all_objects)!=NULL) {
//                std::cout << "AAAA" << std::endl;
//                if(o->getType() == 4) {
//                    CgCube* co = (CgCube*)o;
//                    std::cout << co << std::endl;
//                    list_of_all_objects.push_back(co);
//                } else if(o->getType() == 2) {
//                    CgPolyline* po = (CgPolyline*)o;
//                    std::cout << po << std::endl;
//                    list_of_all_objects.push_back(po);
//                }
                std::cout << o << std::endl;
                CgBaseRenderableObject* no = (o);

                std::cout << no << std::endl;
                list_of_all_objects.push_back(no);
            } else {
                std::cout << o << std::endl;
                list_of_all_objects.push_back(o);
            }
        }
        std::vector<CgScenegraphEnity*> children = top->getChildren();
        if(children.size() > 0) {
            for(int i = children.size() - 1; i >= 0; i--) {
                stack_of_enities.push(children[i]);
            }
        }
    }
    return list_of_all_objects;
}

void CgScenegraph::render(CgBaseRenderer *renderer,glm::mat4 mv_matrix,glm::vec4 m_color) {
    render(m_root_node,renderer,mv_matrix,m_color);
}

const CgScenegraphEnity* CgScenegraph::getRootNode() const {
    return m_root_node;
}

const std::stack<glm::mat4> &CgScenegraph::getModelviewMatrixStack() const {
    return m_modelview_matrix_stack;
}
