INF01202 ALGORITMOS E PROGRAMAÇÃO 2016/1 - Trabalho Final
Prof. Marcelo Walter
Prof. Rodrigo Ruas Oliveira

Guilherme Gomes Haetinger 00274702
Lucas Nunes Alegre 00274693        

    Para jogar, execute o arquivo SnakeAdvanced.exe encontrado nessa pasta, é importante que o os arquivos .c e .h estejam
na mesma pasta do arquivo .exe e que os arquivos de texto dos níveis estejam na pasta "Levels".
    É possível também abrir o arquivo do projeto no codeblocks, apertando F9 para compilar e rodar o jogo.	

            SNAKE ADVANCED

	Nosso trabalho, seguindo as especificações ditadas pelos professores, é dividido
em uma série de conjuntos de funções, cada um com um devido objetivo e efetuado pelo grupo 
como um todo:

     main.c : Contém a função main(), que efetua a função Menu() do conjunto Menu.c até uma das 5 opções 
listadas nele serem escolhidas. Quando escolhida, a opção redireciona o usuário para uma função específica,
sendo ou (SCORES) printHighScores() do conjunto Files.c, (STORY MODE) StoryMode() do conjunto Snake.c, 
(INSTRUCTIONS) printInstructons() do conjunto Menu.c, (SURVIVAL) ou (EXIT) que efetua a saída do jogo.

    snake.c : Contém as funções que implementam efitavamente a mecânica do jogo e as funções que controlam os dois modos
de jogo, Story e Survival. Como por exemplo a função void updateSnakeCoord(SNAKE *snake), que recebe uma estrutura snake 
e faz a mudança da coordenada de cada parte da snake a cada laço de jogo.
    No modo story, temos a função void storyMode(), que controla o jogo inicializando as pontuações, vidas, etc e executando
a função void playOneLevel(int level, int objetivo, int speed, LEVEL_SCENE scenario, int *lifes, int *score), que recebe
respectivamente o número da fase, o número de ratos necessários para completar a fase, a velocidade inicial da fase, o cenário
da fase, os números de vidas e pontuações atuais do jogador. Desse modo, se o jogador terminar a fase(comeu a maçã), a
variável level é incrementada e dentro de um switch de fases, outra fase do jogo é executada, terminando esse loop quando ou 
o jogador terminar todas as fases e completar o jogo, ou quando o jogador perder todas suas vidas. Devido a dificuldade do jogo,
foi decidido que a cada fase completada, o jogador receberá uma vida extra.
    Já o modo survival é uma versão mais simples do jogo, onde só há uma vida e uma fase e o jogador deve tentar comer o maior
número de ratos possíveis até morrer.
    Para representação dos elementos do jogo, foram utilizadas as seguintes estruturas:
	
	Snake:
	typedef struct str_snake
        {
          int size;
          char direction;
          char body[ROWSMAX*COLUMNSMAX];
          int x[ROWSMAX*COLUMNSMAX];
          int y[ROWSMAX*COLUMNSMAX];

        } SNAKE;
	Guarda as coordenadas, o tamanho, a direção da movimentação e os caracteres de cada parte da snake, facilitando a passagem
por paramêtros nas funções.

     Mapa:
	 char map[ROWSMAX][COLUMNSMAX]; 
	 Lido pela função void readMap(int level, int *rows, int *columns, char map[][COLUMNSMAX],int *rocksNum, POSN rocks[], POSN *initialCoord),
guarda os caracteres de cada coordenada do mapa.

     Maçã, ratos e pedras:
	 typedef struct str_posn
     {
       int x;  //cordenada X
       int y;  //cordenada Y

     } POSN;
	 
	POSN rocks[ROWSMAX*COLUMNSMAX];  Guarda as coordenadas de todas as pedras
    POSN rats[4];  Como um rato some a cada 4N movimentos (N==10), há 4 ratos que aparecem e desaparecem, sendo geradas coordenadas aleatórias.
    POSN apple;  

      animation.c : Contém as funções de produto gráfico e cinemático principalmente para a storyMode 
do conjunto Snake.c. Essas funções efetuam efeitos como fadeIn e fadeOut, colocando na tela níveis diferentes
de densidade dos caracteres especiais 176, 177, 178 da tabela ASCII em diferentes graduações para dar o efeito
de surgir na tela ou sair "smoothly", animam a entrada de texto, além de efetuar os diálogos do modo história
e colocar na tela as ASCIIart de cada nível.

      menu.c : Contém funções de personalização de tela ligadas ao menu do jogo. Essas funções colocam na tela 
as ASCIIart do título e do menu de opções à partir de matrizes de caracteres especiais utilizadas para moldar as
duas, e são pintadas pela matriz de mesmo tamanho de números inteiros que especifica a cor de cada coordenada,
as funções também colocam na tela o menu de instruções, ligado diretamente com o principal, e efetuam a 
coordenação dos controles digitados para a escolha das opções.

     files.c : Funções que manipulam arquivos de texto(para os mapas) e arquivos binários para as pontuações, 
como void uptadeHighScore(int score, FILE *arq). Foi utilizada a seguinte estrutura para guardar o rank:
     typedef struct str_player
     {
        char name[15];
        int score;

    } PLAYER;
	
     utilities.c : Contém funções como void hideCursor() e void textcolor(int ForgC), além de implementações da conio.h.
	
     Há ainda dois arquivos headers sem um par ".c", são eles a defines.h que guarda defines de cores, caracteres e teclas,
e a types.h, que armazena as definições de estruturas utilizadas no jogo.

    Explicações e comentários das funções utilizadas podem ser encontradas nos comentários, tanto dos arquivos .c quanto
dos arquivos .h guardados nessa mesma pasta.
	
	

	
	
	