#ifndef SNAKEGAME_GRAPHICS_H
#define SNAKEGAME_GRAPHICS_H

/*! \file graphics.h
    \brief A játék grafikájával, renderelésével foglalkozó modul fejléce.
*/

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "menus.h"

/*! \struct Window
    \brief A megjelenítő ablak adatai
*/
typedef struct Window {
    int width; /**< Az ablak szélessége. */
    int height; /**< Az ablak magassága. */
}Window;

/*! \struct SnakeBody
    \brief A kígyó testét tartalmazó struct. A fej adatait nem tartalmazza, azt a Snake struct tárolja.
    Több SnakeBody struct együtt egy duplán láncolt listát alkot.
*/
typedef struct SnakeBody{
    int x; /**< A kígyótest egy elemének helyzete x koordináta szerint. */
    int y; /**< A kígyótest egy elemének helyzete y koordináta szerint. */
    struct SnakeBody *next; /**< A következő SnakeBody helye a memóriában. */
    struct SnakeBody *prev; /**< Az előző SnakeBody helye a memóriában */
}SnakeBody;

/*! \struct SnakeBodyEnclosing
    \brief A kígyó testének strázsája, és sentinelje.
*/
typedef struct SnakeBodyList{
    SnakeBody *head;  /**< Strázsa helye a memóriában. A strázsa kivételesen HASZNOS adatot tárol! Tárolja a kígyó fejének x és y helyét.*/
    SnakeBody *last;  /**< Sentinel helye a memőriában. */
}SnakeBodyList;

/*! \struct Snake
    \brief A kígyó, és fejének adatait tartalmazó struct.
*/
typedef struct Snake{
    int x; /**< A kígyó pozíciója x koordináta szerint. */
    int y; /**< A kígyó pozíciója y koordináta szerint. */
    double vx;/**< A kígyó x irányú sebessége */
    double vy; /**< A kígyó y irányú sebessége */
    unsigned int r; /**< A kígyó RGB kódban megadott piros színe. */
    unsigned int g; /**< A kígyó RGB kódban megadott zöld színe. */
    unsigned int b; /**< A kígyó RGB kódban megadott kék színe. */
    int points; /**< A kígyó pontszáma */
    struct SnakeBody *firstBodyElement;/**< Az első kígyótestre mutató pointer. */
    char lastPos; /**< A legutolsó irány, amerre a kígyó ment. Kezdőértéke 0. U: up, D: down, L: left, R: right. Ez akadályozza meg, hogy a kígyó beleforduljon a saját testébe. */
} Snake;



typedef struct fruit{
    int x; /**< A gyümölcs pozíciója x koordináta szerint. */
    int y; /**< A gyümölcs pozíciója y koordináta szerint. */
    SDL_Color color; /**< A gyümölcs színe */
    struct fruit *nextFruit; /**< A következő gyümölcs helye a memóriában. */
}fruit;


Uint32 add_waitEvent(Uint32 ms, void *param);

SDL_Event event;
SDL_Renderer *renderer;
SDL_Window *window;
SDL_TimerID id;
SDL_TimerID fruitShowTimer;
SDL_TimerID allow_snakeTimer;
SDL_Surface *text_Surface;
SDL_Texture *text_Texture;
SDL_Texture *fruitTexture;

extern SDL_Rect hova;
TTF_Font *font1;
TTF_Font *font2;

extern int moveMentScale;

/*! \fn int initSDL_everything()
    \brief Betölti az SDL grafikus könyvtár adatait.
    \return visszaad 1 -et, ha sikerült a betöltés.
*/
int initSDL_everything();
/*! \fn int renderText(TTF_Font *textFont,SDL_Surface *textSurface,SDL_Texture *textTexture, SDL_Rect where,int r, int g, int b, char* Text)
    \brief Kiír egy szöveget a befoglaló SDL_Rect-be, balra zártan
    \param textFont A használandó betűtípus.
    \param textSurface A renderernek szükséges felület, amire rárendereli majd a szöveget.
    \param textTexture A szöveg textúrája. Ezt felhasználva készíti majd el a renderer a megjeleníthető szöveget a textSurface -re.
    \param where Hova rendereljen majd ki a kijelzőn a renderer.
    \param r A szöveg RGB színének piros értéke.
    \param g A szöveg RGB színének zöld értéke.
    \param b A szöveg RGB színének kék értéke.
    \param Text A kiírandó szöveg.
    \return visszaad 1 -et, ha sikerült a betöltés.
*/
int renderText(TTF_Font *textFont,SDL_Surface *textSurface,SDL_Texture *textTexture, SDL_Rect where,int r, int g, int b, char* Text);

/*! \fn int renderText_middle(TTF_Font *textFont,SDL_Surface *textSurface,SDL_Texture *textTexture, SDL_Rect where,int r, int g, int b, char* Text)
    \brief Kiír egy szöveget a befoglaló SDL_Rect-be, azon belül középre.
    \param textFont A használandó betűtípus.
    \param textSurface A renderernek szükséges felület, amire rárendereli majd a szöveget.
    \param textTexture A szöveg textúrája. Ezt felhasználva készíti majd el a renderer a megjeleníthető szöveget a textSurface -re.
    \param where Hova rendereljen majd ki a kijelzőn a renderer.
    \param r A szöveg RGB színének piros értéke.
    \param g A szöveg RGB színének zöld értéke.
    \param b A szöveg RGB színének kék értéke.
    \param Text A kiírandó szöveg.
    \return visszaad 1 -et, ha sikerült a renderelés.
*/
int renderText_middle(TTF_Font *textFont,SDL_Surface *textSurface,SDL_Texture *textTexture, SDL_Rect where,int r, int g, int b, char* Text);
/*! \fn void renderMenu(const TTF_Font *textFont, SDL_Surface *textSurface,SDL_Texture *textTexture, SDL_Renderer *renderer,const ButtonBox *buttons, const int lenMenu)
    \brief Előkészít a renderer számára egy menüt. A szövegek balra zártan jelennek majd meg benne.
    \param textFont A használandó betűtípus.
    \param textSurface A renderernek szükséges felület, amire rárendereli majd a szöveget.
    \param textTexture A szöveg textúrája. Ezt felhasználva készíti majd el a renderer a megjeleníthető szöveget a textSurface -re.
    \param renderer Az SDL renderelője.
    \param buttons A megjelenítendő gombokat, grafikai elemeket tartalmazó ButtonBox struct.
    \param lenMenu A megjelenítendő grafikai elemek száma.
*/
void renderMenu(const TTF_Font *textFont, SDL_Surface *textSurface, SDL_Texture *textTexture, SDL_Renderer *renderer,const ButtonBox *buttons, const int lenMenu);
/*! \fn void renderMenu_middle(const TTF_Font *textFont, SDL_Surface *textSurface,SDL_Texture *textTexture, SDL_Renderer *renderer,const ButtonBox *buttons, const int lenMenu)
    \brief Előkészít a renderer számára egy menüt. A szövegek középre igazítva jelennek majd meg benne.
    \param textFont A használandó betűtípus.
    \param textSurface A renderernek szükséges felület, amire rárendereli majd a szöveget.
    \param textTexture A szöveg textúrája. Ezt felhasználva készíti majd el a renderer a megjeleníthető szöveget a textSurface -re.
    \param renderer Az SDL renderelője.
    \param buttons A megjelenítendő gombokat, grafikai elemeket tartalmazó ButtonBox struct.
    \param lenMenu A megjelenítendő grafikai elemek száma.
*/
void renderMenu_middle(const TTF_Font *textFont, SDL_Surface *textSurface, SDL_Texture *textTexture, SDL_Renderer *renderer,const ButtonBox *buttons, const int lenMenu);
/*! \fn void setFPS(int fps);
    \brief Beállítja, hány képkocka/másodperccel működjön a játék
    \param fps A beállítandó képkockasebesség.
*/


Uint32 allow_fruitRender(Uint32 ms, void *param);
Uint32 allow_moveSnake(Uint32 ms, void *param);

void setFPS(int fps);

void renderSnakeBody(SnakeBodyList *o,Snake s);
//void renderFrame();

#endif //SNAKEGAME_GRAPHICS_H
