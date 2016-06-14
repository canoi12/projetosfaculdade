/***********************************
Instruções do programa:
    - Quando abrir a interface gráfica, digite o número de pipelines que você deseja que a simulção tenha e pressione ENTER para rodar a simulação
    - Quando a simulação começar a rodar, aperte espaço para avançar o ciclo.
    - Caso a quantidade de Pipelines não caiba na tela, aperte setas direita ou esquerda para mover a camera.
    - Quando a simulação terminar, o único modo de fazer outra é iniciando o programa novamente.
************************************/


#include<stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include"pipeline.h"
#include"instruction.h"
#include<math.h>

#include<allegro5/allegro.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_primitives.h>

const float FPS = 60; // Frames por segundo
const int WIDTH = 1366; // Largura da tela
const int HEIGHT = 768; // Altura da tela
int camerax=0,cameray=0; // Valores X e Y da camera

// Enum criado para facilitar a identifição de cada estágio do pipeline dentro dos vetores
enum {
    IF = 0,
    ID = 1,
    EX = 2,
    MEM = 3,
    WB = 4
};

// Função responsável por contar as linhas das instruções
int contaLinhas(char* arquivo)
{
    int linhas = 0; // Variável que guarda a quantidade de linhas
    std::string line; // Variável que guarda a linha atual do txt
    ifstream myfile(arquivo); // Abre o arquivo txt
    
    if(myfile.is_open())
    {
        // Enquanto não estiver no final, vai incrementando a variável linhas
        while(!myfile.eof())
        {
            getline(myfile,line);

            linhas++;
        }
        myfile.close();
    }
    
    return linhas;  // Retorna a quantidade de linhas
}


// Pega todas as instruções a vai salvando no vetor
void pegaInstrucoes(char* arquivo, Instruction **inst)
{
    ifstream myfile(arquivo); // Abre o arquivo
    int instAtualTxt = 0; // Índice da instrução atual
    std::string line; // Linha atual
    
    if(myfile.is_open())
    {
        // Percorre todo o txt
        while(!myfile.eof())
        {
            getline(myfile,line); // Pega a linha atual, contendo a instrução e seus devidos valores
            
            // Cria uma nova instrução na posição atual do vetor
            inst[instAtualTxt] = new Instruction();
           
            std::size_t pos = line.find(" "); // Procura a posição do primeiro espaço
            
            // Roda o for, dependendo do valor do i, vai preenchendo os valores da instrução atual contida no vetor
            for(int i=0; i < 8; i++){
                pos = line.find(" ");
                
                switch(i)
                {
                    case 0:
                        inst[instAtualTxt]->m_id = line.substr(0,pos);
                        break;
                    case 1:
                        inst[instAtualTxt]->m_type = line.substr(0,pos);
                        break;
                    case 2:
                        inst[instAtualTxt]->m_rg1 = line.substr(0,pos);
                        break;
                    case 3:
                        inst[instAtualTxt]->m_rg2 = line.substr(0,pos);
                        break;
                    case 4:
                        inst[instAtualTxt]->m_rg3 = line.substr(0,pos);
                        break;
                    case 5:
                        pos = line.find(",");
                        inst[instAtualTxt]->m_dep[0] = line.substr(0,pos);
                        break;
                    case 6:
                        pos = line.find(",");
                        inst[instAtualTxt]->m_dep[1] = line.substr(0,pos);
                        break;
                    case 7:
                        inst[instAtualTxt]->m_dep[2] = line;
                        break;

                }
                    
                line.erase(0,pos+1);
            }

        
            instAtualTxt++; // Incrementa a variável instrução atual para pegar a próxima
        }
        myfile.close();
    }
}



int main(int argc, char *argv[])
{
    
    inicio:
    
    // Variável de janela da interface gráfica
    ALLEGRO_DISPLAY *janela = NULL;
    
    // Variáveis que guardam fonte 
    ALLEGRO_FONT *fonte = NULL; 
    ALLEGRO_FONT *fonteInst = NULL;
    
    // Fila de eventos da interface gráfica
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    
    // Timer para controlar o FPS
    ALLEGRO_TIMER *timer = NULL;
    
    // Pega o estado do teclado
    ALLEGRO_KEYBOARD_STATE keystate;
    
    // Inicia o allegro
    al_init();
    
    // Inicia as fontes
    al_init_font_addon();
    
    // Inicia os ttf
    al_init_ttf_addon();
    
    // Inicia o teclado
    al_install_keyboard();
    al_install_mouse();
    
    
    // Cria a janela
    janela = al_create_display(WIDTH,HEIGHT);
    
    // Carrega as fontes
    fonte = al_load_font("Early GameBoy.ttf", 24, 0);
    fonteInst = al_load_font("Early GameBoy.ttf",16,0);
    
    // Cria o timer
    timer = al_create_timer(1.0/FPS);
    
    bool claudinho; // Variável porteiro, que diz quando as instruções podem entrar ou não em algum pipeline
    int n; // Quantidade de pipelines
    int instAtual = 0, cicloAtual=0; // Instrução atual e ciclo atual
    int espDesPipe = 250; // Espaçamento de cada desenho do pipeline
    int numEstagiosNaoUtilizado = 0;
    int xDesPipe = 450, yDesPipe = 300; // X e Y do desenho Pipeline
    int yDesInst = 0; // Y das instruções
    int numBolhas = 0; // Número de bolhas
    int numPipeNaoUtilizados = 0; // Número de Pipelines não utilizados
    bool teste = true; // Variável que controla o laço principal
    std::string numPipe; // Variável que recebe o número de Pipelines na interface gráfica
    
    fila_eventos = al_create_event_queue(); // Cria a fila de eventos
    
    al_register_event_source(fila_eventos, al_get_display_event_source(janela)); // Registra os eventos do display na fila de eventos
    al_register_event_source(fila_eventos, al_get_keyboard_event_source()); // Registra os eventos do teclado na fila de eventos
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer)); // Registra o timer na fila de eventos
    al_register_event_source(fila_eventos,al_get_mouse_event_source());
    
    al_start_timer(timer); // Inicia o timer
    
    // Laço responsável por pegar a entrada do usuário que representa a quantidade de pipelines
    while(1)
    {
        ALLEGRO_EVENT evento; // Cria uma variável que guarda o evento atual
        
        al_wait_for_event(fila_eventos,&evento); // Espera algum evento acontecer
        
        al_clear_to_color(al_map_rgb(255,255,255)); // Pinta a tela toda de branco
        al_draw_text(fonte,al_map_rgb(0,0,0),50,50,ALLEGRO_ALIGN_LEFT,"Digite a quantidade de Pipelines:"); // Imprime um texto na tela
    
        al_draw_text(fonte,al_map_rgb(0,0,0),50,100,ALLEGRO_ALIGN_LEFT,numPipe.c_str()); // Imprime outro texto na tela
    
        al_flip_display(); // Troca o display
        
        // Se o usuário fechou a janela, sai do laço, e seta a variável teste para falso
        // Então ele não entra no outro laço
        if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            teste = false;
            break;
        }
        // Verifica se o usuário pressionou alguma tecla
        if(evento.type == ALLEGRO_EVENT_KEY_DOWN)
        {
             // Se a tecla for um número então ele concatenando esse valor à variável numPipe
            if(evento.keyboard.keycode >= ALLEGRO_KEY_0 && evento.keyboard.keycode <= ALLEGRO_KEY_9)
            {
                int a = evento.keyboard.keycode - 27;
                stringstream ss;
                ss << a;
                numPipe += ss.str();
                
                std::cout << numPipe << std::endl;
            }
            // Se a tecla for backspace ele apaga o ultimo digito na variável numPipe
            if(evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
            {
                numPipe = numPipe.substr(0,numPipe.size()-1);
                std::cout << numPipe << std::endl;
            }
            // Se a tecla for enter, sai do laço
            if(numPipe != "" && evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
            {
                break;
            }
        }
    }
    
    // Converte o valor da variável numPipe, que é string, para int.
    n = atoi(numPipe.c_str());
    
    // Chama a função contaLinhas, que conta a quantidade de linhas do arquivo .txt que representa a quantidade de instruções
    // e guarda o valor na variável numLinhas
    int numLinhas = contaLinhas(argv[1]);
    
    // Usa a variável numLinhas para criar um vetor de instruções
    Instruction *inst[numLinhas];
    
    // Pega todas as instruções guardadas no arquivo txt, e as coloca no vetor de instruções.
    pegaInstrucoes(argv[1], inst);
    
    // Cria um novo vetor de pipelines de tamanho n
    Pipeline *p = new Pipeline[n];
    
    // Entra no laço principal do programa
    while(teste){
        //std::cout << "Ciclo " << cicloAtual << std::endl;
        claudinho = true; // claudinho truta
        
        ALLEGRO_EVENT evento; // Cria uma variável que guarda o evento atual
        
        al_clear_to_color(al_map_rgb(255,255,255)); // Pinta a tela toda de branco
        
        al_wait_for_event(fila_eventos,&evento); // Espera algum evento acontecer
        
        // Se o usuário fechou a janela, sai do laço, e seta a variável teste para falso
        if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            teste = false;
        }
        // Se o usuário apertou alguma tecla, entra no if
        if(evento.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            // Se a tecla for espaço
            if(evento.keyboard.keycode == ALLEGRO_KEY_SPACE){   
                // Percorre todos os pipelines
                for(int i = 0; i < n; i++)
                {  
                    // Percorre novamente todos os pipelines, dessa vez testando se existe dependencia entre a instrução atual
                    // E alguma outra que está em algum pipeline
                    for(int j =0; j < n;j++)
                    {
                        if(instAtual < numLinhas)
                        {
                            // Caso encontre dependencia, o porteiro claudinho fica false, e o laço é quebrado
                            if(p[j].checkDep(*inst[instAtual]))
                            {   
                                claudinho = false;
                                break;
                            }
                        }
                    }
                    
                    // Chama a função move para o pipeline atual, que move as instruções dentro dos estágios de cada pipeline
                    p[i].move();
                    
                    // Caso não haja dependencia, é chamada a função push para o pipeline atual, inserindo uma nova instrução nele
                    // E incrementando a variável instAtual, que por sua vez será o indice da nova instrução
                    if(claudinho)
                    {
                        if(instAtual < numLinhas)
                        {
                            p[i].push(*inst[instAtual]);
                            yDesInst += 20; // Incrementa o Y do desenho das instruções
                            instAtual++;
                        }   
                    }
                    else
                    {
                        
                    }
                }
                
                // For que percorre todos os pipelines, testando se estão todos vazios.
                for(int i = 0; i < n && cicloAtual > 0; i++)
                {
                    // Caso todos os pipelines estejam vazios, teste fica falso
                    if(p[i].estagio[IF].m_id == "(" && p[i].estagio[ID].m_id == "(" && p[i].estagio[EX].m_id == "(" && p[i].estagio[MEM].m_id == "(" && p[i].estagio[WB].m_id == "(")
                    {
                        teste = false; 
                    }
                    // Se não, teste permanece true, e o laço é quebrado
                    else
                    {
                        teste = true;
                        break;
                    }
                }
                
                // Número de pipelines não utilizado, a partir do despacho da primeira instrução
                if(cicloAtual >= 4 && teste)
                {
                    for(int k = 0; k < n; k++)
                    {
                        if(p[k].estagio[WB].m_id == "(")
                        {
                            numPipeNaoUtilizados += 1;
                        }
                        for(int l = 0; l < 5; l++)
                        {
                            if(p[k].estagio[l].m_id == "(" && instAtual <= numLinhas)
                                numEstagiosNaoUtilizado += 1;
                        }
                    }
                    if(instAtual == numLinhas)
                        instAtual++;
                }
                std::cout << instAtual << std::endl; 
                std::cout << numLinhas << std::endl;
                std::cout << numEstagiosNaoUtilizado << std::endl;
                cicloAtual++; // Incrementa o ciclo
            }
        }
        
       // Se o evento for timer
       if(evento.type == ALLEGRO_EVENT_TIMER)
       {
            // Pega o estado atual do teclado
            al_get_keyboard_state(&keystate);
            
            // Se o estado for "tecla pressionada", e a tecla for seta para a direita
            // incrementa a variável que guarda o valor x da camera
            if(al_key_down(&keystate,ALLEGRO_KEY_RIGHT))
            {
                if(camerax < xDesPipe+(espDesPipe*n)-WIDTH)
                {
                    camerax += 10;
                }
            }
            // Se não, se o estado for "tecla pressionada", e a tecla for seta para a esquerda
            // decrementa a variável que guarda o valor x da camera
            else if(al_key_down(&keystate,ALLEGRO_KEY_LEFT))
            {
                if(camerax > 0)
                {
                    camerax -= 10;
                }
            }
            
            // Desenha um texto na tela
            al_draw_textf(fonte,al_map_rgb(0,0,255),xDesPipe,yDesPipe-50,ALLEGRO_ALIGN_LEFT,"Ciclo %d",cicloAtual);
            
            // For que percorre todos os pipelines
            for(int i = 0; i < n; i++){
                
                // Desenha um texto na tela
                al_draw_textf(fonte,al_map_rgb(0,0,255),xDesPipe+(espDesPipe*i)-camerax,yDesPipe,ALLEGRO_ALIGN_LEFT,"Pipeline %d",i+1);
                
                // For que percorre todos os estagios do pipeline
                for(int j = 0; j < 5; j++)
                {
                    std::string estagio; // Variável que guarda o estagio atual que está sendo testado
                    switch(j)
                    {
                        case 0:
                            estagio = "IF";
                            break;
                        case 1:
                            estagio = "ID";
                            break;
                        case 2:
                            estagio = "EX";
                            break;
                        case 3:
                            estagio = "MEM";
                            break;
                        case 4:
                            estagio = "WB";
                            break;
                    }
                    // Se o estagio atual estiver vazio, printa uma bolha e o texto azul
                    if(p[i].estagio[j].m_id != "(")
                        al_draw_textf(fonte,al_map_rgb(0,0,0),xDesPipe+(espDesPipe*i)-camerax,yDesPipe+(30*(j+1)),ALLEGRO_ALIGN_LEFT,"%s: %s.%s",estagio.c_str(),p[i].estagio[j].m_id.c_str(),p[i].estagio[j].m_type.c_str());
                    // Se não, printa de boas
                    else
                        al_draw_textf(fonte,al_map_rgb(0,128,128),xDesPipe+(espDesPipe*i)-camerax,yDesPipe+(30*(j+1)),ALLEGRO_ALIGN_LEFT,"%s: %s",estagio.c_str(),p[i].estagio[j].m_id.c_str());
                }
                
                // For que desenha as linhas entre os pipelines
                for(int z = 0; z < n; z++)
                {
                    al_draw_line(xDesPipe+(espDesPipe*i)-5-camerax,yDesPipe,xDesPipe+(espDesPipe*i)-5-camerax,yDesPipe+170,al_map_rgb(0,0,0),2);
                }
            }
            // Desenha um retângulo
            al_draw_filled_rectangle(0,0,430,768,al_map_rgb(0,0,0));
            
            // Desenha uma linha
            al_draw_line(0,yDesPipe,430,yDesPipe,al_map_rgb(0,0,255),2);
            
            // Variável j que recebe a quantidade de instruções
            int j = numLinhas;
            
            // For que percorre todas as instruções e as imprime invertidas
            for(int i = 0; i < numLinhas; i++)
            {
                al_draw_textf(fonteInst,al_map_rgb(255,255,255),10,(-(i*20))+yDesPipe-20+yDesInst,ALLEGRO_ALIGN_LEFT,"Inst: %s %s %s %s %s %s %s %s",inst[i]->m_id.c_str(),inst[i]->m_type.c_str(),inst[i]->m_rg1.c_str(),inst[i]->m_rg2.c_str(),inst[i]->m_rg3.c_str(),inst[i]->m_dep[0].c_str(),inst[i]->m_dep[1].c_str(),inst[i]->m_dep[2].c_str());
                j--;
            }
            
            al_flip_display(); // Muda o display
        
        }
    }
    
    std::cout << "São necessários" << cicloAtual << "ciclos para executar essas instruções." << std::endl;
    std::cout << "Bolhas: " << numPipeNaoUtilizados << std::endl;
    std::cout << "IPC: " << (float)numLinhas/cicloAtual << std::endl;
    std::cout << "Média de não utilizados: " << (float)numEstagiosNaoUtilizado/(5*n) << std::endl;
    
    // Desenha as informações finais
    while(1){
        
        ALLEGRO_EVENT evento;
        
        al_wait_for_event(fila_eventos,&evento);
        
        if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            break;
        }
        al_clear_to_color(al_map_rgb(255,255,255)); // Pinta a tela de branco, de novo
        xDesPipe = 50; // Seta xDesPipe para o seu valor padrão
        al_draw_textf(fonte,al_map_rgb(0,0,255),xDesPipe,yDesPipe,ALLEGRO_ALIGN_LEFT,"sao necessarios %d ciclos para executar essas instrucoes.",cicloAtual);
        al_draw_textf(fonte,al_map_rgb(0,0,255),xDesPipe,yDesPipe+120,ALLEGRO_ALIGN_LEFT,"Bolhas: %d",numPipeNaoUtilizados);
        al_draw_textf(fonte,al_map_rgb(0,0,255),xDesPipe,yDesPipe+150,ALLEGRO_ALIGN_LEFT,"IPC: %f",(float)numLinhas/cicloAtual);
        al_draw_textf(fonte,al_map_rgb(0,0,255),xDesPipe,yDesPipe+180,ALLEGRO_ALIGN_LEFT,"Media de nao utilizacao: %f",(float)numEstagiosNaoUtilizado/(5*n));

        al_flip_display(); // Muda o display, de novo
    }
    
    
    // Destroi as variáveis do allegro
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
    al_destroy_font(fonte);
    
    //goto inicio;
    
    return 0;
}
