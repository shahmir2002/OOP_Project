#pragma once
#include "SDL.h"

class CharCollision;

class AABBCollision
{
public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB); 
    static bool AABB(const CharCollision &colA, const CharCollision &colB);
};