// Resgate A Princesa.cpp : Defines the entry point for the console application.
//
/**
    Resgate a Princesa

    Programadores: Canoi Gomes e Alan Belmont

    Audio:
    "Pixelland"
    Kevin MacLeod (incompetech.com)
    Licensed under Creative Commons: By Attribution 3.0
    http://creativecommons.org/licenses/by/3.0/

    Fonte:
        Jimmy Campbell (jruff3@yahoo.com)

*/
#include"GameControl.h"
#include"Recursos.h"

// Variável para controlar qual tela será exibida
int tela = 0; // 0 = Menu; 1 = Jogo; 2 = Gameover; 3 = Ranking; 4 = História; 5 = Sobre o Jogo


int main()
{

	User pessoa[10];

	// Cria o objeto de GameControl
	GameControl *game = new GameControl;



	// Cria os elementos do allegro
	// fila de eventos
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

	// Display
	ALLEGRO_DISPLAY *display = NULL;

	// Imagens
	ALLEGRO_BITMAP *imagem[7];
	ALLEGRO_BITMAP *menu[5];
	ALLEGRO_BITMAP *gameover[3];
	ALLEGRO_BITMAP *ranking[4];
	ALLEGRO_BITMAP *sobreojogo;
	// Timer
	ALLEGRO_TIMER *tempo = NULL;
	ALLEGRO_KEYBOARD_STATE keystate;
	// Audio
	ALLEGRO_SAMPLE *sample = NULL;
	// Fonte
	ALLEGRO_FONT *fonte[2];
	ALGIF_ANIMATION *gif = NULL;

	//Cria as variáveis
	bool fim = false;
	int fps = 60;
	int vspd = 1;
	int auxPontos = 0;

    // Messagem de erro caso o ALLEGRO não consiga ser iniciado
	if (!al_init()) {
		al_show_native_message_box(NULL, "AVISO!", "ERRO!", "ERRO AO INICIAR ALLEGRO", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

    // Inicia o display
	display = al_create_display(game->largura_t, game->altura_t);

	// Exibe mensagem de erro caso o display não seja iniciado
	if (!display) {
		al_show_native_message_box(NULL, "AVISO!", "ERRO!", "ERRO AO INICIAR DISPLAY", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;

	}

	// Insere os primeiros elementos na fila
	game->inicializaTudo();

	// Inicializa os recursos do Allegro
	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(1);
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();

	// Carrega as imagens do Jogo
	imagem[0] = al_load_bitmap("imagens/ceu.png");
	imagem[1] = al_load_bitmap("imagens/chao1-2.png");
	imagem[2] = al_load_bitmap("imagens/cavaleiro e princesa - anim2.png");
	imagem[3] = al_load_bitmap("imagens/chao2.png");
	imagem[4] = al_load_bitmap("imagens/dragao2.png");
	imagem[5] = al_load_bitmap("imagens/fogo2.png");
	imagem[6] = al_load_bitmap("imagens/idfases.png");

    // Carrega as imagens do Menu
	menu[0] = al_load_bitmap("imagens/BotaoIniciar.png");
	menu[1] = al_load_bitmap("imagens/BotaoRanking.png");
	menu[2] = al_load_bitmap("imagens/BotaoSobreOJogo.png");
	menu[3] = al_load_bitmap("imagens/menu.png");
	menu[4] = al_load_bitmap("imagens/Ponteiro.png");
	gif = algif_load_animation("imagens/historia3.gif");

    // Carrega as imagens da tela de Game Over
	gameover[0] = al_load_bitmap("imagens/lapide3.png");

    //Carrega as imagens do Ranking
	ranking[0] = al_load_bitmap("imagens/ranking3.png");
	ranking[1] = al_load_bitmap("imagens/BotaoJogarNovamente.png");
	ranking[2] = al_load_bitmap("imagens/BotaoMenu.png");
	ranking[3] = al_load_bitmap("imagens/Ponteiro.png");

	// Carrega as imagens da tela de Sobre o Jogo
	sobreojogo = al_load_bitmap("imagens/ajuda.png");

	// Carrega o audio
	sample = al_load_sample("musicas/Pixelland.ogg");

    // Carrega as fontes
	fonte[0] = al_load_ttf_font("fonte/Early GameBoy.ttf", 16, 0);
	fonte[1] = al_load_ttf_font("fonte/Early GameBoy.ttf", 50, 0);

    // Cria a fila de eventos
	fila_eventos = al_create_event_queue();

	// Cria o timer
	tempo = al_create_timer(1.0 / fps);

    // Registra os eventos na fila de eventos
	al_register_event_source(fila_eventos,al_get_keyboard_event_source());
	al_register_event_source(fila_eventos,al_get_timer_event_source(tempo));
	al_register_event_source(fila_eventos,al_get_display_event_source(display));

    // Lê o ranking do arquivo .txt e guarda no vetor de struct auxRank
	leRanking(game->auxRank);

    // Toca a música
	al_play_sample(sample,1.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    // Inicia o timer
	al_start_timer(tempo);

	// Inicia o loop principal do jogo
	while (!fim) {
        // Exibe o menu se a tela for igual 0
		if (tela == 0) {
			game->menu(fila_eventos,menu,&fim,&tela);
		}
        // Exibe o jogo se a tela for igual 1
		if (tela== 1) {
			game->jogo(fila_eventos, &fim, imagem, fonte[0], &tela);
		}
		// Exibe a tela de gameover se a tela for igual 2
		if (tela == 2) {
			game->gameover(fila_eventos,&fim,gameover,fonte,&tela);
		}
        // Exibe o ranking se a tela for igual 3
		if (tela == 3) {
			game->ranking(fila_eventos, &fim, ranking, fonte[0], &tela);
		}
		// Exibe a tela de história se a tela for igual 4
		if (tela == 4) {
			game->historia(fila_eventos, &fim, gif, &tela);
		}
		// Exibe a tela de sobre o jogo se a tela for igual a 5
		if (tela == 5) {
			game->sobreoJogo(fila_eventos, &fim,sobreojogo, &tela);
		}
	}
	// Destroi o display
	al_destroy_display(display);
	// Destroi o timer
	al_destroy_timer(tempo);
    // Deleta as imagens do Jogo
	for(int i = 0;i < 6;i++){
        al_destroy_bitmap(imagem[i]);
	}
	delete(imagem);
	// Deleta as imagens do Menu
	for(int i = 0;i < 4;i++){
        al_destroy_bitmap(menu[i]);
	}
	delete(menu);
	// Deleta as imagens do GameOver
	for(int i = 0;i < 3;i++){
        al_destroy_bitmap(gameover[i]);
	}
	delete(gameover);
	// Deleta as imagens do Ranking
	for(int i = 0;i < 1;i++){
        al_destroy_bitmap(ranking[i]);
	}
	delete(ranking);
	// Deleta o gif da história
	algif_destroy_animation(gif);
    // Destroi o áudio
	al_destroy_sample(sample);
	// Destroi as fontes
	al_destroy_font(fonte[0]);
	al_destroy_font(fonte[1]);
	// Destroi a fila de eventos
	al_destroy_event_queue(fila_eventos);

	return 0;
}

