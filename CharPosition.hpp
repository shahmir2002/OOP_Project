#pragma once
#include "CharComponents.hpp"

// a vector to store the coordinates
struct Vector
{
        float x;
        float y;

    Vector (float X = 0.0f, float Y = 0.0f){
    x = X;
    y = Y;
}

//Operator overloading
Vector& operator+=(const Vector &vec)
{
    this->x += vec.x;
    this->y += vec.y;

    return *this;
   
}
};


class CharPosition : public CharComponent
{   private:
        int height = 32;
        int width = 32;
        int scale = 2;
        int speed = 3;
    public:
        Vector position;
        Vector velocity;
        
        //Function overloading
        CharPosition()
        {
            position.x = 0;
            position.y = 0;
        }
        CharPosition(int sc)
        {
            position.x = 0;
            position.y = 0;
            scale = sc;
        }
        CharPosition(float x, float y) {
            position.x = x;
            position.y = y;
        }
        CharPosition(float x, float y, int w, int h, int sc) 
        {
            position.x = x;
            position.y = y;
            height = h;
            width = w;
            scale = sc;
        }
        void init() override
        {
            velocity.x = 0;
            velocity.y = 0;
        }
        void update() override
        {
            position.x += velocity.x * speed;
            position.y += velocity.y * speed;
        }

        int getHeight(){
            return height;
        }

        int getWidth(){
            return width;
        }

        int getSpeed(){
            return speed;
        }

        void setSpeed(int s){
            speed = s;
        }

        int getScale(){
            return scale;
        }
};