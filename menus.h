//
// Created by Gutási Ádám on 2021. 11. 01..
//

#ifndef SNAKEGAME_MENUS_H
#define SNAKEGAME_MENUS_H

#include "io.h"
typedef struct ButtonBox{
    int value;
    int colorR;
    int colorG;
    int colorB;
    int posX1;
    int posY1;
    int posX2;
    int posY2;
    char* text;
    int textColorR;
    int textColorG;
    int textColorB;
}ButtonBox;
extern ButtonBox mainMenu[3];
extern ButtonBox gameSettingsMenu[2];
extern ButtonBox inGameMenu_solo[2];
extern ButtonBox inGameMenu_multi[3];

ButtonBox create_highScore_menu_elements(dynamic_ScoreBoard const *sB, int const lenofScoreBoard);

int checkClick(ButtonBox *buttons,int menuLen,int mousePosX, int mousePosY);

#endif //SNAKEGAME_MENUS_H
