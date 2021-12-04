//
// Created by Gutási Ádám on 2021. 11. 01..
//

#ifndef SNAKEGAME_MENUS_H
#define SNAKEGAME_MENUS_H

/*! \file menus.h
    \brief A menükkal kapcsolatos függvényeket tartlalmazó modulhoz tartozó header.
*/

#include "io.h"

/*! \struct ButtonBox
    \brief Egy menü egy grafikai elemének adatait tartalmazó struct.
*/
typedef struct ButtonBox{
    int value; /**< A checkClick() funkció visszatérési értéke. Ezáltal lehet tovább vezérelni a programot. */
    int colorR; /**< A téglalap RGB piros színe */
    int colorG; /**< A téglalap RGB zöld színe */
    int colorB; /**< A téglalap RGB kék színe */
    int posX1; /**< A téglalap bal alsó sarkának x koordinátája */
    int posY1; /**< A téglalap bal alsó sarkának y koordinátája */
    int posX2; /**< A téglalap jobb felső sarkának x koordinátája */
    int posY2; /**< A téglalap jobb felső sarkának y koordinátája */
    char* text; /**< A téglalapban megjelenítendő szöveg */
    int textColorR; /**< A szöveg RGB piros színe */
    int textColorG; /**< A szöveg RGB zöld színe */
    int textColorB; /**< A szöveg RGB kék színe */
}ButtonBox;


/*! \struct scoreBoard_highscores_Elements
    \brief A dicsőségtábla elemeit tartalmazú struct.
*/
typedef struct scoreBoard_highscores_Elements{
    ButtonBox menuElements[11];/**< 11 hosszú tömb, benne a 10 legjobb játékos adataival és a visszalépés (X) gombbal */
}scoreBoard_highscores_Elements;


extern ButtonBox mainMenu[3]; /**< A főmenü grafikai adatait tartalmazza. */
extern ButtonBox gameSettingsMenu[10]; /**< A játék indítás előtti menüjénak adatait tartalmazza. */
extern ButtonBox gameSettingsMenu_multi[6];
extern ButtonBox inGameMenu[1];/**< A játék játék közbeni menüjénak adatait tartalmazza. */

/*! \fn scoreBoard_highscores_Elements create_highscores_menuElements(scoreBoard_highscores sB_H)
    \brief A dicsőségtábla betöltése ButtonBox -okba, így megjeleníthetővé téve azokat.


    \param sB_H A dicsőségtábla structja.
*/
scoreBoard_highscores_Elements create_highscores_menuElements(scoreBoard_highscores sB_H);

/*! \fn int checkClick(ButtonBox *buttons,int menuLen,int mousePosX, int mousePosY)
    \brief Megnézi, hogy az ablakban kattintás érvényes volt e, azaz, egy grafikai elemre történt-e a kattintás
    \return Ha érvényes a kattintás, visszatér az érvényes ButtonBox ButtonBox.value értékével. Egyébként -1 -et ad.
*/
int checkClick(ButtonBox *buttons,int menuLen,int mousePosX, int mousePosY);

#endif //SNAKEGAME_MENUS_H
