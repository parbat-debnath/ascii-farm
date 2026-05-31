#include "../libraries/definitions.h"
#include "./farm.h"
#include "./crop.h"
#include "./render.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool isInBounds(int x, int y)
{
    return x >= 0 && x < FARM_WIDTH && y >= 0 && y < FARM_HEIGHT;
}

static void clearTile(CropTile *tile)
{
    if (!tile)
        return;

    memset(tile, 0, sizeof(*tile));
    tile->cropTile = -1;
    tile->occupied = false;
}

void initFarm(Farm *farm)
{
    if (!farm)
        return;

    for (int y = 0; y < FARM_HEIGHT; y++)
    {
        for (int x = 0; x < FARM_WIDTH; x++)
        {
            clearTile(&farm->tiles[y][x]);
        }
    }
}

CropTile *getFarmTile(Farm *farm, int x, int y)
{
    if (!farm || !isInBounds(x, y))
        return NULL;

    return &farm->tiles[y][x];
}

bool isFarmTileEmpty(Farm *farm, int x, int y)
{
    CropTile *tile = getFarmTile(farm, x, y);

    if (!tile)
        return false;

    return !tile->occupied;
}

bool canHarvest(Farm *farm, int x, int y)
{
    CropTile *tile = getFarmTile(farm, x, y);

    if (!tile || !tile->occupied)
        return false;

    return isCropMature(tile);
}

void plantCrop(GameState *game, int x, int y, int cropType)
{
    if (!game)
        return;

    const CropType *type = getCropType(cropType);
    if (!type)
    {
        strcpy(game->message, "Invalid crop type.");
        return;
    }

    CropTile *tile = getFarmTile(&game->farm, x, y);
    if (!tile)
    {
        strcpy(game->message, "Invalid tile.");
        return;
    }

    if (tile->occupied)
    {
        strcpy(game->message, "Tile is already occupied.");
        return;
    }

    if (game->inventory.seeds[cropType] <= 0)
    {
        strcpy(game->message, "No seeds available.");
        return;
    }

    tile->type = *type;
    tile->cropTile = cropType;
    tile->growthStage = 0;
    tile->plantedTick = game->tick;
    tile->occupied = true;

    game->inventory.seeds[cropType]--;

    snprintf(game->message, sizeof(game->message), "%s planted.", tile->type.name);
}

void harvestCrop(GameState *game, int x, int y)
{
    if (!game)
        return;

    CropTile *tile = getFarmTile(&game->farm, x, y);
    if (!tile)
    {
        strcpy(game->message, "Invalid tile.");
        return;
    }

    if (!tile->occupied)
    {
        strcpy(game->message, "Nothing to harvest.");
        return;
    }

    if (!canHarvest(&game->farm, x, y))
    {
        strcpy(game->message, "Crop is not ready yet.");
        return;
    }

    if (tile->cropTile < 0 || tile->cropTile >= MAX_CROP_TYPES)
    {
        strcpy(game->message, "Invalid crop state.");
        return;
    }

    game->inventory.crops[tile->cropTile]++;

    snprintf(game->message, sizeof(game->message), "%s harvested.", tile->type.name);

    clearTile(tile);
}

void updateFarm(GameState *game)
{
    if (!game)
        return;

    for (int y = 0; y < FARM_HEIGHT; y++)
    {
        for (int x = 0; x < FARM_WIDTH; x++)
        {
            updateCrop(&game->farm.tiles[y][x], game->tick);
        }
    }
}