#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include"Recursos.h"


class GameControl
{
public:
	int pontos = 0, // Guarda a pontua��o do jogador
	 x = 0, // Vari�vel que controla o movimento dos blocos
	 largura_t = 640, // Largura da tela
	 altura_t = 640, // Altura da tela
	 vspd = 2, // Vari�vel que simula a gravidade
	 dragaoY = 0, // Vari�vel que controla o Y do drag�o
    controleMenu = 0,   // Vari�vel que indica qual bot�o do menu est� selecionado
    controleRanking = 0; // Vari�vel que indica qual bot�o do Ranking est� selecionado


	double sec = 0; // Vari�vel que controla a anima��o do gif

	bool erro = false,  // Vari�vel que indica se a mensagem de erro ser� exibida
	atirou = false, // Vari�vel que controla quando o drag�o pode soltar bola de fogo
	controleMusica = true,
	exibe = false; // Vari�vel que controla a exibi��o dos marcadores das fases

	Player *jogador = new Player(); // Cria um novo objeto tipo Player para ser o personagem
	Fase *fila = new Fase; // Inicia a fila
	BolaDeFogo *claudinho; // Cria um novo objeto do tipo BolaDeFogo
	Bloco matriz[20][20]; // Cria uma matriz de blocos para receber os dados do txt, e passa esses dados para o n� da fila, quando for inserido
	ALLEGRO_KEYBOARD_STATE keystate;
	User aux; // Cria uma vari�vel auxiliar do tipo User, para receber o nome e a pontua��o do usu�rio
	User auxRank[10]; // Cria um vetor auxiliar do tipo User, para guardar os dados do ranking lidos do txt

	GameControl(); // Construtor da classe
	void setImgs();


	/**
    * Cria as filas e as primeiras fases
    */
	void inicializaTudo();

	/**
    * Desenha o menu, mostra os bot�es e faz eles funcionarem
    * @param *fila_eventos Vari�vel de controle de qual eventos est� sendo executado naquele momento
    * @param **menu Vari�vel que guarda as imagens do menu
    * @param *fim Vari�vel que controla o termino da aplica��o
    * @param *tela Vari�vel que controla qual tela est� sendo exibida
    */
	void menu(ALLEGRO_EVENT_QUEUE *fila_eventos,ALLEGRO_BITMAP **menu, bool *fim,int *tela);

	/**
    * Desenha o gif da hist�ria do jogo
    * @param *fila_eventos Vari�vel de controle de qual eventos est� sendo executado naquele momento
    * @param *fim Vari�vel que controla o termino da aplica��o
    * @param *gif Vari�vel que guarda o gif
    * @param *tela Vari�vel que controla qual tela est� sendo exibida
    */
	void historia(ALLEGRO_EVENT_QUEUE *fila_eventos, bool *fim, ALGIF_ANIMATION *gif,int *tela);

	/**
    * Desenha as fases, o personagem, e mantem o controle das mec�nicas do jogo
    * @param *fila_eventos Vari�vel de controle de qual eventos est� sendo executado naquele momento
    * @param *fim Vari�vel que controla o termino da aplica��o
    * @param **imagem Vari�vel que guarda as imagens do jogo
    * @param *fonte Vari�vel que recebe a fonte
    * @param *tela Vari�vel que controla qual tela est� sendo exibida
    */
	void jogo(ALLEGRO_EVENT_QUEUE *fila_eventos, bool *fim,ALLEGRO_BITMAP **imagem,ALLEGRO_FONT *font,int *tela);

	/**
    * Fun��o que exibe a tela de game over, desenhando ela e pegando as entradas do usu�rio, tamb�m � onde lemos o arquivo do ranking, ordenamos e o reescrevemos
    * @param *fila_eventos Vari�vel de controle de qual eventos est� sendo executado naquele momento
    * @param *fim Vari�vel que controla o termino da aplica��o
    * @param **gameover Vari�vel que guarda as imagens da tela de Game Over
    * @param **fonte Vari�vel que recebe a fonte
    * @param *tela Vari�vel que controla qual tela est� sendo exibida
    */
	void gameover(ALLEGRO_EVENT_QUEUE *fila_eventos, bool *fim, ALLEGRO_BITMAP **gameover, ALLEGRO_FONT **fonte, int *tela);

	/**
    * Fun��o que exibe a tela de ranking
    * @param *fila_eventos Vari�vel de controle de qual eventos est� sendo executado naquele momento
    * @param *fim Vari�vel que controla o termino da aplica��o
    * @param **ranking Vari�vel que guarda as imagens do ranking
    * @param *fonte Vari�vel que recebe a fonte
    * @param *tela Vari�vel que controla qual tela est� sendo exibida
    */
	void ranking(ALLEGRO_EVENT_QUEUE *fila_eventos, bool *fim, ALLEGRO_BITMAP **ranking, ALLEGRO_FONT *fonte, int *tela);

    /**
    * Fun��o que exibe a tela de ranking
    * @param *fila_eventos Vari�vel de controle de qual eventos est� sendo executado naquele momento
    * @param *fim Vari�vel que controla o termino da aplica��o
    * @param *sobreojogo Vari�vel que guarda a imagem da tela de "sobre o jogo"
    * @param *tela Vari�vel que controla qual tela est� sendo exibida
    */
    void sobreoJogo(ALLEGRO_EVENT_QUEUE *fila_eventos, bool *fim, ALLEGRO_BITMAP *sobreojogo, int *tela);
	/**
    * Fun��o que destroi os objetos usados
    */
	void destroiTudo();
	~GameControl();
};

#endif // GAMECONTROL_H
