#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
typedef struct ButtonBox{
    int value;
    int colorR;
    int colorG;
    int colorB;
    int posX1;
    int posY1;
    int posX2;
    int posY2;
    char* text;
    int textColorR;
    int textColorG;
    int textColorB;
}ButtonBox;
ButtonBox mainMenu[3]={
        {1,216,233,168,360-200,720/2-100,360+200,720/2-50,"Játék",26,26,25},
        {2,216,233,168,720/2-200,720/2-25,720/2+200,720/2+25,"Dicsőségtábla",26,26,25},
        {3,216,233,168,720/2-200,720/2+50,720/2+200,720/2+100,"Kilépés",149,1,1}
};

ButtonBox gameSettingsMenu[2]={
        {1,216,233,168,720/2-200,720/2-25,720/2+200,720/2+25,"1",26,26,25},
        {2,216,233,168,720/2-200,720/2+50,720/2+200,720/2+100,"2",26,26,25}
};

ButtonBox inGameMenu_solo[2]={
        {0,21,45,53,720/2-100,720-((720-600)/2)-50,720/2+100,720-((720-600)/2)+50,"Pontszám",213,113,73},
        {0,21,45,53,720-100,720-((720-600)/2)-50,720,720-((720-600)/2)+50,"Kilépés",149,1,1}
};

ButtonBox inGameMenu_multi[3]={
        {0,21,45,53,15,720-((720-600)/2)-50,215,720-((720-600)/2)+50,"Pontszám1: ",213,113,73},
        {0,21,45,53,520,720-((720-600)/2)-50,720,720-((720-600)/2)+50,"Pontszám2: ",213,113,73},
        {0,21,45,53,720/2-200,720/2+50,720/2+200,720/2+100,"Kilépés",149,1,1}
};

ButtonBox create_highScore_menu_elements(dynamic_ScoreBoard const *sB, int const lenofScoreBoard){
    ButtonBox temp[lenofScoreBoard];
    for(int i=0;i<lenofScoreBoard;i++){
        temp[i].value=0;
        temp[i].colorR=21;
        temp[i].colorG=45;
        temp[i].colorB=53;
        temp[i].posX1=21; temp[i].posX2=21;
        temp[i].posY1=21; temp[i].posY2=21;
        temp[i].text=(sB->data[i].name)+((int) sB->data[i].score);
    }
}

int checkClick(ButtonBox *buttons,int menuLen,int mousePosX, int mousePosY){
    for(int i=0;i<menuLen;i++){
        int boxPosX1=buttons[i].posX1;
        int boxPosX2=buttons[i].posX2;
        int boxPosY1=buttons[i].posY1;
        int boxPosY2=buttons[i].posY2;
        if((mousePosX>=boxPosX1 && mousePosX<=boxPosX2) && ((mousePosY>=boxPosY1 && mousePosY<=boxPosY2))){
            //printf("Clicked it!\n");
            return buttons[i].value;

        }
    }
    return -1;
}
