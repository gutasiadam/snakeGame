#include "Headers/menus.h"
#include "Headers/io.h"

ButtonBox mainMenu[3]={
        {1,216,233,168,360-200,720/2-100,360+200,720/2-50,"Játék",26,26,25},
        {2,216,233,168,720/2-200,720/2-25,720/2+200,720/2+25,"Dicsőségtábla",26,26,25},
        {3,216,233,168,720/2-200,720/2+50,720/2+200,720/2+100,"Kilépés",149,1,1}
};

ButtonBox gameSettingsMenu[11]={
        {-1,213,113,73,(720/2-200)-100,720/2-25,(720/2-200)-50,720/2+25,"P1",0,0,0}, //Kígyó 1 előnézet
        {-1,109,152,134,(720/2-200)-100,720/2+50,(720/2-200)-50,720/2+100,"P2",0,0,0}, //Kígyó 2 előnézet
        {1,216,233,168,(720/2-100),720/2+120,(720/2+100),720/2+160,"1 Játékos mód",26,26,25},
        {103,213,113,73,(720/2)-20,720/2-25,(720/2)+30,720/2+25,"",26,26,25},//Kígyó szín 1:1
        {104,99, 97, 96,(720/2)+50,720/2-25,(720/2)+100,720/2+25,"",26,26,25},//Kígyó szín 1:2
        {105,129, 168, 22,(720/2)+120,720/2-25,(720/2)+170,720/2+25,"",26,26,25},//Kígyó szín 1:3
        {2,216,233,168,(720/2-100),720/2+190,(720/2+100),720/2+230,"2 játékos mód",26,26,25},
        {207,109,152,134,(720/2)-20,720/2+50,(720/2)+30,720/2+100,"",26,26,25},//Kígyó szín 2:1
        {208,186, 13, 88,(720/2)+50,720/2+50,(720/2)+100,720/2+100,"",26,26,25},//Kígyó szín 2:2
        {209,51, 42, 133,(720/2)+120,720/2+50,(720/2)+170,720/2+100,"",26,26,25},//Kígyó szín 2:3
        {3,216,233,168,(720/2-100),720/2+250,(720/2+100),720/2+290,"Vissza",26,26,25}

};

ButtonBox inGameMenu_multi[1]={
        {0,21,45,53,0,650,100,690,"Kilépés",149,1,1}
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
    ButtonBox tmpExit={100,21,45,53,5,680,30,710,"X",149,1,1};
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
