#pragma once

#include <vector>
#include "core/engine.h"
#include "utils/gl_utils.h"
#include "utils/glm_utils.h"
#include "utils/math_utils.h"
#include "core/gpu/mesh.h"
#include "tank_wars/Projectile.h"


namespace m1
{
    class Trajectory
    {
    public:
        Trajectory(const std::vector<float> &heightMap);
        Trajectory();
        ~Trajectory();

        void Init(glm::vec3 barrelPos, float barrelRotation);
        void UpdateTranslate(glm::vec3 newBarrelPosition);
        void Update(float barrelRotation);
        
        Mesh* mesh;

    private:
        std::vector<float> terrainHeightMap;

        static constexpr float m = Projectile::Magnitude;
        static constexpr float g = Projectile::Gravity;
        static constexpr float s = Projectile::Speed;
        static constexpr float c = 0.1;

        glm::vec3 barrelPosition;
        std::vector<VertexFormat> vertices;
        std::vector<unsigned int> indices;
    };
}
