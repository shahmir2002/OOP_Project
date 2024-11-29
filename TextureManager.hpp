#pragma once
#include "HabibMania.hpp"

class TextureManager
{
    public:
        static SDL_Texture* LoadTexture(const char* filename);  //filename of texture we want to render
        static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
        static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};
