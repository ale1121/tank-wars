#include "tank_wars/Terrain.h"
#include "tank_wars/transform2D.h"
#include "tank_wars/object2D.h"
#include "tank_wars/Colors.h"


using namespace std;
using namespace m1;

#define GENERATE_TERRAIN(x) 20 * (3 + 0.5 * sin(x) + sin(0.4 * x) + 0.2 * sin(2.5 * x) + 0.3 * sin(0.3 * x))


Terrain::Terrain() 
{
	mesh = object2D::CreateSquare("terrain", glm::vec3(0, -1, 0), 1, Colors::Terrain, true);
}


Terrain::~Terrain()
{
}


void Terrain::Init(int windowWidth)
{
	width = windowWidth;
	heightMap.resize(width + 1);
	update.resize(width + 1, false);
	squares.resize(width);

	// randomize terrain
	srand(time(NULL));
	int random = rand() % 120;

	// initialise height map
	for (int i = 0; i < heightMap.size(); i++) {
		float x = float(i + random * 10) / 20;
		heightMap[i] = GENERATE_TERRAIN(x);
	}

	// initialise squares
	for (int i = 0; i < squares.size(); i++) {
		squares[i] = GenerateSquare(glm::vec2(i, heightMap[i]), glm::vec2(i + 1, heightMap[i + 1]));
	}
}


glm::mat3 Terrain::GenerateSquare(glm::vec2 A, glm::vec2 B)
{
	return transform2D::Translate(A.x, A.y)
		* transform2D::Shear(0, (B.y - A.y) / (B.x - A.x))
		* transform2D::Scale(B.x - A.x, max(B.y, A.y));
}


void Terrain::Update(float deltaTime, list<Projectile>& projectiles)
{
	CheckCollision(projectiles);
	Landslide(deltaTime);

	// update modified squares
	for (int i = 0; i < squares.size(); i++) {
		if (update[i] || update[i + 1]) {
			squares[i] = GenerateSquare(glm::vec2(i, heightMap[i]), glm::vec2(i + 1, heightMap[i + 1]));
			update[i] = false;
		}
	}
	update[squares.size()] = false;
}


void Terrain::CheckCollision(list<Projectile>& projectiles)
{
	for (auto& p = projectiles.begin(); p != projectiles.end();) {
		glm::vec2 P = glm::vec2(p->position.x, p->position.y);

		if (P.x < -5 || P.x > width + 5) {
			// projectile left the screen
			p = projectiles.erase(p);
			continue;
		}

		if (P.x < 0 || P.x > width) {
			p++;
			continue;
		}

		glm::vec2 A = glm::vec2(floor(P.x), heightMap[floor(P.x)]);
		glm::vec2 B = glm::vec2(A.x + 1, heightMap[A.x + 1]);

		float t = (P.x - A.x) / (B.x - A.x);
		float yProjection = A.y + t * (B.y - A.y);

		if (P.y - yProjection <= Projectile::Radius) {
			// projectile collides with terrain
			p = projectiles.erase(p);
			Deform(P);
			continue;
		}

		p++;
	}
}

// deform the terrain around point P
void Terrain::Deform(glm::vec2 P)
{
	for (int x = P.x - DeformRadius; x <= P.x + DeformRadius; x++) {
		if (x < 0 || x > width) {
			continue;
		}

		float d = sqrt(pow(DeformRadius, 2) - pow(P.x - float(x), 2));
		heightMap[x] = min(heightMap[x], P.y - d);

		if (heightMap[x] < 0) heightMap[x] = 0;

		update[x] = true;
	}
}


void Terrain::Landslide(float deltaTime)
{
	for (int x = 0; x < heightMap.size() - 1; x++) {
		float d = heightMap[x] - heightMap[x + 1];

		if (d > LsThreshold || -d > LsThreshold) {
			heightMap[x] -= d * deltaTime;
			heightMap[x + 1] += d * deltaTime;
			
			update[x] = true;
			update[x + 1] = true;
		}
	}
}
