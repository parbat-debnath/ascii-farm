#include "../libraries/definitions.h"

void clearScreen();
void drawHUD(GameState *game, int x, int y);
void drawMessage(GameState *game, int x, int y);
void drawPlayer(GameState *game);
void drawBorder();
void drawInventory(GameState *game, int x, int y);
void renderGraphic(graphics *g, int x, int y);
graphics loadGraphics(const char *filename);
void freeGraphics(graphics *g);
void renderFarm(Farm *f, int x, int y);
void drawShop(GameState *game, int x, int y);
void hideCursor();
void showCursor();