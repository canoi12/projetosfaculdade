#include "trocalinha.h"
#include<stdio.h>
#include <stdlib.h>
#include <dirent.h>
/* -------- Descrição das subrotinas no arquivo trocalinha.h ------------- */
int troca_lincol(int n, int nn, int g[14][14],int x, int y){
	if (g[x][y] == n && y < 14 && x < 14 && y >= 0 && x >= 0) {
		g[x][y] = nn;
		troca_lincol(n,nn,g,x-1,y);
		troca_lincol(n,nn,g,x,y+1);
		troca_lincol(n,nn,g,x+1,y);
		troca_lincol(n,nn,g,x,y-1);
	}
}
int checa_tudo(int n, int m[14][14],int x, int y){
	int i,j,cont=0;	
	for(i=0;i<14;i++){
		for(j=0;j<14;j++){
			if(m[i][j] == n){
				cont = cont + 1;
			}		
		}
	}
	printf("%d\n",cont);
	if(cont == 196){
		return 1;
	}
}
void checa_dir(){
	DIR *dir;
	struct dirent *lsdir;
	dir = opendir("saves/");
	while((lsdir = readdir(dir)) != NULL) {
		printf("%s ",lsdir->d_name);
	}
	printf("\n");
	closedir(dir);
}

