#pragma once

#include "core/gpu/mesh.h"


namespace m1
{
    class SkyElement
    {
    public:
        static constexpr bool Up = true;
        static constexpr bool Down = false;
        Mesh* mesh;
        glm::mat3 modelMatrix;

        SkyElement(float X, float Y, float radius, glm::vec3 color, int frames, bool dir);
        SkyElement(float X, float Y, float radius);
        SkyElement();
        ~SkyElement();

        void Update(float deltaTime);

    private:
        float x, y;
        int frame;
        int numFrames;
        bool direction;
    };
}
