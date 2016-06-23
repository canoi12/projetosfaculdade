#include "GameControl.h"



GameControl::GameControl()
{
}

void GameControl::setImgs() {
}

void GameControl::inicializaTudo()
{
	leMatriz(0,matriz);
	fila = criaFase();
	fila = insereFases(fila, matriz,0);
	leMatriz(1,matriz);
	fila = insereFases(fila, matriz,1);
}
void GameControl::menu(ALLEGRO_EVENT_QUEUE *fila_eventos,ALLEGRO_BITMAP **menu, bool *fim,int *tela) {
	ALLEGRO_EVENT ev;
	al_wait_for_event(fila_eventos,&ev);
	if (ev.type == ALLEGRO_EVENT_KEY_UP) {
		al_get_keyboard_state(&keystate);
		// Se apertar a tecla para cima, vai para a opção acima da atual
		if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
		{
			if (controleMenu == 1) {
				controleMenu = 0;
			}
			else if (controleMenu == 2) {
				controleMenu = 1;
			}
		}
		// Se apertar a tecla para baixo, vai para a opção abaixo da atual
		else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
		{
			if (controleMenu == 1) {
				controleMenu = 2;
			}
			else if (controleMenu == 0) {
				controleMenu = 1;
			}
		}
		// Vai para a tela, dependendo da opção selecionada
		if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            // Se a opção selecionada foi a 0, vai para a tela da história
			if (controleMenu == 0) {
				*tela = 4;
				sec = 0;
			}
            // Se a opção selecionada foi a 1, vai para a tela do ranking
			if (controleMenu == 1) {
				*tela = 3;
			}
			// Se a opção selecionada foi a 2, vai para a tela de "Sobre o jogo"
			if (controleMenu == 2) {
				*tela = 5;
			}
		}
		if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
			*fim = true;
		}
	}
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        *fim = true;
	}
	if (ev.type == ALLEGRO_EVENT_TIMER)
	{
	    // Desenha a imagem de fundo do menu
		al_draw_bitmap(menu[3],0,0,0);

		// Desenha os botões
		al_draw_bitmap(menu[0],448,384,0);
		al_draw_bitmap(menu[1],448,464,0);
		al_draw_bitmap(menu[2],448,544,0);
		// Desenha o ponteiro para indicar qual opção está selecionada no momento
		al_draw_bitmap(menu[4],416,384 + (controleMenu*80),0);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));

	}
}

void GameControl::historia(ALLEGRO_EVENT_QUEUE *fila_eventos, bool *fim,ALGIF_ANIMATION *gif,int *tela){
    ALLEGRO_EVENT ev;
	al_wait_for_event(fila_eventos, &ev);
	if (ev.type == ALLEGRO_EVENT_KEY_UP) {
     if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
        *fim = true;
     }
     // Se apertar enter, vai para a tela de jogo
     if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
        *tela = 1;
     }
	}
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        *fim = true;
	}
	if(ev.type == ALLEGRO_EVENT_TIMER){
            // Se a animação acabou, vai para a tela de jogo
            if(sec > 10){
                *tela = 1;
            }
            // Exibe a animação da história, enquanto ela não acabou
            if (sec < 10){
                al_draw_scaled_bitmap(algif_get_bitmap(gif,sec),0,0,320,320,1,1,640,640,0);
                sec += 0.02;
            }
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
	}
}

void GameControl::jogo(ALLEGRO_EVENT_QUEUE *fila_eventos, bool *fim,ALLEGRO_BITMAP *imagem[],ALLEGRO_FONT *fonte,int *tela) {

	ALLEGRO_EVENT ev;
	al_wait_for_event(fila_eventos, &ev);
	if (ev.type == ALLEGRO_EVENT_KEY_UP) {
        if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
            *fim = true;
        }
        // Se a tecla de espaço for pressionada, ativa a exibição dos marcadores da tela
		if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE)
		{
			exibe = !exibe;
		}
	}
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        *fim = true;
	}
	if (ev.type == ALLEGRO_EVENT_TIMER)
	{
		al_get_keyboard_state(&keystate);
		if (al_key_down(&keystate, ALLEGRO_KEY_UP) && testeColY(jogador, fila, &vspd))
		{
			vspd -= 24;
		}
		// Caso a tecla Escape seja pressionada, o loop principal irá parar
		if (al_key_down(&keystate, ALLEGRO_KEY_ESCAPE)) {
			*fim = true;
		}

		// Continuar a "move"(o que se move é o mapa, mas o player tem a gravidade) o player, enquanto ele não estiver colidindo
		jogador->move(testeColY(jogador, fila, &vspd), testeColX(jogador, fila, &vspd), &vspd, &x, &pontos, tela);

		// Se a variável que controla o X dos blocos for menor que -632, ela vai zerar, então deletaremos o primeiro nó da fila
		// Depois inserimos uma nova fase randomica no final
		// Caso não seja menor que -632, continuamos a decrementar a variável
		if (x < -632) {
			x = 0;
			srand(time(NULL));
			int teste = rand() % 9;
			removeLista(fila);
			leMatriz(teste, matriz);
			insereFases(fila, matriz,teste);
		}
		else {
			x -= 8;
		}
		// Faz o dragão atirar bola de fogo toda vez que a pontuação % 200 for igual a zero
		if(pontos % 200 == 0){
			atirou = true;
			claudinho = new BolaDeFogo(dragaoY + 35);
		}
		//cout << x << endl;
		for (int i = 0;i < 20;i++) {
			for (int j = 0;j < 20; j++) {
				// Desenha a matriz que está na frente da fila
				if (fila->prox->matriz[j][i].tipo == 0) {
					fila->prox->matriz[j][i].Draw(imagem[0], j * fila->prox->matriz[j][i].w + x, i * fila->prox->matriz[j][i].h);
				}
				if (fila->prox->matriz[j][i].tipo == 1) {
					fila->prox->matriz[j][i].Draw(imagem[3], j * fila->prox->matriz[j][i].w + x, i * fila->prox->matriz[j][i].h);
				}
				if (fila->prox->matriz[j][i].tipo == 2) {
					fila->prox->matriz[j][i].Draw(imagem[1], j * fila->prox->matriz[j][i].w + x, i * fila->prox->matriz[j][i].h);
				}
				// Desenha a matriz que está na segunda posição da fila
				if (fila->prox->prox->matriz[j][i].tipo == 0) {
					fila->prox->prox->matriz[j][i].Draw(imagem[0], j * fila->prox->prox->matriz[j][i].w + largura_t + x, i * fila->prox->prox->matriz[j][i].h);
				}
				if (fila->prox->prox->matriz[j][i].tipo == 1) {
					fila->prox->prox->matriz[j][i].Draw(imagem[3], j * fila->prox->prox->matriz[j][i].w + largura_t + x, i * fila->prox->prox->matriz[j][i].h);
				}
				if (fila->prox->prox->matriz[j][i].tipo == 2) {
					fila->prox->prox->matriz[j][i].Draw(imagem[1], j * fila->prox->prox->matriz[j][i].w + largura_t + x, i * fila->prox->prox->matriz[j][i].h);
				}
				// Se exibe for verdadeiro, exibiremos os marcadores de fase, se não, elas serão somente blocos de ceu comuns
				if (exibe == false) {
					if (fila->prox->matriz[j][i].tipo == 9) {
						fila->prox->matriz[j][i].Draw(imagem[0], j * fila->prox->matriz[j][i].w + x, i * fila->prox->matriz[j][i].h);
					}
					if (fila->prox->prox->matriz[j][i].tipo == 9) {
						fila->prox->prox->matriz[j][i].Draw(imagem[0], j * fila->prox->prox->matriz[j][i].w + largura_t + x, i * fila->prox->prox->matriz[j][i].h);
					}
				} else {
                    if (fila->prox->matriz[j][i].tipo == 9 && fila->prox->n >=0 && fila->prox->n <= 4){
                        fila->prox->matriz[j][i].drawRegion(imagem[6], j * fila->prox->matriz[j][i].w + x, i * fila->prox->matriz[j][i].h, 32*fila->prox->n,0);
                    }
                    else if(fila->prox->matriz[j][i].tipo == 9 && fila->prox->n >=5 && fila->prox->n <= 9){
                        fila->prox->matriz[j][i].drawRegion(imagem[6], j * fila->prox->matriz[j][i].w + x, i * fila->prox->matriz[j][i].h, 32*(fila->prox->n-5),32);
                    }

                    if (fila->prox->prox->matriz[j][i].tipo == 9 && fila->prox->prox->n >=0 && fila->prox->prox->n <= 4){
                        fila->prox->prox->matriz[j][i].drawRegion(imagem[6], j * fila->prox->prox->matriz[j][i].w + largura_t + x, i * fila->prox->prox->matriz[j][i].h, 32*fila->prox->prox->n,0);
                    }
                    else if(fila->prox->prox->matriz[j][i].tipo == 9 && fila->prox->prox->n >=5 && fila->prox->prox->n <= 9){
                        fila->prox->prox->matriz[j][i].drawRegion(imagem[6], j * fila->prox->prox->matriz[j][i].w + largura_t + x, i * fila->prox->prox->matriz[j][i].h, 32*(fila->prox->prox->n-5),32);
                    }
				}

			}
		}
		// Se o y do jogador for maior que a altura da tela, fazemos ele voltar lá pra cima
		if (jogador->y > altura_t) {
			jogador->y = 0;
		}
		// Desenha o jogador
		jogador->Draw(imagem[2]);

        // Caso a variável atirou seja verdadeira, ou seja, se o dragão atirou a bola de fogo
        // Desenhamos ela na tela e a movemos
        // caso o X dela seja maior que a largura da tela(640) ou se colidir com o jogador, ela será destruída
        // E se a tela for diferente de 1, ela será destruída também
        // E em todos os casos, a variável atirou volta a ser false
		if (atirou) {
			claudinho->Draw(imagem[5]);
			claudinho->moveFogo();
			if (claudinho->x > 640) {
				delete claudinho;
				atirou = false;
			}
			if (claudinho->colFogo(jogador)) {
				delete claudinho;
				atirou = false;
				*tela = 2;
			}
			if(*tela != 1){
				delete claudinho;
				atirou = false;
			}
		}
		// Se a tela for diferente de 1 (ou seja, diferente da tela atual) resetamos as variáveis, e deletamos os nós na fila, e inserimos novamente os dois iniciais
		if (*tela != 1) {
			jogador->y = 0;
			x = 0;
			vspd = 2;
			dragaoY = 0;
			removeLista(fila);
			removeLista(fila);
			inicializaTudo();
			aux.pontos = pontos;
			pontos = 0;
		}
		// Desenha o dragão
		al_draw_bitmap(imagem[4],0,dragaoY,0);
		// Faz o dragão seguir o Y do personagem, decrementando caso o jogador estija mais acima dele, ou incrementando, caso o jogador esteja mais abaixo
		if (dragaoY > jogador->y && dragaoY < 448) {
			dragaoY -= 1;
		}
		else if(dragaoY < jogador->y && dragaoY < 448) {
			dragaoY += 1;
		}
		// Desenha os pontos na tela
		al_draw_textf(fonte, al_map_rgb(0, 0, 0), 64, 32, ALLEGRO_ALIGN_LEFT, "Pontos: %d", pontos);

		// Caso a variável de exibir os marcadores de fase esteja ativa, desenhamos um quadrado verde em cada fase
		if (exibe == true) {
			al_draw_rectangle(fila->prox->matriz[0][0].x, fila->prox->matriz[0][0].y, fila->prox->matriz[0][0].x + largura_t, fila->prox->matriz[0][0].y + altura_t, al_map_rgb(0, 255, 0), 0);
		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
}

void GameControl::gameover(ALLEGRO_EVENT_QUEUE *fila_eventos,bool *fim,ALLEGRO_BITMAP **gameover,ALLEGRO_FONT **fonte,int *tela) {
	ALLEGRO_EVENT ev;
	al_wait_for_event(fila_eventos, &ev);
	if (ev.type == ALLEGRO_EVENT_KEY_UP) {
        if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
            *fim = true;
        }
        // Pega a entrada do usuário, e vai concatenando em uma string, enquanto o número de letras for menor que 3
		if ((ev.keyboard.keycode > 0 && ev.keyboard.keycode < 27) && aux.nome.length() < 3) {
			aux.nome += ev.keyboard.keycode + '@';
		}
		if ((ev.keyboard.keycode > 26 && ev.keyboard.keycode < 38) && aux.nome.length() < 3) {
			aux.nome += ev.keyboard.keycode + 21;
		}

        // Apaga a ultima letra da string
		if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
				aux.nome = aux.nome.substr(0, aux.nome.length() - 1);
		}
		// Quando enter for pressionado, caso o numero de letras na string for menor que 2, ele exibe a mensagem de erro
		// Se não
		// Ele lê o ranking de um txt e coloca em um vetor de struct que contem variável de nome(string) e pontuação(int)
		// Então ele testa para ver se a pontuação atual do jogador é maior que a ultima do ranking, se sim, coloca a pontuação atual e o nome na ultima posição do vetor e ordena.
		// E depois ele escreve tudo no txt novamente
		// Quando sair desse if, ele troca de tela, vai para a tela do ranking
		// Caso nem entre nesse if, ele vai somente pra tela do ranking, nem faz nada
		if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
			if (aux.nome.length() > 2) {
				leRanking(auxRank);
				if (aux.pontos > auxRank[9].pontos) {
					auxRank[9] = aux;
					quickSort(auxRank, 0, 9);
					escreveRanking(auxRank);
				}
				*tela = 3;
				erro = false;
			}
			else {
				erro = true;
			}
		}
	}
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        *fim = true;
	}
	if (ev.type == ALLEGRO_EVENT_TIMER) {
        // Desenha a tela de game over
		al_draw_bitmap(gameover[0],0,0,0);
        // Desenha o nome do jogador, a medida que ele for digitando
		al_draw_text(fonte[1],al_map_rgb(132,126,135),384,320,ALLEGRO_ALIGN_CENTER,aux.nome.c_str());
		// Desenha os pontos do jogador
		al_draw_textf(fonte[1], al_map_rgb(255, 255, 0), 288, 464, ALLEGRO_ALIGN_CENTER, "%i", aux.pontos);

		// Caso o jogaodor aperte Enter antes de digitar os 3 caracteres, essa mensagem será exibida
		if (erro) {
			al_draw_text(fonte[0],al_map_rgb(255,0,0),32,640-32,0,"Voce precisa digitar 3 caracteres!!");
		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0,0,0));
	}
}
void GameControl::ranking(ALLEGRO_EVENT_QUEUE * fila_eventos, bool * fim, ALLEGRO_BITMAP ** ranking, ALLEGRO_FONT * fonte, int * tela)
{
	ALLEGRO_EVENT ev;
	al_wait_for_event(fila_eventos, &ev);
	if (ev.type == ALLEGRO_EVENT_KEY_UP) {
        if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                *fim = true;
        }
            // Se apertar a tecla para cima, vai para a opção acima da atual
        if (ev.keyboard.keycode == ALLEGRO_KEY_UP)
        {
            if (controleRanking == 1) {
				controleRanking = 0;
            }
		}
		// Se apertar a tecla para baixo, vai para a opção abaixo da atual
		else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN)
		{

			if (controleRanking == 0) {
				controleRanking = 1;
			}
		}

        // Quando a tecla enter for pressionada, muda a tela dependendo da função escolhida
		if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
            // Se a opção 0 for a selecionada, vai para a tela de jogo
			if(controleRanking == 0){
                *tela = 1;
			}
			// Se a opção selecionada for a 1, vai para a tela do menu
			if(controleRanking == 1){
                *tela = 0;
			}
		}
	}
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        *fim = true;
	}
	if (ev.type == ALLEGRO_EVENT_TIMER) {
	    // Desenha a imagem de fundo do ranking
		al_draw_bitmap(ranking[0], 0, 0, 0);
        // Desenha todo o ranking na tela (Nome e pontuação)
		for (int i = 0;i < 10;i++) {
			al_draw_text(fonte, al_map_rgb(0, 0, 0), 224, 80 + (40 * i), 0, auxRank[i].nome.c_str());
			al_draw_textf(fonte, al_map_rgb(0, 0, 0), 384,80+ (40 * i), 0,"%i",auxRank[i].pontos);
		}
		// Desenha os botões
        al_draw_bitmap(ranking[1],32,416,0);
		al_draw_bitmap(ranking[2],32,496,0);
		al_draw_bitmap(ranking[3],0,416+(80*controleRanking),0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
}


void GameControl::sobreoJogo(ALLEGRO_EVENT_QUEUE *fila_eventos, bool *fim, ALLEGRO_BITMAP *sobreojogo, int *tela){
    ALLEGRO_EVENT ev;
	al_wait_for_event(fila_eventos, &ev);
	if (ev.type == ALLEGRO_EVENT_KEY_UP) {
     if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
        *fim = true;
     }
     // Se apertar enter, vai para a tela de menu
     if(ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
        *tela = 0;
     }
	}
	if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        *fim = true;
	}
	if(ev.type == ALLEGRO_EVENT_TIMER){
        al_draw_bitmap(sobreojogo,0,0,0);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
	}
}
	void GameControl::destroiTudo()
	{
	    delete claudinho;
	    delete fila;
	    delete jogador;
	    delete matriz;
	    delete auxRank;
	}

	GameControl::~GameControl()
{
}
