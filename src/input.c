#include <stdbool.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>

bool isMovementKey(char key);

char getInput()
{
    return getch();
}

void processInput()
{
    char key = getInput();
    if(isMovementKey(key))
    {
        switch(toupper(key))
        {
            case 'W':
            {
                // move UP
                break;
            }
            case 'A':
            {
                // move LEFT
                break;
            }
            case 'D':
            {
                // move RIGHT
                break;
            }
            case 'S':
            {
                // move DOWN
                break;
            }
            default:
                printf("ERROR : Undefined movement key");
        }
    }
    else
    {
        switch(toupper(key))
        {
            case 'E':
            {
                // Open inventory
                break;
            }
            case 'M':
            {
                // Open shop
                break;
            }
            case 'Q':
            {
                // Quit game
                break;
            }
            case 'F':
            {
                // Go to field
                break;
            }
            case 'P':
            {
                // Plant seed
                break;
            }
            case 'H':
            {
                // Harvest Seed
                break;
            }
            default:
                printf("ERROR : Unknown key");
        }
    }
}

bool isMovementKey(char key)
{
    return key == 'a' || key == 's'
        || key == 'd' || key == 'w'
        || key == 'A' || key == 'S'
        || key == 'D' || key == 'W';
}