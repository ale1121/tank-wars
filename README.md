# TankWars

A 1v1 2D tank game built in C++ using OpenGL, with procedurally generated graphics, terrain deformation and physics-based projectile trajectories

Players control tanks on a randomly generated landscape, adjust their firing angle and launch projectiles to damage the opponent while dinamically reshaping the terrain.

![tankwars](https://github.com/user-attachments/assets/87ab9e99-6332-4415-86b6-44fd69f963a0)

## Gameplay Overview

Each player can move along the terrain surface, adjust firing angle and shoot projectiles at the opponent.

Projectiles follow a phyisics-based trajectory affected by gravity and gradually lose velocity. When a projectile hits the terrain, it creates a crater that modifies the terrain shape, causing it to begin self-leveling.

The match ends when one player's health reaches zero.

### Controls

|          | Move                  | Aim                | Shoot   |
|----------|-----------------------|--------------------|---------|
| Player 1 | `A`/`D`               | `W`/`S`            | `Space` |
| Player 2 | `Left`/`Right` arrows | `Up`/`Down` arrows | `Enter` |

### Graphics and Features

- Procedural terrain generation using a function composed of multiple sine waves
- Destructible terrain on projectile collision
- Terrain relaxation simulation where steep slopes gradually collapse to simulate sand-like behavior
- Projectile trajectory preview
- Physics-based projectile motion including velocity decay and gravity effects
- Health and damage system with visual health bar

## Technical Details

- Implemented in C++ with OpenGL
- Rendering using vertex geometry
- Built using [gfx-framework](https://github.com/UPB-Graphics/gfx-framework)

## Building and running

Follow the instructions from the [gfx-framework repository](https://github.com/UPB-Graphics/gfx-framework?tab=readme-ov-file#gear-building). This project uses module 1. 

## Preview

https://github.com/user-attachments/assets/d4d06e01-92c5-4df8-a73f-d07952105e8f

## Project Structure

The TankWars implementation is in [`src/tank_wars`](src/tank_wars)
