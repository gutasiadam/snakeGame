/*! \file main.c
    \brief A játék főmodulja.
    \warning Windows rendszeren ki kell hagyni a projekten belül minden olyan fájlnév elől a "../" karaktereket, ahol
    meg akarunk nyitni egy fájlt. pl.: fopen();
*/
/*
███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗
██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝
███████╗██╔██╗ ██║███████║█████╔╝ █████╗
╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝
███████║██║ ╚████║██║  ██║██║  ██╗███████╗
╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝
 Készítette: Gutási Ádám
 */
#include <stdlib.h>
#include <time.h>
#include "stdbool.h"

#include "gameLogic.h"
//#include "debugmalloc.h"

#include "menus.h"
#include "io.h"
#include "graphics.h"


int main(int argc, char *argv[]) {
    srand(time(0));
    globalSettings.isRunning=true;
    FILE *fp; /**< Dicsőségtáblát tartalmazó fájl.. */
    fp = fopen("../highscores.txt", "r+"); // Windows: ../-t elhagyni!
    initSDL_everything();
    setFPS(50);
    SnakeBody *snake1Body = NULL; SnakeBody *snake2Body = NULL;
    Snake snake1={0,0,0,0,213,113,73,0,snake1Body,'0'};
    Snake snake2={0,0,0,0,109,152,134,0,snake2Body,'0'};
    scoreBoard_highscores highscores=loadScoreBoard(fp);
    scoreBoard_highscores_Elements highScoreMenu= create_highscores_menuElements(highscores);
    while (globalSettings.isRunning){
        SDL_Event sdl_event;
        SDL_WaitEvent(&sdl_event);
        if(globalSettings.init_mainMenu){
            mainMenu_init(&globalSettings);
            mainMenuLogic(&globalSettings);
        }
        if(globalSettings.show_gameSettings){
            render_gameSettingsMenu(&globalSettings);
            gameSettingsLogic(&globalSettings,&snake1,&snake2);
        }
        if(globalSettings.init_highScoreboard){
            highScoreMenu= create_highscores_menuElements(highscores);
            render_highScoresMenu(&globalSettings,highScoreMenu);
        }
        if(globalSettings.show_highScoreboard){
            highScoresMenu_Logic(&globalSettings,highScoreMenu);
        }
        if(globalSettings.game_Init){
            randomize_snakePos(&snake1);
            if(globalSettings.twoPlayerMode){
                randomize_snakePos(&snake2);
            }
            globalSettings.game_Init=false;
            globalSettings.show_mainGame=true;
        }
        if(globalSettings.show_mainGame){
            mainGame_Logic(&globalSettings,&snake1,&snake2,&highscores);
        }
        if(globalSettings.exitGame){
            stopGame(&globalSettings);
        }
        SDL_RenderPresent(renderer);
    }
    exitProgram(&globalSettings,fp,&highscores);
    return 0;
}
