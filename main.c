#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <time.h>
#include "stdbool.h"

#include "gameLogic.h"

#include "menus.h"
#include "io.h"
#include "graphics.h"
#include "gameLogic.h"
/*Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}*/
int main(int argc, char *argv[]) {
    srand(time(0));
    bool isRunning=true;
    FILE *fp;
    fp = fopen("../resources/highscores.txt", "r");
    dynamic_ScoreBoard top10Players= create_dynamic_Scoreboard(fp);
    int len_highScoreBoard=5;
    //ButtonBox highScoreMenu[len_highScoreBoard]=create_highScore_menu_elements(&top10Players,len_highScoreBoard);
    destroy_dynamic_Scoreboard(&top10Players);
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
    int currPoint=snakePoints;
    int mX,mY;
    int egyszer=1;
    char pontszam[(int)((ceil(log10(1000))+1)*sizeof(char))];

    while (isRunning){
        SDL_Event event;
        SDL_WaitEvent(&event);
        if(init_mainMenu){
            printf("MainMenu");
            printCurrentSettings();
            mainMenu_init(&show_mainMenu,&init_mainMenu,font1,font2);
            mainMenuLogic(&show_mainMenu,&exitGame,&show_gameSettings,&game_Init);
            printf("Game init value: \t%d\n",game_Init);
            printCurrentSettings();
            SDL_RenderPresent(renderer);
        }
        if(show_gameSettings){
            show_mainMenu=false;
            printf("Showing GameSettings.\n");
            printCurrentSettings();
            gameSettingsMenu_init(&drawn_gameSettings,font1);
            gameSettingsLogic(&show_gameSettings,&twoPlayerMode,&show_mainGame,&game_Init,&isRunning);
            printCurrentSettings();
        }
        if(show_mainGame){

            if(!game_Init){
                randomise_snakePos(&snake1);
                if(twoPlayerMode)
                    randomise_snakePos(&snake2);
                game_Init=true;
            }
            switch (event.type){
                case SDL_QUIT:
                    isRunning=false;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT: snake1.left = false; break;
                        case SDLK_RIGHT: snake1.right = false; break;
                        case SDLK_UP: snake1.up = false; break;
                        case SDLK_DOWN: snake1.down=false; break;
                        case SDLK_x: exitGame=true; break;

                        case SDLK_w: if(twoPlayerMode){snake2.up = false;}break;
                        case SDLK_a: if(twoPlayerMode){snake2.down = false;} break;
                        case SDLK_s: if(twoPlayerMode){snake2.left = false;} break;
                        case SDLK_d: if(twoPlayerMode){snake2.right=false;} break;

                        case SDLK_BACKSPACE:
                            SDL_RenderClear(renderer);
                            show_mainGame=false; init_mainMenu=true;  init_gameSettings=false;  game_Init=false; show_gameSettings=false;//menuItemsWereDrawn=false;
                            printCurrentSettings();
                            resetSnake(&snake1);
                            resetSnake(&snake2);
                            break;
                    }
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            snake1.left = true;
                            snake1.vx=-0.25*moveMentScale;
                            snake1.vy=0;
                            break;
                        case SDLK_RIGHT:
                            snake1.right = true;
                            snake1.vx=0.25*moveMentScale;
                            snake1.vy=0;
                            snakePoints++;
                            printf("%d\n",snakePoints);
                            break;
                        case SDLK_UP:
                            snake1.up = true;
                            snake1.vx=0;
                            snake1.vy=(-0.25)*moveMentScale;
                            break;
                        case SDLK_DOWN:
                            snake1.down=true;
                            snake1.vx=0;
                            snake1.vy=0.25*moveMentScale;
                            break;
                        case SDLK_a:
                            if(twoPlayerMode) {
                                snake2.left = true;
                                snake2.vx = -0.25 * moveMentScale;
                                snake2.vy = 0;
                            }
                            break;
                        case SDLK_d:
                            if(twoPlayerMode) {
                                snake2.right = true;
                                snake2.vx = 0.25 * moveMentScale;
                                snake2.vy = 0;
                            }
                            break;
                        case SDLK_w:
                            if(twoPlayerMode) {
                                snake2.up = true;
                                snake2.vx = 0;
                                snake2.vy = (-0.25) * moveMentScale;
                            }
                            break;
                        case SDLK_s:
                            if(twoPlayerMode) {
                                snake2.down = true;
                                snake2.vx = 0;
                                snake2.vy = 0.25 * moveMentScale;
                            }
                            break;
                    }
                    break;
                case SDL_USEREVENT:
                    /* kitoroljuk az elozo poziciojabol (nagyjabol) */
                    //boxRGBA(renderer,snake1.x,snake1.y,snake1.x-20,snake1.y-20,0,0,0,255);
                    snake1.x+=snake1.vx;
                    snake1.y+=snake1.vy;
                    if (snake1.x<20 || snake1.x>=720 || snake1.y<20 || snake1.y>=600){
                        show_mainGame=false; init_mainMenu=true;  init_gameSettings=false;  game_Init=false; show_gameSettings=false;
                        resetSnake(&snake1);
                        resetSnake(&snake2);
                        printCurrentSettings();
                    }
                    if(twoPlayerMode){
                        snake2.x+=snake2.vx;
                        snake2.y+=snake2.vy;
                        if (snake2.x<20 || snake2.x>=720 || snake2.y<20 || snake2.y>=600){
                            show_mainGame=false; init_mainMenu=true;  init_gameSettings=false;  game_Init=false; show_gameSettings=false;
                            resetSnake(&snake1);
                            resetSnake(&snake2);
                            printCurrentSettings();
                        }
                    }

                    /* ujra kirajzolas, mehet a kepernyore */
                    boxRGBA(renderer,0,600,720,0,217,202,179,255);//pálya
                    boxRGBA(renderer,0,600,720,0,255,0,0,20);
                    boxRGBA(renderer,snake1.x,snake1.y,snake1.x-20,snake1.y-20,snake1.r,snake1.g,snake1.b,255);
                    if(twoPlayerMode){
                        boxRGBA(renderer,snake2.x,snake2.y,snake2.x-20,snake2.y-20,snake2.r,snake2.g,snake2.b,255);
                    }

                    SDL_Rect renderPoints={0,650,0,0};
                    sprintf(pontszam, "%d", currPoint);
                    if(egyszer==1){
                        if(!twoPlayerMode){
                            inGameButtons(inGameMenu_solo,font1,font2,2);
                        }else{
                            inGameButtons(inGameMenu_multi,font1,font2,3);
                        }
                        renderText(font1,text_Surface,text_Texture,renderPoints,255,255,255,pontszam);
                        egyszer=0;
                    }
                    //printf("%d %d",currPoint, snakePoints);
                    if(currPoint!=snakePoints){
                        sprintf(pontszam, "%d", currPoint);
                        printf("Updating");
                        if(!twoPlayerMode){
                            inGameButtons(inGameMenu_solo,font1,font2,2);
                        }else{
                            inGameButtons(inGameMenu_multi,font1,font2,3);
                        }
                        renderText(font1,text_Surface,text_Texture,renderPoints,255,255,255,pontszam);
                        currPoint=snakePoints;
                    }
                    break;

            }
        }
        if(exitGame){
            SDL_RenderClear(renderer);
            stringRGBA(renderer, 110, 350, "SIKER! Kilepes.", 255, 255, 255, 255);
            isRunning=false;
        }
        SDL_RenderPresent(renderer);
    }

    isRunning=false;
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
    SDL_RemoveTimer(id);
    IMG_Quit();
    SDL_Delay(500);
    printf("Closing app");
    SDL_Quit();
    return 0;
}