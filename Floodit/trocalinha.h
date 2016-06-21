#ifndef __TROCALINHA
#define __TROCALINHA
#include<stdio.h>

/* --- Tipos definidos --- */
typedef struct {
	int m[14][14];
	int chances;
} Jogo;
/* --- Sub-rotinas --- */

/**
 * Procura se tem determinado valor nas c�lulas adjacentes a primeira, e das outras sucessivamente
 * @param n N�mero da primeira c�lula, o qual deve ser conferido se 	� o mesmo nas c�lulas adjascentes
 * @param nn O novo n�mero que substituir� o antigo
 * @param g[][] A matriz na qual ser�o feitas as mudan�as
 * @param x A linha que eu quero que comece a procura
 * @param y A colula que eu quero que comece a procura
 */
int troca_lincol(int n, int nn, int g[14][14],int x, int y);
/**
 * Percorre toda a matriz, checando se est� preenchida com somente um n�mero
 * @param n N�mero que ser� comparado, checando se a matriz est� completa somente com ele
 * @param m[14][14] A matriz que ser� checada
 * @param x Linha da qual come�ar� a procura
 * @param y Coluna da qual come�ar� a procura
 * @return Retorna um, caso todas as c�lulas da matriz estiverem preenchidas com um �nico n�mero
*/
int checa_tudo(int n, int m[14][14],int x, int y);
/**
 * Checa uma determinada pasta, e lista todos os arquivos presentes nela	
 */
void checa_dir();


#endif
