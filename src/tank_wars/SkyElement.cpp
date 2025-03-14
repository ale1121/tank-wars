#include "tank_wars/SkyElement.h"
#include "tank_wars/object2D.h"
#include "tank_wars/transform2D.h"
#include "tank_wars/Colors.h"

using namespace std;
using namespace m1;


// create a planet
SkyElement::SkyElement(float X, float Y, float radius, glm::vec3 color, int frames, bool dir)
{
	mesh = object2D::CreateDisk("planet", glm::vec3(0, 0, 0), radius, 2, 0.05, color);
	x = X;
	y = Y;
	modelMatrix = transform2D::Translate(x, y);

	numFrames = frames;
	direction = dir;
	frame = 0;
}

// create a star
SkyElement::SkyElement(float X, float Y, float radius)
{
	mesh = object2D::CreateDisk("star", glm::vec3(0, 0, 0), radius, 2, 0.2, Colors::White);
	x = X;
	y = Y;
	modelMatrix = transform2D::Translate(x, y);

	numFrames = 0;
	direction = false;
	frame = 0;
}


SkyElement::SkyElement()
{
}


SkyElement::~SkyElement()
{
}

// planet animation
void SkyElement::Update(float deltaTime)
{
	y = direction ? y + 2 * deltaTime : y - 2 * deltaTime;
	modelMatrix = transform2D::Translate(x, y);
	frame++;
	if (frame == numFrames) {
		frame = 0;
		direction = !direction;
	}
}
