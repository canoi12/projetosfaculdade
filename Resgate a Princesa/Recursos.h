#ifndef RECURSOS_H
#define RECURSOS_H


#include<iostream>
#include<allegro5/allegro.h>
#include<allegro5/allegro_native_dialog.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_acodec.h>
#include<allegro5/allegro_audio.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<sstream>
#include"Player.h"
#include"Bloco.h"
#include"BolaDeFogo.h"
#include<algif.h>
//#include"GameControl.h"

using namespace std;

//Bloco matriz[20][20];

typedef struct fase Fase;
//tipos definidos'
struct fase {
	Bloco matriz[20][20];
	int n;
	Fase *prox;
};


typedef struct {
	string nome;
	int pontos;
} User;

/**
    * Carrega o ranking do .txt e guarda no usuario
    * @param *pessoa Vetor para receber os dados do arquivo .txt
    */
void leRanking(User *pessoa);

/**
    * Converte um inteiro para uma string
    * @param *x Valor que vai ser convertido
    */
string stringalizar(int x);

/**
    * Passa os dados do ranking para o .txt
    * @param *pessoa Vetor que armazena os dados que ser�o escritos
    */
void escreveRanking(User *pessoa);
/**
    * Carrega os dados da matriz de um arquivo .txt
    * @param matriz[20][20]
    */
void leMatriz(int n,Bloco matriz[20][20]);
/**
    * Cria a cabe�a da fila
    */
Fase* criaFase();
/**
    * Insere uma matriz de blocos no final da fila
    * @param *fila recebe um novo n�
    * @param matriz[20][20] matriz auxiliar que guarda as fases lidas do .txt
    * @param n Recebe o numero da fase atual, serve somente para exibir mais tarde o n�mero da fase atual
    */
Fase* insereFases(Fase* fila, Bloco matriz[20][20],int n);
/**
    * Remove uma matriz de blocos do inicio da fila
    * @param *fila A fila da qual o n� ser� deletado
    */
Fase* removeLista(Fase* fila);

Fase* removeTudo(Fase *fila);
/**
    * Testa de colis�o no eixo Y
    * @param *Jogador Personagem com o qual sera testado a colis�o
    * @param *fila Contem os blocos que ser�o usados no teste de colis�o
    * @param *vspd Gravidade, valor que influencia no teste de colis�o
    */
bool testeColY(Player *jogador, Fase *fila, int *vspd);
/**
    * Testa de colis�o no eixo X
    * @param *Jogador personagem com o qual sera testado a colis�o
    * @param *fila contem os blocos que ser�o usados no teste de colis�o
    * @param *vspd gravidade, valor que influencia no teste de colis�o
    */
bool testeColX(Player *jogador, Fase *fila, int *vspd);
/**
    * Algoritmo de ordena��o usado para ordenar o ranking
    * @param valor[] vetor que precisamos ordenar
    * @param esquerda valor usado durante o processo de ordena��o
    * @param direita valor usado durante o processo de ordena��o
    */
void quickSort(User valor[], int esquerda, int direita);

#endif // RECURSOS_H
