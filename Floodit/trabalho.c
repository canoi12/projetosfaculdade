#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include"conio.h"
#include <stdlib.h>
#include <dirent.h>
#include "trocalinha.h"
#define NC 14
#define NL 14


int main(){
	/* -------- Variáveis -------- */
	int i,j,nums;
	FILE *fp;
	Jogo jogo,aux;
	jogo.chances = 0;
	char num,c,nome[100],aux1[100];
	/* ---------- Gera matriz aleatoriamente ----------- */
	srand (time(NULL));
	for(i=0;i<NL;i++){
		for(j=0;j<NC;j++){
			jogo.m[i][j] = rand() % 6;
		}
	}
	/* ---------- Instruções --------- */
	printf("Instrucoes:\n");
	printf("Pressione 'q' para sair\n");
	printf("Pressione 's' para salvar\n");
	printf("Pressione 'o' para carregar um jogo salvo\n\n");
		/* --------- Jogos salvos ----------- */
	printf("Jogos salvos ate o momento:\n");
	checa_dir();
	/* ---------- Lê nome do usuário ----------- */
	printf("Digite seu nome:\n");
	scanf("%s",nome);
	if(nome == "q"){
		return 0;
	}
	sprintf(aux1,"saves/%s",nome);
	/* -------- Laço que faz jogo rodar ----------- */
	while(jogo.chances < 26){
	/* --------- Exibe tabuleiro ----------- */
		for(i=0;i<NL;i++){
			for(j=0;j<NC;j++){
				printf("%d ",jogo.m[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		/* --------------- Lê entrada do usuário --------------- */
		printf("Rodada %i\n",jogo.chances+1);
		printf("Digite um numero: \n");
		num = getch();
		printf("\n");
	/* ---------- Sai do jogo ao pressionar Q ------------*/
		if(num == 'q')
		{
			break;
		} 
	/* --------------------- Salva arquivo ------------------- */
		else if(num == 's')
		{
			checa_dir();
			fp = fopen(aux1,"w");
			if(fp == NULL){
				printf("Arquivo nao encontrado");
			} else {
				for(i=0;i<14;i++){
					for(j=0;j<14;j++){
						fputc(jogo.m[i][j]+'0',fp);
					}
				}
			}
			fclose(fp);
			fp = fopen(aux1,"a");
			fputc(jogo.chances+'0',fp);
			fclose(fp);
		}
		/* --------------------- Carrega arquivo ------------------------- */
		else if(num == 'o')
		{
			checa_dir();
			printf("Digite o nome do arquivo que voce quer carregar:\n");
			scanf("%s",nome);
			sprintf(aux1,"saves/%s",nome);
			fp = fopen(aux1,"r");
			if(fp == NULL){
				printf("Arquivo nao encontrado");
			} else {
				for(i=0;i<14;i++){
					for(j=0;j<14;j++){
						c = fgetc(fp);
						jogo.m[i][j] = c-'0';
					}
			}
			c = fgetc(fp);
			jogo.chances = c - '0';
			}
		}
		/* ---------- Variável int recebe valor correspondente ao valor da variável tipo char --------*/
		if (num >= '0' && num <= '5') 
		{
			nums = num - '0';
		}
		/* ----------- Troca o número somente se o número digitado for:
		 * Maior ou igual a zero
		 * Menor ou igual a cinco
		 * Se o valor digitado for diferente do da primeira célula da matriz
		*/
		if(num >= '0' && num <= '5' && nums != jogo.m[0][0])
		{
			troca_lincol(jogo.m[0][0], nums, jogo.m,0,0);
			jogo.chances++;
		}
		/* -------- Variável do tipo Jogo chamada aux, recebe os valores guardados na variável jogo */
		aux = jogo;
		/* ------- Checa se a matriz está preenchida com somente um número, se sim, termina o jogo --------- */
		if(checa_tudo(aux.m[0][0],aux.m,0,0) == 1)
		{
			printf("Voce ganhou! Parabens!!\n");
			break;
		}
	}
	if((jogo.chances + 1) >= 26){
		printf("Lixo");
	}
	return 0;
}
