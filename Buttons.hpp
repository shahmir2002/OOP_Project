#include <iostream>
#include <SDL.h>


//for start, intructions and resume button
struct Button{
    
    SDL_Rect rect;   // x, y, width, height of the button
    bool isOver = false;     // True if mouse is over the button
    bool isClicked = false;  // True if button is clicked

    Button();
};

//a location structure
struct Location{
    std::string name;
    int x;
    int y;

    //Constructor to initialize locations
    Location(std::string n, int X, int Y);
};
