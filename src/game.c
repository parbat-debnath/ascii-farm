#include "../libraries/definitions.h"
#include "./render.h"
#include <stdlib.h>

void initGame()
{
    graphics bannerGraphics = loadGraphics("farm.txt");
    
    Player player = {
        .pos.x = 105,
        .pos.y = 10
    };

    graphics playerGraphics = loadGraphics("player.txt");
    renderGraphic(&bannerGraphics, 0, 0);
    renderGraphic(&playerGraphics, player.pos.x, player.pos.y);
}

void gameLoop()
{
    while(1)
    {

    }
}

void updateGame()
{

}

void renderGame()
{

}

void shutdownGame()
{
    exit(0);
}

void switchScreen(int screen)
{

}

GameState *getGameState()
{

}