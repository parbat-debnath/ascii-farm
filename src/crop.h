#include "../libraries/definitions.h"

void initCropDatabase();
CropType *getCropType();
void updateCrop(CropTile *crop);
char getCropSymbol(CropTile *crop);
bool isCropMature(CropTile *crop);