//
//  Highscore.h
//  Game
//
//  Created by Jennifer Rakete on 24.05.20.
//  Copyright © 2020 Jennifer Rakete. All rights reserved.
//

#ifndef Highscore_h
#define Highscore_h
#define HS_SIZE 10
#include <stdbool.h>

typedef struct {
    char name[20];
    int32_t points;
} HSEntry;

HSEntry* readHS( const char *filename );
void writeHS( const char *filename, const HSEntry *list );
bool isNewEntry( const HSEntry *list, int points );
void addEntry( HSEntry *list, const char *name, int points );
void printHighscores( HSEntry *list );
int cmp(const void *c, const void *d);

#endif
