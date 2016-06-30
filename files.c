#include "types.h"
#include "defines.h"
#include "files.h"
#include "utilities.h"

///Printa o Ranking de Pontua��o
void printHighScores()
{
    FILE *arq;
    PLAYER rankStory[15];  //rank para o modo story
    PLAYER rankSurvival[15];  //rank para o modo survival
    int i;  //contador para o for
    int line;  //auxiliar para formata��o do print

    arq = fopen("highscore.bin", "rb");
    if(arq == NULL)
        printf("error");
    fread(rankStory, sizeof(PLAYER), 15, arq);   //l� o ranking do modo story
    fclose(arq);

    arq = fopen("highscore_survival.bin", "rb");
    if(arq == NULL)
        printf("error");
    fread(rankSurvival, sizeof(PLAYER), 15, arq);   //l� o ranking do modo survival
    fclose(arq);

    printf("\n%38s\n\n", "Highscores");

    textcolor(BLUE2);
    printf("      Story Mode:\n\n");
    for(i=0; i<15; i++)  //printa os 15 melhores colocados do modo story
    {
        printf("    %2d - %-5s        %04d\n", i+1, rankStory[i].name, rankStory[i].score);
    }

    textcolor(RED);
    gotoxy(43,3);
    printf("Survival Mode:\n\n");
    line = 5;
    for(i=0; i<15; i++)   //printa os 15 melhores colocados do modo survival
    {
        gotoxy(40, line);
        printf(" %2d - %-5s        %04d\n", i+1, rankSurvival[i].name, rankSurvival[i].score);
        line++;;
    }

    getch(); //pausa at� uma tecla ser apertada
    system("cls");
}

///Atualiza o arquivo bin�rio de pontua��es
void uptadeHighScore(int score, FILE *arq)
{
    int i, j; //contadores de for
    BOOL recorded;  //Flag que indica se o jogador atual entrou no rank
    PLAYER rank[15]; //Jogadores com melhor pontua��o
    PLAYER player;

    fread(rank, sizeof(PLAYER), 15, arq); //L� as 15 coloca��es do rank e fecha o arquivo

    player.score = score;

    recorded = 0;
    i=0;
    while(i<15 && recorded == 0)  //testa as 15 coloca��es enquanto n�o terminar e n�o for encontrado a posi��o certa
    {
        if(player.score > rank[i].score)  //Come�ando do primeiro colocado, confere se o jogador tem pontua��o maior
        {
            printf(" Enter your name:\n");  //l� o nome do jogador
            gets(player.name);

            for(j=14; j>i; j--)
            {
                rank[j] = rank[j-1];    //Diminui uma posi��o no rank todos os jogadores abaixo do jogador
            }

            rank[i] = player;   //insere o jogador na sua posi��o correta
            recorded = 1;     //indica que o jogador j� foi colocado no rank
        }
        i++;
    }

    if(recorded == 1)  //Se o jogador entrou no rank, escreve novo rank no arquivo
    {
        rewind(arq);
        fwrite(rank, sizeof(PLAYER), 15, arq);
    }

    fclose(arq); //fecha o arquivo
}

///L� o arquivo de texto correspondente ao n�vel atual e atualiza o mapa
void readMap(int level, int *rows, int *columns, char map[][COLUMNSMAX],int *rocksNum, POSN rocks[], POSN *initialCoord)
{
    FILE *arq;
    int x, y;

    for(y = 0; y < ROWSMAX; y++)       //limpa a matriz do mapa antes de ler um novo mapa
    {
        for(x = 0; x < COLUMNSMAX; x++)
        {
            map[y][x] = ' ';
        }
    }

    switch(level)
    {
    case 1:
        if(!(arq = fopen("Levels\\level1.txt", "r")))
            perror("Error!\n");
        break;
    case 2:
        if(!(arq = fopen("Levels\\level2.txt", "r")))
            printf("Error!\n");
        break;
    case 3:
        if(!(arq = fopen("Levels\\level3.txt", "r")))
            printf("Error!\n");
        break;
    case 4:
        if(!(arq = fopen("Levels\\level4.txt", "r")))
            printf("Error!\n");
        break;
    case 5:
        if(!(arq = fopen("Levels\\level5.txt", "r")))
            printf("Error!\n");
        break;
    case 6:
        if(!(arq = fopen("Levels\\level6.txt", "r")))
            printf("Error!\n");
        break;
    case 7:
        if(!(arq = fopen("Levels\\level7.txt", "r")))
            printf("Error!\n");
        break;
    case 8:
        if(!(arq = fopen("Levels\\level8.txt", "r")))
            printf("Error!\n");
        break;
    case 9:
        if(!(arq = fopen("Levels\\level9.txt", "r")))
            printf("Error!\n");
        break;
    case 10:
        if(!(arq = fopen("Levels\\level10.txt", "r")))
            printf("Error!\n");
        break;
    case 11:
        if(!(arq = fopen("Levels\\level11.txt", "r")))
            printf("Error!\n");
        break;
    case 12:
        if(!(arq = fopen("Levels\\level12.txt", "r")))
            printf("Error!\n");
        break;
    case 13:
        if(!(arq = fopen("Levels\\level13.txt", "r")))
            printf("Error!\n");
        break;
    case 42:
        if(!(arq = fopen("Levels\\survival.txt", "r")))
            printf("Error!\n");
        break;
    }

    fscanf(arq, "%d %d\n", rows, columns);  //l� o n�mero de linhas e colunas do arquivo de texto

    for(y=0; y< *rows; y++) //l� todas as linhas do mapa
    {
        fgets(map[y], *columns + 2, arq);  //(+1 para o \0 e +1 para o \n)
    }

    fclose(arq);

    *rocksNum = 0; //zera o n�mero de pedras
    for(y = 0; y < *rows; y++)
    {
        for(x = 0; x < *columns; x++)
        {
            if(map[y][x] == '*')   //grava as coordenadas das pedras e contabiliza o n�mero de pedras
            {
                rocks[*rocksNum].x = x;
                rocks[*rocksNum].y = y;
                (*rocksNum)++;
            }
            else if(map[y][x] == 'O')  //grava a posi��o que a snake deve iniciar
            {
                initialCoord->x = x;
                initialCoord->y = y;
            }
        }
    }
}
