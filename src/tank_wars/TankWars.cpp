#include <vector>
#include <iostream>
#include "tank_wars/transform2D.h"
#include "tank_wars/object2D.h"
#include "tank_wars/object2D.h"
#include "tank_wars/TankWars.h"
#include "tank_wars/Colors.h"
#include "tank_wars/HealthBar.h"

using namespace std;
using namespace m1;


TankWars::TankWars()
{
}


TankWars::~TankWars()
{
}


void TankWars::Init()
{
    glm::vec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    terrain.Init(LogicWidth);

    vis.Init(resolution, LogicWidth, LogicHeight);

    for (int i = 0; i < NumTanks; i++) {
        tanks.push_back(Tank(i, &terrain.heightMap));
        tanks[i].Init();
    }

    meshes["projectile"] =
        object2D::CreateDisk("projectile", glm::vec3(0, 0, 0), Projectile::Radius, 2, 0.2, Colors::White);

    InitSkyDecor();
}

void TankWars::InitSkyDecor() {
    skyDecor.push_back(SkyElement(30, 105, 10, Colors::Pink1, 180, SkyElement::Up));
    skyDecor.push_back(SkyElement(65, 140, 20, Colors::Pink2, 120, SkyElement::Down));
    skyDecor.push_back(SkyElement(170, 110, 13, Colors::Pink3, 230, SkyElement::Up));
    skyDecor.push_back(SkyElement(240, 145, 17, Colors::Pink1, 110, SkyElement::Down));
    skyDecor.push_back(SkyElement(285, 100, 10, Colors::Pink2, 120, SkyElement::Up));

    skyDecor.push_back(SkyElement(15, 140, 0.5));
    skyDecor.push_back(SkyElement(20, 80, 0.2));
    skyDecor.push_back(SkyElement(35, 160, 1));
    skyDecor.push_back(SkyElement(70, 95, 0.5));
    skyDecor.push_back(SkyElement(100, 130, 1));
    skyDecor.push_back(SkyElement(135, 85, 0.2));
    skyDecor.push_back(SkyElement(140, 140, 0.5));
    skyDecor.push_back(SkyElement(190, 165, 1));
    skyDecor.push_back(SkyElement(200, 100, 1));
    skyDecor.push_back(SkyElement(220, 125, 0.2));
    skyDecor.push_back(SkyElement(260, 110, 0.5));
    skyDecor.push_back(SkyElement(285, 160, 1));
    skyDecor.push_back(SkyElement(305, 140, 0.5));
}


void TankWars::FrameStart()
{
    glClearColor(Colors::Sky.r, Colors::Sky.g, Colors::Sky.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void TankWars::Update(float deltaTimeSeconds)
{
    terrain.Update(deltaTimeSeconds, projectiles);

    // update tanks, render health bars
    for (auto& tank : tanks) {
        if (!tank.Update(projectiles)) continue;

        RenderMesh2D(tank.healthBar.outline, shaders["VertexColor"],
            vis.matrix * tank.hbModelMatrix);
        RenderMesh2D(tank.healthBar.fill, shaders["VertexColor"],
            vis.matrix * tank.hbModelMatrix * tank.healthBar.fillModelMatrix);
    }

    // render terrain
    for (int i = 0; i < terrain.squares.size(); i++) {
        RenderMesh2D(terrain.mesh, shaders["VertexColor"], vis.matrix * terrain.squares[i]);
    }

    // render tanks
    for (auto &tank : tanks) {
        if (!tank.isAlive) continue;

        int numMeshes = tank.meshes.size();
        for (int j = 0; j < numMeshes - 1; j++) {
            RenderMesh2D(tank.meshes[j], shaders["VertexColor"], vis.matrix * tank.tankModelMatrix);
        }
        RenderMesh2D(tank.meshes[numMeshes - 1], shaders["VertexColor"],
            vis.matrix * tank.barrelModelMatrix);
    }

    // render projectiles
    for (auto& p : projectiles) {
        p.Update(deltaTimeSeconds);
        RenderMesh2D(meshes["projectile"], shaders["VertexColor"], vis.matrix * p.modelMatrix);
    }

    // render trajectories
    for (auto& tank : tanks) {
        if (tank.isAlive) {
            RenderMesh2D(tank.GetTrajectoryMesh(), shaders["VertexColor"], vis.matrix);
        }
    }

    // render planets
    for (int i = 0; i < NumPlanets; i++) {
        skyDecor[i].Update(deltaTimeSeconds);
        RenderMesh2D(skyDecor[i].mesh, shaders["VertexColor"], vis.matrix * skyDecor[i].modelMatrix);
    }

    // render stars
    for (int i = NumPlanets; i < skyDecor.size(); i++) {
        RenderMesh2D(skyDecor[i].mesh, shaders["VertexColor"], vis.matrix * skyDecor[i].modelMatrix);
    }
}


void TankWars::FrameEnd()
{
}


void TankWars::OnInputUpdate(float deltaTime, int mods)
{
    if (tanks[0].isAlive) {
        if (window->KeyHold(GLFW_KEY_A)) {
            tanks[0].Move(-deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            tanks[0].Move(deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_W)) {
            tanks[0].MoveBarrel(deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            tanks[0].MoveBarrel(-deltaTime);
        }
    }
    
    if (tanks[1].isAlive) {
        if (window->KeyHold(GLFW_KEY_LEFT)) {
            tanks[1].Move(-deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_RIGHT)) {
            tanks[1].Move(deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_UP)) {
            tanks[1].MoveBarrel(-deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_DOWN)) {
            tanks[1].MoveBarrel(deltaTime);
        }
    }
    
}


void TankWars::OnKeyPress(int key, int mods)
{
    if (tanks[0].isAlive && key == GLFW_KEY_SPACE) {
        projectiles.push_back(tanks[0].Shoot());
    }

    if (tanks[1].isAlive && key == GLFW_KEY_ENTER) {
        projectiles.push_back(tanks[1].Shoot());
    }
}


void TankWars::OnKeyRelease(int key, int mods)
{
}


void TankWars::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}


void TankWars::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}


void TankWars::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void TankWars::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void TankWars::OnWindowResize(int width, int height)
{
}
