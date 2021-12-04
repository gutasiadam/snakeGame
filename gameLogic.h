
#ifndef SNAKEGAME_GAMELOGIC_H
#define SNAKEGAME_GAMELOGIC_H

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
/* Windows rendszeren:
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
 */
#include <stdbool.h>
#include "graphics.h"
#include "menus.h"

/*! \struct global_Settings
    \brief A játék fő beállításait("főflagek") tartalmazó struct
*/
typedef struct global_Settings{
    bool twoPlayerMode; /**< többjátékos mód kapcsoló */
    bool show_mainMenu; /**< Főmenü mutatása, hozzátartozó vezérlő bekapcsolása */
    bool init_mainMenu; /**< Főmenü renderelésének megkezdése */
    bool show_gameSettings; /**< Játék indítása előtti beállítások mutatása */
    bool show_mainGame; /**< Játék mutatása, vele együtt játék vezérlőinek engedélyezése */
    bool show_highScoreboard; /**< Dicsőségtábla mutatása, vele együtt dicsőségtábla vezérlőinek engedélyezése*/
    bool game_Init; /**< Játék inicializálása */
    bool exitGame; /**< Játékot bezáró folyamat elindítása */
    bool init_highScoreboard; /**< Dicsőségtábla előrenderelése */
    bool isRunning; /**< Fut-e a program */
}global_Settings;
extern global_Settings globalSettings;

void stopGame(global_Settings *g);

void mainMenu_init(global_Settings *g);
void mainMenuLogic(global_Settings *g);

void render_gameSettingsMenu(global_Settings *g);
void gameSettingsLogic(global_Settings *g,Snake *snake1,Snake *snake2);

void render_highScoresMenu(global_Settings *g,scoreBoard_highscores_Elements m);
void highScoresMenu_Logic(global_Settings *g,scoreBoard_highscores_Elements);
void inGameButtons(ButtonBox *buttons,int len);

void mainGame_Logic(global_Settings *g, Snake *snake1, Snake *snake2,scoreBoard_highscores *hS); //,scoreBoard_highscores hS
void randomize_snakePos(Snake *s);

void resetSnake(Snake *s1);
void resetSnakePoints(Snake *s1);
void P1_Controller(Snake *snake1, SDL_Event ev);
void P2_Controller(Snake *s2, SDL_Event ev);

void changeHighScoreList(Snake *s, const char* playerName,int idx, scoreBoard_highscores *h);
int checkScore(Snake *s, scoreBoard_highscores hS);
bool enter_text(char *where, size_t len, SDL_Rect box, SDL_Color backgroundColor, SDL_Color textColor);
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
void exitProgram(global_Settings *g,FILE *fp,scoreBoard_highscores *highscores);
void calculateNewScoreboard(scoreBoard_highscores *hS,Snake snake1, Snake snake2);
void highscore_subRoutine(int snakeIndex,scoreBoard_highscores *hS, Snake playerSnake,short whichSnake);
#endif //SNAKEGAME_GAMELOGIC_H

