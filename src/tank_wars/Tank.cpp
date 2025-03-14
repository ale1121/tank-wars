#include <math.h>
#include "tank_wars/Tank.h"
#include "tank_wars/object2D.h"
#include "tank_wars/transform2D.h"
#include "tank_wars/Colors.h"
#include "tank_wars/TankWars.h"


using namespace std;
using namespace m1;


Tank::Tank(int tankID, vector<float> *heightMap)
{
	id = tankID;
	terrainHeightMap = heightMap;
	isAlive = true;
}


Tank::Tank()
{
}


Tank::~Tank()
{
}


void Tank::Init()
{
	glm::vec3 color;
	glm::vec3 colorDark;

	// choose tank color
	if (id == 0) {
		color = Colors::Yellow;
		colorDark = Colors::YellowDark;
		position.x = TankWars::LogicWidth / 6;
	}
	else {
		color = Colors::Blue;
		colorDark = Colors::BlueDark;
		position.x = TankWars::LogicWidth * 5 / 6;
	}

	// create tank meshes
	meshes.resize(4);
	meshes[0] = object2D::CreateTrapezoid("top", glm::vec3(-5, 1, 0), 10, 9, 2.5, color);
	meshes[1] = object2D::CreateTrapezoid("bottom", glm::vec3(-3.5, 0, 0), 7, 8, 1, colorDark);
	meshes[2] = object2D::CreateDisk("turret", glm::vec3(0, 3.5, 0), 2, 1, 0.1, color);
	meshes[3] = object2D::CreateRectangle("barrel", glm::vec3(-0.3, 0, 0), 0.6, 4.5, colorDark, true);

	barrelRotation = 0;
	UpdateModelMatrix();

	trajectory = Trajectory(*terrainHeightMap);
	trajectory.Init(barrelPosition, barrelRotation);

	newX = position.x;
	newY = position.y;
}

// returns false if the tank is not alive
bool Tank::Update(std::list<Projectile>& projectiles)
{
	if (!isAlive) return false;

	// check collision with projectiles, return false if hp reaches 0
	if (CheckCollision(projectiles)) return false;

	// calculate new tank position
	glm::vec2 A = glm::vec2(floor(newX), (*terrainHeightMap)[floor(newX)]);
	glm::vec2 B = glm::vec2(A.x + 1, (*terrainHeightMap)[A.x + 1]);

	float t = (newX - A.x) / (B.x - A.x);
	newY = A.y + t * (B.y - A.y);

	// if position hasn't changed, return
	if (position.x == newX && position.y == newY) return true;

	// update position
	position.x = newX;
	position.y = newY;

	// update rotation
	glm::vec2 V = B - A;
	tankRotation = atan2(V.y, V.x);

	UpdateModelMatrix();
	trajectory.UpdateTranslate(barrelPosition);

	return true;
}


void Tank::UpdateModelMatrix()
{
	tankModelMatrix = transform2D::Translate(position.x, position.y)
		* transform2D::Scale(1.5, 1.5)
		* transform2D::Rotate(tankRotation);

	barrelModelMatrix = tankModelMatrix
		* transform2D::Translate(0, 4.5)
		* transform2D::Rotate(barrelRotation - tankRotation);

	barrelPosition = barrelModelMatrix * glm::vec3(0, 0, 1);

	hbModelMatrix = transform2D::Translate(position.x, position.y)
		* transform2D::Scale(1.5, 1.5);
}

// calculate new x
void Tank::Move(float distance)
{
	// adjust speed based on slope (tank rotation)
	if (distance < 0) {
		newX = position.x + distance * Speed * (tankRotation + 2);
	}
	else {
		newX = position.x + distance * Speed * (2 - tankRotation);
	}

	// if new x goes out of bounds, revert to old position
	if (newX < 0 || newX > TankWars::LogicWidth) {
		newX = position.x;
		return;
	}
}


void Tank::MoveBarrel(float angle)
{
	barrelRotation += angle;

	barrelModelMatrix = tankModelMatrix
		* transform2D::Translate(0, 4.5)
		* transform2D::Rotate(barrelRotation - tankRotation);

	trajectory.Update(barrelRotation);
}

// returns a new projectile
Projectile Tank::Shoot()
{
	return Projectile(id, glm::vec2(barrelPosition.x, barrelPosition.y), -barrelRotation);
}

// returns true if hp reaches 0
bool Tank::CheckCollision(list<Projectile> &projectiles)
{
	for (auto& p = projectiles.begin(); p != projectiles.end();) {
		if (p->tankID != id && glm::distance(position, p->position) <= 8.5) {
			// projectile is inside the tank's hitbox

			if (healthBar.DecreaseHP()) {
				// hp reached 0
				isAlive = false;
				p = projectiles.erase(p);
				return true;
			}

			p = projectiles.erase(p);
			continue;
		}
		p++;
	}

	return false;
}

Mesh* Tank::GetTrajectoryMesh()
{
	return trajectory.mesh;
}