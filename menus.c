#include "menus.h"
#include "io.h"

ButtonBox mainMenu[3]={
        {1,216,233,168,360-200,720/2-100,360+200,720/2-50,"Játék",26,26,25},
        {2,216,233,168,720/2-200,720/2-25,720/2+200,720/2+25,"Dicsőségtábla",26,26,25},
        {3,216,233,168,720/2-200,720/2+50,720/2+200,720/2+100,"Kilépés",149,1,1}
};

ButtonBox gameSettingsMenu[10]={
        {1,216,233,168,150,120,320,160,"1 Játékos",26,26,25},
        {2,77,77,77,400,120,570,160,"2 játékos",26,26,25},
        {-1,213,113,73,60,310,130,385,"P1",0,0,0}, //Kígyó 1 előnézet
        {103,213,113,73,175+25,322,225+25,372,"",26,26,25},//Kígyó szín 1:1
        {104,21, 109, 150,240+25,322,290+25,372,"",26,26,25},//Kígyó szín 1:2
        {105,1212, 192, 174,305+25,322,355+25,372,"",26,26,25},//Kígyó szín 1:3
        {106,26, 193, 199,370+25,322,420+25,372,"",26,26,25},//Kígyó szín 1:4
        {107,205, 230, 69,435+25,322,485+25,372,"",26,26,25},//Kígyó szín 1:5
        {5,216,233,168,(720/2-100),720/2+190,(720/2+100),720/2+230,"Kezdés",26,26,25},
        {3,216,233,168,(720/2-100),720/2+250,(720/2+100),720/2+290,"Menü",26,26,25}

};

ButtonBox gameSettingsMenu_multi[6]={
        {-1,109,152,134,60,410,130,485,"P2",0,0,0}, //Kígyó 2 előnézet
        {201,109,152,134,175+25,422,225+25,472,"",26,26,25},//Kígyó szín 2:1
        {202,176, 19, 90,240+25,422,290+25,472,"",26,26,25},//Kígyó szín 2:2
        {203,85, 62, 168,305+25,422,355+25,472,"",26,26,25},//Kígyó szín 2:3
        {204,35, 68, 186,370+25,422,420+25,472,"",26,26,25},//Kígyó szín 2:4
        {205,176, 114, 77,435+25,422,485+25,472,"",26,26,25},//Kígyó szín 2:5
};

ButtonBox inGameMenu[1]={
        {0,255,255,53,15,645,100,675,"Menü",149,30,1}
};

scoreBoard_highscores_Elements create_highscores_menuElements(scoreBoard_highscores sB_H){
    scoreBoard_highscores_Elements tmp;
    char scoreStr[10];
    for(int i=0;i<10;i++){
        ButtonBox tmpButtonBox={i,21,45,53,120+5,0+(i*72),600+5,50+(i*72),sB_H.data[i].name,213,113,73};
        if(sB_H.data[i].score!=0){
            sprintf(scoreStr,"%d",sB_H.data[i].score);
            strcat(tmpButtonBox.text,"  -  ");
            strcat(tmpButtonBox.text,scoreStr);
        }
        tmp.menuElements[i]=tmpButtonBox;
    }
    ButtonBox tmpExit={100,255,255,53,5,5,75,35,"Menü",149,1,1};
    tmp.menuElements[10]=tmpExit;
    return tmp;
}

int checkClick(ButtonBox *buttons,int menuLen,int mousePosX, int mousePosY){
    for(int i=0;i<menuLen;i++){
        int boxPosX1=buttons[i].posX1;
        int boxPosX2=buttons[i].posX2;
        int boxPosY1=buttons[i].posY1;
        int boxPosY2=buttons[i].posY2;
        if((mousePosX>=boxPosX1 && mousePosX<=boxPosX2) && ((mousePosY>=boxPosY1 && mousePosY<=boxPosY2))){
            return buttons[i].value;

        }
    }
    return -1;
}
