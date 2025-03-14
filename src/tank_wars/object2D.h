#pragma once

#include <string>
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    Mesh* CreateSquare(const std::string &name, glm::vec3 corner, float length, glm::vec3 color, bool fill);
    Mesh* CreateRectangle(const std::string &name, glm::vec3 corner, float length, float height, glm::vec3 color, bool fill);
    Mesh* CreateTrapezoid(const std::string &name, glm::vec3 corner, float base1, float base2, float height, glm::vec3 color);
    Mesh* CreateDisk(const std::string &name, glm::vec3 center, float radius, float radians, float angular_step, glm::vec3 color);
}
