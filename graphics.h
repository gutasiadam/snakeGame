#ifndef SNAKEGAME_GRAPHICS_H
#define SNAKEGAME_GRAPHICS_H

/*! \file graphics.h
    \brief A játék grafikájával, renderelésével foglalkozó modul fejléce.
*/

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_ttf.h"
/* Wndows rendszeren:
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
 */
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

/*! \struct SnakeBodyList
    \brief A kígyó testének strázsája, és sentinelje.
*/
typedef struct SnakeBodyList{
    SnakeBody *head;  /**< Strázsa helye a memóriában. A strázsa HASZNOS adatot tárol! Ide másolódik a kígyó fejének x és y koordinátája.*/
    SnakeBody *last;  /**< Sentinel helye a memőriában. */
}SnakeBodyList;

/*! \struct Snake
    \brief A kígyó, és fejének adatait tartalmazó struct.
*/
typedef struct Snake{
    int x; /**< A kígyó fejének pozíciója x koordináta szerint. */
    int y; /**< A kígyó fejének pozíciója y koordináta szerint. */
    double vx;/**< A kígyó fejének x irányú sebessége */
    double vy; /**< A kígyó fejének y irányú sebessége */
    unsigned int r; /**< A kígyó színének RGB bontásban vett piros színe. */
    unsigned int g; /**< A kígyó RGB bontásban vett zöld színe. */
    unsigned int b; /**< A kígyó RGB bontásban vett kék színe. */
    int points; /**< A kígyó pontszáma */
    struct SnakeBody *firstBodyElement;/**< Az első kígyótestre mutató pointer. */
    char lastPos; /**< A legutolsó irány, amerre a kígyó ment. Kezdőértéke 0. U: up, D: down, L: left, R: right. Ez akadályozza meg, hogy a kígyó beleforduljon a saját testébe. */
} Snake;

/*! \struct fruit
    \brief Egy gyümölcs adatait tartalmazó struct.
*/
typedef struct fruit{
    int x; /**< A gyümölcs pozíciója x koordináta szerint. */
    int y; /**< A gyümölcs pozíciója y koordináta szerint. */
    SDL_Color color; /**< A gyümölcs színe */
    struct fruit *nextFruit; /**< A következő gyümölcs helye a memóriában. */
}fruit;


Uint32 add_waitEvent(Uint32 ms, void *param);

SDL_Event event;
SDL_Renderer *renderer; /**< A futás alatt használt megjelenítő */
SDL_Window *window; /**< Az ablak, amiben a játék fut. */
SDL_TimerID id; /**< A megfelelő képcsokasebesség betartásáért felelős időzítő. */
SDL_Surface *text_Surface;
SDL_Texture *text_Texture;

extern SDL_Rect rect_where; /**< Tartalmazza, hova másolódjona  kijelzőn egy textúra. lásd: renderText() függvény. */
TTF_Font *font1; /**< Elsődleges betűtípus. */
TTF_Font *font2; /**< Másodlagos betűtípus. */

extern int moveMentScale; /**< Szorzó, amivel a mozgás finomhangolható. Mivel a kígyó egy-egy eleme 20x20px méretű, a
 P1_Controller()  és a P2_Controller() 0.25-értéket ad a sebességekhez, a moveMentscale alapértelmezetten 80, hogy 20px
 távot tegyen meg a kígyó egy-egy mozgásnál. */

/*! \fn int initSDL_everything()
    \brief Betölti a játékhoz szükséges SDL könyvtárat, illetve az SDL2gfx további szükséges almoduljait.

    Ha valamelyik almodul betöltése sikertelen, akkor a programot a
    hibatáblázatban megfelelő kóddal megállítja.

    (Kódszám, és a hozzátartozó hiba)
     #|   Hiba jelentése
     1|   Nem indítható az SDL.
     2|   Nem hozható létre az ablak.
     3|   Nem hozható létre a renderer (megjelenítő).
     4|   Nem sikerült betölteni az 1. fontot.
     5|   Nem sikerült betölteni a 2. fontot.


    \return visszaad 1 -et, ha sikerült a betöltés.
*/
int initSDL_everything();
/*! \fn int renderText(TTF_Font *textFont,SDL_Surface *textSurface,SDL_Texture *textTexture, SDL_Rect where,int r, int g, int b, char* Text)
    \brief Kiír egy szöveget a befoglaló SDL_Rect -be, annak a közepére.
    \param textFont A használandó betűtípus.
    \param textSurface A RAM-ban tárolt, szoftveresen renderelt pixelhalmaz.
    \param textTexture A VRAM-ban tárolt, szoftveresen renderelt pixelhalmaz.
    \param where SDL_Rect, amibe a szöveget renderelni kell
    \param r A szöveg RGB színének piros értéke.
    \param g A szöveg RGB színének zöld értéke.
    \param b A szöveg RGB színének kék értéke.
    \param Text A kiírandó szöveg.
    \return visszaad 1 -et, ha sikerült a betöltés. Ha nagyobb a szöveg, mint a cél téglalap, akkor is kiírja a szöveget.
    Ekkor az kilóg a téglalapból.
*/
int renderText(TTF_Font *textFont,SDL_Surface *textSurface,SDL_Texture *textTexture, SDL_Rect where,int r, int g, int b, char* Text);

/*! \fn void renderMenu(const TTF_Font *textFont, SDL_Surface *textSurface, SDL_Texture *textTexture,const ButtonBox *buttons, int lenMenu)
    \brief Előkészít a renderer számára egy menüt. A szövegek balra zártan jelennek majd meg benne.
    \param textFont A használandó betűtípus.
    \param textSurface A renderernek szükséges felület, amire rárendereli majd a szöveget.
    \param textTexture A szöveg textúrája. Ezt felhasználva készíti majd el a renderer a megjeleníthető szöveget a textSurface -re.
    \param renderer Az SDL renderelője.
    \param buttons A megjelenítendő gombokat, grafikai elemeket tartalmazó ButtonBox struct.
    \param lenMenu A megjelenítendő grafikai elemek száma.
*/
void renderMenu(TTF_Font *textFont, SDL_Surface *textSurface, SDL_Texture *textTexture,ButtonBox *buttons, int lenMenu);
/*! \fn void renderMenu_middle(const TTF_Font *textFont, SDL_Surface *textSurface, SDL_Texture *textTexture,const ButtonBox *buttons, int lenMenu)
    \brief Előkészít a renderer számára egy menüt. A szövegek középre igazítva jelennek majd meg benne.
    \param textFont A használandó betűtípus.
    \param textSurface A RAM-ban tárolt, szoftveresen renderelt pixelhalmaz.
    \param textTexture A VRAM-ban tárolt, szoftveresen renderelt pixelhalmaz.
    \param buttons A megjelenítendő gombokat, grafikai elemeket tartalmazó ButtonBox struct.
    \param lenMenu A megjelenítendő grafikai elemek száma.
*/
void renderMenu_middle(TTF_Font *textFont, SDL_Surface *textSurface, SDL_Texture *textTexture, ButtonBox *buttons, int lenMenu);
/*! \fn void setFPS(int fps);
    \brief Beállítja, hány képkocka/másodperccel működjön a játék
    \param fps A beállítandó képkockasebesség.
*/

/*! \fn Uint32 allow_fruitAdd(Uint32 ms, void *param)
    \brief Engedélyez egy gyümölcs hozzáadását.
    \param ms Az idő, amit két engedélyezés közt várjon a függvény
    \param param Egyéb poaraméterek, ha vannak
    \return Betesz egy SDL_USEREVENT eseményt az event stackra. Ennek az eventnek 42-es számú egyedi kódot ad.

*/
Uint32 allow_fruitAdd(Uint32 ms, void *param);

/*! \fn Uint32 allow_moveSnake(Uint32 ms, void *param)
    \brief Engedélyezi a kígyó mozgatását.
    \param ms Az idő, amit két engedélyezés közt várjon a függvény
    \param param Egyéb poaraméterek, ha vannak
    \return Betesz egy SDL_USEREVENT eseményt az event stackra. Ennek az eventnek 43-as számú egyedi kódot ad.

*/
Uint32 allow_moveSnake(Uint32 ms, void *param);

/*! \fn void renderFruits(fruit *fruitList)
    \brief Megjeleníti a gyümölcsöket,
    \param fruitList A gyümölcsöket tartalmazó láncolt lista első elemére mutató pointer.
    \return Azonnal visszatér, ha fruitList NULL-ra mutat. .
*/
void renderFruits(fruit *fruitList);

/*! \fn void renderSnakeBody(SnakeBodyList *o,Snake s)
    \brief Megjeleníti a kígyó testét.
    \param o A Kígyó testének strázsáját és sentineljét tartalmazza.
    \param s A Kígyó feje, és az adaiatit tartalmazó Snake struct.
*/
void renderSnakeBody(SnakeBodyList *o,Snake s);

void setFPS(int fps);


#endif
