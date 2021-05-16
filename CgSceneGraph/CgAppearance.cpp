#include "CgAppearance.h"

CgAppearance::CgAppearance(glm::vec3 color,glm::vec3 material):
object_color(color),
difuse_material(material)
{

}

CgAppearance::~CgAppearance()
{

}

const glm::vec3& CgAppearance::getObjectColor() const {
    return object_color;
}

const glm::vec3& CgAppearance::getDifuseMaterial() const {
    return difuse_material;
}

void CgAppearance::setObjectColor(glm::vec3 color) {
    object_color = color;
}

void CgAppearance::setDifuseMaterial(glm::vec3 material) {
    difuse_material = material;
}
