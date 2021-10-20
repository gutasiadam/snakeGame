#include <stdio.h>
#include <stdbool.h>
#include "string.h"

typedef struct highScorePlayer{
    char name[50];
    int score;
}highScorePlayer;

typedef struct dynamic_ScoreBoard {
    highScorePlayer *data;
    int size;
} dynamic_ScoreBoard;


int determine_countOfTopScores(FILE* scoreboardTxt){
    int lineCount=0;
    char buffer[50];
    while(fscanf(scoreboardTxt,"%s",buffer)!=EOF){
        lineCount++;
    }
    return lineCount/2;
}

bool allocate_memory_scoreboard(dynamic_ScoreBoard *dS, int size){
    dS->size = size;
    dS->data = (highScorePlayer *) malloc(size* sizeof(highScorePlayer));
    return dS->size != 0;
}

void print_dynamic_scoreboard(dynamic_ScoreBoard const *dS){
    for(int i=0;i<dS->size;++i){
        printf("%s - %d\n",dS->data[i].name,dS->data[i].score);
    }
    printf("\nEOF\n");
}

void destroy_dynamic_Scoreboard(dynamic_ScoreBoard *dS){
    free(dS->data);
}

dynamic_ScoreBoard create_dynamic_Scoreboard(FILE* scoreBoardTxt){
    int lineCount=determine_countOfTopScores(scoreBoardTxt);
    dynamic_ScoreBoard scoreBoard;
    if(allocate_memory_scoreboard(&scoreBoard,lineCount)){
        printf("Memalloc success.\n");
        //load_data(scoreBoardTxt,lineCount,&scoreBoard);
        rewind(scoreBoardTxt);
        highScorePlayer temp;
        highScorePlayer *copyWhere=scoreBoard.data;
        while(fscanf(scoreBoardTxt," %s\t%d",&temp.name,&temp.score)==2){
            *copyWhere=temp;
            copyWhere++;
        }
        printf("LoadData Complete.\n");
    }
    //print_dynamic_scoreboard(&scoreBoard);
    return scoreBoard;
}


void loadSettings();
void saveSettings();
