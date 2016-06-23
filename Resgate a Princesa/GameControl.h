#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include"Recursos.h"


class GameControl
{
public:
	int pontos = 0, // Guarda a pontuação do jogador
	 x = 0, // Variável que controla o movimento dos blocos
	 largura_t = 640, // Largura da tela
	 altura_t = 640, // Altura da tela
	 vspd = 2, // Variável que simula a gravidade
	 dragaoY = 0, // Variável que controla o Y do dragão
    controleMenu = 0,   // Variável que indica qual botão do menu está selecionado
    controleRanking = 0; // Variável que indica qual botão do Ranking está selecionado


	double sec = 0; // Variável que controla a animação do gif

	bool erro = false,  // Variável que indica se a mensagem de erro será exibida
	atirou = false, // Variável que controla quando o dragão pode soltar bola de fogo
	controleMusica = true,
	exibe = false; // Variável que controla a exibição dos marcadores das fases

	Player *jogador = new Player(); // Cria um novo objeto tipo Player para ser o personagem
	Fase *fila = new Fase; // Inicia a fila
	BolaDeFogo *claudinho; // Cria um novo objeto do tipo BolaDeFogo
	Bloco matriz[20][20]; // Cria uma matriz de blocos para receber os dados do txt, e passa esses dados para o nó da fila, quando for inserido
	ALLEGRO_KEYBOARD_STATE keystate;
	User aux; // Cria uma variável auxiliar do tipo User, para receber o nome e a pontuação do usuário
	User auxRank[10]; // Cria um vetor auxiliar do tipo User, para guardar os dados do ranking lidos do txt

	GameControl(); // Construtor da classe
	void setImgs();


	/**
    * Cria as filas e as primeiras fases
    */
	void inicializaTudo();

	/**
    * Desenha o menu, mostra os botões e faz eles funcionarem
    * @param *fila_eventos Variável de controle de qual eventos está sendo executado naquele momento
    * @param **menu Variável que guarda as imagens do menu
    * @param *fim Variável que controla o termino da aplicação
    * @param *tela Variável que controla qual tela está sendo exibida
    */
	void menu(ALLEGRO_EVENT_QUEUE *fila_eventos,ALLEGRO_BITMAP **menu, bool *fim,int *tela);

	/**
    * Desenha o gif da história do jogo
    * @param *fila_eventos Variável de controle de qual eventos está sendo executado naquele momento
    * @param *fim Variável que controla o termino da aplicação
    * @param *gif Variável que guarda o gif
    * @param *tela Variável que controla qual tela está sendo exibida
    */
	void historia(ALLEGRO_EVENT_QUEUE *fila_eventos, bool *fim, ALGIF_ANIMATION *gif,int *tela);

	/**
    * Desenha as fases, o personagem, e mantem o controle das mecânicas do jogo
    * @param *fila_eventos Variável de controle de qual eventos está sendo executado naquele momento
    * @param *fim Variável que controla o termino da aplicação
    * @param **imagem Variável que guarda as imagens do jogo
    * @param *fonte Variável que recebe a fonte
    * @param *tela Variável que controla qual tela está sendo exibida
    */
	void jogo(ALLEGRO_EVENT_QUEUE *fila_eventos, bool *fim,ALLEGRO_BITMAP **imagem,ALLEGRO_FONT *font,int *tela);

	/**
    * Função que exibe a tela de game over, desenhando ela e pegando as entradas do usuário, também é onde lemos o arquivo do ranking, ordenamos e o reescrevemos
    * @param *fila_eventos Variável de controle de qual eventos está sendo executado naquele momento
    * @param *fim Variável que controla o termino da aplicação
    * @param **gameover Variável que guarda as imagens da tela de Game Over
    * @param **fonte Variável que recebe a fonte
    * @param *tela Variável que controla qual tela está sendo exibida
    */
	void gameover(ALLEGRO_EVENT_QUEUE *fila_eventos, bool *fim, ALLEGRO_BITMAP **gameover, ALLEGRO_FONT **fonte, int *tela);

	/**
    * Função que exibe a tela de ranking
    * @param *fila_eventos Variável de controle de qual eventos está sendo executado naquele momento
    * @param *fim Variável que controla o termino da aplicação
    * @param **ranking Variável que guarda as imagens do ranking
    * @param *fonte Variável que recebe a fonte
    * @param *tela Variável que controla qual tela está sendo exibida
    */
	void ranking(ALLEGRO_EVENT_QUEUE *fila_eventos, bool *fim, ALLEGRO_BITMAP **ranking, ALLEGRO_FONT *fonte, int *tela);

    /**
    * Função que exibe a tela de ranking
    * @param *fila_eventos Variável de controle de qual eventos está sendo executado naquele momento
    * @param *fim Variável que controla o termino da aplicação
    * @param *sobreojogo Variável que guarda a imagem da tela de "sobre o jogo"
    * @param *tela Variável que controla qual tela está sendo exibida
    */
    void sobreoJogo(ALLEGRO_EVENT_QUEUE *fila_eventos, bool *fim, ALLEGRO_BITMAP *sobreojogo, int *tela);
	/**
    * Função que destroi os objetos usados
    */
	void destroiTudo();
	~GameControl();
};

#endif // GAMECONTROL_H
