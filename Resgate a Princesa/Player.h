#ifndef PLAYER_H
#define PLAYER_H

#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<iostream>
#include "Bloco.h"
class Player
{
public:
	int x = 320, // Vari�vel que cont�m o X do jogador
	y = 0, // Vari�vel que cont�m o Y do jogador
	w = 32 , // Vari�vel que guarda a largura do jogador
	h = 32; // Vari�vel que guarda a altura do jogador
	int anim = 0; // Vari�vel que controla a anima��o do jogador
	Player();

	/**
    * Desenha o personagem
    * @param *imagem Vari�vel que guarda a imagem do jogador
    */
	void Draw(ALLEGRO_BITMAP *imagem);

	/**
    * Testa se h� colis�o na vertical do jogador com os blocos
    * @param yb Recebe o y do bloco
    * @param xb Recebe o x do bloco
    * @param *vspd Recebe a velocidade vertical(gravidade) do jogador
    */
	bool colisaoY(int yb, int xb, int *vspd);

	/**
    * Testa se h� colis�o na horizontal do jogador com os blocos
    * @param yb Recebe o y do bloco
    * @param xb Recebe o x do bloco
    * @param *vspd Recebe a velocidade vertical(gravidade) do jogador
    */
	bool colisaoX(int yb,int xb, int *vspd);

	/**
    * Continua a mover o jogador, caso n�o haja colis�o horizontal. Tamb�m faz a gravidade funcionar, puxando o jogador para baixo caso n�o
    * haja colis�o vertical
    * @param testeY Recebe o resultado do teste de colis�o vertical do jogador
    * @param testeX Recebe o resultado do teste de colis�o horizontal do jogador
    * @param *hspd Recebe a velocidade de movimento dos blocos
    * @param *vspd Recebe a velocidade vertical(gravidade) do jogador
    * @param
    */
	void move(bool testeY,bool testeX, int *vspd, int *hspd,int *pontos,int *tela);
	~Player();
};

#endif // PLAYER_H
