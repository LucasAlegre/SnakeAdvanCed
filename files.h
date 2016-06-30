#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

///Printa o Ranking de Pontua��o
void printHighScores();

///Atualiza o arquivo bin�rio de pontua��es
void uptadeHighScore(int score, FILE *arq);

///L� o arquivo de texto correspondente ao n�vel atual e atualiza o mapa
void readMap(int level, int *rows, int *columns, char map[][COLUMNSMAX],int *rocksNum, POSN rocks[], POSN *initialCoord);

#endif // FILES_H_INCLUDED
