#include "BolaDeFogo.h"



BolaDeFogo::BolaDeFogo(int dragaoY)
{
	y = dragaoY;
}

void BolaDeFogo::moveFogo()
{
	x = x + 8;
}

void BolaDeFogo::Draw(ALLEGRO_BITMAP * bolaDeFogo)
{
	al_draw_bitmap(bolaDeFogo, x, y, 0);
}

bool BolaDeFogo::colFogo(Player * jogador)
{
		// Se colidiu
		if (y + h > jogador->y
			&& x + w > jogador->x
			&& y < jogador->y + jogador->h
			&& x < jogador->x + jogador->w)
		{
			return true;
		}
		// Se não colidiu
		return false;
}


BolaDeFogo::~BolaDeFogo()
{
}
