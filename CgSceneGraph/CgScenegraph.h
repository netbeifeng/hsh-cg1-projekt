#ifndef CGSCENEGRAPH_H
#define CGSCENEGRAPH_H

#include "CgScenegraphEnity.h"
#include <glm/glm.hpp>
#include <stack>
#include <string>
#include "CgBase/CgBaseRenderer.h"

class CgScenegraph {

private:
    CgScenegraphEnity* m_root_node;

    std::stack<glm::mat4> m_modelview_matrix_stack;

    void pushMatrix() {m_modelview_matrix_stack.push(m_modelview_matrix_stack.top());}
    void popMatrix() {m_modelview_matrix_stack.pop();}
    void applyTransform(glm::mat4 arg) {m_modelview_matrix_stack.top()*=arg;}

public:
    CgScenegraph(CgScenegraphEnity* rootNode,glm::mat4 init_matrix);
    CgScenegraph(CgScenegraphEnity* rootNode,std::stack<glm::mat4> modelview_matrix_stack);
    ~CgScenegraph();
    CgBaseRenderableObject* findObject(CgBaseRenderableObject* o, std::vector<CgBaseRenderableObject*> list_of_all_objects);
    void render(CgBaseRenderer* renderer,glm::mat4 current_transformation,glm::vec4 m_color);
    void render(CgScenegraphEnity* enities,CgBaseRenderer *renderer,glm::mat4 current_transformation,glm::vec4 m_color);
    const std::vector<CgBaseRenderableObject*> getAllObjectsOfGraph();
    const CgScenegraphEnity* getRootNode() const;
    const std::stack<glm::mat4> &getModelviewMatrixStack() const;
};

#endif // CGSCENEGRAPH_H
