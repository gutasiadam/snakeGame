/*! \file io.c
    \brief A játék fájlkezeléssel foglalkozó adatait tartalmazó modul.
*/
#include "io.h"


/*! \fn scoreBoard_highscores loadScoreBoard(FILE* scoreboardTxt)
    \brief Betölti a dicsőségtábla adatait.
    Az eredmény alapján átállítja a játék globális beállításait.
    \param scoreboardTxt A dicsőségtábla adatait tartalmazó szüveges fájl.
    \return visszaad egy scoreBoard_highscores structot, benne a dicsőségtábla adataival.
*/
scoreBoard_highscores loadScoreBoard(FILE* scoreboardTxt){
    scoreBoard_highscores temp;
    highScorePlayer tempHi;
    rewind(scoreboardTxt);
    int i=0;
    for(i=0;i<10;i++) {
        tempHi.score = 0;
        strcpy(tempHi.name,"Töltsd fel te ezt a helyet!");
        temp.data[i] = tempHi;
    }
    i=0;
    while(fscanf(scoreboardTxt," %s\t%d",&tempHi.name,&tempHi.score)==2){
        temp.data[i++]=tempHi;
    }
    return temp;
}

/*! \fn writeScoreBoardToFile(FILE* scoreboardTxt,scoreBoard_highscores hS)
    \brief Elmenti a dicsőségtáblát egy külső fájlba
    \warning Windows rendszeren ki kell hagyni a fájlnév elől a "../" karaktereket!
    \param scoreboardTxt A dicsőségtábla adatait tartalmazó szüveges fájl.
    \param hS A program futása alatt a frissített dicsőségtáblát tartalmazó struct.
*/
void writeScoreBoardToFile(FILE* scoreboardTxt,scoreBoard_highscores hS){
    scoreboardTxt=freopen("../highscores.txt","w",scoreboardTxt); // Windows: ../-t elhagyni!
    rewind(scoreboardTxt);
    for(int i=0;i<10;i++){
        if(hS.data[i].score!=0)
        fprintf(scoreboardTxt,"%s\t%d\n",hS.data[i].name,hS.data[i].score);
    }

}
