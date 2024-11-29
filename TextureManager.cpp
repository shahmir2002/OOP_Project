#include "TextureManager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{   //std:: cout << "texture loaded" << std:: endl;
    SDL_Surface* tempSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(HabibMania::renderer, tempSurface);
    SDL_FreeSurface(tempSurface); 
    
    return tex;
}
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
{   
    //std:: cout <<"texture drawn" << std::endl;
    SDL_RenderCopy(HabibMania::renderer, tex, &src, &dest);  
}
void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)  //overloading for when a sprite has to be flipped basically the player
{
    //std::cout<<"texture drawn"<<std::endl;
    SDL_RenderCopyEx(HabibMania::renderer, tex, &src, &dest, NULL, NULL, flip);  //NULLs are for angle , flip para decides to flip the character when moving in other directions 
}
