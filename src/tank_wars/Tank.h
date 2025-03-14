#pragma once

#include <vector>
#include "core/engine.h"
#include "utils/gl_utils.h"
#include "utils/glm_utils.h"
#include "utils/math_utils.h"
#include "core/gpu/mesh.h"
#include "tank_wars/Projectile.h"
#include "tank_wars/Trajectory.h"
#include "tank_wars/HealthBar.h"


namespace m1
{
    class Tank
    {
    public:
        std::vector<Mesh*> meshes;
        glm::vec2 position;
        glm::mat3 tankModelMatrix;
        glm::mat3 barrelModelMatrix;
        glm::mat3 hbModelMatrix;
        bool isAlive;
        HealthBar healthBar;

        Tank(int tankID, std::vector<float> *heightMap);
        Tank();
        ~Tank();

        void Init();
        void Move(float distance);
        void MoveBarrel(float angle);
        bool Update(std::list<Projectile> &projectiles);
        Projectile Shoot();
        Mesh* GetTrajectoryMesh();

    private:
        static constexpr float Speed = 20;
        int id;
        float tankRotation;
        float barrelRotation;
        glm::vec3 barrelPosition;
        Trajectory trajectory;
        std::vector<float>* terrainHeightMap;

        float newX, newY;

        bool CheckCollision(std::list<Projectile>& projectiles);
        void UpdateModelMatrix();
    };
}
