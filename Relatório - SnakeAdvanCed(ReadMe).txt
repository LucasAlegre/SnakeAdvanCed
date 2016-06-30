INF01202 ALGORITMOS E PROGRAMA��O 2016/1 - Trabalho Final
Prof. Marcelo Walter
Prof. Rodrigo Ruas Oliveira

Guilherme Gomes Haetinger 00274702
Lucas Nunes Alegre 00274693        

    Para jogar, execute o arquivo SnakeAdvanced.exe encontrado nessa pasta, � importante que o os arquivos .c e .h estejam
na mesma pasta do arquivo .exe e que os arquivos de texto dos n�veis estejam na pasta "Levels".
    � poss�vel tamb�m abrir o arquivo do projeto no codeblocks, apertando F9 para compilar e rodar o jogo.	

            SNAKE ADVANCED

	Nosso trabalho, seguindo as especifica��es ditadas pelos professores, � dividido
em uma s�rie de conjuntos de fun��es, cada um com um devido objetivo e efetuado pelo grupo 
como um todo:

     main.c : Cont�m a fun��o main(), que efetua a fun��o Menu() do conjunto Menu.c at� uma das 5 op��es 
listadas nele serem escolhidas. Quando escolhida, a op��o redireciona o usu�rio para uma fun��o espec�fica,
sendo ou (SCORES) printHighScores() do conjunto Files.c, (STORY MODE) StoryMode() do conjunto Snake.c, 
(INSTRUCTIONS) printInstructons() do conjunto Menu.c, (SURVIVAL) ou (EXIT) que efetua a sa�da do jogo.

    snake.c : Cont�m as fun��es que implementam efitavamente a mec�nica do jogo e as fun��es que controlam os dois modos
de jogo, Story e Survival. Como por exemplo a fun��o void updateSnakeCoord(SNAKE *snake), que recebe uma estrutura snake 
e faz a mudan�a da coordenada de cada parte da snake a cada la�o de jogo.
    No modo story, temos a fun��o void storyMode(), que controla o jogo inicializando as pontua��es, vidas, etc e executando
a fun��o void playOneLevel(int level, int objetivo, int speed, LEVEL_SCENE scenario, int *lifes, int *score), que recebe
respectivamente o n�mero da fase, o n�mero de ratos necess�rios para completar a fase, a velocidade inicial da fase, o cen�rio
da fase, os n�meros de vidas e pontua��es atuais do jogador. Desse modo, se o jogador terminar a fase(comeu a ma��), a
vari�vel level � incrementada e dentro de um switch de fases, outra fase do jogo � executada, terminando esse loop quando ou 
o jogador terminar todas as fases e completar o jogo, ou quando o jogador perder todas suas vidas. Devido a dificuldade do jogo,
foi decidido que a cada fase completada, o jogador receber� uma vida extra.
    J� o modo survival � uma vers�o mais simples do jogo, onde s� h� uma vida e uma fase e o jogador deve tentar comer o maior
n�mero de ratos poss�veis at� morrer.
    Para representa��o dos elementos do jogo, foram utilizadas as seguintes estruturas:
	
	Snake:
	typedef struct str_snake
        {
          int size;
          char direction;
          char body[ROWSMAX*COLUMNSMAX];
          int x[ROWSMAX*COLUMNSMAX];
          int y[ROWSMAX*COLUMNSMAX];

        } SNAKE;
	Guarda as coordenadas, o tamanho, a dire��o da movimenta��o e os caracteres de cada parte da snake, facilitando a passagem
por param�tros nas fun��es.

     Mapa:
	 char map[ROWSMAX][COLUMNSMAX]; 
	 Lido pela fun��o void readMap(int level, int *rows, int *columns, char map[][COLUMNSMAX],int *rocksNum, POSN rocks[], POSN *initialCoord),
guarda os caracteres de cada coordenada do mapa.

     Ma��, ratos e pedras:
	 typedef struct str_posn
     {
       int x;  //cordenada X
       int y;  //cordenada Y

     } POSN;
	 
	POSN rocks[ROWSMAX*COLUMNSMAX];  Guarda as coordenadas de todas as pedras
    POSN rats[4];  Como um rato some a cada 4N movimentos (N==10), h� 4 ratos que aparecem e desaparecem, sendo geradas coordenadas aleat�rias.
    POSN apple;  

      animation.c : Cont�m as fun��es de produto gr�fico e cinem�tico principalmente para a storyMode 
do conjunto Snake.c. Essas fun��es efetuam efeitos como fadeIn e fadeOut, colocando na tela n�veis diferentes
de densidade dos caracteres especiais 176, 177, 178 da tabela ASCII em diferentes gradua��es para dar o efeito
de surgir na tela ou sair "smoothly", animam a entrada de texto, al�m de efetuar os di�logos do modo hist�ria
e colocar na tela as ASCIIart de cada n�vel.

      menu.c : Cont�m fun��es de personaliza��o de tela ligadas ao menu do jogo. Essas fun��es colocam na tela 
as ASCIIart do t�tulo e do menu de op��es � partir de matrizes de caracteres especiais utilizadas para moldar as
duas, e s�o pintadas pela matriz de mesmo tamanho de n�meros inteiros que especifica a cor de cada coordenada,
as fun��es tamb�m colocam na tela o menu de instru��es, ligado diretamente com o principal, e efetuam a 
coordena��o dos controles digitados para a escolha das op��es.

     files.c : Fun��es que manipulam arquivos de texto(para os mapas) e arquivos bin�rios para as pontua��es, 
como void uptadeHighScore(int score, FILE *arq). Foi utilizada a seguinte estrutura para guardar o rank:
     typedef struct str_player
     {
        char name[15];
        int score;

    } PLAYER;
	
     utilities.c : Cont�m fun��es como void hideCursor() e void textcolor(int ForgC), al�m de implementa��es da conio.h.
	
     H� ainda dois arquivos headers sem um par ".c", s�o eles a defines.h que guarda defines de cores, caracteres e teclas,
e a types.h, que armazena as defini��es de estruturas utilizadas no jogo.

    Explica��es e coment�rios das fun��es utilizadas podem ser encontradas nos coment�rios, tanto dos arquivos .c quanto
dos arquivos .h guardados nessa mesma pasta.
	
	

	
	
	