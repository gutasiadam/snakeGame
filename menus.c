#include "Headers/menus.h"
#include "Headers/io.h"

ButtonBox mainMenu[3]={
        {1,216,233,168,360-200,720/2-100,360+200,720/2-50,"Játék",26,26,25},
        {2,216,233,168,720/2-200,720/2-25,720/2+200,720/2+25,"Dicsőségtábla",26,26,25},
        {3,216,233,168,720/2-200,720/2+50,720/2+200,720/2+100,"Kilépés",149,1,1}
};

ButtonBox gameSettingsMenu[2]={
        {1,216,233,168,720/2-200,720/2-25,720/2+200,720/2+25,"1",26,26,25},
        {2,216,233,168,720/2-200,720/2+50,720/2+200,720/2+100,"2",26,26,25}
};

ButtonBox inGameMenu_solo[1]={
        //{0,21,45,53,720/2-100,720-((720-600)/2)-50,720/2+100,720-((720-600)/2)+50,"Pontszám",213,113,73},
        {0,21,45,53,0,650,100,690,"Kilépés",149,1,1}
};

ButtonBox inGameMenu_multi[1]={
        //{0,21,45,53,15,720-((720-600)/2)-50,215,720-((720-600)/2)+50,"Pontszám1: ",213,113,73},
        //{0,21,45,53,520,720-((720-600)/2)-50,720,720-((720-600)/2)+50,"Pontszám2: ",213,113,73},
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
            printf("Clicked it! %d\n",i);
            return buttons[i].value;

        }
    }
    return -1;
}
