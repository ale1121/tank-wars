#include <vector>
#include <iostream>
#include "tank_wars/transform2D.h"
#include "tank_wars/object2D.h"
#include "tank_wars/Visualizer.h"

using namespace std;
using namespace m1;


Visualizer::Visualizer()
{
}


Visualizer::~Visualizer()
{
}


void Visualizer::Init(glm::vec2 resolution, int width, int height)
{
    logicSpace = LogicSpace(0, 0, width, height);
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    matrix = VisualizationTransf2D(logicSpace, viewSpace);
}


glm::mat3 Visualizer::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}
