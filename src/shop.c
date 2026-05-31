#include "../libraries/definitions.h"
#include "./audio.h"
#include "./shop.h"
#include "./game.h"
#include "./render.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void enterShop()
{
    GameState *game = getGameState();

    if (!game)
        return;

    game->currentScreen = SCREEN_SHOP;
    strcpy(game->message, "Entered the shop.");
}

void updateShop(GameState *game)
{

}

int getSeedPrice(int cropType)
{
    switch (cropType)
    {
    case RICE:
        return 50;
    case WHEAT:
        return 10;
    case CORN:
        return 25;
    default:
        return -1;
    }
}

int getCropPrice(int cropType)
{
    switch (cropType)
    {
    case RICE:
        return 10;
    case WHEAT:
        return 2;
    case CORN:
        return 5;
    default:
        return -1;
    }
}

void buySeed(int cropType, int qty)
{
    GameState *game = getGameState();

    if (!game || qty <= 0)
        return;

    if (cropType < 0 || cropType >= MAX_CROP_TYPES)
    {
        strcpy(game->message, "Invalid seed type.");
        return;
    }

    int price = getSeedPrice(cropType) * qty;

    if (price > game->money)
    {
        strcpy(game->message, "Not enough money.");
        return;
    }

    game->money -= price;
    game->inventory.seeds[cropType] += 10 * qty;

    playBuySfx();
    
    snprintf(game->message, sizeof(game->message), "%dx seeds bought.", 10 * qty);
}

void sellCrop(int cropType, int qty)
{
    
    GameState *game = getGameState();
    
    if (!game)
    return;
    
    if (qty <= 0)
    {
        strcpy(game->message, "Invalid quantity.");
        return;
    }
    
    int price = getCropPrice(cropType) * qty;
    
    if (price < 0)
    return;
    
    if (cropType < 0 || cropType >= MAX_CROP_TYPES)
    {
        strcpy(game->message, "Invalid crop type");
        return;
    }
    
    if (game->inventory.crops[cropType] < qty)
    {
        strcpy(game->message, "Insufficient quantity for selling.");
        return;
    }
    
    game->inventory.crops[cropType] -= qty;
    game->money += price;
    
    playBuySfx();
    snprintf(game->message, sizeof(game->message), "%dx crop sold", qty);
}