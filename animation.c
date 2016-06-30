#include "types.h"
#include "defines.h"
#include "animation.h"
#include "utilities.h"

///Printa Game Over na tela
void printGameOver()
{
    textcolor(RED);
    gotoxy(5,3);
    puts("     _____          __  __ ______    ______      ________ _____ ");
    puts("         / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ ");
    puts("        | |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |");
    puts("        | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  /");
    puts("        | |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ ");
    puts("         \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\ ");

    getch(); //pause
    system("cls");

}

///Printa na tela uma animação de texto
void ANIMATIONtext(char text[], int color)
{
    int i, adjusty=0, adjustx=0, limitpassed=0;

    textcolor(color);

    for(i=0; i<(strlen(text)); i++) // coloca as palavras na tela, verificando quando mudar de linha e pausando entre colocar uma e outra letra
    {
        gotoMapXY(adjustx, adjusty+10);
        printf("%c", text[i]);
        if(!kbhit())Sleep(50);
        if(((i%30)==0)&&i!=0) limitpassed=1;
        if(limitpassed &&(text[i]==' ' || text[i+1]==' '))
        {
            limitpassed=0;
            adjusty+=1;
            adjustx=0;
        }
        adjustx++;
    }
    gotoMapXY(0, adjusty + 11);  // mudar a posição que vai colocar o "Pressione qualquer tecla para continuar. . ."
    system("pause");

    limitpassed=0; // zerar as variáveis para colocar ' ' no lugar das letras
    adjustx=0;
    adjusty=0;

    for(i=0; i<(strlen(text)); i++)
    {
        gotoMapXY(adjustx, adjusty+10);
        printf(" ");
        if(((i%30)==0)&&i!=0) limitpassed=1;
        if((limitpassed &&(text[i]==' ' || text[i+1]==' '))||text[i]=='\n')
        {
            limitpassed=0;
            adjusty+=1;
            adjustx=0;
        }
        adjustx++;
    }
    for(i=0; i<(strlen("pressione qualquer tecla para continuar. . .")); i++) // apargar o "Pressione qualquer tecla para continuar. . ."
    {
        gotoMapXY(i, adjusty+11);
        printf(" ");
    }

}

///Dependendo do level, printa uma história diferente
void printHistoryLines(int level)
{
    switch(level)  // chamar os diálogos de cinemáticas, criando as scenas de cada parte do jogo
    {
    case 1:
        ANIMATIONtext("Hello Carlos, seek the guidance of the great master for answers - RANDOM VOICE IN YOUR HEAD THAT THE GAME PLACED SO IT WOULD LOOK MYSTERIOUS", GREY);
        break;
    case 2:
        ANIMATIONtext("I am the reptile master of metamorphosis and eating lasagna, but that last one in unecessary to pronounce, lets move on", PINK);
        ANIMATIONtext("It looks like you, Carlos, has been chosen by the stone of destiny that by obvious reasons is on the menu of this own game(sorry to break the 4th wall lol).", PINK);
        ANIMATIONtext("This means you are destined to save us, snakes.", PINK);
        ANIMATIONtext("You see, the rats are working on a plan to travel to Antartica, where there would be no snakes to eat them.", PINK);
        ANIMATIONtext("SIDE BAR : This plan is pretty dumb since they would starve to death.", PINK);
        ANIMATIONtext("WE HAVE TO STOP THIS!!", PINK);
        ANIMATIONtext("Your mission is to collect all 3 sacred artifacts, which I will not give any physic or any remote explanation about, hidden in each of their headquarters.", PINK);
        ANIMATIONtext("This headquarters are casually located nearby for no reason and have different extreme weather conditions so this game can have somewhat of a contrast.", PINK);
        ANIMATIONtext("BUT FIRST : you need to prove yourself by going through a trial.", PINK);
        ANIMATIONtext("I would wish you luck, but you will need more than that.....", PINK);
        break;
    case 3:
        ANIMATIONtext("YOU ARE READY!!!! NOW LET'S MOVE ON TO THE LIST OF SPECIAL ATTACKS!!", PINK);
        ANIMATIONtext("HADOUKEN :<v>B; SHORIOUKEN:<^^A;  MACHINE-GUN:BB; STAB:ABA; LASER-VISION:XBB  JUMP-KICK:ABB", PINK);
        ANIMATIONtext("JOKES ON YOU!! YOU'RE A FREAKING SNAKE YOU CAN'T HADOUKEN LOLOLOL", PINK);
        break;
    case 4:
        ANIMATIONtext("Hola! here lies the desert headquarter!", YELLOW);
        ANIMATIONtext("It's weird though, because every rat here speaks spanish", YELLOW);
        break;
    case 5:
        ANIMATIONtext("HIJO DE PUTA, DESAYUNÓ NUESTRAS TORTILLAS!!", YELLOW);
        break;
    case 6:
        ANIMATIONtext("So, in this forest headquarters, rats are savage.", GREEN);
        ANIMATIONtext("This doesn't mean a thing since they wont attack you, so they aren't special.", GREEN);
        break;
    case 7:
        ANIMATIONtext("Whatever, is not like we are important LOL", GREEN);
        break;
    case 8:
        ANIMATIONtext("This headquarter is the sea headquarter, where rats like surfing and enjoying the vibe", LIGHT_BLUE);
        break;
    case 9:
        ANIMATIONtext("HEY BRO, you killed our vibe, not cool bro... not cool...", LIGHT_BLUE);
        break;
    case 10:
        ANIMATIONtext("HEY YOU DID IT!! You are indeed worthy!!", PINK);
        ANIMATIONtext("BOOM", RED);
        ANIMATIONtext("WE WANT THE 3 RELIQUES WITH NO EXPLANATION! IF YOU GIVE THEM TO US WE WON'T SPARE YOUR LIVES!", GREY);
        ANIMATIONtext("That's the worst negociation I have ever been in... GO CARLOS!!", PINK);
        ANIMATIONtext("To go further into this amazing story, buy our DLC for only $200!!! OMG IT'S A BARGAIN", RED);
        system("cls");
        Sleep(10000);
        ANIMATIONtext("YOU JUST GOT PRANKE BRAH!", RED);
        break;

    }

    system("cls");
}

///Efeito de fade in
void fadeIN(int h, int w, int color, int option)
{
    int i, j;

    textcolor(color);

    for(i=0; i<h; i++)
        for(j=0; j<w; j++) //colocar um retângulo do tamanho do objeto a ser colocado na tela com o caracter mais diluído
        {
            if(option == 1)
                gotoMapXY(j, i);
            if(option == 2)
                gotoMenuXY(j, i);
            if(option == 3)
                gotoTITLE(j, i);
            printf("%c", 176);
        }
    Sleep(80);
    for(i=0; i<h; i++)  //colocar um retângulo do tamanho do objeto a ser colocado na tela com o caracter de média consistência
        for(j=0; j<w; j++)
        {
            if(option == 1)
                gotoMapXY(j, i);
            if(option == 2)
                gotoMenuXY(j, i);
            if(option == 3)
                gotoTITLE(j, i);
            printf("%c", 177);
        }
    Sleep(80);
    for(i=0; i<h; i++)  //colocar um retângulo do tamanho do objeto a ser colocado na tela com o caracter mais denso
        for(j=0; j<w; j++)
        {
            if(option == 1)
                gotoMapXY(j, i);
            if(option == 2)
                gotoMenuXY(j, i);
            if(option == 3)
                gotoTITLE(j, i);
            printf("%c", 178);
        }
    Sleep(80);
    for(i=0; i<h; i++)  // apagar os caracteres
        for(j=0; j<w; j++)
        {
            if(option == 1)
                gotoMapXY(j, i);
            if(option == 2)
                gotoMenuXY(j, i);
            if(option == 3)
                gotoTITLE(j, i);
            printf(" ");
        }
}

///Efeito de fade out
void fadeOUT(int h, int w, int color, int option)
{

    int i, j;

    textcolor(color);

    for(i=0; i<h; i++) //colocar um retângulo do tamanho do objeto a ser colocado na tela com o caracter mais denso
        for(j=0; j<w; j++)
        {
            if(option == 1)
                gotoMapXY(j, i);
            if(option == 2)
                gotoMenuXY(j, i);
            if(option == 3)
                gotoTITLE(j, i);
            printf("%c", 178);
        }
    Sleep(80);
    for(i=0; i<h; i++) //colocar um retângulo do tamanho do objeto a ser colocado na tela com o caracter de média consistência
        for(j=0; j<w; j++)
        {
            if(option == 1)
                gotoMapXY(j, i);
            if(option == 2)
                gotoMenuXY(j, i);
            if(option == 3)
                gotoTITLE(j, i);
            printf("%c", 177);
        }
    Sleep(80);
    for(i=0; i<h; i++) //colocar um retângulo do tamanho do objeto a ser colocado na tela com o caracter mais diluído
        for(j=0; j<w; j++)
        {
            if(option == 1)
                gotoMapXY(j, i);
            if(option == 2)
                gotoMenuXY(j, i);
            if(option == 3)
                gotoTITLE(j, i);
            printf("%c", 176);
        }
    Sleep(80);

    system("cls");

}

///Coloca na tela um mapa 10x30 para os diálogos
void printLOBBYdeCONVERSA(int color)
{
    int i, j;
    fadeIN(10, 30, color, 1);
    textcolor(color);

    for(i=0; i<10; i++)
        for(j=0; j<30; j++)
        {
            gotoMapXY(j, i);
            if(i==0 || i==9 || j==29 || j==0)printf("#");
            else if(i==5 && j==14)printf("-");
            else if(i==5 && j==15)printf("<");
            else printf(" ");
        }
}

///Coloca na tela a arte de cada nível
void print_lvlART(LEVEL_SCENE level, int plusx, int plusy)
{
    int i, j;
    textcolor(level.color);
    for(i=0; i<10; i++)
        for(j=0; j<20; j++)
        {
            gotoMapXY(j+plusx, i+plusy);
            printf("%c", level.art[i][j]);
        }
}
