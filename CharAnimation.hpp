#pragma once
#include "CharComponents.hpp"
#include "SDL.h"
#include "TextureManager.hpp"
#include <map>

//Stores the basic parameters of our player
struct Animation
{
    int index;
    int frames;
    int speed; //for our animation
    Animation(){} 
    Animation(int i, int f, int s)  //constructor to set parameters
    {
        index = i;
        frames = f;
        speed = s;
    }
};

class CharAnimation : public CharComponent
{
    private:
    //we will need to refer to the positions. 
        CharPosition *transform;
        SDL_Texture *texture;
        SDL_Rect srcRect, destRect;

        bool animated = false;
        int frames = 0;
        int speed = 100;

    public:
        int animIndex = 0; //initial pos = 0
        std::map<const char *, Animation> animations; //maps the states with animations e.g idle state will have a particular animation
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;   

        CharAnimation() = default;
        
        //to load the texture of our animation.
        CharAnimation(const char* path)
        {
            setTex(path);
            animated = false; //indicating no animations are defined yet
        }

        //to render animation of the player 
        CharAnimation(const char* path, bool isAnimated)
        {
            std:: cout << "CharAnimation called" << std:: endl;
            animated = isAnimated;


            Animation idle = Animation(0, 1, 50);  //index = 1, frame = 1, speed = 50
            Animation up = Animation(0, 1, 50);         
            Animation down = Animation(0, 1, 50);
            Animation walk = Animation(0, 1, 50);
            
            //mapping player's state with animations
            animations.emplace("Idle", idle);
            animations.emplace("Up", up);
            animations.emplace("Down", down);
            animations.emplace("Walk", walk);

            Play("Idle");
            setTex(path);

        }
        ~CharAnimation()
        {
            SDL_DestroyTexture(texture);
        }

        void setTex(const char* path) //to load the texture
        {
            //std:: cout<< "setTex called" << std::endl;
            texture = TextureManager::LoadTexture(path);
        }

        //initializes the players position        
        void init() override  
        {
            transform = &gameObject->getComponent<CharPosition>(); //reference to get the component

            srcRect.x = srcRect.y = 0;
            srcRect.w = transform->getWidth();
            srcRect.h = transform->getHeight();
            
        }
        //sets the src and dest of the animation according to the frame and index
        void update() override
        {
            if (animated)
            {
                srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
            }
            srcRect.y = animIndex * transform->getHeight();  //initial pos = 0 because aniIndex set to 0, when aniIndex=1, the pos will be change and so on
            
            destRect.x = static_cast<int>(transform->position.x);
            destRect.y = static_cast<int>(transform->position.y);
            destRect.w = static_cast<int>(transform->getWidth() * transform->getScale() + 1);
            destRect.h = static_cast<int>(transform->getHeight() * transform->getScale()+ 1);
        }
        //renders the current animation using the src and dest
        void draw() override
        {
            TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
        }
        //function which sets the frames, index and speed based on the current animation 
        void Play(const char* animName)
        {
            frames = animations[animName].frames;
            animIndex = animations[animName].index;
            speed = animations[animName].speed;
        }
};