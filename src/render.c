#include "./crop.h"
#include "./render.h"
#include "./shop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void gotoXY(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
}

void clearScreen()
{
    printf("\033[2J\033[3J\033[H");
}

void drawHUD(GameState *game, int x, int y)
{
    gotoXY(x, y + 1);
    printf("Money : %-5d", game->money);

    gotoXY(x, y + 2);
    printf("Screen: %-10s",
           (game->currentScreen == SCREEN_FARM) ? "FARM" : "SHOP");
    gotoXY(x, y + 3);
    printf("Selected: %s",
           game->selectedCropType == RICE ? "Rice" : game->selectedCropType == WHEAT ? "Wheat" : game->selectedCropType == CORN ? "Corn" : "None");
}

void drawMessage(GameState *game, int x, int y)
{
    gotoXY(x, y);
    printf("%-60s", game->message);
}

void drawPlayer(GameState *game)
{
    gotoXY(game->player.pos.x, game->player.pos.y);
    printf("P");
}

void drawBorder()
{
    int left = 0;
    int top = 0;
    int width = FARM_WIDTH + 2;
    int height = FARM_HEIGHT + 2;

    for (int x = 0; x < width; x++)
    {
        gotoXY(left + x, top);
        printf("#");

        gotoXY(left + x, top + height - 1);
        printf("#");
    }

    for (int y = 0; y < height; y++)
    {
        gotoXY(left, top + y);
        printf("#");

        gotoXY(left + width - 1, top + y);
        printf("#");
    }
}

void drawInventory(GameState *game, int x, int y)
{
    int line = y;
    const char *cropNames[MAX_CROP_TYPES] = {"Rice", "Wheat", "Corn"};

    gotoXY(x, line++);
    printf("Inventory");

    for (int i = 0; i < MAX_CROP_TYPES; i++)
    {
        gotoXY(x, line++);
        printf("%-5s seeds : %d", cropNames[i], game->inventory.seeds[i]);
    }

    line++;

    for (int i = 0; i < MAX_CROP_TYPES; i++)
    {
        gotoXY(x, line++);
        printf("%-5s crops : %d", cropNames[i], game->inventory.crops[i]);
    }
}

void renderGraphic(graphics *g, int x, int y)
{
    if (!g || !g->data)
        return;

    for (int i = 0; i < g->height; i++)
    {
        gotoXY(x, y + i);
        printf("%s", g->data[i]);
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
        int len = (int)strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n')
            len--;

        if (len > g.width)
            g.width = len;

        g.height++;
    }

    rewind(fp);

    g.data = malloc(sizeof(char *) * g.height);
    if (!g.data)
    {
        fclose(fp);
        printf("Out of memory while loading %s\n", fullpath);
        exit(1);
    }

    for (int i = 0; i < g.height; i++)
    {
        fgets(buffer, sizeof(buffer), fp);
        buffer[strcspn(buffer, "\n")] = '\0';

        g.data[i] = malloc(strlen(buffer) + 1);
        if (!g.data[i])
        {
            fclose(fp);
            printf("Out of memory while loading %s\n", fullpath);
            exit(1);
        }

        strcpy(g.data[i], buffer);
    }

    fclose(fp);
    return g;
}

void freeGraphics(graphics *g)
{
    if (!g || !g->data)
        return;

    for (int i = 0; i < g->height; i++)
    {
        free(g->data[i]);
    }

    free(g->data);
    g->data = NULL;
    g->height = 0;
    g->width = 0;
}

void renderFarm(Farm *f, int x, int y)
{
    for (int i = 0; i < FARM_HEIGHT; i++)
    {
        for (int j = 0; j < FARM_WIDTH; j++)
        {
            char ch = getCropSymbol(&f->tiles[i][j]);

            gotoXY(x + j, y + i);
            printf("%c", ch);
        }
    }

    fflush(stdout);
}

void drawShop(GameState *game, int x, int y)
{
    static graphics shopGraphic;
    static int loaded = 0;

    if (!loaded)
    {
        shopGraphic = loadGraphics("shop.txt");
        loaded = 1;
    }

    renderGraphic(&shopGraphic, x, y);
    fflush(stdout);
}

void hideCursor()
{
    printf("\033[?25l");
}

void showCursor()
{
    printf("\033[?25h");
}
