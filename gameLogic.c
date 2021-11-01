
#include "gameLogic.h"
#include "graphics.h"

bool twoPlayerMode=true;
//bool quit=false;
bool show_mainMenu=true;
bool init_mainMenu=true;
bool show_gameSettings=false;
bool init_gameSettings=true;
bool drawn_gameSettings=false;
//bool menuItemsWereDrawn=false;
bool show_mainGame=false;
bool game_Init=false;
bool exitGame=false;

global_Settings globalSettings1={false,
true,
true,
false,
true,
false,
false,
false,
false
};
void printCurrentSettings(){
    return;
    printf("Settings:\nshow_mainMenu: %d\ninit_mainMenu: %d\nshow_gameSettings: %d\nshow_mainGame: %d\ngame_Init: %d\nexitGame: %d\n\n---\n",
           show_mainMenu,init_mainMenu,show_gameSettings,show_mainGame,game_Init,exitGame);
}

void stopGame(bool *isRunning){
    SDL_RenderClear(renderer);
    stringRGBA(renderer, 110, 350, "SIKER! Kilepes.", 255, 255, 255, 255);
    *isRunning=false;
}

void mainMenu_init(bool *f_show_mainMenu,bool *f_init_mainMenu, TTF_Font *font1,TTF_Font *font2){
    printf("InitMainMenu\n");
    boxRGBA(renderer,0,720,720,0,26,26,25,255);
    renderMenu(font1,text_Surface,text_Texture,renderer,mainMenu,3);
    SDL_Rect where={720/2,150};
    renderText(font2,text_Surface,text_Texture,where,78,159,61,"Snake");
    *f_init_mainMenu=false;
    *f_show_mainMenu=true;
    SDL_RenderPresent(renderer);
}
void mainMenuLogic(bool *f_show_mainMenu, bool *f_exitGame, bool *f_show_gameSettings, bool *f_game_Init){
    printf("MainMenuLogic ready.\n");
    while(*f_show_mainMenu){
        //printf("Waiting for input.\n");
        SDL_WaitEvent(&event);
        int mX, mY;
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        SDL_GetMouseState(&mX,&mY);
                        printf("Mouse @ %d %d",mX,mY);
                        switch(checkClick(mainMenu,3,mX,mY)){
                            case(1):
                                *f_show_gameSettings=true; //f_show_gameSettings=false;
                                //game=true; drawMainMenu=false;
                                // ;
                                f_game_Init=false;
                                return;
                                break;
                            case(2):
                                //drawHighScoreBoard=true;
                                //drawMainMenu=false;
                                return;
                                break;
                            case(3):
                                *f_show_mainMenu=false;
                                *f_exitGame=true;
                                //*quit=true;
                                return;
                                break;
                            default:
                                break;
                        }
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE: *f_show_gameSettings=true; *f_show_mainMenu=false; *f_game_Init=false; return; break;
                    case SDLK_x: *f_exitGame=true;  *f_show_mainMenu=false; return; break;// *quit=true;
                }
                break;
        }
        SDL_RenderPresent(renderer);
    }
}

void gameSettingsMenu_init(bool *f_show_gameSettings, TTF_Font *font1){
    boxRGBA(renderer,0,720,720,0,26,26,25,255);
    renderMenu(font1,text_Surface,text_Texture,renderer,gameSettingsMenu,2);
    SDL_Rect where={720/2,150};
    renderText(font1,text_Surface,text_Texture,where,78,159,61,"Játékosok száma");
    *f_show_gameSettings=true;
    //*display_Game=true;
    SDL_RenderPresent(renderer);
    printf("Menu display complete.\n");
}
void gameSettingsLogic(bool *f_show_gameSettings, bool *playerMode,bool *init_MainGame, bool *f_game_Init, bool *isRunning){
    int mX, mY;
    while(*f_show_gameSettings) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        SDL_GetMouseState(&mX, &mY);
                        printf("Mouse @ %d %d\n", mX, mY);
                        switch (checkClick(gameSettingsMenu, 2, mX, mY)) {
                            case (1):
                                *init_MainGame = true;
                                *f_show_gameSettings = false;
                                *f_game_Init = false;
                                *playerMode = false;
                                return;
                                break;
                            case (2):
                                *init_MainGame = true;
                                *f_show_gameSettings = false;
                                *f_game_Init = false;
                                *playerMode = true;
                                return;
                                break;
                            default:
                                return;
                                break;
                        }
                        break;
                }
                break;
        }
    }
}

void inGameButtons(ButtonBox *buttons,TTF_Font *font1,TTF_Font *font2,int len){
    //printf("RenderInGameButtons\n");
    //boxRGBA(renderer,0,720,720,0,26,26,25,255);
    renderMenu(font1,text_Surface,text_Texture,renderer,buttons,2);
    SDL_Rect where={720/2,150};
    //renderText(font2,text_Surface,text_Texture,where,78,159,61,"Snake");
    SDL_RenderPresent(renderer);
}

void randomise_snakePos(Snake *s){
    s->x=rand()%680;
    s->y=rand()%680;
    s->vx=0;
    s->vy=0;
}

void resetSnake(Snake *s1){
    s1->vx=0; s1->vy=0; s1->x=50; s1->y=50;
}

