#include "../libraries/definitions.h"
#include "./crop.h"
# include <stdio.h>

static const CropType cropDatabase[MAX_CROP_TYPES] =
{
    { "Rice",  { '+', '*', '#' }, 300, 900, 300 },
    { "Wheat", { '.', ':', '%' }, 200, 600, 400  },
    { "Corn",  { ',', ';', '@' }, 250, 700, 450  }
};

//     { "Rice",  { '+', '*', '#' }, 10, 50, 10 },
//     { "Wheat", { '.', ':', '%' }, 15, 10, 2  },
//     { "Corn",  { ',', ';', '@' }, 20, 25, 5  }

void initCropDatabase(void)
{
    /* Static database: nothing to initialize. */
}

const CropType *getCropType(int cropType)
{
    if (cropType < 0 || cropType >= MAX_CROP_TYPES)
        return NULL;

    return &cropDatabase[cropType];
}

void updateCrop(CropTile *crop, int currentTick)
{
    if (!crop || !crop->occupied)
        return;

    const CropType *type = getCropType(crop->cropTile);
    if (!type)
        return;

    int age = currentTick - crop->plantedTick;
    if (age < 0)
        age = 0;

    int stage = age / type->growthTime;

    if (stage < 0)
        stage = 0;
    if (stage > 2)
        stage = 2;

    crop->growthStage = stage;
}

char getCropSymbol(const CropTile *crop)
{
    if (!crop || !crop->occupied)
        return ' ';

    const CropType *type = getCropType(crop->cropTile);
    if (!type)
        return '?';

    int stage = crop->growthStage;

    if (stage < 0)
        stage = 0;
    if (stage > 2)
        stage = 2;

    return type->stages[stage];
}

bool isCropMature(const CropTile *crop)
{
    if (!crop || !crop->occupied)
        return false;

    return crop->growthStage >= 2;
}