#ifndef SHOP_H
#define SHOP_H

#include "../libraries/definitions.h"

void enterShop();
void updateShop(GameState *game);

void buySeed(int cropType, int qty);
void sellCrop(int cropType, int qty);

int getSeedPrice(int cropType);
int getCropPrice(int cropType);

void freeShop();

#endif