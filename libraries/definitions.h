#include <stdbool.h>
#include "constants.h"

typedef struct Position
{
    int x, y;
} Position;

typedef struct Player
{
    Position pos;
} Player;

typedef struct CropType
{
    char name[20];
    char stages[3];
    int growthTime;

    int seedPrice;
    int sellPrice;
} CropType;

typedef struct CropTile
{
    CropType type;
    int cropTile;
    int growthStage;
    int plantedTick;
    bool occupied;
} CropTile;

typedef struct Inventory
{
    int seeds[3];
    int crops[3];

} Inventory;

typedef struct Farm
{
    CropTile tiles[FARM_HEIGHT][FARM_WIDTH];

} Farm;

typedef struct GameState
{
    Player player;
    Farm farm;
    Inventory inventory;
    int money;
    int tick;
    int currentScreen;
    char message[100];
} GameState;

typedef struct graphics
{
    char **data;
    int width;
    int height;
} graphics;

typedef enum
{
    SCREEN_FARM,
    SCREEN_SHOP
} Screen;

typedef enum
{
    RICE,
    WHEAT,
    CORN
} CropID;