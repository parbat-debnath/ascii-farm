#ifndef CROP_H
#define CROP_H

#include "../libraries/definitions.h"

void initCropDatabase(void);
const CropType *getCropType(int cropType);
void updateCrop(CropTile *crop, int currentTick);
char getCropSymbol(const CropTile *crop);
bool isCropMature(const CropTile *crop);

#endif