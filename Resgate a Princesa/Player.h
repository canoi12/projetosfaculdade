#ifndef PLAYER_H
#define PLAYER_H

#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<iostream>
#include "Bloco.h"
class Player
{
public:
	int x = 320, // Variável que contém o X do jogador
	y = 0, // Variável que contém o Y do jogador
	w = 32 , // Variável que guarda a largura do jogador
	h = 32; // Variável que guarda a altura do jogador
	int anim = 0; // Variável que controla a animação do jogador
	Player();

	/**
    * Desenha o personagem
    * @param *imagem Variável que guarda a imagem do jogador
    */
	void Draw(ALLEGRO_BITMAP *imagem);

	/**
    * Testa se há colisão na vertical do jogador com os blocos
    * @param yb Recebe o y do bloco
    * @param xb Recebe o x do bloco
    * @param *vspd Recebe a velocidade vertical(gravidade) do jogador
    */
	bool colisaoY(int yb, int xb, int *vspd);

	/**
    * Testa se há colisão na horizontal do jogador com os blocos
    * @param yb Recebe o y do bloco
    * @param xb Recebe o x do bloco
    * @param *vspd Recebe a velocidade vertical(gravidade) do jogador
    */
	bool colisaoX(int yb,int xb, int *vspd);

	/**
    * Continua a mover o jogador, caso não haja colisão horizontal. Também faz a gravidade funcionar, puxando o jogador para baixo caso não
    * haja colisão vertical
    * @param testeY Recebe o resultado do teste de colisão vertical do jogador
    * @param testeX Recebe o resultado do teste de colisão horizontal do jogador
    * @param *hspd Recebe a velocidade de movimento dos blocos
    * @param *vspd Recebe a velocidade vertical(gravidade) do jogador
    * @param
    */
	void move(bool testeY,bool testeX, int *vspd, int *hspd,int *pontos,int *tela);
	~Player();
};

#endif // PLAYER_H
