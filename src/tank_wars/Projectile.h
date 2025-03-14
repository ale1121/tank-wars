#pragma once

#include <vector>
#include "core/engine.h"
#include "utils/gl_utils.h"
#include "utils/glm_utils.h"


namespace m1
{
    class Tank;

    class Projectile
    {
    public:
        static constexpr float Magnitude = 15;
        static constexpr float Gravity = 20;
        static constexpr float Speed = 10;
        static constexpr float Radius = 1;

        int tankID;
        glm::vec2 position;
        glm::mat3 modelMatrix;

        Projectile(int id, glm::vec2 startPosition, float angle);
        Projectile();
        ~Projectile();

        void Update(float deltaTime);

    private:
        glm::vec2 velocity;
    };
}
