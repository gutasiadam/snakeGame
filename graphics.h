#ifndef SNAKEGAME_GRAPHICS_H
#define SNAKEGAME_GRAPHICS_H

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "menus.h"

typedef struct Window {
    int width;
    int height;
}Window;

typedef struct Snake{
    int x,y;
    double vx,vy;
    unsigned int r,g,b;
    bool up,down,left,right;
} Snake;

Uint32 add_waitEvent(Uint32 ms, void *param);

SDL_Event event;
SDL_Renderer *renderer;
SDL_Window *window;
SDL_TimerID id;
SDL_Surface *text_Surface;
SDL_Texture *text_Texture;
extern SDL_Rect hova;
TTF_Font *font;

extern int moveMentScale;
int initSDL_everything();
int renderText(TTF_Font *textFont,SDL_Surface *textSurface,
               SDL_Texture *textTexture, SDL_Rect where,
               int r, int g, int b, char* Text);
void renderMenu(const TTF_Font *textFont, SDL_Surface *textSurface, SDL_Texture *textTexture, SDL_Renderer *renderer,const ButtonBox *buttons, const int lenMenu);
void setFPS(int fps);

void renderFrame();

#endif //SNAKEGAME_GRAPHICS_H
