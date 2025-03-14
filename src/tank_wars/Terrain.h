#pragma once

#include <vector>
#include "core/engine.h"
#include "core/gpu/mesh.h"
#include "utils/gl_utils.h"
#include "utils/glm_utils.h"
#include "utils/math_utils.h"
#include "tank_wars/Projectile.h"


namespace m1
{
    class Terrain
    {
    public:
        std::vector<glm::mat3> squares;
        std::vector <float> heightMap;
        Mesh* mesh;

        Terrain();
        ~Terrain();

        void Init(int windowWidth);
        void Update(float deltaTime, std::list<Projectile>& projectiles);

    private:
        static constexpr float DeformRadius = 15;
        static constexpr float LsThreshold = 0.1;
        int width;
        std::vector<bool> update;

        glm::mat3 GenerateSquare(glm::vec2 A, glm::vec2 B);
        void CheckCollision(std::list<Projectile>& projectiles);
        void Deform(glm::vec2 P);
        void Landslide(float deltaTime);
    };
}
