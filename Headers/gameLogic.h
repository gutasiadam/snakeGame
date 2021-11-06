
#ifndef SNAKEGAME_GAMELOGIC_H
#define SNAKEGAME_GAMELOGIC_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include "graphics.h"
#include "menus.h"

/*! \struct global_Settings
    \brief A játék fő beállításait("főflagek") tartalmazó struct
*/
typedef struct global_Settings{
    bool twoPlayerMode; /**< többjátékos mód kapcsoló */
//bool quit=false;
    bool show_mainMenu; /**< Főmenü mutatása, hozzátartozó vezérlő bekapcsolása */
    bool init_mainMenu; /**< Főmenü renderelésének megkezdése */
    bool show_gameSettings; /**< Játék indítása előtti beállítások mutatása */
    bool init_gameSettings;
    bool drawn_gameSettings;
//bool menuItemsWereDrawn=false;
    bool show_mainGame; /**< Játék mutatása, vele együtt játék vezérlőinek engedélyezése */
    bool show_highScoreboard; /**< Dicsőségtábla mutatása, vele együtt dicsőségtábla vezérlőinek engedélyezése*/
    bool game_Init; /**< Játék inicializálása */
    bool exitGame; /**< Játékot bezáró folyamat elindítása */
    bool init_highScoreboard; /**< Dicsőségtábla előrenderelése */
    bool isRunning; /**< Fut-e a program */
}global_Settings;
extern global_Settings globalSettings;

void printCurrentSettings();

void stopGame(bool *isRunning);

void mainMenu_init(TTF_Font *font1,TTF_Font *font2,global_Settings *g);
void mainMenuLogic(global_Settings *g);

void render_gameSettingsMenu(TTF_Font *font1, global_Settings *g);
void gameSettingsLogic(global_Settings *g);

void render_highScoresMenu(TTF_Font *font1,global_Settings *g,scoreBoard_highscores_Elements m);
void highScoresMenu_Logic(global_Settings *g,scoreBoard_highscores_Elements);
void inGameButtons(ButtonBox *buttons,TTF_Font *font1,TTF_Font *font2,int len);

void mainGame_Logic(TTF_Font *font1,TTF_Font *font2,global_Settings *g, Snake *snake1, Snake *snake2,scoreBoard_highscores *hS); //,scoreBoard_highscores hS
void randomise_snakePos(Snake *s);

void resetSnake(Snake *s1);

void changeHighScoreList(Snake *s, const char* playerName,int idx, scoreBoard_highscores *h);
int checkScore(Snake *s, scoreBoard_highscores hS);
bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer);

#endif //SNAKEGAME_GAMELOGIC_H
