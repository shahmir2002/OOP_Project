#pragma once
#include "HabibMania.hpp"
#include "ObjectManager.hpp"
#include "CharComponents.hpp"

// Checks movement of the character
class CharMovement : public CharComponent{
    public:
    //references to the position and state of the object (player)
    CharPosition *transform;
    CharAnimation *sprite;

    //initializing the references
    void init() override
    {
        transform = &gameObject->getComponent<CharPosition>();
        sprite = &gameObject->getComponent<CharAnimation>();
    }

    void moveup(){
        transform->velocity.y = -1;
        sprite->Play("Up"); //calling out the play function in charanimation to set the frame index and speed
    }

    void movedown(){
        transform->velocity.y = +1;
        sprite->Play("Down");
    }

    void walkright(){
        transform->velocity.x = +1;
        sprite->Play("Walk");
    }

    void walkleft(){
        transform->velocity.x = -1;
        sprite->Play("Walk");
        sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
    }

    void updown_idle(){
        transform->velocity.y = 0;
        sprite->Play("Idle");
    }

    void walkright_idle(){
        transform->velocity.x = 0;
        sprite->Play("Idle");
    }

    void walkleft_idle(){
        transform->velocity.x = 0;
        sprite->Play("Idle");
        sprite->spriteFlip = SDL_FLIP_NONE;
    }
};