#include "tank_wars/HealthBar.h"
#include "tank_wars/object2D.h"
#include "tank_wars/transform2D.h"
#include "tank_wars/Colors.h"

using namespace std;
using namespace m1;


HealthBar::HealthBar()
{
	hp = InitialHP;
	outline = object2D::CreateRectangle("outline", glm::vec3(-4.5, 10, 0), 9, 2.5, Colors::White, false);
	fill = object2D::CreateRectangle("fill", glm::vec3(-4.5, 10, 0), 9, 2.5, Colors::White, true);
	fillModelMatrix = glm::mat3(1);
}


HealthBar::~HealthBar()
{
}


bool HealthBar::DecreaseHP()
{
	hp--;

	// update fill rectangle
	fillModelMatrix = transform2D::Translate(-4.5, 0)
		* transform2D::Scale(float(hp) / 10, 1)
		* transform2D::Translate(4.5, 0);

	// return true if hp reaches 0
	return hp <= 0;
}
