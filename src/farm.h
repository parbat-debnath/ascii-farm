#ifndef FARM_H
#define FARM_H

#include "../libraries/definitions.h"

void initFarm(Farm *farm);
void updateFarm(GameState *game);

void plantCrop(GameState *game, int x, int y, int cropType);
void harvestCrop(GameState *game, int x, int y);

CropTile *getFarmTile(Farm *farm, int x, int y);
bool isFarmTileEmpty(Farm *farm, int x, int y);
bool canHarvest(Farm *farm, int x, int y);

#endif