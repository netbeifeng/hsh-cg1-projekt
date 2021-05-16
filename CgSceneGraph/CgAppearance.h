#ifndef CGAPPEARANCE_H
#define CGAPPEARANCE_H

#include <vector>
#include <glm/glm.hpp>

class CgAppearance {

private:
    glm::vec3 object_color;
    glm::vec3 difuse_material;

public:
    CgAppearance(glm::vec3 color,glm::vec3 material);
    ~CgAppearance();

    const glm::vec3& getObjectColor() const;
    const glm::vec3& getDifuseMaterial() const;

    void setObjectColor(glm::vec3 color);
    void setDifuseMaterial(glm::vec3 material);

};

#endif // CGAPPEARANCE_H
