O que foi feito:
 Básico:
 O jogo faz o básico, lê uma entrada do usuário, substitui na primeira célula do tabuleiro, e vai conferindo se as células
 adjascentes tem o mesmo valor desta primeira. Ele carrega e salva arquivos, e termina o jogo ao pressionar 'q'.

 Extra:
 Um ponto extra que tentamos implementar foi a possibilidade de fazer múltiplos salvamentos, salvando o tabuleiro e o 
 número de chances em um arquivo com o nome do jogador, e sendo possível carregar novamente, digitando o nome do arquivo 
 correspondente, claro.

O que seria feito diferente:
 Nós gostaríamos de fazer a parte gráfica, porém não tinhamos nem ideia de como fazer, então decidimos tentar fazer alguma 
 coisa mais simples pra não dificultar mais o desenvolvimento do projeto.

Compilar:
 Se o programa for compilado no linux, os arquivos 'trabalho.c' e 'trocalinha.c' devem ser compilados juntos, e a 
 biblioteca 'conio.h' deve estar na pasta, . Caso o programa for compilado no Windows, do mesmo jeito os arquivos
 'trabalho.c' e 'trocalinha.c' devem ser compilados juntos, porém se der algum erro de compilação devido ao 'conio.h', 
 o trecho ' #include"conio.h" ', deve ser substituído por '#include<conio.h>'. E sempre deve haver uma pasta chamada 'saves'
 na mesma pasta do projeto, que é onde são salvados os arquivos. Se não houver esta pasta, o programa não conseguirá salvar
 ou carregar nenhum arquivo.

Dupla:
 Átila Caetano da Silveira
 Canoi Gomes de Aguiar

O que cada um fez:
 Canoi: Escreveu todo o código
 Átila: Testou o código, ajudando a solucionar os problemas.