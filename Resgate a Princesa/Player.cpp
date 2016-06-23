#include "Player.h"
#include "Bloco.h"
using namespace std;
Bloco *bloco = new Bloco;


Player::Player()
{
}

void Player::Draw(ALLEGRO_BITMAP * imagem)
{
    anim += 1;
    if(anim < 10){
        al_draw_bitmap_region(imagem,0,0,32,32, x, y, 0);
    }
    else if(anim >= 10 && anim < 20){
        al_draw_bitmap_region(imagem,32,0,32,32, x, y, 0);
    }
    else if(anim >= 20 && anim < 30){
        al_draw_bitmap_region(imagem,64,0,32,32, x, y, 0);
    }
    if(anim >= 30){
        anim = 0;
    }
}
bool Player::colisaoY(int yb, int xb, int *vspd) {
	// Se colidiu
	if (y + h + *vspd > yb
		&& x + w > xb
		&& y < yb + bloco->h
		&& x < xb + bloco->w)
	{
		return true;
	}
	// Se não colidiu
	return false;
}
bool Player::colisaoX(int yb, int xb, int *vspd) {
	// Se colidiu
	if (y + 32> yb + 2
		&& x + 32 > xb + 2
		&& y < yb + 32
		&& x  < xb + 32)
	{
		return true;
	}
	// Se não colidiu
	return false;
}
void Player::move(bool testeY, bool testeX, int *vspd, int *hspd,int *pontos,int *tela) {
	if (testeY == true) {
		*vspd = 0;
		//cout << "colidiu" << endl;
	}
	else {
		*vspd += 2;
		y += *vspd;
		//cout << "nao colidiu" << endl;
	}
	if (testeX == true) {
		*tela = 2;
		*hspd += 8;
		//y = 0;
		//cout << "colidiu" << endl;
	}
	else {
		if (x % 32 == 0) {
			*pontos += 1;
		}
	}
}


Player::~Player()
{
}
