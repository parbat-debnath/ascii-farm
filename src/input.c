#include "../libraries/definitions.h"
#include "../libraries/constants.h"
#include "./input.h"
#include "./game.h"
#include "./shop.h"
#include "./farm.h"
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static char normalizeKey(char key)
{
    return (char)toupper((unsigned char)key);
}

static void setShopCodeInput()
{
    printf("\033[?25h");
    printf("\033[%d;%dH", 23, 78);
}

char getInput(void)
{
    return (char)getch();
}

bool isMovementKey(char key)
{
    key = normalizeKey(key);

    return key == 'W' ||
           key == 'A' ||
           key == 'S' ||
           key == 'D';
}

static void movePlayer(GameState *game, int dx, int dy)
{
    int newX = game->player.pos.x + dx;
    int newY = game->player.pos.y + dy;

    if (newX < FARM_START_X)
        newX = FARM_START_X;
    if (newX >= FARM_WIDTH + FARM_START_X)
        newX = FARM_WIDTH + FARM_START_X - 1;

    if (newY < FARM_START_Y)
        newY = FARM_START_Y;
    if (newY >= FARM_HEIGHT + FARM_START_Y)
        newY = FARM_HEIGHT + FARM_START_Y - 1;

    game->player.pos.x = newX;
    game->player.pos.y = newY;
}

static int getFirstAvailableSeedType(GameState *game)
{
    for (int i = 0; i < MAX_CROP_TYPES; i++)
    {
        if (game->inventory.seeds[i] > 0)
            return i;
    }

    return -1;
}

void processInput(GameState *game, char key)
{
    if (!game)
        return;

    key = normalizeKey(key);

    if (game->currentScreen == SCREEN_FARM)
    {
        switch (key)
        {
        case 'W':
            movePlayer(game, 0, -1);
            break;

        case 'A':
            movePlayer(game, -1, 0);
            break;

        case 'S':
            movePlayer(game, 0, 1);
            break;

        case 'D':
            movePlayer(game, 1, 0);
            break;

        case 'M':
            enterShop();
            break;

        case 'P':
        {
            int cropType = getFirstAvailableSeedType(game);

            if (cropType == -1)
            {
                strcpy(game->message, "No seeds available.");
                break;
            }

            plantCrop(
                game,
                game->player.pos.x - FARM_START_X,
                game->player.pos.y - FARM_START_Y,
                cropType);
            break;
        }

        case 'H':
            harvestCrop(
                game,
                game->player.pos.x - FARM_START_X,
                game->player.pos.y - FARM_START_Y);
            break;

        case 'Q':
            shutdownGame();
            break;

        default:
            break;
        }
    }
    else if (game->currentScreen == SCREEN_SHOP)
    {

        // User will enter 'C' to enter code

        switch (key)
        {
        case 'C':
            setShopCodeInput();
            char mode;
            int option, qty;

            scanf(" %c %d %d", &mode, &option, &qty);
            printf("\033[?25l");


            mode = toupper(mode);

            switch (mode)
            {
            case 'B':
                if (option < 1 || option > MAX_CROP_TYPES)
                {
                    strcpy(game->message, "Invalid transaction code entered.");
                    return;
                }

                buySeed(option - 1, qty);
                break;

            case 'S':
                if (option < MAX_CROP_TYPES + 1 || option > MAX_CROP_TYPES * 2)
                {
                    strcpy(game->message, "Invalid transaction code entered.");
                    return;
                }

                sellCrop(option - MAX_CROP_TYPES - 1, qty);
                break;
            }
            break;

        case 'F':
        case 27:
            game->currentScreen = SCREEN_FARM;
            strcpy(game->message, "Back to the farm.");
            break;

        case 'Q':
            shutdownGame();
            break;

        default:
            break;
        }

        // switch (key)
        // {
        //     case '1':
        //         buySeed(RICE, 1);
        //         break;

        //     case '2':
        //         buySeed(WHEAT, 1);
        //         break;

        //     case '3':
        //         buySeed(CORN, 1);
        //         break;

        //     case 'Z':
        //         sellCrop(RICE, 1);
        //         break;

        //     case 'X':
        //         sellCrop(WHEAT, 1);
        //         break;

        //     case 'C':
        //         sellCrop(CORN, 1);
        //         break;

        //
        // }
    }
}