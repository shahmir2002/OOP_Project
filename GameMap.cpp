#include "GameMap.hpp"
#include "TextureManager.hpp"
#include "HabibMania.hpp"

//each block is of 40x40 so acc to that we have made a nested array for the map
// 1 = location 1
// 2 = location 2
// 3 = location 3
// 4 = location 4
// 5 = location 5
// 0 = grass
// 8 = tree
// 777 = path
int lvl1[16][20] = // Nested array for map
{   
    { 0, 777, 777, 777,  8,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0},
    { 0, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777,  8,  0},
    { 0, 777,  1,   1,   1,   1,  777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 0},
    { 0, 777,  1,   1,   1,   1,  777, 777, 777,  8,  777, 777, 777, 777,  4,   4,   4,   4,   0,  0},
    { 0, 777,  1,   1,   1,   1,  777,  8,   8,   8,  777, 777,  8,  777,  4,   4,   4,   4,   8,  0},
    { 0, 777, 777,  777, 8,  777, 777, 777,  3,   3,   3,   3,   8,  777,  4,   4,   4,   4,  777, 0},
    { 0, 777, 777, 777, 777, 777, 777, 777,  3,   3,   3,   3,   8,  777, 777, 777,  8,  777, 777, 0},
    { 0,  8,  777, 777, 777, 777, 777,  8,   3,   3,   3,   3,  777, 777, 777, 777, 777, 777,  0,  0},
    { 0, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 0},
    { 0, 777, 777,  8,   0,   0,   8,  777, 777, 777, 777,  8,  777, 777, 777, 777, 777, 777,  0,  0},
    { 0, 777, 777, 777,  2,   2,   2,   2,  777, 777, 777, 777, 777, 777, 777, 777, 777, 777,  0,  0},
    { 0, 777, 777, 777,  2,   2,   2,   2,  777, 777, 777, 777, 777,  5,   5,   5,   5,   8,   8,  0},
    { 0, 777, 777,  8,   2,   2,   2,   2,   0,  777, 777, 777, 777,  5,   5,   5,   5,  777, 777, 0},
    { 0, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 777, 0},
    { 0, 777, 777, 777, 777, 777, 777, 777, 777, 777,  8,  777, 777, 777, 777, 777, 777,  8,   8,  0},
    { 0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0}
};

GameMap::GameMap(HabibMania* habibMania)
{   //std:: cout <<"GameMap called" << std:: endl;
    habibManiaInstance = habibMania;
    grass = TextureManager::LoadTexture("assets/g1.jpg");
    path = TextureManager::LoadTexture("assets/goldenhoney.png");
    initialLoc = TextureManager::LoadTexture("assets/gem (1).png");
    tree = TextureManager::LoadTexture("assets/tree (1).png");
    motel = TextureManager::LoadTexture("assets/motel.png");
    loc1 = TextureManager::LoadTexture("assets/purple.png");
    loc2 = TextureManager::LoadTexture("assets/orange.png");
    loc3 = TextureManager::LoadTexture("assets/yellow.png");
    loc4 = TextureManager::LoadTexture("assets/blue.png");
    loc5 = TextureManager::LoadTexture("assets/pink.png");
    
    gem = TextureManager::LoadTexture("assets/gem (1).png");
    
    GameMap::LoadMap(lvl1);

    //dimensions of 1 block
    src.x = src.y = 0; //starts at 0,0
    src.w = dest.w = 40; //width
    src.h = dest.h = 40; //height
}

GameMap::~GameMap()
{
    SDL_DestroyTexture(grass);
   
    SDL_DestroyTexture(path);

    SDL_DestroyTexture(initialLoc);
    SDL_DestroyTexture(tree);
    
    SDL_DestroyTexture(motel);
    SDL_DestroyTexture(loc1);
    SDL_DestroyTexture(loc2);
    SDL_DestroyTexture(loc3);
    SDL_DestroyTexture(loc4);
    SDL_DestroyTexture(loc5);
    SDL_DestroyTexture(gem);

    delete habibManiaInstance;
    habibManiaInstance = nullptr;

}

//if any object other than the path, then it will be added in the collider vector and will be a collidable entity
void GameMap::LoadMap(int arr[16][20])
{
    for (int row = 0; row < 16; row++)
    {
        for (int col = 0; col < 20; col++)
        {
            map[row][col] = arr[row][col];
            if (map[row][col] != 777)
            {   //our addBlocks funtion is not a static function therefore pointing towards it using a pointer of habibMania
                habibManiaInstance->addBlocks(map[row][col], col * 40, row * 40);
            }
        }
    }
}

void GameMap::DrawMap() 
{   //std:: cout << "DrawMap called" << std:: endl;
    int type = 0;
    for (int row = 0; row < 16; row++)
    {
        for (int col = 0; col < 20; col++)
        {   
            type = map[row][col];
            dest.x = col * 40; //for each increment in column,(for eg when row=0 and col=1 texture will move 40 pixels across
            dest.y = row * 40;
            switch (type)
            {
            case 0:
                TextureManager::Draw(grass, src, dest);
                break;
            case 1:
                TextureManager::Draw(loc1, src, dest);
                break;
            case 2:
                TextureManager::Draw(loc2, src, dest);
                break;
            case 3:
                TextureManager::Draw(loc3, src, dest);
                break;
            case 4:
                TextureManager::Draw(loc4, src, dest);
                break;
            case 5:
                TextureManager::Draw(loc5, src, dest);
                break;
            case 6:
                TextureManager::Draw(motel, src, dest);
                break;
            case 777:
                TextureManager::Draw(path, src, dest);
                break; 
            case 8:
                TextureManager::Draw(tree, src, dest);
                break;
            
            default:
                break;
            }       
        }
    }
}