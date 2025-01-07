#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void reverse_generations(char *generations)
{
    int len = strlen(generations);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = generations[i];
        generations[i] = generations[len - i - 1];
        generations[len - i - 1] = temp;
    }
}