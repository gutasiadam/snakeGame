
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

void stopGame(global_Settings *g);

void mainMenu_init(TTF_Font *font1,TTF_Font *font2,global_Settings *g);
void mainMenuLogic(global_Settings *g);

void render_gameSettingsMenu(TTF_Font *font1, global_Settings *g);
void gameSettingsLogic(global_Settings *g,Snake *snake1,Snake *snake2);

void render_highScoresMenu(TTF_Font *font1,global_Settings *g,scoreBoard_highscores_Elements m);
void highScoresMenu_Logic(global_Settings *g,scoreBoard_highscores_Elements);
void inGameButtons(ButtonBox *buttons,TTF_Font *font1,TTF_Font *font2,int len);

void mainGame_Logic(TTF_Font *font1,TTF_Font *font2,global_Settings *g, Snake *snake1, Snake *snake2,scoreBoard_highscores *hS,SDL_TimerID fruitTimer); //,scoreBoard_highscores hS
void randomise_snakePos(Snake *s);

void resetSnake(Snake *s1);
void resetSnakePoints(Snake *s1);
void P1_Controller(Snake *snake1, SDL_Event ev);
void P2_Controller(Snake *s2, SDL_Event ev);

void changeHighScoreList(Snake *s, const char* playerName,int idx, scoreBoard_highscores *h);
int checkScore(Snake *s, scoreBoard_highscores hS);
bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer);



//Gyümölcsök
fruit* add_Fruit(fruit* firstFruit, SnakeBodyList snake1_L, SnakeBodyList snake2_L);
void destroyFruitList(fruit* fruitList);
fruit* checkCollision(fruit* fruitList,Snake s);
fruit* deleteFruit(fruit* fruitList,fruit *toBeDeleted);
bool checkIncomingFruitCollision(fruit newFruit,SnakeBodyList *s);

//Kígyótest
void add_BodyElement(SnakeBodyList *o,Snake s);
void init_SnakeBody(SnakeBodyList *sBody);
void moveBody(SnakeBodyList *s, Snake *sHead);
//void traverse_snakeBody(SnakeBodyList s);
void destroy_snakeBody(SnakeBodyList *s);
bool checkBodyCollision(SnakeBodyList *sList,Snake *sHead);
bool checkHeadCollision(Snake *sHead1, Snake *sHead2);
bool checkWallHit(Snake s);

//IO
void exitProgram(global_Settings *g,TTF_Font* font1,TTF_Font* font2,SDL_TimerID id,FILE *fp,scoreBoard_highscores *highscores);
void calculateNewScoreboard(TTF_Font* program_font1,scoreBoard_highscores *hS,Snake snake1, Snake snake2);
void highscore_subRoutine(int snakeIndex, TTF_Font* program_font1,scoreBoard_highscores *hS, Snake playerSnake,short whichSnake);
#endif //SNAKEGAME_GAMELOGIC_H

