#ifndef BOLADEFOGO_H
#define BOLADEFOGO_H

#include "Recursos.h";
class BolaDeFogo
{
public:
	int x = 24, // Vari�vel que guarda posi��o X da bola de fogo
	y, // Vari�vel que guarda posi��o Y da bola de fogo
	h=16, // Altura da bola de fogo
	w=16; // Largura da bola de fogo
	/**
    * Inicializa a posi��o da bola de fogo
    * @param dragaoY valor usado para inicializar a posi��o da bola de fogo
    */
	BolaDeFogo(int dragaoY);
	/**
    * Incrementa a variavel responsavel pela posic�o x da bola de fogo
    */
	void moveFogo();
	/**
    * Desenha na tela a bola de fogo
    * @param *bolaDeFogo objeto que sera desenhado
    */
	void Draw(ALLEGRO_BITMAP *bolaDeFogo);
	/**
    * Testa de colis�o do personagem com a bola de fogo
    * @param *Jogador personagem com o qual sera testado a colis�o
    */
	bool colFogo(Player *jogador);
	~BolaDeFogo();
};

#endif // BOLADEFOGO_H
