#pragma once

#include <vector>
#include "components/simple_scene.h"
#include "tank_wars/Terrain.h"
#include "tank_wars/Visualizer.h"
#include "tank_wars/Tank.h"
#include "tank_wars/SkyElement.h"

namespace m1
{
    class TankWars : public gfxc::SimpleScene
    {
    public:
        static constexpr float LogicWidth = 320;
        static constexpr float LogicHeight = 180;

        TankWars();
        ~TankWars();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void InitSkyDecor();

        static constexpr int NumTanks = 2;
        static constexpr int NumPlanets = 5;

        m1::Terrain terrain;
        Visualizer vis;
        std::vector<Tank> tanks;
        std::list<Projectile> projectiles;
        std::vector<SkyElement> skyDecor;
    };
}
