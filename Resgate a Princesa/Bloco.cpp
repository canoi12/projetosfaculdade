#include "Bloco.h"

Bloco::Bloco()
{
}

void Bloco::Draw(ALLEGRO_BITMAP *imagem, int a, int b) {
	x = a;
	y = b;
	al_draw_bitmap(imagem,x,y,0);
}
void Bloco::drawRegion(ALLEGRO_BITMAP *imagem,int a, int b,int xi,int yi){
    x = a;
    y = b;
    al_draw_bitmap_region(imagem,xi,yi,w,h,x,y,0);
}


Bloco::~Bloco()
{
}
