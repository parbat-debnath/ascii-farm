#ifndef SAVE_H
#define SAVE_H

#include "../libraries/definitions.h"
#include <stdbool.h>

void saveGame(GameState *game);
void loadGame(GameState *game);
bool saveExists(void);
void createNewSave(GameState *game);

#endif