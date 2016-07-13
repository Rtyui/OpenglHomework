#pragma once
#include "glm\glm.hpp"

typedef unsigned uint;
typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;

typedef glm::mat4 Mat4;

#define FPC_VIEWPORT_WIDTH 200
#define FPC_VIEWPORT_HEIGHT 130

#define IDENTITY4 Mat4(1.f)
#define ORTHO_SIZE 50.f
#define PERSPECTIVE_FOV 60.f
#define PROJ_NEAR 0.1f
#define PROJ_FAR 500.f
#define DISTANCE_TO_PLAYER 300.f

#define PLAYER_SPEED 30.f
#define PLAYER_JUMP 100.f

#define TIME_TO_ROTATE 1.f