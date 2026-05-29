#include "../libraries/definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearScreen()
{
    printf("\033[2J\033[3J\033[H");
}

void drawHUD()
{
}

void drawMessage()
{
}

void drawPlayer()
{
}

void drawBorder()
{
}

void drawInventory()
{
}

void renderGraphic(graphics *g, int x, int y)
{
    for (int i = 0; i < g->height; i++)
    {
        printf("\033[%d;%dH%s", y + i, x, g->data[i]);
    }
    fflush(stdout);
}

graphics loadGraphics(const char *filename)
{
    const char *foldername = "assets/graphics/";
    char fullpath[256];
    sprintf(fullpath, "%s%s", foldername, filename);

    graphics g;

    FILE *fp = fopen(fullpath, "r");

    if (!fp)
    {
        printf("Couldn't load %s\n", fullpath);
        exit(1);
    }

    char buffer[512];

    g.height = 0;
    g.width = 0;

    while (fgets(buffer, sizeof(buffer), fp))
    {
        int len = strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n')
            len--;
        if (len > g.width)
            g.width = len;

        g.height++;
    }

    rewind(fp);

    g.data = malloc(sizeof(char *) * g.height);

    for (int i = 0; i < g.height; i++)
    {
        fgets(buffer, sizeof(buffer), fp);

        buffer[strcspn(buffer, "\n")] = '\0';
        g.data[i] = malloc(strlen(buffer) + 1);

        strcpy(g.data[i], buffer);
    }

    fclose(fp);

    return g;
}

void renderFarm(Farm *f, int x, int y)
{
    for (int i = 0; i < FARM_HEIGHT; i++)
    {
        for (int j = 0; j < FARM_WIDTH; j++)
        {
            if (f->tiles[i][j].occupied)
            {
                int growthStage = f->tiles[i][j].growthStage;
                char crop = f->tiles[i][j].type.stages[growthStage];

                printf("033[%d;%dH%c", y + i, x + j, crop);
            }
        }
    }
}