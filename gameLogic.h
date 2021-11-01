//
// Created by Gutási Ádám on 2021. 11. 01..
//

#ifndef SNAKEGAME_GAMELOGIC_H
#define SNAKEGAME_GAMELOGIC_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include "graphics.h"
#include "menus.h"

typedef struct global_Settings{
    bool twoPlayerMode;
//bool quit=false;
    bool show_mainMenu;
    bool init_mainMenu;
    bool show_gameSettings;
    bool init_gameSettings;
    bool drawn_gameSettings;
//bool menuItemsWereDrawn=false;
    bool show_mainGame;
    bool game_Init;
    bool exitGame;
}global_Settings;
extern global_Settings globalSettings;

extern bool twoPlayerMode;
//bool quit=false;
extern bool show_mainMenu;
extern bool init_mainMenu;
extern bool show_gameSettings;
extern bool init_gameSettings;
extern bool drawn_gameSettings;
//bool menuItemsWereDrawn=false;
extern bool show_mainGame;
extern bool game_Init;
extern bool exitGame;

void printCurrentSettings();

void stopGame(bool *isRunning);

void mainMenu_init(bool *f_show_mainMenu,bool *f_init_mainMenu, TTF_Font *font1,TTF_Font *font2);
void mainMenuLogic(bool *f_show_mainMenu, bool *f_exitGame, bool *f_show_gameSettings, bool *f_game_Init);

void gameSettingsMenu_init(bool *f_show_gameSettings, TTF_Font *font1);
void gameSettingsLogic(bool *f_show_gameSettings, bool *playerMode,bool *init_MainGame, bool *f_game_Init, bool *isRunning);

void inGameButtons(ButtonBox *buttons,TTF_Font *font1,TTF_Font *font2,int len);

void randomise_snakePos(Snake *s);

void resetSnake(Snake *s1);

#endif //SNAKEGAME_GAMELOGIC_H
