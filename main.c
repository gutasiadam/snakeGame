#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <time.h>
#include "stdbool.h"

#include "Headers/gameLogic.h"

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
    IMG_Init(IMG_INIT_PNG);
    initSDL_everything();
    TTF_Init();
    TTF_Font *font1 = TTF_OpenFont("../resources/LiberationSerif-Regular.ttf", 30);
    TTF_Font *font2 = TTF_OpenFont("../resources/snake.ttf", 100);
    if (!font2) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }
    setFPS(60);
    Snake snake1={rand()%720,rand()%720,0,0,213,113,73,false,false,false,false};
    Snake snake2={720/2,720/2,0,0,109,152,134,false,false,false,false};
    SDL_Delay(500);
    //bool initMenu=true;
    int snakePoints=10;
    int mX,mY;
    int egyszer=1;
    scoreBoard_highscores highscores=loadScoreBoard(fp);
    scoreBoard_highscores_Elements highScoreMenu= create_highscores_menuElements(highscores);
    while (globalSettings.isRunning){
        SDL_Event event;
        SDL_WaitEvent(&event);
        if(globalSettings.init_mainMenu){
            printf("MainMenu\t");
            printCurrentSettings();
            mainMenu_init(font1,font2,&globalSettings);
            mainMenuLogic(&globalSettings);
            printf("Game init value: \t%d\n",globalSettings.game_Init);
            printCurrentSettings();
            SDL_RenderPresent(renderer);
        }
        if(globalSettings.show_gameSettings){
            //globalSettings.show_mainMenu=false;
            printf("Showing GameSettings.\n");
            printCurrentSettings();
            render_gameSettingsMenu(font1,&globalSettings);
            gameSettingsLogic(&globalSettings);
            printCurrentSettings();
        }
        if(globalSettings.init_highScoreboard){
            printf("initalizing HighScoreBoard.\n");
            //highscores=loadScoreBoard(fp);
            highScoreMenu= create_highscores_menuElements(highscores);
            render_highScoresMenu(font1,&globalSettings,highScoreMenu);
        }
        if(globalSettings.show_highScoreboard){
            /* szoveg bekerese */

            /* szoveg kirajzolasa */

            highScoresMenu_Logic(&globalSettings,highScoreMenu);
            //printf("Highscorebard logic waiting\n");
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
            mainGame_Logic(font1,font2,&globalSettings,&snake1,&snake2,&highscores);//,highscores
        }
        if(globalSettings.exitGame){
            SDL_RenderClear(renderer);
            stringRGBA(renderer, 110, 350, "SIKER! Kilepes.", 255, 255, 255, 255);
            globalSettings.isRunning=false;
        }
        SDL_RenderPresent(renderer);
    }

    globalSettings.isRunning=false;
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
    SDL_RemoveTimer(id);
    IMG_Quit();
    SDL_Delay(500);
    writeScoreBoardToFile(fp,highscores);
    fclose(fp);
    printf("Closing app");
    SDL_Quit();
    return 0;
}