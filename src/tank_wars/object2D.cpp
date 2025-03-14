#include "tank_wars/object2D.h"
#include <vector>
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 corner,
    float length,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}


Mesh* object2D::CreateRectangle(
    const std::string &name,
    glm::vec3 corner,
    float length, float height,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}


Mesh* object2D::CreateTrapezoid(
    const std::string &name,
    glm::vec3 corner,
    float base1, float base2, float height,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(base1, 0, 0), color),
        VertexFormat(corner + glm::vec3((base1 - base2) / 2 + base2, height, 0), color),
        VertexFormat(corner + glm::vec3((base1 - base2) / 2, height, 0), color)
    };

    Mesh* trapezoid = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    indices.push_back(0);
    indices.push_back(2);

    trapezoid->InitFromData(vertices, indices);
    return trapezoid;
}


Mesh* object2D::CreateDisk(
    const std::string &name,
    glm::vec3 center,
    float radius, float radians, float angular_step,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices(radians / angular_step + 2, glm::vec3(0));
    std::vector<unsigned int> indices(vertices.size());

    vertices[0] = VertexFormat(center, color);
    indices[0] = 0;

    for (int i = 1; i < vertices.size(); i++) {
        vertices[i] = VertexFormat(
            center + radius * glm::vec3(cos((i - 1) * angular_step * M_PI), sin((i - 1) * angular_step * M_PI), 0), color);
        indices[i] = i;
    }

    Mesh* disk = new Mesh(name);
    disk->SetDrawMode(GL_TRIANGLE_FAN);
    disk->InitFromData(vertices, indices);
    return disk;
}
