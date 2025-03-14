#pragma once

#include "core/gpu/mesh.h"


namespace m1
{
    class Tank;

    class HealthBar
    {
    public:
        Mesh* outline;
        Mesh* fill;

        glm::mat3 fillModelMatrix;

        HealthBar();
        ~HealthBar();

        bool DecreaseHP();

    private:
        static constexpr int InitialHP = 10;
        int hp;
    };
}
