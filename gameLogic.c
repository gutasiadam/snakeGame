/*! \file gameLogic.c
    \brief A játék közbeni vezérlés, és a menük előkészítéséért, és rendereléséért felelős modul.
*/

#include "debugmalloc.h"
#include "gameLogic.h"
#include "graphics.h"

global_Settings globalSettings={false,
                                true,
                                true,
                                false,
                                false,
                                false,
                                false,
                                false,
                                false,
                                false,
                                false,
                                false
};


/*! \fn void stopGame(global_Settings *g)
    \brief Beállítja a globális flageket úgy, hogy ne fusson tovább a játék
    Előkészíti a kilépést.
    \param font1 A játék első betűtípusa.
    \param font2 A játék második betűtípusa.
    \param g A játék globális beállításait tartalmazó struct.
*/
void stopGame(global_Settings *g){
    SDL_RenderClear(renderer);
    g->isRunning=false;
}

/*! \fn void mainMenu_init(TTF_Font *font1,TTF_Font *font2,global_Settings *g)
    \brief A főmenü előkészítése, majd kirenderelése.
    \param font1 A játék első betűtípusa.
    \param font2 A játék második betűtípusa.
    \param g A játék globális beállításait tartalmazó struct.
*/
void mainMenu_init(TTF_Font *program_font1,TTF_Font *program_font2,global_Settings *g){
    boxRGBA(renderer,0,720,720,0,26,26,25,255);
    renderMenu_middle(program_font1,text_Surface,text_Texture,mainMenu,3);
    SDL_Rect where={720/2,150};
    renderText(program_font2,text_Surface,text_Texture,where,78,159,61,"Snake");
    g->init_mainMenu=false;
    g->show_mainMenu=true ;
    SDL_RenderPresent(renderer);
}
/*! \fn void mainMenuLogic(global_Settings *g)
    \brief A menü vezérlését kezelő függvény.
    egérgomlenyomás esetén meghívja a checkClick() függvényt, ellenőrizve, hogy rákattintott-e valamire a játékos.
    Az eredmény alapján átállítja a játék globális beállításait.
    \param g A játék globális beállításait tartalmazó struct.
*/
void mainMenuLogic(global_Settings *g){
    while (g->show_mainMenu){
        SDL_WaitEvent(&event);
        int mX, mY;
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        SDL_GetMouseState(&mX,&mY);

                        switch(checkClick(mainMenu,3,mX,mY)){
                            case(1):
                                g->show_gameSettings=true;
                                g->game_Init=false;
                                g->show_mainMenu=false;
                                return;
                                break;
                            case(2):
                                g->show_mainMenu=false;
                                g->init_highScoreboard=true;
                                return;
                                break;
                            case(3):
                                g->show_mainMenu=false;
                                g->exitGame=true;
                                return;
                                break;
                            default:
                                break;
                        }
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        g->show_gameSettings=true; g->show_mainMenu=false; g->game_Init=false;
                        return; break;
                    case SDLK_x:
                        g->exitGame=true; g->show_mainMenu=false;
                        return; break;
                }
                break;
        }
        SDL_RenderPresent(renderer);
    }
}

/*! \fn void render_gameSettingsMenu(TTF_Font *font1,global_Settings *g)
    \brief A játék indítása előtti almenü előkészítése, majd kirenderelése.
    \param font1 A játék első betűtípusa.
    \param g A játék globális beállításait tartalmazó struct.
*/

void render_gameSettingsMenu(TTF_Font *program_font1,global_Settings *g){
    boxRGBA(renderer,0,720,720,0,26,26,25,255);
    SDL_Rect mainTextLoc={720/2,40}; SDL_Rect P1ControlTextLoc={610,347}; SDL_Rect P2ControlTextLoc={610,447};
    SDL_Rect colorSelectLoc={720/2,280}; SDL_Rect controlsTextLoc={610,280}; SDL_Rect prewievTextLoc={100,280};
    renderText(program_font1,text_Surface,text_Texture,mainTextLoc,255,255,255,"Válaszd ki a játékosok számát, majd a színüket!");
    renderText(program_font1,text_Surface,text_Texture,P1ControlTextLoc,200,200,200,"Nyilak");

    renderText(program_font1,text_Surface,text_Texture,colorSelectLoc,170,170,170,"Választható színek");
    renderText(program_font1,text_Surface,text_Texture,controlsTextLoc,170,170,170,"Irányítás");
    renderText(program_font1,text_Surface,text_Texture,prewievTextLoc,170,170,170,"Előnézet");

    lineRGBA(renderer,40,397,(720-40),397,255,255,255,255);
    lineRGBA(renderer,40,300,(720-40),300,255,255,255,255);

    if(gameSettingsMenu[8].value==6){
        gameSettingsMenu[0].colorR=77; gameSettingsMenu[0].colorG=77; gameSettingsMenu[0].colorB=77;
        gameSettingsMenu[1].colorR=216; gameSettingsMenu[1].colorG=233; gameSettingsMenu[1].colorB=168;
        renderMenu(program_font1,text_Surface,text_Texture,gameSettingsMenu_multi,6);
        renderText(program_font1,text_Surface,text_Texture,P2ControlTextLoc,200,200,200,"WASD");

        lineRGBA(renderer,160,250,160,495,255,255,255,255);
        lineRGBA(renderer,550,250,550,495,255,255,255,255);
    }else{
        gameSettingsMenu[1].colorR=77; gameSettingsMenu[1].colorG=77; gameSettingsMenu[1].colorB=77;
        gameSettingsMenu[0].colorR=216; gameSettingsMenu[0].colorG=233; gameSettingsMenu[0].colorB=168;

        lineRGBA(renderer,160,250,160,410,255,255,255,255);
        lineRGBA(renderer,550,250,550,410,255,255,255,255);
    }
    renderMenu(program_font1,text_Surface,text_Texture,gameSettingsMenu,10);
    g->show_gameSettings=true;
    SDL_RenderPresent(renderer);
}

/*! \fn void gameSettingsLogic(global_Settings *g)
    \brief A játék indítása előtti almenü vezérlését kezelő függvény.
    egérgomlenyomás esetén meghívja a checkClick() függvényt, ellenőrizve, hogy rákattintott-e valamire a játékos.
    Az eredmény alapján átállítja a játék globális beállításait.
    \param g A játék globális beállításait tartalmazó struct.
    \param snake1 Az első kígyó fejére/adataira mutató pointer.
    \param snake2 A második kígyó fejére/adataira mutató pointer.
*/
void gameSettingsLogic(global_Settings *g,Snake *snake1,Snake *snake2){
    int mX, mY;
    while(g->show_gameSettings) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        SDL_GetMouseState(&mX, &mY);
                        int clickVal=checkClick(gameSettingsMenu, 10, mX, mY);
                        if(clickVal>=100){ //Ha színt szeretne állítani a felhasználó:
                            snake1->r=gameSettingsMenu[clickVal%100].colorR; gameSettingsMenu[2].colorR=gameSettingsMenu[clickVal%100].colorR;
                            snake1->g=gameSettingsMenu[clickVal%100].colorG; gameSettingsMenu[2].colorG=gameSettingsMenu[clickVal%100].colorG;
                            snake1->b=gameSettingsMenu[clickVal%100].colorB; gameSettingsMenu[2].colorB=gameSettingsMenu[clickVal%100].colorB;
                        }
                        clickVal=checkClick(gameSettingsMenu_multi, 6, mX, mY);
                        if(clickVal>=200){ //Ha színt szeretne állítani a felhasználó:
                            snake2->r=gameSettingsMenu_multi[clickVal%100].colorR; gameSettingsMenu_multi[0].colorR=gameSettingsMenu_multi[clickVal%100].colorR;
                            snake2->g=gameSettingsMenu_multi[clickVal%100].colorG; gameSettingsMenu_multi[0].colorG=gameSettingsMenu_multi[clickVal%100].colorG;
                            snake2->b=gameSettingsMenu_multi[clickVal%100].colorB; gameSettingsMenu_multi[0].colorB=gameSettingsMenu_multi[clickVal%100].colorB;
                        }
                        switch (checkClick(gameSettingsMenu, 10, mX, mY)) {
                            case (1):
                                gameSettingsMenu[8].value=5;
                                return;  // Kiugrik a menü logikából a program, hogy újrarajzolhassa a táblázatot.
                                break;
                            case (2):
                                gameSettingsMenu[8].value=6;
                                return;  // Kiugrik a menü logikából a program, hogy újrarajzolhassa a táblázatot.
                                break;
                            case (5):
                                g->game_Init=true;
                                g->show_gameSettings=false;
                                g->twoPlayerMode=false;
                                g->show_mainGame=true;
                                return;
                                break;
                            case (6):
                                g->game_Init=true;
                                g->show_gameSettings=false;
                                g->twoPlayerMode=true;
                                g->show_mainGame=true;
                                return;
                                break;
                            case(3):
                                printf("Vissza");
                                g->show_gameSettings=false;
                                g->init_mainMenu=true;
                                g->show_mainMenu=true;
                                return;
                                break;
                            default:
                                return;
                                break;
                        }
                        break;
                }
                break;
        }
    }
}


/*! \fn void render_highScoresMenu(TTF_Font *font1,global_Settings *g,scoreBoard_highscores_Elements m)
    \brief A dicsőségtábla kiírását megvalósító függvény.
    \param font1 A játék első betűtípusa.
    \param g A játék globális beállításait tartalmazó struct.
    \param m a dicsőségtábla grafikus elemeit tartalmazó struct.
*/
void render_highScoresMenu(TTF_Font *program_font1,global_Settings *g,scoreBoard_highscores_Elements m){
    boxRGBA(renderer,0,720,720,0,26,26,25,255);
    renderMenu_middle(program_font1,text_Surface,text_Texture,m.menuElements,10);
    renderMenu(program_font1,text_Surface,text_Texture,&m.menuElements[10],1); /* A bezáró gomb kirenderelése. Azért kell külön, mert ez nem középre kerül. */
    SDL_Rect where={0,650};
    g->show_highScoreboard=true;
    g->init_highScoreboard=false;
    SDL_RenderPresent(renderer);
}

/*! \fn void highScoresMenuLogic(global_Settings *g)
    \brief A dicsőségtábla vezérlő függvénye
    egérgomlenyomás esetén meghívja a checkClick() függvényt, ellenőrizve, hogy rákattintott-e valamire a játékos.
    Az eredmény alapján átállítja a játék globális beállításait.
    \param g A játék globális beállításait tartalmazó struct.
*/
void highScoresMenu_Logic(global_Settings *g,scoreBoard_highscores_Elements highScoreMenu){
    int mX, mY;
    while(g->show_highScoreboard) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        SDL_GetMouseState(&mX, &mY);
                        switch (checkClick(highScoreMenu.menuElements, 11, mX, mY)) {
                            case (100):
                                g->game_Init=false;
                                g->show_gameSettings=false;
                                g->twoPlayerMode=false;
                                g->show_mainGame=false;
                                g->show_highScoreboard=false;
                                g->init_mainMenu=true;
                                return;
                                break;
                            default:
                                return;
                                break;
                        }
                        break;
                }
                break;
        }
    }
}

void inGameButtons(ButtonBox *buttons,TTF_Font *program_font1,TTF_Font *program_font2,int len){
    renderMenu(program_font1,text_Surface,text_Texture,buttons,len);
    SDL_Rect where={720/2,150};
    SDL_RenderPresent(renderer);
}

/*! \fn void mainGame_Logic(TTF_Font *font1,TTF_Font *font2,global_Settings *g, Snake *snake1, Snake *snake2)
    \brief A játék futása alatti logikai motor
    \param program_font1 A játék első betűtípusa.
    \param program_font2 A játék második betűtípusa.
    \param g A játék globális beállításait tartalmazó struct.
    \param snake1 Az első játékos kígyójának adatai
    \param snake2 A második játékos kígyójának adatai
    \param hS A dicsőságtáblára mutató pointer

*/
void mainGame_Logic(TTF_Font *program_font1,TTF_Font *program_font2,global_Settings *g, Snake *snake1, Snake *snake2,scoreBoard_highscores *hS){
    SDL_RenderClear(renderer); // előző menü törlése
    int mX;
    int mY;
    boxRGBA(renderer,0,0,720,720,20,20,19,255);
    SnakeBodyList s1L; init_SnakeBody(&s1L);
    SnakeBodyList s2L; init_SnakeBody(&s2L);
    bool collision=false;
    fruit* fruitList;
    fruitList=NULL;
    SDL_TimerID SnakeMoveTimer= SDL_AddTimer(200,allow_moveSnake,NULL);
    SDL_TimerID fruitTimer=SDL_AddTimer(2000,allow_fruitAdd,NULL);
    while(g->show_mainGame){
        SDL_WaitEvent(&event);

        if(collision){ //Ha ütközés van, már ne számoljon tovább új pozíciót a játék.
            resetSnake(snake1);
            resetSnake(snake2);
            g->show_mainGame=false;
            g->init_mainMenu=true;
            g->init_gameSettings=false;
            g->game_Init=false;
            g->show_gameSettings=false;
            SDL_RemoveTimer(fruitTimer);
            SDL_RemoveTimer(SnakeMoveTimer);
            destroyFruitList(fruitList); // vége a játéknak, megszüntetjük a gyümölcsök láncolt listáját.
            destroy_snakeBody(&s2L);
            destroy_snakeBody(&s1L);
            calculateNewScoreboard(font1,hS,*snake1,*snake2);
            SDL_FlushEvent(SDL_USEREVENT);
            resetSnakePoints(snake1);
            resetSnakePoints(snake2);
            break; // már ne próbáljon meg renderelni, vége a játéknak.
        }
        switch (event.type){
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mX, &mY);
                int clickVal=checkClick(inGameMenu,1,mX,mY);
                if (clickVal==0){
                    resetSnakePoints(snake1);
                    resetSnakePoints(snake2);
                    collision=true;
                }
                break;
            case SDL_QUIT:
                g->isRunning=false;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_BACKSPACE:
                        resetSnakePoints(snake1);
                        resetSnakePoints(snake2);
                        collision=true;
                        break;
                }
                break;
            case SDL_KEYDOWN:
                P1_Controller(snake1,event);
                if(g->twoPlayerMode)
                    P2_Controller(snake2,event);
                break;
            case SDL_USEREVENT:
                if(event.user.code==43){ // 43: mozgás engedélyezése.
                    moveBody(&s1L,snake1);
                    snake1->x+=snake1->vx;
                    snake1->y+=snake1->vy;
                    if (checkWallHit(*snake1)){
                        resetSnake(snake1);
                        resetSnake(snake2);
                        collision=true;
                        printf("\n%s:%d elso utkozik",__FILE_NAME__,__LINE__);
                    }
                    if (checkBodyCollision(&s1L,snake1)) {
                        printf("P1: Body collision!");
                        collision=true;
                    }
                    if(g->twoPlayerMode){
                            moveBody(&s2L,snake2);
                            snake2->x += snake2->vx;
                            snake2->y += snake2->vy;
                        if (checkWallHit(*snake2)){
                            resetSnake(snake1);
                            resetSnake(snake2);
                            collision=true;
                            printf("%s:%d masodik utkozik",__FILE_NAME__,__LINE__);
                        }
                        if (checkBodyCollision(&s2L,snake2)) {
                            resetSnake(snake1);
                            resetSnake(snake2);
                            collision=true;
                        }
                    }
                    SDL_FlushEvents(SDL_USEREVENT,SDL_USEREVENT); // megszünteti a néha random ugró kígyó problémát.
                }
                fruit *s1F=checkCollision(fruitList,*snake1);//érintkezik-e valamelyik gyümölcs P1-gyel.
                fruit *s2F=checkCollision(fruitList,*snake2);//érintkezik-e valamelyik gyümölcs P2-vel.
                if(s1F!=NULL) {
                    add_BodyElement(&s1L,*snake1);
                    snake1->points++;
                    fruitList=deleteFruit(fruitList, s1F);
                }
                if(s2F!=NULL){
                    add_BodyElement(&s2L,*snake2);
                    snake2->points++;
                    fruitList=deleteFruit(fruitList, s2F);
                }

                // Ütközés ellenőrzése mozgatás után, de render előtt.

                if(g->twoPlayerMode){
                    collision=(checkBodyCollision(&s2L,snake1) || checkBodyCollision(&s1L,snake2) || checkHeadCollision(snake1,snake2));
                }
                //kirajzolás
                boxRGBA(renderer,0,600,720,0,184,82,82,255); //keret (határ) kirenderlése, ennek ütközhet neki a kígyó.
                boxRGBA(renderer,20,580,700,20,20,20,19,255);// pálya újra kirajzolása, ezzel a kígyó előző pozíciójainak kitörlése

                boxRGBA(renderer,snake1->x,snake1->y,snake1->x+20,snake1->y+20,snake1->r,snake1->g,snake1->b,255);// P1 fej renderelése
                renderSnakeBody(&s1L,*snake1);//P1 test renderelése

                if(g->twoPlayerMode){
                    boxRGBA(renderer,snake2->x,snake2->y,snake2->x+20,snake2->y+20,snake2->r,snake2->g,snake2->b,255);//P2 fej renderelése
                    renderSnakeBody(&s2L,*snake2); // test renderelése,
                }
                if(event.user.code==42){ // gyümölcs hozzáadás
                    fruitList=add_Fruit(fruitList,s1L,s2L);
                    SDL_FlushEvents(SDL_USEREVENT,SDL_USEREVENT); // megszünteti a néha random ugró kígyó problémát.
                }
                renderFruits(fruitList);//Minden egyes gyümölcs kirenderelése
                SDL_Rect renderPoints_snake1={0,620,0,0};
                SDL_Rect renderPoints_snake2={0,660,0,0};
                inGameButtons(inGameMenu,program_font1,program_font2,1);
                char pSnake1[50];
                char pSnake2[50];
                sprintf(pSnake1,"%d",snake1->points);
                sprintf(pSnake2,"%d",snake2->points);
                //roundedBoxRGBA(renderer,200,640,500,720,20,0,0,0,255);
                boxRGBA(renderer,200,620,500,720,20,20,19,255);
                renderText(program_font1,text_Surface,text_Texture,renderPoints_snake1,snake1->r,snake1->g,snake1->b,pSnake1);
                if(g->twoPlayerMode){
                    renderText(program_font1,text_Surface,text_Texture,renderPoints_snake2,snake2->r,snake2->g,snake2->b,pSnake2);
                }
                break;

        }
    }
}

/*! \fn void randomise_snakePos(Snake *s)
    \brief A Kígyó pozíciójának véletlenszerű elhelyezése.

    Az eredmény alapján átállítja a Kígyó pozíciójára és sebességére vonatkozó beállításait.
    \param s A kígyó adatait tartalmazó struct
*/
void randomise_snakePos(Snake *s){
    s->x=20*(rand()%34)+20;
    s->y=20*(rand()%28)+20;
    s->vx=0;
    s->vy=0;
}

/*! \fn void resetSnake(Snake *s1)
    \brief A Kígyó pozíciójának alaphelyzetbe állítása.
    \param s A kígyó adatait tartalmazó struct
*/
void resetSnake(Snake *s){
    s->vx=0; s->vy=0; s->x=20; s->y=20; s->lastPos=' ';
}

/*! \fn void resetSnakePoints(Snake *s1)
    \brief A Kígyó pontszámának visszaállítása.

    Azért nem jó a resetSnake() függvény ehhez, mert a játék véget érése után a
    dicsőségtáblát kezelő függvényeknek még el kell ériük a kígyó pontszámát.
    \param s A kígyó adatait tartalmazó struct
*/
void resetSnakePoints(Snake *s1){
    s1->points=0;
}

/*! \fn void P1_Controller(Snake *s1, SDL_Event ev)
    \brief Az első számú kígyó vezérléséért felelős függvény

    Azért kell külön P1_Controller() és P2_Controller(), mert más billentyűkre változik a kígyók mozgása. Egyszerűbb különvéve kezelni őket.
    \param s1 A kígyó adatait tartalmazó Snake structra mutató pointer
*/
void P1_Controller(Snake *snake1, SDL_Event ev){
    switch (ev.key.keysym.sym) {
        case SDLK_LEFT:
            if(snake1->lastPos!='R'){
                snake1->vx=-0.25*moveMentScale;
                snake1->vy=0;
                snake1->lastPos='L';
                SDL_FlushEvent(SDLK_LEFT);
            }
            break;
        case SDLK_RIGHT:
            if(snake1->lastPos!='L') {
                snake1->vx = 0.25 * moveMentScale;
                snake1->vy = 0;
                snake1->lastPos='R';
                SDL_FlushEvent(SDLK_RIGHT);
            }
            break;
        case SDLK_UP:
            if(snake1->lastPos!='D') {
                snake1->vx = 0;
                snake1->vy = (-0.25) * moveMentScale;
                snake1->lastPos='U';
                SDL_FlushEvent(SDLK_UP);
            }
            break;
        case SDLK_DOWN:
            if(snake1->lastPos!='U') {
                snake1->vx = 0;
                snake1->vy = 0.25 * moveMentScale;
                snake1->lastPos='D';
                SDL_FlushEvent(SDLK_DOWN);
            }
            break;
    }
}
void P2_Controller(Snake *snake2, SDL_Event ev){
    switch (event.key.keysym.sym) {
        case SDLK_a:
            if(snake2->lastPos!='R'){
                snake2->vx=-0.25*moveMentScale;
                snake2->vy=0;
                snake2->lastPos='L';
            }
            break;
        case SDLK_d:
            //snake1->right = true;
            if(snake2->lastPos!='L') {
                snake2->vx = 0.25 * moveMentScale;
                snake2->vy = 0;
                snake2->lastPos='R';
            }
            break;
        case SDLK_w:
            //snake1->up = true;
            if(snake2->lastPos!='D') {
                snake2->vx = 0;
                snake2->vy = (-0.25) * moveMentScale;
                snake2->lastPos='U';
            }
            break;
        case SDLK_s:
            //snake1->down=true;
            if(snake2->lastPos!='U') {
                snake2->vx = 0;
                snake2->vy = 0.25 * moveMentScale;
                snake2->lastPos='D';
            }
            break;
    }
}

/*! \fn int checkScore(Snake *s, scoreBoard_highscores hS)
    \brief Megnézi, hogy a játékos által elért eredmény benne van-e a top 10-ben.
    \param s A kígyó adatait tartalmazó struct
    \param hS az eddigi legjobb 10 adatait tartalmazó scoreBoard_highscores struct.
    \return Ha top10-nek számít, akkor visszatér azzal az indexszel, aminek adatánál nagyobb(, jobb) az elért eredmény.
    Különben -1 -et ad.
*/
int checkScore(Snake *s, scoreBoard_highscores hS){
    if(s->points==0)
        return -1;
    for(int i=0;i<10;i++){
        if(s->points>hS.data[i].score){
            return i;
        }
    }
    return -1;
}

/*! \fn void changeHighScoreList(Snake *s,const char* playerName, int idx, scoreBoard_highscores *h)
    \brief Módosítja a dicsőségtáblát
    \param s A kígyó adatait tartalmazó struct
    \param playerName A játékos nevét tartalmazó struct
    \param h A program futása alatt a dicsőségtáblát tartalmazó struct.
*/
void changeHighScoreList(Snake *s,const char* playerName, int idx, scoreBoard_highscores *h){
    highScorePlayer tmpPlayer={"N/A", s->points};
    strcpy(tmpPlayer.name,playerName);
    scoreBoard_highscores tmp;
    int i=0;
    while(i<idx){
        tmp.data[i]=h->data[i];
        i++;
    }
    tmp.data[i++]=tmpPlayer;
    while(i<10){
        tmp.data[i]=h->data[i-1];
        i++;
    }
    for(int j=0;j<10;j++){
        h->data[j]=tmp.data[j]; //felülírás
        //printf("%s %d\n",h->data[j].name,h->data[j].score); debug
    }
}

bool enter_text(char *where, size_t len, SDL_Rect box, SDL_Color backgroundColor, SDL_Color textColor, TTF_Font *program_font, SDL_Renderer *program_renderer){
    int maxUseableAreaWidth=box.w-2;
    int maxUseableAreaHeight=box.h-2;

    char currentTextEditing[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
    currentTextEditing[0]='\0';

    char textandcurrentTextEditing[len + SDL_TEXTEDITINGEVENT_TEXT_SIZE + 1];
    where[0]='\0';

    bool enterPressed=false;
    SDL_StartTextInput();
    while(!enterPressed){
        /* Box kirajzolása, ahova lehet írni: */
        boxRGBA(renderer,box.x,box.y,box.x+box.w,box.y+box.h,backgroundColor.r,backgroundColor.g,backgroundColor.b,255);
        /* Boxot befogó keret rajzolása, azzal a színnel, amelyik kígyóhoz tartozik majd ez a név. */
        rectangleRGBA(renderer,box.x-1,box.y-1,box.x+box.w+1,box.y+box.h+1,textColor.r,textColor.g,textColor.b,255);

        /* Beírt szöveg kirenderelése */
        strcpy(textandcurrentTextEditing,where);
        strcat(textandcurrentTextEditing,currentTextEditing);

        if(textandcurrentTextEditing[0]!='\0'){ // van benne szöveg, nem üres
            //ellenőrzés, hogy tartalmaz-e space-t. Ha igen, akkor ezt jelezze a játékosnak!
            char* charIterator=textandcurrentTextEditing;
            while(*charIterator!='\0'){
                if(*charIterator==' '){
                    rectangleRGBA(renderer,box.x-1,box.y-1,box.x+box.w+1,box.y+box.h+1,255,0,0,200);
                    SDL_Rect renderWarningLoc={720/2,(720/2)+100};
                    renderText(program_font,text_Surface,text_Texture,renderWarningLoc,255,0,0,"Nem tartalmazhat szóközt!");// Ez a figyelmeztetés maradjon ott, hogy biztos észrevegye a felhasználó.
                    break;
                }
                charIterator++;
            }
            SDL_Surface *textSurface= TTF_RenderUTF8_Blended(program_font,textandcurrentTextEditing,textColor);
            SDL_Texture *textTexture= SDL_CreateTextureFromSurface(renderer,textSurface);
            SDL_Rect rect_destination = { box.x, box.y, textSurface->w < maxUseableAreaWidth ? textSurface->w : maxUseableAreaWidth, textSurface->h < maxUseableAreaHeight ? textSurface->h : maxUseableAreaHeight };
            SDL_RenderCopy(renderer,textTexture,NULL,&rect_destination);
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
            lineRGBA(renderer,box.x+textSurface->w+2,box.y+textSurface->h-2,box.x+textSurface->w+2,box.y,textColor.r,textColor.g,textColor.b,255);
        }

        SDL_RenderPresent(renderer);
        SDL_WaitEvent(&event);
        switch(event.type){
            case (SDL_KEYDOWN):
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    /* SDLK_BACKSPACE viselkedése másolva az infoC oldal SDL grafika oldaláról:
                     * URL:https://infoc.eet.bme.hu/sdl/#7
                     * */
                    int Len_where = strlen(where);
                    do {
                        if (Len_where == 0) {
                            break;
                        }
                        if ((where[Len_where - 1] & 0x80) == 0x00) {
                            /* Egy bajt */
                            where[Len_where - 1] = 0x00;
                            break;
                        }
                        if ((where[Len_where - 1] & 0xC0) == 0x80) {
                            /* Bajt, egy tobb-bajtos szekvenciabol */
                            where[Len_where - 1] = 0x00;
                            Len_where--;
                        }
                        if ((where[Len_where - 1] & 0xC0) == 0xC0) {
                            /* Egy tobb-bajtos szekvencia elso bajtja */
                            where[Len_where - 1] = 0x00;
                            break;
                        }
                    } while (true);
                }
                if (event.key.keysym.sym == SDLK_RETURN) {
                    char* charIterator=textandcurrentTextEditing;
                    while(*charIterator!='\0'){
                        if(*charIterator==' '){
                            break;
                        }
                        charIterator++;
                    }
                    if(*charIterator=='\0' && (strlen(textandcurrentTextEditing)!=0)) {
                        enterPressed = true;
                    }
                    break;
                }
                break;
            case (SDL_TEXTINPUT):
                if(len>(strlen(where)+strlen(event.text.text))){
                    strcat(where,event.text.text); // Az if feltétel biztosítja, hogy elfér a bevitt szöveg.
                }
                currentTextEditing[0]='\0';
                break;
            case (SDL_TEXTEDITING):
                strcpy(currentTextEditing,event.edit.text);
                break;

        }
    }

    SDL_StopTextInput();
    return true;
}

bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer) {
    /* infoC weboldaláról másolt rész. még ÚJRA KELL ÍRNOM */
    /* Ez tartalmazza az aktualis szerkesztest */
    char composition[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
    composition[0] = '\0';
    /* Ezt a kirajzolas kozben hasznaljuk */
    char textandcomposition[hossz + SDL_TEXTEDITINGEVENT_TEXT_SIZE + 1];
    /* Max hasznalhato szelesseg */
    int maxw = teglalap.w - 2;
    int maxh = teglalap.h - 2;

    dest[0] = '\0';

    bool enter = false;
    bool kilep = false;

    SDL_StartTextInput();
    while (!kilep && !enter) {
        /* doboz kirajzolasa */
        boxRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, hatter.r, hatter.g, hatter.b, 255);
        rectangleRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, szoveg.r, szoveg.g, szoveg.b, 255);
        /* szoveg kirajzolasa */
        int w;
        strcpy(textandcomposition, dest);
        strcat(textandcomposition, composition);
        if (textandcomposition[0] != '\0') {
            SDL_Surface *felirat = TTF_RenderUTF8_Blended(font, textandcomposition, szoveg);
            SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
            SDL_Rect cel = { teglalap.x, teglalap.y, felirat->w < maxw ? felirat->w : maxw, felirat->h < maxh ? felirat->h : maxh };
            SDL_RenderCopy(renderer, felirat_t, NULL, &cel);
            SDL_FreeSurface(felirat);
            SDL_DestroyTexture(felirat_t);
            w = cel.w;
        } else {
            w = 0;
        }
        /* kurzor kirajzolasa */
        if (w < maxw) {
            vlineRGBA(renderer, teglalap.x + w + 2, teglalap.y + 2, teglalap.y + teglalap.h - 3, szoveg.r, szoveg.g, szoveg.b, 192);
        }
        /* megjeleniti a képernyon az eddig rajzoltakat */
        SDL_RenderPresent(renderer);

        //SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
            /* Kulonleges karakter */
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    int textlen = strlen(dest);
                    do {
                        if (textlen == 0) {
                            break;
                        }
                        if ((dest[textlen-1] & 0x80) == 0x00)   {
                            /* Egy bajt */
                            dest[textlen-1] = 0x00;
                            break;
                        }
                        if ((dest[textlen-1] & 0xC0) == 0x80) {
                            /* Bajt, egy tobb-bajtos szekvenciabol */
                            dest[textlen-1] = 0x00;
                            textlen--;
                        }
                        if ((dest[textlen-1] & 0xC0) == 0xC0) {
                            /* Egy tobb-bajtos szekvencia elso bajtja */
                            dest[textlen-1] = 0x00;
                            break;
                        }
                    } while(true);
                }
                if (event.key.keysym.sym == SDLK_RETURN) {
                    enter = true;
                }
                break;

                /* A feldolgozott szoveg bemenete */
            case SDL_TEXTINPUT:
                if (strlen(dest) + strlen(event.text.text) < hossz) {
                    strcat(dest, event.text.text);
                }

                /* Az eddigi szerkesztes torolheto */
                composition[0] = '\0';
                break;

                /* Szoveg szerkesztese */
            case SDL_TEXTEDITING:
                strcpy(composition, event.edit.text);
                break;

            case SDL_QUIT:
                SDL_PushEvent(&event);
                kilep = true;
                break;
        }
    }

    SDL_StopTextInput();
    return enter;
}

/*! \fn fruit* add_Fruit(fruit* firstFruit, SnakeBodyList snake1_L, SnakeBodyList snake2_L)
    \brief Generál egy új gyümölcsöt, beteszi a gyümölcsöket tartalmazó lista elejére.

    Ha ez a gyümölcs ütközne az egyik kígyóval, akkor újat generál-
    \param firstFruit A gyümölcslista első elemére mutató pointer.
    \param snake1_L Az 1. kígyó testét tartalmazó struct.
    \param snake2_L A 2. kígyó testét tartalmazó struct.
    \return Visszatér a frissített gyümölcslista elejáre mutató pointerre.
*/
fruit* add_Fruit(fruit* firstFruit, SnakeBodyList snake1_L, SnakeBodyList snake2_L){
    SDL_Color fC={0,200,rand()%100}; // A gyümölcs színe
    fruit *newFruit;
    newFruit=(fruit*) malloc(sizeof(fruit));
    //bejárja a kígyók listáját, megnézi, hogy van e ütközés, ha igen, akkor újrarandomizál egy számot.
    int posX; int posY;
    do {
        posX=20*(rand()%34)+20;
        posY=20*(rand()%28)+20;
        newFruit->x=posX; newFruit->y=posY; newFruit->color=fC;
    }while((checkIncomingFruitCollision(*newFruit,&snake1_L) || checkIncomingFruitCollision(*newFruit,&snake2_L)));

    newFruit->nextFruit=firstFruit;
    firstFruit=newFruit;

    return firstFruit;
}

void destroyFruitList(fruit* fruitList){
    fruit *iter=fruitList;
    while(iter!=NULL){
        fruit *tmp=iter->nextFruit;
        free(iter);
        iter=tmp;
    }
}

fruit* checkCollision(fruit* fruitList,Snake s){
    int snakeX=s.x; int SnakeY=s.y;
    int fruitX=0; int fruitY=0;
    fruit *m;
    for (m = fruitList; m != NULL; m = m->nextFruit){
        fruitX=m->x;fruitY=m->y;
        if(snakeX==fruitX && SnakeY==fruitY) {
            return m;
        }

    }
    return NULL;
}

/*! \fn fruit* deleteFruit(fruit* fruitList,fruit *toBeDeleted)
    \brief Kitöröl egy gyümölcsöt a láncolt listából.
    \param fruitList A gyümölcsöket tartalmazú láncolt lista.
    \param toBeDeleted A kitörlendő gyümölcs címe.
    \return fruit*
*/
fruit* deleteFruit(fruit* fruitList,fruit *toBeDeleted){
    fruit *before = NULL;
    fruit *after = fruitList;
    while (after != NULL && after->nextFruit != toBeDeleted->nextFruit) {
        before = after;
        after = after->nextFruit;
    }
    if (after== NULL) {
        return fruitList;
    } else if (before == NULL) {
        fruit *new_fristElement = after->nextFruit;
        free(after);
        fruitList = new_fristElement;
        return fruitList;
    } else {
        before->nextFruit = after->nextFruit;
        free(after);
        return fruitList;
    }
}

/*! \fn bool checkIncomingFruitCollision(fruit newFruit,SnakeBodyList *s)
    \brief Megnézi, hogy a frissen beilleszteni kívánt gyümölcs ütközne-e egy játékossal.
    \param newFruit Az újonnan beillesztendő gyümölcs
    \param s A kígyó fejét tartalmazú struct.
    \return true értékkel tér vissza, ha ütközne a gyümölcs, false értékkel, ha nem. true érték esetén új pozíciót
    generál az add_Fruit() függvény.
*/
bool checkIncomingFruitCollision(fruit newFruit,SnakeBodyList *s){
    int fruitX=newFruit.x; int fruitY=newFruit.y;
    if(s->head->next==s->last)
        return false;
    SnakeBody *mov = s->head;
    //bejárás elölről
    while (mov != s->last->prev) {
        if(mov->x == fruitX && mov->y == fruitY){
            return true;
        }
        mov = mov->next;
    }
    return false;
}

/*! \fn void add_BodyElement(SnakeBodyList *o,Snake s)
    \brief Megnöveli a kígyó hosszát 1-gyel.
    \param o A kígyó testét tartalmazó SnakeBodyList struct
    \param s A kígyó fejét tartalmazú struct.
*/
void add_BodyElement(SnakeBodyList *o,Snake s){
    SnakeBody *new=(SnakeBody*) malloc(sizeof(SnakeBody));
    new->x=s.x;
    new->y=s.y;
    if(o->head->next==o->last){ //Üres a lista
        new->next=o->last;
        new->prev=o->head;
        o->head->next=new;
        o->last->prev=new;
    }else{
        new->next=o->head->next;
        o->head->next->prev=new;
        new->prev=o->head;
        o->head->next=new;
    }
}
/*! \fn void moveBody(SnakeBodyList *s, Snake *sHead)
 * \brief Elmozdítja a kígyó testét.
 *
 * Hátulról bejárja a láncolt listát, és mindig az adott elem előtti elem adatait átmásolja.
 *
 * A láncolt lista legeleján található elem a SnakeBodyList head elemében eltárolt x és y pozíciót másolja át.
 * Ez a Snake fejelemből vevődik át.
 * \param s A kígyó testének strázsája, és sentinelje.
 * \param sHead Snake típusú struct.
 */
void moveBody(SnakeBodyList *s, Snake *sHead){
    // Ha nincs elem a listában (nincs teste a kígyónak), akkor ne is fusson le.
    if(s->head->next==s->last)
        return;
    SnakeBody *mov = s->last->prev;
    s->head->x=sHead->x;
    s->head->y=sHead->y;
    //bejárás hátulról, a következő elem mindig becsúszik az előzőbe
    while (mov != s->head) {
        mov->x=mov->prev->x;
        mov->y=mov->prev->y;
        mov = mov->prev;
    }
}
/*!
 * \fn void init_SnakeBody(SnakeBodyList *tmp)
 * \brief Előkészíti a kígyó testének duplán láncolt listáját.
 *
 * Létrehozza a strázsát és a sentinelt. Összelinkeli őket, hogy egyásra mutassanak.
 * \param sBody Az inicializálandó SnakeBodyList struct
 */
void init_SnakeBody(SnakeBodyList *sBody){
    SnakeBody* h=(SnakeBody*) malloc(sizeof(SnakeBody));
    SnakeBody* l=(SnakeBody*) malloc(sizeof(SnakeBody));
    sBody->head=h;
    sBody->last=l;
    sBody->head->next=sBody->last;
    sBody->head->prev=NULL;
    sBody->last->prev=sBody->head;
    sBody->last->next=NULL;
}

/*!
 * \fn bool checkWallHit(Snake s)
 * \brief Megnézi, hogy a Snake kígyófej ütközött e éppen a fallal
 * \param s Az adott kígyó feje.
 * \return true értékkel tér vissza, ha a kígyó ütközött a fallal, és false-al, ha nem.
 */
bool checkWallHit(Snake s){
    if (s.x<=0 || s.x>=700 || s.y<=0 || s.y>=580){
        return true;
    }
    return false;
}

/*! \fn void exitProgram(global_Settings *g,TTF_Font* font1,TTF_Font* font2,SDL_TimerID id,FILE *fp,scoreBoard_highscores *highscores)
    \brief Bezárja az SDL könyvtárakat és kiírja az új dicsőségtáblát a fájlba,
    \param g A kígyó adatait tartalmazó struct
    \param font1 Az első használt betűtípus.
    \param font2 A második használt betűtípus.
    \param id A beállított fps számolásáért felelős időzítő
    \param fp A dicsőségtábla adatait tartalmazó fájl
    \param highscores A program futása során tárolt diőcségtábla.
*/
void exitProgram(global_Settings *g,TTF_Font* program_font1,TTF_Font* program_font2,SDL_TimerID id,FILE *fp,scoreBoard_highscores *highscores){
    globalSettings.isRunning=false;
    TTF_CloseFont(program_font1);
    TTF_CloseFont(program_font2);
    SDL_RemoveTimer(id);
    writeScoreBoardToFile(fp,*highscores);
    fclose(fp);
    SDL_Quit();
}

/*!
 * \fn void destroy_snakeBody(SnakeBodyList *s)
 * \brief Felszabadítja a kígyó testéhez lefoglalt duplán láncolt listát.
 *
 * \param s A felszabadítandó dupllán láncolt listához tartozó SnakeBodyList struct
 */
void destroy_snakeBody(SnakeBodyList *s){
    SnakeBody *mov = s->head;
    while (mov != s->last) {
        SnakeBody *tmp=mov->next;
        free(mov);
        mov = tmp;
    }
    free(mov); //s->last is felszabadul.
}

/*!
 * \fn bool checkBodyCollision(SnakeBodyList *sList,Snake *sHead)
 * \brief Megnézi, hogy két test (a.k.a. az egyik kígyó feje és a másik teste) ütközik-e.
 *
 * \param sHead Az egyik kígyó feje.
 * \param sList A másik kígyó teste
 * \return Ha ütközik a fej a testtel, TRUE-t ad vissza, egyébként FALSE-t.
 */
bool checkBodyCollision(SnakeBodyList *sList,Snake *sHead){
    SnakeBody *mov = sList->head->next;
    while (mov != sList->last) {
        if((sHead->x == mov->x) && (sHead->y == mov->y)){
            return true;
        }
        mov = mov->next;
    }
    return false;
}


bool checkHeadCollision(Snake *sHead1, Snake *sHead2){
    if(sHead1->x==sHead2->x && sHead1->y==sHead2->y)
        return true;
    return false;
}

void calculateNewScoreboard(TTF_Font* program_font1,scoreBoard_highscores *hS,Snake snake1, Snake snake2){
    int s1Idx= checkScore(&snake1,*hS);//s1 rekordindexe
    int s2Idx= checkScore(&snake2,*hS);//s2 rekordindexe
    //printf("Record indexes: P1: %d P2: %d\n",s1Idx,s2Idx);
    if(s1Idx!=-1 && s2Idx!=-1 && s1Idx!=s2Idx){//Ha mindkettő rekorder, de nem ugyanahhoz az indexhez képest
        if(s1Idx<=s2Idx){ // Ekkor az első ért el jobb helyezést, őt kell először kiszáolni.
            //printf("Case: 1");
            highscore_subRoutine(s1Idx,program_font1,hS,snake1,1);
            SDL_Delay(100);
            highscore_subRoutine(s2Idx,program_font1,hS,snake2,2);
        }if(s1Idx>=s2Idx){
            //printf("Case: 2");
            highscore_subRoutine(s2Idx,program_font1,hS,snake2,2);
            SDL_Delay(100);
            highscore_subRoutine(s1Idx,program_font1,hS,snake1,1);
        }
        if(s1Idx==s2Idx){ //mindekettő ugyannál a számnál nagyobb.
            if(snake1.points>snake2.points){
                //printf("Case: 3");
                highscore_subRoutine(s1Idx,program_font1,hS,snake1,1);
                SDL_Delay(100);
                highscore_subRoutine(s2Idx,program_font1,hS,snake2,2);
            }else{
                highscore_subRoutine(s2Idx,program_font1,hS,snake2,2);
                SDL_Delay(100);
                highscore_subRoutine(s1Idx,program_font1,hS,snake1,1);
            }
        }
    }else{
        if(s1Idx!=-1){
            highscore_subRoutine(s1Idx,program_font1,hS,snake1,1);}
        if(s2Idx!=-1){
            highscore_subRoutine(s2Idx,program_font1,hS,snake2,2);
        }
    }
}

void highscore_subRoutine(int snakeIndex, TTF_Font* program_font1,scoreBoard_highscores *hS, Snake playerSnake,short whichSnake){
    SDL_RenderClear(renderer);
    char playerName[50];
    char playerPoints[50];
    sprintf(playerPoints,"%d",playerSnake.points);
    SDL_Rect r = { 150, 350, 420, 40 };
    boxRGBA(renderer,0,0,720,720,20,20,19,255);
    SDL_Color snakeColor = {playerSnake.r, playerSnake.g, playerSnake.b}, black = { 0, 0, 0 };
    SDL_Rect render_CongratsText_loc={100,150,520,40};
    SDL_Rect render_Points_loc={100,250,520,40};
    SDL_Rect render_Points_text_loc={100,280,520,40};
    renderText(program_font1,text_Surface,text_Texture,render_Points_loc,playerSnake.r, playerSnake.g, playerSnake.b,playerPoints);
    renderText(program_font1,text_Surface,text_Texture,render_Points_text_loc,playerSnake.r, playerSnake.g, playerSnake.b,"pont");
    if(whichSnake==1) renderText(program_font1,text_Surface,text_Texture,render_CongratsText_loc,playerSnake.r, playerSnake.g, playerSnake.b,"P1: Top10! Írd be a neved:");
    if(whichSnake==2) renderText(program_font1,text_Surface,text_Texture,render_CongratsText_loc,playerSnake.r, playerSnake.g, playerSnake.b,"P2: Top10! Írd be a neved:");
    enter_text(playerName, 25, r, black, snakeColor, program_font1, renderer);
    changeHighScoreList(&playerSnake,playerName,snakeIndex,hS);
}

