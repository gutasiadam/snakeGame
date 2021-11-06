/*! \file io.h
    \brief A játék fájlkezeléssel foglalkozó adatait tartalmazó modul.
*/

#ifndef SNAKEGAME_IO_H
#define SNAKEGAME_IO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "string.h"


/*! \struct highScorePlayer
    \brief A dicsőségtábla egy elemének az adatai.
*/
typedef struct highScorePlayer{
    char name[50]; /**< a játékos neve. Maximum 50 karakter hosszú. */
    int score; /**< A játékos eredménye. */
}highScorePlayer;

/*! \struct scoreBoard_highscores
    \brief A dicsőségtáblát tartalmazú struct
*/
typedef struct scoreBoard_highscores {
    highScorePlayer data[10]; /**< A játékosok adatait highScorePlayer structokban tartalmazó tömbje. */
} scoreBoard_highscores;

scoreBoard_highscores loadScoreBoard(FILE* scoreboardTxt);
void writeScoreBoardToFile(FILE* scoreboardTxt,scoreBoard_highscores hS);


void loadSettings();
void saveSettings();


#endif //SNAKEGAME_IO_H
