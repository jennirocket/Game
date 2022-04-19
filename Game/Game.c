//
//  Game.c
//  Game
//
//  Created by Jennifer Rakete on 22.05.20.
//  Copyright © 2020 Jennifer Rakete. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Riddles.h"
#include "Game.h"
#include "Highscore.h"

int keinZeichen = 0;

char *createRiddle (char const* const str ) {
    char* riddle = malloc(sizeof(str));
    if (riddle == NULL) {
        fprintf(stderr, "Kein Speicher mehr verfügbar!\n");
        EXIT_FAILURE;
    }
    for (int i = 0; i < (int) strlen(str); ++i) {
        if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)) {
            riddle[i] = '*';
        } else {
            riddle[i] = str[i];
            keinZeichen += 1;
        }
    }
    return riddle;
}
int uncoverLetter(char *riddle, const char *solution, char letter) {
    int count = 0;
    for (int i = 0; i < (int) strlen(solution); i++) {
        if (solution[i] == letter) {
            if (riddle[i] == '*') {
                riddle[i] = letter;
                ++count;
            }
        }
    }
    return count;
}
int gamingLoop(const char* solution) {
    char *riddle = createRiddle(solution);
    srand ((int)time (NULL));
    int spielerPunktzahl = 0;
    int punkteInsgesamt = 0;
    int count = 0;
    while (count < (int) strlen(solution) - keinZeichen) {
        printf("%s\n", riddle);
        punkteInsgesamt = ((rand() % 10) + 1) * 100;
        printf("Zu erreichende Punkte: %d\n", punkteInsgesamt);
        printf("Bitte gib einen Buchstaben ein: ");
        char letter;
        int x = scanf(" %c", &letter);
        if (x != 1) {
            printf("Ungültige Eingabe!\n");
        }
        int new = uncoverLetter(riddle, solution, letter);
        if (new > 0) {
            count += new;
            spielerPunktzahl += punkteInsgesamt;
        } else {
            spielerPunktzahl -= new;
        }
        printf("Erreichte Gesamtpunktzahl: %d\n", spielerPunktzahl);
    }
    printf("%s\n", solution);
    return spielerPunktzahl;
}
void startGame() {
    srand ((int)time (NULL));
    int x = gamingLoop(riddles[rand() % sizeof(riddles) / sizeof(riddles[0])]);
    char *filename = "game.txt";
    HSEntry *list = readHS(filename);
    if (isNewEntry(list, x)) {
        char * name = malloc(20);
        printf("Neuer Highscore! Bitte gib deinen Namen ein: ");
        scanf(" %s", name);
        addEntry(list, name, x);
        writeHS(filename, list);
    }
    printHighscores(list);
}
