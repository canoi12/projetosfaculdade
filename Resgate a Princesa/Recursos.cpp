#include "Recursos.h"

void leRanking(User *pessoa) {
    // Cria uma variável para auxiliar na leitura do txt, já que tem nome em uma linha e pontos na outra
	bool alterna = false;
	// String usada para ler a linha atual do txt
	string line;
	// Variável para auxiliar em qual elemento do vetor nós devemos alocar esse dados
	int i = 0;
	// Carrega o txt
	ifstream myFile("ranking/ranking.txt");
	if (myFile.is_open()) {
		while (!myFile.eof()) {
			getline(myFile, line);

			// Se alterna for false, ele coloca a linha atual dentro da variável "nome" do nosso struct
			if (alterna == false) {
				pessoa[i].nome = line;
				//cout << "foi sim" << endl;
			}
			// Se alterna for true, ele coloca a linha atual convertida para int dentro da variável "pontos" do nosso struct
			// E depois incrementa o i, para podemos fazer o mesmo para os próximos elementos do struct
			else if (alterna == true) {
				//cout << "foi nao" << endl;
				pessoa[i].pontos = atoi(line.c_str());
				//cout << "foi" << endl;
				i++;
			}
			alterna = !alterna;
		}
		myFile.close();
	}
}

string stringalizar(int x)
{
    // Cria uma variável ostringstream, concatena um int nela, e retorna ela "convertida" em string
    ostringstream oss;
	oss << x;
	return oss.str();
}

void escreveRanking(User *pessoa) {
    // Cria a variável auxiliar pontoString para guardar o valor do int convertido para string
	string pontoString;
	int i = 0;
	// Carrega o arquivo txt que será usado para guardar o ranking
	ofstream myFile;
	myFile.open("ranking/ranking.txt", ios::trunc);
	if (myFile.is_open()) {
		for (int i = 0;i < 10;i++) {
            // Adiciona o nome no arquivo e dá uma quebra de linha
			myFile << pessoa[i].nome + "\n";
            // Converte a variável pontos para string, e a iguala a pontosString
			pontoString = stringalizar(pessoa[i].pontos);
			if (i<9) {
				myFile << pontoString + "\n";
			}
			else {
				myFile << pontoString;
			}
		}
		myFile.close();
	}
}



// Lê a matriz através de um arquivo .txt
void leMatriz(int n, Bloco matriz[20][20]) {
	FILE *fp;
	int i, j;
	char arq[20];
	// Cria as variável lermos o arquivo txt
	string fase("fase"), num2, txt(".txt");
	// Criamos o tipo ostringstream, para nos ajudar a converter int para string
	ostringstream tmp;
	tmp << n;
	num2 = tmp.str();
	// Concatenamos as 3 variáveis, e usamos ela completa para abrir o nome do arquivo que desejamos
	fase += num2 + txt;
	fp = fopen(fase.c_str(), "r");
	// Depois de aberto o arquivo, usamos ele para passar os dados necessários para nossa matriz de Blocos
	for (i = 0; i < 20;i++) {
		for (j = 0; j < 20; j++) {
			fscanf(fp, "%i ", &matriz[j][i].tipo);
			matriz[j][i].y = i * 32;
			matriz[j][i].x = j * 32;

		}
		fscanf(fp, "\n");
	}

	fclose(fp);
}

Fase* criaFase() {
    // Função usada somente para criar a cabeça da fila
	Fase *novo = new Fase;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20;j++) {
			novo->matriz[j][i].tipo = 0;
		}
	}
	novo-> n = 0;
	novo->prox = NULL;

	return novo;
}
Fase* insereFases(Fase* fila, Bloco matriz[20][20],int n) {
	// Cria o novo nó
	Fase* novo = new Fase;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20;j++) {
			novo->matriz[j][i] = matriz[j][i];
		}
	}
    novo->n = n;
	novo->prox = NULL;

    // Percorre toda a lista, e adiciona o novo nó no final
	Fase* aux = new Fase;
	aux = fila;
	while (aux->prox != NULL) {
		aux = aux->prox;
	}
	aux->prox = novo;
	return fila;
}
Fase* removeLista(Fase* fila) {
    // Remove o primeiro nó da lista
	Fase* aux = new Fase;
	aux = fila->prox;
	fila->prox = aux->prox;
	delete aux;
	return NULL;
}


Fase *removeTudo(Fase* fila) {
	Fase *aux = new Fase;
	while (fila->prox != NULL) {
		//cout << fila->matriz[0][0] << endl;
		aux = fila;
		fila = fila->prox;
		removeLista(aux);
	}
	return aux;
}

bool testeColY(Player *jogador, Fase *fila, int *vspd) {
	bool teste = false;
	// Faz o teste de colisão entre o personagem e bloco atual na vertical, usando a função dentro da classe player, e retornando true caso esteja colidindo
	for (int i = 0;i < 20;i++) {
		for (int j = 0; j < 20;j++) {
			if (fila->prox->prox->matriz[j][i].tipo != 0) {
				teste = jogador->colisaoY(fila->prox->prox->matriz[j][i].y, fila->prox->prox->matriz[j][i].x, vspd);
				if (teste) {
					return teste;
				}
			}
			if (fila->prox->matriz[j][i].tipo != 0 && fila->prox->matriz[j][i].x > 240) {
				teste = jogador->colisaoY(fila->prox->matriz[j][i].y, fila->prox->matriz[j][i].x, vspd);
				if (teste) {
					return teste;
				}
			}


			//cout << fila->prox->matriz[i][j].y << endl;
		}
	}
	return teste;
}

// Teste de colisão do X
bool testeColX(Player *jogador, Fase *fila, int *vspd) {
	bool teste = false;
	// Faz o teste de colisão entre o personagem e bloco atual na horizontal, usando a função dentro da classe player, e retornando true caso esteja colidindo
	for (int i = 0;i < 20;i++) {
		for (int j = 0; j < 20;j++) {
			if (fila->prox->matriz[j][i].tipo != 0 && fila->prox->matriz[j][i].x > 240) {
				teste = jogador->colisaoX(fila->prox->matriz[j][i].y, fila->prox->matriz[j][i].x, vspd);

				if (teste) {
					//cout << "aqui 1" << endl;
					return teste;
				}
			}
			else if (fila->prox->prox->matriz[j][i].tipo != 0 && fila->prox->prox->matriz[j][i].x > 240) {
				teste = jogador->colisaoX(fila->prox->prox->matriz[j][i].y, fila->prox->prox->matriz[j][i].x, vspd);
				if (teste) {
					//cout << "aqui 2" << endl;
					return teste;
				}
			}


			//cout << fila->prox->matriz[i][j].y << endl;
		}
	}
	return teste;
}





void quickSort(User valor[], int esquerda, int direita)
{
    // Algoritmo de ordenação QuickSort, estamos usando o ultimo elemento como pivô, e mudamos o algoritmo para funcionar na ordem descrescente
	int i, j, x;
	User y;
	i = esquerda;
	j = direita;
	x = valor[direita].pontos;

	while (i <= j)
	{
		while (valor[i].pontos > x && i < direita)
		{
			i++;
		}
		while (valor[j].pontos < x && j > esquerda)
		{
			j--;
		}
		if (i <= j)
		{
			y = valor[i];
			valor[i] = valor[j];
			valor[j] = y;
			i++;
			j--;
		}
	}
	if (j > esquerda)
	{
		quickSort(valor, esquerda, j);
	}
	if (i < direita)
	{
		quickSort(valor, i, direita);
	}
}
