#ifndef INPUT_H
#define INPUT_H

#include "../libraries/definitions.h"

char getInput(void);
void processInput(GameState *game, char key);
bool isMovementKey(char key);

#endif