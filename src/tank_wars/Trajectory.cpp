#include <math.h>
#include "tank_wars/Trajectory.h"
#include "tank_wars/transform2D.h"
#include "tank_wars/Colors.h"
#include "tank_wars/TankWars.h"


using namespace std;
using namespace m1;


Trajectory::Trajectory(const vector<float>& heightMap)
{
	terrainHeightMap = heightMap;
	mesh = new Mesh("trajectory");
	mesh->SetDrawMode(GL_LINE_STRIP);
	glLineWidth(3);

	vertices.resize(100, VertexFormat(glm::vec3(0), Colors::Gray));
	indices.resize(100);

	for (int i = 0; i < 100; i++) {
		indices[i] = i;
	}
}


Trajectory::Trajectory()
{
}


Trajectory::~Trajectory()
{
}


void Trajectory::Init(glm::vec3 barrelPos, float barrelRotation)
{
	barrelPosition = barrelPos;
	Update(barrelRotation);
}

// recalculates the trajectory
void Trajectory::Update(float barrelRotation)
{
	float x0 = barrelPosition.x;
	float y0 = barrelPosition.y;

	float t = -barrelRotation;

	vertices[0].position.x = x0;
	vertices[0].position.y = y0;

	for (int k = 1; k < vertices.size(); k++) {
		vertices[k].position.x = x0 + k * s * c * m * sin(t);
		vertices[k].position.y = y0 + s * c * (k * m * cos(t) - (k * (k - 1) / 2) * c * g);
	}

	mesh->InitFromData(vertices, indices);
}

// translates the trajectory to the new position
void Trajectory::UpdateTranslate(glm::vec3 newBarrelPosition)
{
	float deltaX = newBarrelPosition.x - barrelPosition.x;
	float deltaY = newBarrelPosition.y - barrelPosition.y;

	barrelPosition = newBarrelPosition;
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].position.x += deltaX;
		vertices[i].position.y += deltaY;
	}

	mesh->InitFromData(vertices, indices);
}
