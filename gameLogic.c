/*! \file gameLogic.c
    \brief A játék közbeni vezérlés, és a menük előkészítéséért, és rendereléséért felelős modul.
*/

#include "Headers/debugmalloc.h"
#include "Headers/gameLogic.h"
#include "Headers/graphics.h"

global_Settings globalSettings={false,
                                true,
                                true,
                                false,
                                true,
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
void mainMenu_init(TTF_Font *font1,TTF_Font *font2,global_Settings *g){
    printf("InitMainMenu\n");
    boxRGBA(renderer,0,720,720,0,26,26,25,255);
    renderMenu_middle(font1,text_Surface,text_Texture,renderer,mainMenu,3);
    SDL_Rect where={720/2,150};
    renderText_middle(font2,text_Surface,text_Texture,where,78,159,61,"Snake");
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
    printf("MainMenuLogic ready.\n");
    //while(*f_show_mainMenu){
    while (g->show_mainMenu){
        //printf("Waiting for input.\n");
        SDL_WaitEvent(&event);
        int mX, mY;
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        SDL_GetMouseState(&mX,&mY);
                        printf("\nMouse @ %d %d",mX,mY);
                        switch(checkClick(mainMenu,3,mX,mY)){
                            case(1):
                                g->show_gameSettings=true;
                                //game=true; drawMainMenu=false;
                                // ;
                                g->game_Init=false;
                                g->show_mainMenu=false;
                                return;
                                break;
                            case(2):
                                printf("HighscoreBoard click\n");
                                g->show_mainMenu=false;
                                g->init_highScoreboard=true;
                                //g->exitGame=true;
                                return;
                                break;
                            case(3):
                                g->show_mainMenu=false;
                                g->exitGame=true;
                                //*quit=true;
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
                        return; break;// *quit=true;
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

void render_gameSettingsMenu(TTF_Font *font1,global_Settings *g){
    boxRGBA(renderer,0,720,720,0,26,26,25,255);
    renderMenu_middle(font1,text_Surface,text_Texture,renderer,gameSettingsMenu,2);
    SDL_Rect where={720/2,150};
    renderText_middle(font1,text_Surface,text_Texture,where,78,159,61,"Játékosok száma");
    g->show_gameSettings=true;
    SDL_RenderPresent(renderer);
    printf("[gameSettings] Menu display complete.\n");
}

/*! \fn void gameSettingsLogic(global_Settings *g)
    \brief A játék indítása előtti almenü vezérlését kezelő függvény.
    egérgomlenyomás esetén meghívja a checkClick() függvényt, ellenőrizve, hogy rákattintott-e valamire a játékos.
    Az eredmény alapján átállítja a játék globális beállításait.
    \param g A játék globális beállításait tartalmazó struct.
*/
void gameSettingsLogic(global_Settings *g){
    printf("[gameSettings] logic begin\n");
    int mX, mY;
    while(g->show_gameSettings) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        SDL_GetMouseState(&mX, &mY);
                        printf("Mouse @ %d %d\n", mX, mY);
                        switch (checkClick(gameSettingsMenu, 2, mX, mY)) {
                            case (1):
                                //printf("Valid click detected\n");
                                g->game_Init=true;
                                g->show_gameSettings=false;
                                g->twoPlayerMode=false;
                                g->show_mainGame=true;
                                return;
                                break;
                            case (2):
                                //printf("Valid click detected\n");
                                g->game_Init=true;
                                g->show_gameSettings=false;
                                g->twoPlayerMode=true;
                                g->show_mainGame=true;
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
void render_highScoresMenu(TTF_Font *font1,global_Settings *g,scoreBoard_highscores_Elements m){
    boxRGBA(renderer,0,720,720,0,26,26,25,255);
    renderMenu_middle(font1,text_Surface,text_Texture,renderer,m.menuElements,10);
    //ButtonBox back[1]={{100,21,45,53,5,680,30,710,"X",149,1,1}};
    renderMenu(font1,text_Surface,text_Texture,renderer,&m.menuElements[10],1); /* A bezáró gomb kirenderelése. Azért kell külön, mert ez nem középre kerül. */
    SDL_Rect where={0,650};
    //renderText(font1,text_Surface,text_Texture,where,78,159,61,"Visszalépés: BackSpace / X");
    g->show_highScoreboard=true;
    g->init_highScoreboard=false;
    SDL_RenderPresent(renderer);
    printf("[highScores] Menu display complete.\n");
}

/*! \fn void highScoresMenuLogic(global_Settings *g)
    \brief A dicsőségtábla vezérlő függvénye
    egérgomlenyomás esetén meghívja a checkClick() függvényt, ellenőrizve, hogy rákattintott-e valamire a játékos.
    Az eredmény alapján átállítja a játék globális beállításait.
    \param g A játék globális beállításait tartalmazó struct.
*/
void highScoresMenu_Logic(global_Settings *g,scoreBoard_highscores_Elements highScoreMenu){
    //printf("[gameSettings] logic begin\n");
    int mX, mY;
    while(g->show_highScoreboard) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        SDL_GetMouseState(&mX, &mY);
                        printf("Mouse @ %d %d\n", mX, mY);
                        switch (checkClick(highScoreMenu.menuElements, 11, mX, mY)) {
                            case (100):
                                printf("Valid click detected\n");
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

void inGameButtons(ButtonBox *buttons,TTF_Font *font1,TTF_Font *font2,int len){
    //printf("RenderInGameButtons\n");
    //boxRGBA(renderer,0,720,720,0,26,26,25,255);
    renderMenu(font1,text_Surface,text_Texture,renderer,buttons,len);
    SDL_Rect where={720/2,150};
    //renderText(font2,text_Surface,text_Texture,where,78,159,61,"Snake");
    SDL_RenderPresent(renderer);
}

/*! \fn void mainGame_Logic(TTF_Font *font1,TTF_Font *font2,global_Settings *g, Snake *snake1, Snake *snake2)
    \brief A játék futása alatti grafikai folyamatok kezelése.
    \param font1 A játék első betűtípusa.
    \param font2 A játék második betűtípusa.
    \param g A játék globális beállításait tartalmazó struct.
    \param snake1 Az első játékos kígyójának adatai
    \param snake2 A második játékos kígyójának adatai
*/
void mainGame_Logic(TTF_Font *font1,TTF_Font *font2,global_Settings *g, Snake *snake1, Snake *snake2,scoreBoard_highscores *hS,SDL_TimerID fruitTimer){
    SnakeBodyList s1L; init_SnakeBody(&s1L);
    SnakeBodyList s2L; init_SnakeBody(&s2L);
    bool collision=false;
    fruit* fruitList;
    fruitList=NULL;
    SDL_TimerID SnakeMoveTimer= SDL_AddTimer(150,allow_moveSnake,NULL);
    fruitTimer=SDL_AddTimer(2000,allow_fruitRender,NULL);
    while(g->show_mainGame){
        SDL_WaitEvent(&event);
        // Ha egymásba vagy a saját testükbe ütköznek.
        collision=(checkBodyCollision(&s2L,snake1) || checkBodyCollision(&s1L,snake2)); //  checkBodyCollision(&s1L,snake1) || checkBodyCollision(&s2L,snake2)
        switch (event.type){
            case SDL_QUIT:
                g->isRunning=false;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_BACKSPACE:
                        collision=true;
                        destroyFruitList(fruitList);
                        destroy_snakeBody(&s1L);
                        destroy_snakeBody(&s2L);
                        SDL_RemoveTimer(fruitTimer);
                        SDL_RemoveTimer(SnakeMoveTimer);
                        SDL_RenderClear(renderer);
                        g->show_mainGame=false;
                        g->init_mainMenu=true;
                        g->init_gameSettings=false;
                        g->game_Init=false;
                        g->show_gameSettings=false;
                        resetSnake(snake1); resetSnakePoints(snake1);
                        resetSnake(snake2); resetSnakePoints(snake2);
                        break;
                }
                break;
            case SDL_KEYDOWN:
                P1_Controller(snake1,event);
                if(g->twoPlayerMode)
                    P2_Controller(snake2,event);
                break;
            case SDL_USEREVENT:
                if(event.user.code==43){
                    moveBody(&s1L,snake1);
                    snake1->x+=snake1->vx;
                    snake1->y+=snake1->vy;
                }
                //gyümölcsökkel érintkezés ellenőrzése
                fruit *s1F=checkCollision(fruitList,*snake1);
                fruit *s2F=checkCollision(fruitList,*snake2);
                if(s1F!=NULL) {
                    add_BodyElement(&s1L,*snake1);
                    //traverse_snakeBody(s1L);
                    snake1->points++;
                    fruitList=deleteFruit(fruitList, s1F);
                }
                if(s2F!=NULL){
                    add_BodyElement(&s2L,*snake2);
                    snake2->points++;
                    fruitList=deleteFruit(fruitList, s2F);
                }
                if (checkWallHit(*snake1)){
                    resetSnake(snake1);
                    resetSnake(snake2);
                    collision=true;
                    printf("%s:%d elso utkozik",__FILE_NAME__,__LINE__);
                }
                if(g->twoPlayerMode){
                    if(event.user.code==43) {
                        moveBody(&s2L,snake2);
                        snake2->x += snake2->vx;
                        snake2->y += snake2->vy;
                    }
                    if (checkWallHit(*snake2)){
                        printf("%s:%d masodik utkozik",__FILE_NAME__,__LINE__);
                        resetSnake(snake1);
                        resetSnake(snake2);
                        collision=true;
                    }
                }
                SDL_FlushEvent(SDL_LASTEVENT);
                if(collision){
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
                    SDL_FlushEvent(SDL_USEREVENT);
                    int s1Idx= checkScore(snake1,*hS);//s1 rekordindexe
                    int s2Idx= checkScore(snake2,*hS);//s2 rekordindexe
                    SDL_Rect r = { 150, 350, 420, 40 };

                    char playerName[50];
                    boxRGBA(renderer,100,100,620,620,20,20,19,40);
                    SDL_Color feher = {255, 255, 255}, fekete = { 0, 0, 0 };
                    SDL_Rect render_CongratsText={100,150,520,40};
                    if(s1Idx!=-1 && s2Idx!=-1){
                        renderText_middle(font1,text_Surface,text_Texture,render_CongratsText,0,0,0,"top10! Írd be a neved:");
                        input_text(playerName, 50, r, fekete, feher, font1, renderer);
                        printf("%s\n",playerName);
                        //mindkettő rekorder
                        if(s1Idx==s2Idx){
                            //mindekettő ugyannál a számnál nagyobb.
                            if(snake1->points>snake2->points){
                                //ha snake1 pontszáma nagyobb, akkor először a kisebbet kell belemozganti a listába, majd snake2-t.
                                changeHighScoreList(snake2,playerName,s2Idx,hS);
                                //ha snake1 bele lett mozgatva a listába, akkor jöhet snake2, pont snake1 alá.
                                changeHighScoreList(snake1,playerName,s1Idx,hS);
                            }else{
                                //ha snake1 pontszáma nagyobb, akkor először a kisebbet kell belemozganti a listába, majd snake2-t.
                                changeHighScoreList(snake1,playerName,s1Idx,hS);
                                //ha snake1 bele lett mozgatva a listába, akkor jöhet snake2, pont snake1 alá.
                                changeHighScoreList(snake2,playerName,s2Idx,hS);
                            }
                        }
                    }else{
                        renderText_middle(font1,text_Surface,text_Texture,render_CongratsText,0,0,0,"top10! Írd be a neved:");
                        input_text(playerName, 50, r, fekete, feher, font1, renderer);
                        printf("%s\n",playerName);
                        if(s1Idx!=-1){
                            changeHighScoreList(snake1,playerName,s1Idx,hS);
                        }
                        if(s2Idx!=-1){
                            changeHighScoreList(snake2,playerName,s2Idx,hS);
                        }
                    }
                    resetSnakePoints(snake1);
                    resetSnakePoints(snake2);

                    break; // már ne próbáljon meg renderelni, vége a játéknak.
                }
                //kirajzolas, mehet a kepernyore */
                boxRGBA(renderer,0,600,720,0,184,82,82,255); //keret (határ) kirenderlése, ennek ütközhet neki a kígyó.
                boxRGBA(renderer,20,580,700,20,217,202,179,255);// pálya újra kirajzolása, ezzel a kígyó előző pozíciójainak kitörlése

                boxRGBA(renderer,snake1->x,snake1->y,snake1->x+20,snake1->y+20,snake1->r,snake1->g,snake1->b,255);// P1 fej renderelése
                renderSnakeBody(&s1L,*snake1);//P1 test renderelése

                if(g->twoPlayerMode){
                    boxRGBA(renderer,snake2->x,snake2->y,snake2->x+20,snake2->y+20,snake2->r,snake2->g,snake2->b,255);//P2 fej renderelése
                    renderSnakeBody(&s2L,*snake2); // test renderelése,
                }
                if(event.user.code==42){ // gyümölcs hozzáadás
                    fruitList=add_Fruit(fruitList);
                }

                //Minden egyes gyümölcs kirenderelése:
                fruit *m;
                if(fruitList!=NULL){
                    m=fruitList;
                    for (m; m != NULL; m = m->nextFruit){
                        int px=m->x; int py=m->y;
                        boxRGBA(renderer,px,py,px+20,py+20,0,0,255,255);
                    }
                }
                SDL_Rect renderPoints_snake1={0,650,0,0};
                SDL_Rect renderPoints_snake2={0,690,0,0};
                inGameButtons(inGameMenu_multi,font1,font2,1);
                char pSnake1[50];
                char pSnake2[50];
                sprintf(pSnake1,"%d",snake1->points);
                sprintf(pSnake2,"%d",snake2->points);
                roundedBoxRGBA(renderer,200,640,500,720,20,0,0,0,255);
                roundedBoxRGBA(renderer,200,640,500,720,20,20,20,19,255);
                renderText_middle(font1,text_Surface,text_Texture,renderPoints_snake1,snake1->r,snake1->g,snake1->b,pSnake1);
                if(g->twoPlayerMode){
                    renderText_middle(font1,text_Surface,text_Texture,renderPoints_snake2,snake2->r,snake2->g,snake2->b,pSnake2);
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
void resetSnake(Snake *s1){
    s1->vx=0; s1->vy=0; s1->x=50; s1->y=50;
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
            //snake1->left = true;
            if(snake1->lastPos!='R'){
                snake1->vx=-0.25*moveMentScale;
                snake1->vy=0;
                snake1->lastPos='L';
            }
            break;
        case SDLK_RIGHT:
            //snake1->right = true;
            if(snake1->lastPos!='L') {
                snake1->vx = 0.25 * moveMentScale;
                snake1->vy = 0;
                snake1->lastPos='R';
            }
            break;
        case SDLK_UP:
            //snake1->up = true;
            if(snake1->lastPos!='D') {
                snake1->vx = 0;
                snake1->vy = (-0.25) * moveMentScale;
                snake1->lastPos='U';
            }
            break;
        case SDLK_DOWN:
            //snake1->down=true;
            if(snake1->lastPos!='U') {
                snake1->vx = 0;
                snake1->vy = 0.25 * moveMentScale;
                snake1->lastPos='D';
            }
            break;
    }
}
void P2_Controller(Snake *snake2, SDL_Event ev){
    switch (event.key.keysym.sym) {
        case SDLK_a:
            //snake1->left = true;
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
    \return Ha top10-nek számít, akkor visszatér azzal az indexel, aminek adatánál nagyobb az elért eredmény.
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
    highScorePlayer tmpPlayer={"Test", s->points};
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
        printf("%s %d\n",h->data[j].name,h->data[j].score);
    }
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

        SDL_Event event;
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
fruit* add_Fruit(fruit* firstFruit){
    SDL_Color fC={255,0,255};
    int posX=20*(rand()%34)+20;
    int posY=20*(rand()%28)+20;
    fruit *newFruit;
    newFruit=(fruit*) malloc(sizeof(fruit));
    newFruit->x=posX; newFruit->y=posY; newFruit->color=fC;
    newFruit->nextFruit=firstFruit;
    firstFruit=newFruit;

    return firstFruit;
}

fruit* destroyFruitList(fruit* fruitList){
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
    //SDL_Rect snakeHead={s.x,s.y,20,20};
    //SDL_Rect fruitRect={0,0,20,20};
    //bool isColliding;
    fruit *m;
    for (m = fruitList; m != NULL; m = m->nextFruit){
        fruitX=m->x;fruitY=m->y;
        if(snakeX==fruitX && SnakeY==fruitY) {
            //printf("Checking collision");
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

/*! \fn void add_BodyElement(SnakeBodyList *o,Snake s)
    \brief Megnöveli a kígyó hosszát 1-gyel.
    \param o A kígyó testét tartalmazó SnakeBodyList struct
    \param s A kígyó fejét tartalmazú struct.s
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
    //bejárás hátulról
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
    if (s.x<=0 || s.x>=700 || s.y<=0 || s.y>=580)
        return true;
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
void exitProgram(global_Settings *g,TTF_Font* font1,TTF_Font* font2,SDL_TimerID id,FILE *fp,scoreBoard_highscores *highscores){
    globalSettings.isRunning=false;
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
    SDL_RemoveTimer(id);
    SDL_Delay(500);
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

