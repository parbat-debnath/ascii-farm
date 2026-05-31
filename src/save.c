#include "./save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAVE_PATH "saves/save.dat"
#define SAVE_MAGIC "ASCFARM"
#define SAVE_VERSION 1u

typedef struct
{
    char magic[8];
    unsigned int version;
    GameState game;
} SaveFile;

bool saveExists(void)
{
    FILE *fp = fopen(SAVE_PATH, "rb");
    if (!fp)
        return false;

    fclose(fp);
    return true;
}

void saveGame(GameState *game)
{
    if (!game)
        return;

    FILE *fp = fopen(SAVE_PATH, "wb");
    if (!fp)
    {
        printf("Failed to open save file for writing.\n");
        return;
    }

    SaveFile saveData;
    memset(&saveData, 0, sizeof(saveData));

    memcpy(saveData.magic, SAVE_MAGIC, strlen(SAVE_MAGIC));
    saveData.version = SAVE_VERSION;
    saveData.game = *game;

    if (fwrite(&saveData, sizeof(saveData), 1, fp) != 1)
    {
        printf("Failed to write save file.\n");
        fclose(fp);
        return;
    }

    fclose(fp);
}

void createNewSave(GameState *game)
{
    if (!game)
        return;

    saveGame(game);
}

void loadGame(GameState *game)
{
    if (!game)
        return;

    if (!saveExists())
    {
        createNewSave(game);
        return;
    }

    FILE *fp = fopen(SAVE_PATH, "rb");
    if (!fp)
    {
        printf("Failed to open save file for reading.\n");
        return;
    }

    SaveFile saveData;
    memset(&saveData, 0, sizeof(saveData));

    if (fread(&saveData, sizeof(saveData), 1, fp) != 1)
    {
        printf("Failed to read save file.\n");
        fclose(fp);
        return;
    }

    fclose(fp);

    if (strncmp(saveData.magic, SAVE_MAGIC, strlen(SAVE_MAGIC)) != 0 ||
        saveData.version != SAVE_VERSION)
    {
        printf("Save file is invalid or outdated.\n");
        createNewSave(game);
        return;
    }

    *game = saveData.game;
}