

/*
███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗
██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝
███████╗██╔██╗ ██║███████║█████╔╝ █████╗
╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝
███████║██║ ╚████║██║  ██║██║  ██╗███████╗
╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝
 Készítette: Gutási Ádám
 */
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "stdbool.h"

#include "Headers/gameLogic.h"
#include "Headers/debugmalloc.h"

#include "Headers/menus.h"
#include "Headers/io.h"
#include "Headers/graphics.h"
#include "Headers/gameLogic.h"

/*! \file main.c
    \brief A játék főmodulja.
*/
int main(int argc, char *argv[]) {
    srand(time(0));
    //bool isRunning=true;
    globalSettings.isRunning=true;
    FILE *fp; /**< Dicsőségtáblát tartalmazó fájl.. */
    fp = fopen("../resources/highscores.txt", "r+");
    initSDL_everything();

    setFPS(50);
    SnakeBody *snake1Body = NULL;
    SnakeBody *snake2Body = NULL;
    Snake snake1={rand()%720,rand()%720,0,0,213,113,73,0,snake1Body,false,false,false,false};
    Snake snake2={720/2,720/2,0,0,109,152,134,0,snake2Body,false,false,false,false};
    SDL_Delay(500);
    scoreBoard_highscores highscores=loadScoreBoard(fp);
    scoreBoard_highscores_Elements highScoreMenu= create_highscores_menuElements(highscores);
    while (globalSettings.isRunning){
        SDL_Event event;
        SDL_WaitEvent(&event);
        if(globalSettings.init_mainMenu){
            printf("MainMenu\t");
            mainMenu_init(font1,font2,&globalSettings);
            mainMenuLogic(&globalSettings);
            printf("Game init value: \t%d\n",globalSettings.game_Init);
            SDL_RenderPresent(renderer);
        }
        if(globalSettings.show_gameSettings){
            //globalSettings.show_mainMenu=false;
            printf("Showing GameSettings.\n");
            render_gameSettingsMenu(font1,&globalSettings);
            gameSettingsLogic(&globalSettings);
        }
        if(globalSettings.init_highScoreboard){
            printf("initalizing HighScoreBoard.\n");
            //highscores=loadScoreBoard(fp);
            highScoreMenu= create_highscores_menuElements(highscores);
            render_highScoresMenu(font1,&globalSettings,highScoreMenu);
        }
        if(globalSettings.show_highScoreboard){
            highScoresMenu_Logic(&globalSettings,highScoreMenu);
        }
        if(globalSettings.game_Init){
            randomise_snakePos(&snake1);
            if(globalSettings.twoPlayerMode){
                randomise_snakePos(&snake2);
            }
            globalSettings.game_Init=false;
            globalSettings.show_mainGame=true;
        }
        if(globalSettings.show_mainGame){
            mainGame_Logic(font1,font2,&globalSettings,&snake1,&snake2,&highscores,fruitShowTimer);
        }
        if(globalSettings.exitGame){
            stopGame(&globalSettings);
        }
        SDL_RenderPresent(renderer);
    }
    exitProgram(&globalSettings,font1,font2,id,fp,&highscores);
    return 0;
}