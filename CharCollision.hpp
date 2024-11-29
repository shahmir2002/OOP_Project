#pragma once
#include <string>
#include "SDL.h"
#include "CharComponents.hpp"
#include "CharPosition.hpp"

class CharCollision : public CharComponent
{
    private:
        bool hit = false;
    public:
        SDL_Rect collider;
        //tag is the name for collider
        std::string tag;
        //the hit bool keeps in check for the initial condition that the hit is once only. 
        
    //a pointer to charposition class
    CharPosition* transform;

    void setHit(bool h){
        hit = h;
    }
    bool getHit(){
        return hit;
    }

    CharCollision(std::string t) //ctor to initialize our tag
    {
        tag = t;
    }
    void init() override
    {   
        //if any game object has no position associated with it then it firsts add its position
        if (!gameObject-> hasComponent <CharPosition> ()) 
        {
            gameObject->addComponent<CharPosition>(); 
        }
        //tranform pointer stores the reference to charposition and this will be used to update position of collider
        transform = &gameObject->getComponent<CharPosition>();

        //add all the collidable entities' reference to the collider vector
        HabibMania::colliders.push_back(this);
    }

    //this function is keeping the collider's position in sync with the gameObject's position
    //allows dynamic and accurate collision detection so even if the properties of gameObject changes, the collision's accuracy is not affected
    void update() override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->getWidth() * transform->getScale();
        collider.h = transform->getHeight() * transform->getScale();
    }
};