#include "graphics.h"
#include "io.h"
#include "menus.h"
#include "debugmalloc.h"

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
        //SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    //else{ printf("SDL base init complete\n");}
    window = SDL_CreateWindow("snakeGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, programWindow.width, programWindow.height, 0);
    if (window == NULL) {
        //SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(2);
    }
    //else{ printf("SDL window complete\n");}
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        //SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(3);
    }
    TTF_Init();
    font1 = TTF_OpenFont("../LiberationSerif-Regular.ttf", 30); // Windows: ../-t elhagyni!
    if (!font1) {
        //SDL_Log("Nem sikerult megnyitni az 1. fontot! %s\n", TTF_GetError());
        exit(4);
    }
    font2 = TTF_OpenFont("../snake.ttf", 100); // Windows: ../-t elhagyni!
    if (!font2) {
        //SDL_Log("Nem sikerult megnyitni a 2. fontot! %s\n", TTF_GetError());
        exit(5);
    }
    //else{ printf("SDL renderer ready.\n");}
    SDL_RenderClear(renderer);
    return 1;
}

int renderText(TTF_Font *textFont,SDL_Surface *textSurface, SDL_Texture *textTexture, SDL_Rect where, int r, int g, int b, char* Text){
    SDL_Color color={r,g,b};
    textSurface = TTF_RenderUTF8_Blended(textFont, Text, color);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    hova.x=(where.x+(where.w/2)-(textSurface->w/2));
    hova.y=(where.y+(where.h/2)-(textSurface->h/2));

    hova.w=textSurface->w;
    hova.h=textSurface->h;

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
    hova.w = textSurface->w;
    hova.h = textSurface->h;

    SDL_RenderCopy(renderer, textTexture, NULL, &hova);
    SDL_FreeSurface(text_Surface);
    SDL_DestroyTexture(textTexture);
    return 1;
}

void renderMenu_middle(TTF_Font *textFont, SDL_Surface *textSurface, SDL_Texture *textTexture,ButtonBox *buttons, int lenMenu){
    for(int i=0;i<lenMenu;i++){
        boxRGBA(renderer,buttons[i].posX1,buttons[i].posY1,buttons[i].posX2,buttons[i].posY2,buttons[i].colorR,buttons[i].colorG,buttons[i].colorB,255);
        SDL_Rect where={buttons[i].posX1,buttons[i].posY1,buttons[i].posX2-buttons[i].posX1,buttons[i].posY2-buttons[i].posY1};
        if(strcmp(buttons[i].text,"")!=0){
            renderText(textFont,textSurface,textTexture,where,buttons[i].textColorR,buttons[i].textColorG,buttons[i].textColorB,buttons[i].text);
        }
    }
}

void renderMenu(TTF_Font *textFont, SDL_Surface *textSurface, SDL_Texture *textTexture,ButtonBox *buttons,int lenMenu){
    for(int i=0;i<lenMenu;i++){
        boxRGBA(renderer,buttons[i].posX1,buttons[i].posY1,buttons[i].posX2,buttons[i].posY2,buttons[i].colorR,buttons[i].colorG,buttons[i].colorB,255);
        SDL_Rect where={buttons[i].posX1,buttons[i].posY1,buttons[i].posX2-buttons[i].posX1,buttons[i].posY2-buttons[i].posY1};
        if(strcmp(buttons[i].text,"")!=0){
            renderText(textFont,textSurface,textTexture,where,buttons[i].textColorR,buttons[i].textColorG,buttons[i].textColorB,buttons[i].text);
        }
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


Uint32 allow_fruitAdd(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    ev.user.code=42;
    ev.user.data1=0;
    ev.user.data2=0;
    SDL_PushEvent(&ev);
    return ms;
}

void renderFruits(fruit *fruitList){
    fruit *m;
    if(fruitList!=NULL){
        m=fruitList;
        for (m; m != NULL; m = m->nextFruit){
            int px=m->x; int py=m->y;
            boxRGBA(renderer,px,py,px+20,py+20,m->color.r,m->color.g,m->color.b,255);
        }
    }
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
