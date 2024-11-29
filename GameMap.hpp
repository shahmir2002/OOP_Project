#pragma once
#include "HabibMania.hpp"

//GameMap is to render static images on the game Screen
class GameMap
{
public:
    GameMap(HabibMania* habibMania);
    ~GameMap();

    void LoadMap(int arr[16][20]);
    void DrawMap();

private:
    HabibMania* habibManiaInstance;
    SDL_Rect src, dest;

    // Initializing all variables for texture loading
    SDL_Texture *path;   
    SDL_Texture *initialLoc;
    SDL_Texture *motel;
    SDL_Texture *tree;
    SDL_Texture *loc1;
    SDL_Texture *loc2;
    SDL_Texture *loc3;
    SDL_Texture *loc4;
    SDL_Texture *loc5;
    SDL_Texture *grass;
    SDL_Texture *gem;

    int map[16][20]; 
};