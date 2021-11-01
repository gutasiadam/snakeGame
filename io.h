//
// Created by Gutási Ádám on 2021. 11. 01..
//

#ifndef SNAKEGAME_IO_H
#define SNAKEGAME_IO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "string.h"

typedef struct highScorePlayer{
    char name[50];
    int score;
}highScorePlayer;

typedef struct dynamic_ScoreBoard {
    highScorePlayer *data;
    int size;
} dynamic_ScoreBoard;


int determine_countOfTopScores(FILE* scoreboardTxt);

bool allocate_memory_scoreboard(dynamic_ScoreBoard *dS, int size);
void print_dynamic_scoreboard(dynamic_ScoreBoard const *dS);
void destroy_dynamic_Scoreboard(dynamic_ScoreBoard *dS);
dynamic_ScoreBoard create_dynamic_Scoreboard(FILE* scoreBoardTxt);


void loadSettings();
void saveSettings();


#endif //SNAKEGAME_IO_H
