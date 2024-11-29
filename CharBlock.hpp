#pragma once
#include "ObjectManager.hpp"
#include "CharPosition.hpp"
#include "CharAnimation.hpp"
#include "SDL.h"

//Adding blocks to the game
//Each block has a drawing over. This is necessary to define our colliders in the game as well.
class CharBlock : public CharComponent
{   private:
        char *path;
        int blockID;
        SDL_Rect tileRect;

    public:
    CharPosition* transform;
    CharAnimation *sprite;

    CharBlock() = default;

    CharBlock(int x, int y, int w, int h, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        blockID = id; 

        switch (blockID)
        {
        case 0:
            path = "assets/g1.jpg";
            break;
        case 1:
            path = "assets/tree.png";
            break;
        case 3:
            path = "assets/gem (1).png";
            break;
            
        case 20:
            path = "assets/invisible.png";
            break;
        default:
            break;
        }
    }

    //gets the reference of position and animation and blocks are drawn on the screen.
    void init() override
    {
        gameObject->addComponent<CharPosition>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1); //adding component to the entity
        transform = &gameObject->getComponent<CharPosition>();

        gameObject->addComponent<CharAnimation>(path);
        sprite = &gameObject->getComponent<CharAnimation>();
    }
};