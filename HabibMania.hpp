#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include "ObjectManager.hpp"
//#include "CharPosition.h"
#include "Buttons.hpp"
#include "Riddle.hpp"


class CharCollision;

class HabibMania{
public:
    HabibMania();
    ~HabibMania();

    Button button;
    Button resumeButton;
    Button instructionsButton;
    RiddleManager riddleManager;
    ObjectManager manager;
    
    GameObject* initialLoc;
    GameObject* player;
    GameObject* gem1;
    GameObject* gem2;
    GameObject* gem3;
    GameObject* gem4;
    GameObject* gem5;
    GameObject* chaser1;
    GameObject* chaser2;
    GameObject* chaser3;
    GameObject* chaser4;
    GameObject* tile;

    //collider vector to hold colliders
    static std::vector<CharCollision* > colliders;

    //vector to hold locations
    static std::vector<Location> locations;

    //font, screen variables of type SDL
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static TTF_Font* riddleFont;
    static TTF_Font* textFont;

    void init(const char* title, int xpos, int ypos, int width, int height, int flags); // method for intitializing the game
    void render(); // renders textures on the screen
    void update(); // keeps updating the objects
    void handleEvents(); // pause, restart, play. isrunning is also used here for quit game
    void cleanMemory(); // freeing all memory
    void addObjects(); // Used to initialize all objects in game i.e. player, gems, initial location etc.
    void music(); //adding music in the game
    bool running();
    bool loadMedia();
    void addBlocks(int id, int x, int y);

    private:
        int attendance = 5;
        int gemCollected = 1;
        unsigned int lastCollisionTime;


        bool getLocation;
        bool isRunning; // flag for quit game
        bool paused; // flag for pausing game
        bool gamestart; // flag for start screen
        bool gameover; // flag for game over screen
        bool gamewon;// flag for gamewon
        bool instructions; //flag for instructions screen
        //flags for gems
        bool GEM1;
        bool GEM2;
        bool GEM3;
        bool GEM4;
        bool GEM5;   

        bool chase; // flag for chase
        bool showRiddle; //flag for riddle display
        bool showWarning; //flag for warning
    
    //flags for chasers
        bool CHASER1;
        bool CHASER2;
        bool CHASER3;
        bool CHASER4;

        //timer units, to control time of riddle display and warning display
        Uint32 riddleStartTime;
        Uint32 warningStartTime;

        //string holding the riddle
        std::string currentRiddle;
        std::string wrongLoc;

        std:: string gemID;

        //music
        Mix_Music *bgMusic = nullptr; 
        Mix_Chunk *gemSFX = nullptr;
        Mix_Chunk *habibManiaOverSFX = nullptr;
        Mix_Chunk *winSFX = nullptr;
        Mix_Chunk *ouchSFX = nullptr;
        Mix_Chunk *timerSFX = nullptr;

        //textures and surfaces
        SDL_Texture *pauseTexture;
        SDL_Texture *startTexture; 
        SDL_Texture *overTexture;
        SDL_Texture *winTexture;
        SDL_Texture *gemTexture;
        SDL_Rect src, dest;
        SDL_Window* window;
        SDL_Texture *instructionsTexture;
        SDL_Texture *heartTexture;
        SDL_Texture *riddleTexture;
        SDL_Texture *warningTexture;
        SDL_Texture* message;
        SDL_Surface* surfaceMessage;
        SDL_Surface* textSurface;
        SDL_Texture* textTexture;

};