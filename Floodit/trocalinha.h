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
 * Procura se tem determinado valor nas células adjacentes a primeira, e das outras sucessivamente
 * @param n Número da primeira célula, o qual deve ser conferido se 	é o mesmo nas células adjascentes
 * @param nn O novo número que substituirá o antigo
 * @param g[][] A matriz na qual serão feitas as mudanças
 * @param x A linha que eu quero que comece a procura
 * @param y A colula que eu quero que comece a procura
 */
int troca_lincol(int n, int nn, int g[14][14],int x, int y);
/**
 * Percorre toda a matriz, checando se está preenchida com somente um número
 * @param n Número que será comparado, checando se a matriz está completa somente com ele
 * @param m[14][14] A matriz que será checada
 * @param x Linha da qual começará a procura
 * @param y Coluna da qual começará a procura
 * @return Retorna um, caso todas as células da matriz estiverem preenchidas com um único número
*/
int checa_tudo(int n, int m[14][14],int x, int y);
/**
 * Checa uma determinada pasta, e lista todos os arquivos presentes nela	
 */
void checa_dir();


#endif
