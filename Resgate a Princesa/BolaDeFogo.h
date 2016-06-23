#ifndef BOLADEFOGO_H
#define BOLADEFOGO_H

#include "Recursos.h";
class BolaDeFogo
{
public:
	int x = 24, // Variável que guarda posição X da bola de fogo
	y, // Variável que guarda posição Y da bola de fogo
	h=16, // Altura da bola de fogo
	w=16; // Largura da bola de fogo
	/**
    * Inicializa a posição da bola de fogo
    * @param dragaoY valor usado para inicializar a posição da bola de fogo
    */
	BolaDeFogo(int dragaoY);
	/**
    * Incrementa a variavel responsavel pela posicão x da bola de fogo
    */
	void moveFogo();
	/**
    * Desenha na tela a bola de fogo
    * @param *bolaDeFogo objeto que sera desenhado
    */
	void Draw(ALLEGRO_BITMAP *bolaDeFogo);
	/**
    * Testa de colisão do personagem com a bola de fogo
    * @param *Jogador personagem com o qual sera testado a colisão
    */
	bool colFogo(Player *jogador);
	~BolaDeFogo();
};

#endif // BOLADEFOGO_H
