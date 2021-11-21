#include "Headers/graphics.h"
#include "Headers/io.h"
#include "Headers/menus.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Headers/debugmalloc.h"




/*! \file graphics.c
    \brief A játék grafikájával, renderelésével foglalkozó modul.
*/
Uint32 add_waitEvent(Uint32 ms, void *param) {
    //Minden alkalommal, ha lejárt a timer, lefut ez a kód, betesz egy eseményt az SDl.
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

SDL_Rect hova = { 0, 0, 0, 0 };
int moveMentScale=80;
int initSDL_everything(){
    Window  programWindow={720,720};
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    else{ printf("SDL base init complete\n");}
    window = SDL_CreateWindow("snakeGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, programWindow.width, programWindow.height, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    else{ printf("SDL window complete\n");}
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    TTF_Init();
    font1 = TTF_OpenFont("../resources/LiberationSerif-Regular.ttf", 30);
    font2 = TTF_OpenFont("../resources/snake.ttf", 100);
    if (!font2) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }
    else{ printf("SDL renderer ready.\n");}
    IMG_Init(IMG_INIT_PNG);
    fruitTexture=IMG_LoadTexture(renderer,"../resources/images/apple.png");
    SDL_RenderClear(renderer);
    return 1;
}


int renderText(TTF_Font *textFont,SDL_Surface *textSurface, SDL_Texture *textTexture, SDL_Rect where, int r, int g, int b, char* Text){
    SDL_Color color={r,g,b};
    textSurface = TTF_RenderUTF8_Blended(textFont, Text, color);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    hova.x = where.x;//(720 - textSurface->w) / 2;
    hova.y = where.y;//100;
    //hova.w = where.w;
    //hova.h = where.h;
    hova.w = textSurface->w;
    hova.h = textSurface->h;
    //printf("%s %d %d %d %d\n",Text,hova.x,hova.y,hova.w,hova.h);

    SDL_RenderCopy(renderer, textTexture, NULL, &hova);
    SDL_FreeSurface(text_Surface);
    SDL_DestroyTexture(textTexture);
    return 1;
}

int renderText_middle(TTF_Font *textFont,SDL_Surface *textSurface, SDL_Texture *textTexture, SDL_Rect where, int r, int g, int b, char* Text){
    SDL_Color color={r,g,b};
    textSurface = TTF_RenderUTF8_Blended(textFont, Text, color);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    hova.x = (720 - textSurface->w) / 2;
    hova.y = where.y;//100;
    //hova.w = where.w;
    //hova.h = where.h;
    hova.w = textSurface->w;
    hova.h = textSurface->h;
    //printf("%s %d %d %d %d\n",Text,hova.x,hova.y,hova.w,hova.h);

    SDL_RenderCopy(renderer, textTexture, NULL, &hova);
    SDL_FreeSurface(text_Surface);
    SDL_DestroyTexture(textTexture);
    return 1;
}

void renderMenu_middle(const TTF_Font *textFont, SDL_Surface *textSurface, SDL_Texture *textTexture, SDL_Renderer *renderer,const ButtonBox *buttons, const int lenMenu){
    for(int i=0;i<lenMenu;i++){
        //printf("%d %d %d %d %d %d\n",buttons[i].posX1,buttons[i].posX2,buttons[i].posY2,buttons[i].posY1,buttons[i].colorG,buttons[i].colorB);
        boxRGBA(renderer,buttons[i].posX1,buttons[i].posY1,buttons[i].posX2,buttons[i].posY2,buttons[i].colorR,buttons[i].colorG,buttons[i].colorB,255);
        SDL_Rect where={buttons[i].posX1,buttons[i].posY1};
        renderText_middle(textFont,textSurface,textTexture,where,buttons[i].textColorR,buttons[i].textColorG,buttons[i].textColorB,buttons[i].text);
    }
}

void renderMenu(const TTF_Font *textFont, SDL_Surface *textSurface, SDL_Texture *textTexture, SDL_Renderer *renderer,const ButtonBox *buttons, const int lenMenu){
    for(int i=0;i<lenMenu;i++){
        //printf("%d %d %d %d %d %d\n",buttons[i].posX1,buttons[i].posX2,buttons[i].posY2,buttons[i].posY1,buttons[i].colorG,buttons[i].colorB);
        boxRGBA(renderer,buttons[i].posX1,buttons[i].posY1,buttons[i].posX2,buttons[i].posY2,buttons[i].colorR,buttons[i].colorG,buttons[i].colorB,255);
        SDL_Rect where={buttons[i].posX1,buttons[i].posY1};
        renderText(textFont,textSurface,textTexture,where,buttons[i].textColorR,buttons[i].textColorG,buttons[i].textColorB,buttons[i].text);
    }
}
void setFPS(int fps){
    id=SDL_AddTimer(1000/fps, add_waitEvent, NULL);
    //moveMentScale=720/(fps); //720: ablak szélessége
    moveMentScale=80;
}


void renderSnakeBody(SnakeBodyList *o,Snake s){
    if(o->head->next==o->last)
        return;
    SnakeBody *mov=o->last->prev;
    while(mov->prev!=NULL){
        boxRGBA(renderer,mov->x,mov->y,mov->x+20,mov->y+20,s.r,s.g,s.b,255);
        mov=mov->prev;
    }
}


Uint32 allow_fruitRender(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    ev.user.code=42;
    ev.user.data1=0;
    ev.user.data2=0;
    SDL_PushEvent(&ev);
    return ms;
}

Uint32 allow_moveSnake(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    ev.user.code=43;
    ev.user.data1=0;
    ev.user.data2=0;
    SDL_PushEvent(&ev);
    return ms;
}


