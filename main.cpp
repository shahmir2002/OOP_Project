#include "HabibMania.hpp"

//g++ *.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf



// our Game object
HabibMania* game = nullptr;

// Main function calling necessary functions.
int main(int argc, char* argv[])
{
        
    // Defining the Frame Rate and making the game run more smoothly
    const int FrameRate = 60;
    const int FrameDelay = 1000 / FrameRate;  //max time between frames
    Uint32 FrameStart;  //Unit32 is a large integer
    int FrameTime;

    // Creating a new game object, initializing it and making sure
    // that the game runs in a loop and handling all game updates
    // and renderes
    game = new HabibMania();
    game->init("HabibMania", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, 0);   //Chap1 is name of window, next two para allows the window to be positioned in the center and the other two determine size and last para is 0 SDL flags which shows window simply
    if( !game->loadMedia() ) ////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		printf( "Failed to load media!\n" );
	}
    // // Main game loop handles all Game events, user inputs and Updates the Screen and the objects(position etc)
    while(game->running()) 
    {
        FrameStart = SDL_GetTicks();  //current running time is milliseconds
        
        game->handleEvents();
        game->update();
        game->render();   

        FrameTime = SDL_GetTicks() - FrameStart;  //this gives us how long it takes to go through handling of events, objects and rendering it
        // Handles the Frame Rate of The game such that it can dip below 60 but
        // Not exceed 60
        game->music(); /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (FrameDelay > FrameTime)
        {
            SDL_Delay(FrameDelay - FrameTime);  //delays our frames
        }
    }
    // End of the Game when peron presses the Exit window button
    game->cleanMemory();
    return 0;
}