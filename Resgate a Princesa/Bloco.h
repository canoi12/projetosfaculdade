#ifndef BLOCO_H
#define BLOCO_H


#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
class Bloco
{
public:
	int x, // Vari�vel que guarda posi��o X do bloco
	y,  // Vari�vel que guarda posi��o Y do bloco
	tipo,  // Tipo do bloco 0 = ceu/1 = terra/2 = chao
	w = 32, // Largura do bloco
	h = 32; // Altura do bloco
	Bloco();
	/**
    * Fun��o usada para desenhar o bloco na tela, e iguala os par�metros a e b ao x e y respectivamente
    * @param a Valor que ser� passado para o X do nosso bloco
    * @param b Valor que ser� passado para o Y do nosso bloco
    */
	void Draw(ALLEGRO_BITMAP *imagem,int a, int b);

	/**
    * Fun��o usada para desenhar o n�mero da fase na tela usando um tileset, onde devemos mapealo, e pegar a imagem que queremos
    * @param a Valor que ser� passado para o X do nosso bloco
    * @param b Valor que ser� passado para o Y do nosso bloco
    * @param xi Valor do X da imagem que queremos, que est� dentro do nosso tileset
    * @param yi Valor do Y da imagem que queremos, que est� dentro do nosso tileset
    */
	void drawRegion(ALLEGRO_BITMAP *imagem,int a, int b,int xi,int yi);
	~Bloco();
};

#endif // BLOCO_H
