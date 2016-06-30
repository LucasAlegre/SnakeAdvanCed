#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

///Printa o Ranking de Pontuação
void printHighScores();

///Atualiza o arquivo binário de pontuações
void uptadeHighScore(int score, FILE *arq);

///Lê o arquivo de texto correspondente ao nível atual e atualiza o mapa
void readMap(int level, int *rows, int *columns, char map[][COLUMNSMAX],int *rocksNum, POSN rocks[], POSN *initialCoord);

#endif // FILES_H_INCLUDED
