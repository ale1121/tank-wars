#include <math.h>
#include "tank_wars/Projectile.h"
#include "tank_wars/object2D.h"
#include "tank_wars/transform2D.h"
#include "tank_wars/Colors.h"

using namespace std;
using namespace m1;


Projectile::Projectile(int id, glm::vec2 startPosition, float angle)
{
	tankID = id;
	position = startPosition;
	velocity = glm::vec2(sin(angle), cos(angle)) * Magnitude;
	modelMatrix = glm::mat3(1);
	modelMatrix *= transform2D::Translate(position.x, position.y);
}


Projectile::Projectile()
{
}


Projectile::~Projectile()
{
}


void Projectile::Update(float deltaTime)
{
	position += velocity * (deltaTime * Speed);
	velocity.y -= Gravity * deltaTime;

	modelMatrix = transform2D::Translate(position.x, position.y);
}
