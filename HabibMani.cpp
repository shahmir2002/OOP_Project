#include "HabibMania.hpp"
#include "TextureManager.hpp"
#include "CharComponents.hpp"
#include "GameMap.hpp"
#include "CharMovement.hpp"
//#include "Vector2D.h"
#include "AABBCollision.hpp"
#include "CharCollision.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SDL_mixer.h>
#include <chrono>
#include <ctime>
#include "ObjectManager.hpp"
#include <SDL_ttf.h>
#include <SDL.h>
//#include "Buttons.h"

//initializing 
SDL_Renderer* HabibMania::renderer = nullptr;
SDL_Event HabibMania::event;
TTF_Font* HabibMania:: riddleFont;
TTF_Font* HabibMania:: textFont;

std::vector <Location> HabibMania::locations ={
        Location("DBMS", 3*40, 3*40),
        Location("DLD", 5*40, 11*40),
        Location("OOP", 9*40, 6*40),
        Location("PROB",15*40, 3*40),
        Location("AND",15*40, 4*40),
        Location("STATS",15*40, 5*40),
        Location("EM",14*40, 12*40)
    };


//GameMap object
GameMap* map;

std::vector<CharCollision *> HabibMania::colliders;

HabibMania::HabibMania() // ctor
{
}
HabibMania::~HabibMania() // dtor
{}
bool HabibMania::running(){
    return isRunning;
}


//initializing
void HabibMania::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{   //std:: cout << "Initialized called" << std:: endl;
    if (SDL_Init(SDL_INIT_EVERYTHING)==0) 
    {
        std::cout << "Everything Initialized..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, 0); 

        if (window)
        {
            std::cout << "Window Created!" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0); 
        if (renderer) 
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  
            std::cout << "Renderer Created!" << std::endl;
        }

        if (TTF_Init()==-1) {
            std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        }

        riddleFont = TTF_OpenFont("Pixellari.ttf", 24);  // Adjust font path and size
        if (!riddleFont) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        }
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) >= 0 ) ///////////////////////////////////////////////////////////////////////////////////////////////////////////
		{
			printf( "SDL_mixer initialized! SDL_mixer Error: %s\n", Mix_GetError() );		
		}
        
        //initializing bools
        isRunning = true;
        getLocation = false;
        paused = gamestart = gameover = gamewon = instructions = false;
        GEM1 = GEM2 = GEM3 = GEM4 = GEM5 = true;
        
        showRiddle = false;
        showWarning = false;
        chase = false;
        lastCollisionTime = 0;
        CHASER1 = CHASER2 = CHASER3 = CHASER4 = false;

        //Screen width and height
        src.x = src.y = dest.x = dest.y = 0;
        dest.w = src.w = 800;
        dest.h = src.h = 640;
        
        button.rect = {274, 436, 91, 94};
        instructionsButton.rect = {453, 435, 112, 97};
        resumeButton.rect = {708, 587, 84, 46};

        //loading all the textures
        startTexture = TextureManager::LoadTexture("assets/start screen.png");
        pauseTexture = TextureManager::LoadTexture("assets/game paused (1).png");
        overTexture = TextureManager::LoadTexture("assets/game over (1).png");
        winTexture = TextureManager::LoadTexture("assets/game won (1).png");
        instructionsTexture = TextureManager::LoadTexture("assets/instructions (1).png");
        gemTexture = TextureManager::LoadTexture("assets/gem (1).png");
        heartTexture = TextureManager::LoadTexture("assets/Heart.png");
        riddleTexture = TextureManager::LoadTexture("assets/riddle_display.png");
        warningTexture = TextureManager::LoadTexture("assets/warning.png");

        //adding the objects in Objects vector and getting their reference
        initialLoc = &manager.addObject();
        player = &manager.addObject();

        chaser1 = &manager.addObject();
        chaser2 = &manager.addObject();
        chaser3 = &manager.addObject();
        chaser4 = &manager.addObject();

        gem1 = &manager.addObject();
        gem2 = &manager.addObject();
        gem3= &manager.addObject();
        gem4 = &manager.addObject();
        gem5 = &manager.addObject();

    
        //initializing ridddles
        riddleManager.initializeRiddles();
       
        srand(time(0));
    }
    else 
        {
        isRunning = false;
    }
    
    map = new GameMap(this);
    //std:: cout<< "reached here" << std:: endl;
    addObjects();


}

//adding the object's components likes it's position, it's collision. it's animation
void HabibMania::addObjects()
{   //std:: cout << "addObjects called" << std:: endl;
    srand(time(0));
   
    initialLoc->addComponent<CharBlock>(40, 40, 30, 30, 3);
    initialLoc->addComponent<CharCollision>("Initial Location");
    std:: cout<< "added!" << std::endl;

    gem1->addComponent<CharBlock>(5*40, 4*40, 40, 40, 0);
    gem1->addComponent<CharCollision>("Gem 1");
    std:: cout<< "added!" << std::endl;

    gem2->addComponent<CharBlock>(4*40, 11*40, 40, 40, 0);
    gem2->addComponent<CharCollision>("Gem 2");
    std:: cout<< "added!" << std::endl;

    gem3->addComponent<CharBlock>(8*40, 5*40, 40, 40, 0);
    gem3->addComponent<CharCollision>("Gem 3");
    std:: cout<< "added!" << std::endl;

    gem4->addComponent<CharBlock>(17*40, 5*40, 40, 40, 0);
    gem4->addComponent<CharCollision>("Gem 4");
    std:: cout<< "added!" << std::endl;

    gem5->addComponent<CharBlock>(16*40, 11*40, 40, 40, 0);
    gem5->addComponent<CharCollision>("Gem 5");
    std:: cout<< "added!" << std::endl;

    chaser1->addComponent<CharBlock>(13*40, 0, 32, 32, 0);
    chaser1->addComponent<CharCollision>("chaser1");
    

    chaser2->addComponent<CharBlock>(8*40, 0, 32, 32, 0);
    chaser2->addComponent<CharCollision>("chaser2");

    chaser3->addComponent<CharBlock>(0, 10*40, 32, 32, 0);
    chaser3->addComponent<CharCollision>("chaser3");

    chaser4->addComponent<CharBlock>(0, 13*40, 32, 32, 0);
    chaser4->addComponent<CharCollision>("chaser4");
    
    player->addComponent<CharPosition>(42, 0, 32, 32, 1); // Starting x and y positions 
    player->addComponent<CharAnimation>("assets/spritesheet (1).png", true);
    player->addComponent<CharMovement>();
    player->addComponent<CharCollision>("player");
    std:: cout << "added!" << std:: endl;

}

bool HabibMania::loadMedia()  // loading all music files
{
    bool success = true;
	bgMusic = Mix_LoadMUS("media/bg.mp3" );
    gemSFX = Mix_LoadWAV("media/gemCollection.mp3" );
    winSFX = Mix_LoadWAV("media/gamWin.wav" );
    habibManiaOverSFX = Mix_LoadWAV("media/gameover.wav");
    ouchSFX = Mix_LoadWAV("media/collision.wav");
    timerSFX = Mix_LoadWAV("media/timer.wav");
    
	if(bgMusic == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
    if(gemSFX == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
    if(habibManiaOverSFX == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
    if(winSFX == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
    if(ouchSFX == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
    if(timerSFX == NULL){
		printf("Unable to load music: %s \n", Mix_GetError());
		success = false;
	}
	return success;
}

void HabibMania::music() // called in main.cpp to play music
{
    if( Mix_PlayingMusic() == 0 ) // Tells you if music is actively playing,
	{
		//Play the music
		Mix_PlayMusic( bgMusic, 2 );
	}
}


void HabibMania::handleEvents()
{   //std:: cout << "handleEvents called" << std:: endl;
    SDL_PollEvent(&event);
    int x, y;
    bool isInsideButton = false; // passing reference of the event. ie. its location
    bool isInsideInstructionButton = false;
    bool isInsideResumeButton = false;

    SDL_GetMouseState(&x, &y);
    isInsideButton = (x > button.rect.x) && (x < button.rect.x + button.rect.w) &&
                        (y > button.rect.y) && (y < button.rect.y + button.rect.h);
    isInsideInstructionButton = (x > instructionsButton.rect.x) && (x < instructionsButton.rect.x + instructionsButton.rect.w) &&
                        (y > instructionsButton.rect.y) && (y < instructionsButton.rect.y + instructionsButton.rect.h);
    isInsideResumeButton = (x > resumeButton.rect.x) && (x < resumeButton.rect.x + resumeButton.rect.w) &&
                        (y > resumeButton.rect.y) && (y < resumeButton.rect.y + resumeButton.rect.h);
   
    switch (event.type) // this switch case finds the type of the event and tales actions accordingly
    {
    case SDL_MOUSEMOTION:
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:

        if (isInsideButton) {
            switch (event.type) {
                case SDL_MOUSEMOTION:
                    button.isOver = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    button.isClicked = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (button.isClicked) {
                        gamestart = true;  // Start the game
                        button.isClicked = false;
                    }
                    break;
            }
        } 

        else if (isInsideInstructionButton){
            switch (event.type) {
                case SDL_MOUSEMOTION:
                    instructionsButton.isOver = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    instructionsButton.isClicked = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (instructionsButton.isClicked) {
                        gamestart = false;
                        instructions = true; //Show instructions page  
                        instructionsButton.isClicked = false;
                    }
                    break;
            }
        }

        else if(isInsideResumeButton){
             switch (event.type) {
                case SDL_MOUSEMOTION:
                    resumeButton.isOver = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    resumeButton.isClicked = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (resumeButton.isClicked) {
                        gamestart = false;
                        instructions = false;  
                        resumeButton.isClicked = false;
                    }
                    break;
            }
        }
       
        break;

    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
    if (HabibMania::event.type == SDL_KEYDOWN)
        {
            switch (HabibMania::event.key.keysym.sym)
            {
            
            case SDLK_p:
                std::cout << "paused!!" << std::endl;
                paused = true;	
                Mix_PauseMusic();
                break;

            case SDLK_SPACE:
            if (paused){
                paused = false;}
                Mix_ResumeMusic();
                break;
            
            case SDLK_ESCAPE: // quit game
                if (gamestart == false || gameover == true || gamewon == true || paused == true)
                {
                    isRunning = false;
                }
                break;

            case SDLK_UP:
                player->getComponent<CharMovement>().moveup();
                break;
            case SDLK_DOWN:
                player->getComponent<CharMovement>().movedown();
                break;
            case SDLK_RIGHT:
                player->getComponent<CharMovement>().walkright();
                break;
            case SDLK_LEFT:
                player->getComponent<CharMovement>().walkleft();
                break;

            default:
                break;
            }
        }

        if (HabibMania::event.type == SDL_KEYUP)
        {
            switch (HabibMania::event.key.keysym.sym){
                case SDLK_UP:
                    player->getComponent<CharMovement>().updown_idle();
                    break;
                case SDLK_DOWN:
                    player->getComponent<CharMovement>().updown_idle();
                break;
                case SDLK_RIGHT:
                player->getComponent<CharMovement>().walkright_idle();
                break;
                case SDLK_LEFT:
                player->getComponent<CharMovement>().walkleft_idle();
                break;
                default:
                break;
            }
        }
}


// Renders everything onto the screen that needs to be drawn. Called After Update function in main.cpp
void HabibMania::render()
{   std:: cout << "render called" << std:: endl;
	SDL_RenderClear(renderer);  //cleans screen
    //Add textures to be rendered
    src.w = dest.w = 800;
    src.h = dest.h = 640;
    dest.x = dest.y = 0;
   
    if (paused)
    {
        TextureManager::Draw(pauseTexture, src, dest);
    }
    else if (gamestart == false && instructions == false)
    {
        TextureManager::Draw(startTexture, src, dest);
    }
    
    else if (gameover)
    {
        TextureManager::Draw(overTexture, src, dest);
    }
    else if (gamewon)
    {
        TextureManager::Draw(winTexture, src, dest);
    }
    else if (instructions){
        TextureManager::Draw(instructionsTexture, src, dest);
    }

    //creates a new surface and renders riddle on it 
    else if (showRiddle) {
        TextureManager::Draw(riddleTexture, src, dest);
        Mix_PauseMusic(); 
        int wraplength = 300;
        SDL_Color textColor = {0, 0, 0};  // Black color

        // if(currentRiddle.empty()){
        //     std:: cout << "Empty string" << std:: endl;
        // }

        SDL_Surface* surfaceMessage = TTF_RenderText_Blended_Wrapped(riddleFont, currentRiddle.c_str(), textColor, wraplength);
        // if (!surfaceMessage) {
        //     std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl; //     
        // }
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        // if (!message) {
        //     std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        //     SDL_FreeSurface(surfaceMessage);  
        // }

        SDL_Rect message_rect;  // Set the position and size for riddle text
        message_rect.x = 250;  
        message_rect.y = 200;
        message_rect.w = surfaceMessage -> w;
        message_rect.h = surfaceMessage -> h;

        SDL_RenderCopy(renderer, message, NULL, &message_rect);

        // Checking if 15 seconds have passed and riddle will disappear after 15 secs
        if (SDL_GetTicks() - riddleStartTime > 10000) {
            showRiddle = false;
            Mix_HaltChannel(-1);
            Mix_ResumeMusic();
        }
        //freeing the surface and destroying the texture
        SDL_DestroyTexture(message);
        SDL_FreeSurface(surfaceMessage);
    }

    //When incorrect gem is collided with
    else if(showWarning){
        TextureManager::Draw(warningTexture, src, dest);
        int wraplength = 500;
        SDL_Color textColor = {0, 0, 0};  // black color
        wrongLoc= "Oops! Wrong Location";
        
        SDL_Surface* surfaceMessage = TTF_RenderText_Blended_Wrapped(riddleFont, wrongLoc.c_str(), textColor, wraplength);

        // if (!surfaceMessage) {
        //     std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        // }
        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        // if (!message) {
        //     std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        //     SDL_FreeSurface(surfaceMessage);  
        // }

        SDL_Rect message_rect; 
        message_rect.x = 250;  
        message_rect.y = 300;
        message_rect.w = surfaceMessage -> w;
        message_rect.h = surfaceMessage -> h;

        SDL_RenderCopy(renderer, message, NULL, &message_rect);
       
        // Checking if 1 second have passed
        if (SDL_GetTicks() - warningStartTime > 1000) {
            showWarning = false;
        }

        SDL_DestroyTexture(message);
        SDL_FreeSurface(surfaceMessage);
    }

    else
    {
     // Renders the entire map 60 frames every second.
    map->DrawMap();
    //std:: cout << "reached renderer" << std:: endl;

        //rendering gem when correct gem is collided with
        int count = 0;
        while (count != gemCollected){    
        src.w = src.h = dest.w = dest.h = 40;
        src.x = src.y = 0;
        dest.x = (14 + count ) * 40;
        dest.y = 15 * 40;
        TextureManager::Draw(gemTexture, src, dest);
        count++; 
        }
        
        //rendering lives
        for (int i = 0; i < attendance; i++)
        {
            src.w = src.h = dest.w = dest.h = 40;
            src.x = src.y = 0;
            dest.x = i * 40;
            dest.y = 15 * 40;
            TextureManager::Draw(heartTexture, src, dest);
        }
    
   
    //rendering location names
    for (const auto& location : locations) {
        textFont = TTF_OpenFont("Pixellari.ttf", 20);
        SDL_Surface* textSurface = TTF_RenderText_Solid(textFont, location.name.c_str(), {255, 255, 255}); // White color
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        SDL_Rect textRect;
        textRect.x = location.x; 
        textRect.y = location.y;
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;

        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    }

     // Draws all gameObjects
    manager.draw();
    
    }
    SDL_RenderPresent(renderer);
}

// Objects Updated here
void HabibMania::update()
{   std:: cout<< "update called" << std:: endl;
    // check the Players position before any updates
    if (paused != true && gamestart == true && gamewon==false && gameover == false)
    {
    Vector pos = player->getComponent<CharPosition>().position;

    manager.refresh();
    manager.update();

    // Checking if player out of bounds.
    float xpos, ypos;
    xpos = player->getComponent<CharPosition>().position.x;
    ypos = player->getComponent<CharPosition>().position.y;

    gem1->getComponent<CharAnimation>().setTex("assets/gem (1).png"); 
    gem2->getComponent<CharAnimation>().setTex("assets/gem (1).png");
    gem3->getComponent<CharAnimation>().setTex("assets/gem (1).png");
    gem4->getComponent<CharAnimation>().setTex("assets/gem (1).png");
    gem5->getComponent<CharAnimation>().setTex("assets/gem (1).png");

    if (xpos <= 0 || xpos >= 800 || ypos <= 0 || ypos >= 640)
    {
        player->getComponent<CharPosition>().position = pos;
    }

    for (auto cc : colliders)
    {
    bool x = AABBCollision::AABB(player->getComponent<CharCollision>(), *cc);
    if (x)
    {
        if (cc->tag != "player" && cc->tag != "Gem 1" && cc->tag != "Gem 2" && cc->tag != "Gem 3" && cc->tag != "Gem 4" && cc->tag!="Gem 5" && cc->tag!= "Initial Location" && cc->tag!= "PowerUp")
        {
            // if the player collides with an object then set his position to the previous position before collision.
            player->getComponent<CharPosition>().position = pos;
        }
        else
        {
            continue;
        }
        
    }
    }

   //collision between the initialloc and player
    if (AABBCollision::AABB(player->getComponent<CharCollision>(), initialLoc->getComponent<CharCollision>()) && initialLoc->getComponent<CharCollision>().getHit() == false)
    {   
        getLocation = true;
        Mix_PlayChannel(-1, gemSFX, 0); 
        initialLoc->getComponent<CharAnimation>().setTex("assets/goldenhoney.png"); // remove initialLoc

        GEM1 = true;
        GEM2 = true;
        GEM3 =true;
        GEM4 =true;
        GEM5 = true;

        showRiddle = true;
        Mix_PlayChannel( -1, timerSFX, 0 );
        riddleManager.prepareRandomRiddle();
        riddleStartTime = SDL_GetTicks();
        
        //set a new question
        currentRiddle = riddleManager.getQuestion();

        initialLoc->getComponent<CharCollision>().setHit(true);   
    }

    //this ensures a delay between collision to avoid rendering warning and riddle screen simultaneously
    unsigned int currentTime = SDL_GetTicks();
    const unsigned int cooldownPeriod = 1000;
    
    //collision handling between gems and player
    if((GEM1 == true || GEM2 == true || GEM3 == true|| GEM4 == true || GEM5 == true) && getLocation == true && currentTime - lastCollisionTime > cooldownPeriod){
       
        if (GEM1){
            if (AABBCollision::AABB(player->getComponent<CharCollision>(), gem1->getComponent<CharCollision>())){
                gemID = "Gem 1";
                lastCollisionTime = currentTime;

                //if correct gem is collided with, gem will be collected and riddle will be shown
                if (riddleManager.checkAnswer(gemID) == true){
                    Mix_PlayChannel( -1, gemSFX, 0 );
                    riddleManager.prepareRandomRiddle();
                    currentRiddle = riddleManager.getQuestion();
                    gemCollected ++;
                    Mix_PlayChannel( -1, timerSFX, 0 );
                    showRiddle = true;
                    riddleStartTime = SDL_GetTicks();
                    chase = false;
                }
                else{

                    //chase will start
                    showWarning = true;
                    warningStartTime = SDL_GetTicks();
                    chase = true;
                    
                }    
                
            }
        }

        if (GEM2){
            if (AABBCollision::AABB(player->getComponent<CharCollision>(), gem2->getComponent<CharCollision>())){
                gemID = "Gem 2";
                lastCollisionTime = currentTime;

                if (riddleManager.checkAnswer(gemID) == true){
                    Mix_PlayChannel( -1, gemSFX, 0 );
                    riddleManager.prepareRandomRiddle();
                    currentRiddle = riddleManager.getQuestion();
                    gemCollected ++;
                    Mix_PlayChannel( -1, timerSFX, 0 );
                    showRiddle = true;
                    riddleStartTime = SDL_GetTicks();
                    chase = false;
                }
                
                else{
                    showWarning = true;
                    warningStartTime = SDL_GetTicks();
                    chase = true;
                    
                }
            }
        }

        if (GEM3){
            if (AABBCollision::AABB(player->getComponent<CharCollision>(), gem3->getComponent<CharCollision>())){
                gemID = "Gem 3";
                lastCollisionTime = currentTime;

                if (riddleManager.checkAnswer(gemID) == true){
                    Mix_PlayChannel( -1, gemSFX, 0 );
                    riddleManager.prepareRandomRiddle();
                    currentRiddle = riddleManager.getQuestion();
                    gemCollected ++;
                    Mix_PlayChannel( -1, timerSFX, 0 );
                    showRiddle = true;
                    riddleStartTime = SDL_GetTicks();
                    chase = false;
                }
                else
                {
                    showWarning = true;
                    warningStartTime = SDL_GetTicks();
                    chase = true;
                    
                }
            }
        }

        if (GEM4){
            if (AABBCollision::AABB(player->getComponent<CharCollision>(), gem4->getComponent<CharCollision>())){
                gemID = "Gem 4";
                lastCollisionTime = currentTime;

                if (riddleManager.checkAnswer(gemID) == true){
                    Mix_PlayChannel( -1, gemSFX, 0 );
                    riddleManager.prepareRandomRiddle();
                    currentRiddle = riddleManager.getQuestion();
                    gemCollected ++;
                    Mix_PlayChannel( -1, timerSFX, 0 );
                    showRiddle = true;
                    riddleStartTime = SDL_GetTicks();
                    chase = false;
                }

                else{
                    showWarning = true;
                    warningStartTime = SDL_GetTicks();
                    chase = true;
                    
                }
                
            }
        }

        if (GEM5){
            if (AABBCollision::AABB(player->getComponent<CharCollision>(), gem5->getComponent<CharCollision>())){
                gemID = "Gem 5";
                lastCollisionTime = currentTime;

                if (riddleManager.checkAnswer(gemID)==true){
                    Mix_PlayChannel( -1, gemSFX, 0 );
                    riddleManager.prepareRandomRiddle();
                    currentRiddle = riddleManager.getQuestion();
                    gemCollected ++;
                    Mix_PlayChannel( -1, timerSFX, 0 );
                    showRiddle = true;
                    riddleStartTime = SDL_GetTicks();

                    chase = false;
                }
                else {
                    showWarning = true;
                    warningStartTime = SDL_GetTicks();
                    chase = true;
                }
                
            }
        }    

    } // for gem collision checking bracket

    //chase is true then all chasers get active
    if (chase){
        chaser1->getComponent<CharAnimation>().setTex("assets/chaser5.png");
        CHASER1 = true;
        chaser2->getComponent<CharAnimation>().setTex("assets/chaser3.png");
        CHASER2 =true;
        chaser3->getComponent<CharAnimation>().setTex("assets/chaser2.png");
        CHASER3 = true;
        chaser4->getComponent<CharAnimation>().setTex("assets/chaser4.png");
        CHASER4 = true;
        
        int s = rand()% 4 + 5;
        //setting speed
        chaser1->getComponent<CharPosition>().setSpeed(s);
        chaser2->getComponent<CharPosition>().setSpeed(s);
        chaser3->getComponent<CharPosition>().setSpeed(s);
        chaser4->getComponent<CharPosition>().setSpeed(s);

        chaser1->getComponent<CharPosition>().position.y += chaser1->getComponent<CharPosition>().getSpeed();
        chaser2->getComponent<CharPosition>().position.y += chaser2->getComponent<CharPosition>().getSpeed();
        chaser3->getComponent<CharPosition>().position.x += chaser3->getComponent<CharPosition>().getSpeed();
        chaser4->getComponent<CharPosition>().position.x += chaser4->getComponent<CharPosition>().getSpeed();

        //making sure chasers are in the boundary of the screen
        if ((int)chaser1->getComponent<CharPosition>().position.y >= 640)
        {
            chaser1->getComponent<CharPosition>().position.y = 0.0;
            chaser1->getComponent<CharPosition>().position.x = (float)(rand() % 640);
            
        }
        if ((int)chaser2->getComponent<CharPosition>().position.y >= 640)
        {
            chaser2->getComponent<CharPosition>().position.y = 0.0;
            chaser2->getComponent<CharPosition>().position.x = (float)(rand() % 640);
            
        }
        if ((int)chaser3->getComponent<CharPosition>().position.x >= 800)
        {
            chaser3->getComponent<CharPosition>().position.x = 0.0;
            chaser3->getComponent<CharPosition>().position.y = (float)(rand() % 640);
            
        }
        if ((int)chaser4->getComponent<CharPosition>().position.x >= 800)
        {
            chaser4->getComponent<CharPosition>().position.x = 0.0;
            chaser4->getComponent<CharPosition>().position.y = (float)(rand() % 640);
            
        }   
        
    }

    //collision b/w chaser and player will decrease the lives
    if (chase == true && (AABBCollision::AABB(player->getComponent<CharCollision>(), chaser1->getComponent<CharCollision>()) ||
    AABBCollision::AABB(player->getComponent<CharCollision>(), chaser2->getComponent<CharCollision>()) || 
    AABBCollision::AABB(player->getComponent<CharCollision>(), chaser3->getComponent<CharCollision>()) ||
    AABBCollision::AABB(player->getComponent<CharCollision>(), chaser4->getComponent<CharCollision>())))
    {
        if (AABBCollision::AABB(player->getComponent<CharCollision>(), chaser1->getComponent<CharCollision>()) && HabibMania::attendance != 0)
        {
            Mix_PlayChannel( -1, ouchSFX, 0 ); 
            chaser1->getComponent<CharPosition>().position.y = 0.0;
            chaser1->getComponent<CharPosition>().position.x = (float)(rand() % 640);
            HabibMania::attendance--; // reduce life
        }
        else if (AABBCollision::AABB(player->getComponent<CharCollision>(), chaser2->getComponent<CharCollision>()) && HabibMania::attendance != 0)
        {
            Mix_PlayChannel( -1, ouchSFX, 0 );
            chaser2->getComponent<CharPosition>().position.y = 0.0;
            chaser2->getComponent<CharPosition>().position.x = (float)(rand() % 640);
            HabibMania::attendance--; 
        }
        else if (AABBCollision::AABB(player->getComponent<CharCollision>(), chaser3->getComponent<CharCollision>()) && HabibMania::attendance != 0)
        {
            Mix_PlayChannel( -1, ouchSFX, 0 );
            chaser3->getComponent<CharPosition>().position.x = 0.0;
            chaser3->getComponent<CharPosition>().position.y = (float)(rand() % 640);
          
            HabibMania::attendance--;
        }
        else if (AABBCollision::AABB(player->getComponent<CharCollision>(), chaser4->getComponent<CharCollision>()) && HabibMania::attendance != 0)
        {
            Mix_PlayChannel( -1, ouchSFX, 0);
            chaser4->getComponent<CharPosition>().position.x = 0.0;
            chaser4->getComponent<CharPosition>().position.y = (float)(rand() % 640);
            HabibMania::attendance--;
        }
        
        else
        {
            // If player has 0 lives then HabibMania over.
            Mix_PlayChannel( -1, habibManiaOverSFX, 0 ); // HabibMania over sfx
            Mix_PauseMusic(); // pause bgmusic
            gameover = true; // gameover screen
            std::cout << "Game Over!!" << std::endl;
        }
        }
    
    //chase is flase then chasers will hide
    if (chase == false){
        
        chaser1->getComponent<CharAnimation>().setTex("assets/g1.jpg");
        chaser2->getComponent<CharAnimation>().setTex("assets/g1.jpg");
        chaser3->getComponent<CharAnimation>().setTex("assets/g1.jpg");
        chaser4->getComponent<CharAnimation>().setTex("assets/g1.jpg");

        chaser1->getComponent<CharPosition>().setSpeed(0);
        chaser2->getComponent<CharPosition>().setSpeed(0);
        chaser3->getComponent<CharPosition>().setSpeed(0);
        chaser4->getComponent<CharPosition>().setSpeed(0);

        chaser1->getComponent<CharPosition>().position.y = 0;
        chaser2->getComponent<CharPosition>().position.y = 0;
        chaser3->getComponent<CharPosition>().position.x = 0;
        chaser4->getComponent<CharPosition>().position.x = 0;

    }

    if (gemCollected == 5){
        Mix_PauseMusic();
        Mix_HaltChannel(-1);
        Mix_PlayChannel(-1,winSFX,0);
        gamewon = true;
    }

    
}
}

// Called at the end when window and renderer need to be destroyed.
void HabibMania::cleanMemory()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    //free music and sfx
    Mix_FreeMusic(bgMusic); 
    bgMusic = NULL;
    Mix_FreeChunk(winSFX); 
    Mix_FreeChunk(habibManiaOverSFX); 
    Mix_FreeChunk(timerSFX); 
    Mix_FreeChunk(gemSFX);
    Mix_FreeChunk(ouchSFX);

    // setting back to nullptr
    habibManiaOverSFX=NULL;
    ouchSFX=NULL;
    winSFX=NULL;
    gemSFX=NULL;
    timerSFX=NULL;
    Mix_Quit();

    //Closing the font
    TTF_CloseFont(riddleFont);
    TTF_Quit();
    SDL_Quit();

    delete map;
    map = nullptr;

    
    std::cout << "Game Cleaned!" << std::endl;
}
// Adding colliders to the tiles in the map. To make them interactable.
void HabibMania::addBlocks(int id, int x, int y)
{
    tile = &manager.addObject();
    tile -> addComponent<CharBlock>(x, y, 40, 40, 20);
    std::string tiles = "tile";
    tiles += std::to_string(y/40);
    tiles += "x";
    tiles += std::to_string(x/40);
    tile->addComponent<CharCollision>(tiles);
}