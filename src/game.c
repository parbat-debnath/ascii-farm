#include "../libraries/definitions.h"
#include "../libraries/constants.h"
#include "./audio.h"
#include "./game.h"
#include "./render.h"
#include "./farm.h"
#include "./shop.h"
#include "./save.h"
#include "./input.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static GameState game;
static graphics bannerGraphics;
static graphics playerGraphics;

void initGame()
{
    memset(&game, 0, sizeof(GameState));

    game.player.pos.x = FARM_START_X + FARM_WIDTH / 2;
    game.player.pos.y = FARM_START_Y + FARM_HEIGHT / 2;

    game.money = 100;
    game.tick = 0;
    game.currentScreen = SCREEN_FARM;
    strcpy(game.message, "Welcome to ASCIIFarm!");

    game.selectedCropType = RICE;
    initFarm(&game.farm);

    bannerGraphics = loadGraphics("farm.txt");
    playerGraphics = loadGraphics("player.txt");

    hideCursor();

    initAudio();
    playMusic();
    printf("Audio initialized\n");

    loadGame(&game);
}

void gameLoop()
{
    while (1)
    {
        renderGame();

        char key = getInput();
        processInput(&game, key);

        updateGame();
    }
}

void updateGame()
{
    if (game.currentScreen == SCREEN_FARM)
    {
        updateFarm(&game);
    }
    else if (game.currentScreen == SCREEN_SHOP)
    {
        updateShop(&game);
    }

    game.tick++;
}

void renderGame()
{
    clearScreen();

    if (game.currentScreen == SCREEN_FARM)
    {
        renderGraphic(&bannerGraphics, 0, 0);
        renderFarm(&game.farm, FARM_START_X, FARM_START_Y);
        renderGraphic(&playerGraphics, game.player.pos.x, game.player.pos.y);

        drawHUD(&game, 130, 5);
        drawInventory(&game, 130, 15);
        drawMessage(&game, 60, 40);
    }
    else if (game.currentScreen == SCREEN_SHOP)
    {
        drawHUD(&game, 130, 5);
        drawShop(&game, 30, 5);
        drawInventory(&game, 130, 15);

        drawMessage(&game, 60, 40);
    }

    fflush(stdout);
}

void shutdownGame()
{
    saveGame(&game);

    freeGraphics(&bannerGraphics);
    freeGraphics(&playerGraphics);
    shutdownAudio();

    exit(0);
}

void switchScreen(int screen)
{
    if (screen == SCREEN_FARM || screen == SCREEN_SHOP)
    {
        game.currentScreen = screen;
    }
}

GameState *getGameState()
{
    return &game;
}