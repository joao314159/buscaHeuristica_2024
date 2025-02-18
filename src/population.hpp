#pragma once

#include <iostream>
#include <algorithm>
#include <ctime>
#include "solution.hpp"
#include "funcoes.hpp"


class Population{

    public:

    vector<Solution> solutions;

    Solution melhor; 

    int tamanho_maximo;
             
    
    Population(bool inicializar, Instance instance){
        cout<<"TESTE"<<endl<<endl;
        solutions ={};

        if(inicializar){
            for(int i = 0;i<20;i++){
                cout<<"solução " <<i<<" adicionada"<<endl;
                Solution solution(instance);                
                
                solution = solution.random();
                
                this->solutions.push_back(solution);
                
            }
        }    

    }

    Solution Gerar_filho(Solution father, Solution mother){
      
        Instance instance = father.instance;

        //filho
        Solution solution3(instance);
        
        //será necessário para, após adicionados os elementos do pai no filho, não repetir
        //quando adicionar os elementos da mãe
        vector<bool> usados;

        //por enquanto nenhum elemento foi colocado no filho
        for(int i= 0 ;i<instance.quant_Elem;i++){
            usados.push_back(false);
        }

        
        for(int i =0; i< instance.quant_Grup;i++){
            Grupo grupo;
            grupo.tam_minimo = father.solucao[i].tam_minimo;
            grupo.tam_maximo = father.solucao[i].tam_maximo;

            solution3.solucao.push_back(grupo);
        }

        //primeiro preenchemos 50% de cada grupo com a solução do pai
        for(int i=0; i< instance.quant_Grup;i++){

            //nunca haverá valor 0
            int tamanho = solution3.solucao[i].elementos.size();
            tamanho = tamanho/2 +1;

            //passamos cada valor no grupo
            for(int i2=0;i<tamanho;i2++){
                solution3.solucao[i].elementos.push_back(father.solucao[i].elementos[i2]);
            }



        }



        return solution3;

    }

    void Criar_mutacao(int index, int intensidade){

    }

    //todas as soluções passando o tamanho máximo são as soluções 
    //que foram geradas pela última execução dessa função
    void seleciona_e_gera_filhos(){

        //no vector chances o valor na posição i+1 corresponde à soma 
        //do valor na posição i com o potencial da solução i+1 ser escolhida     
        vector<double> chances;
        
        
        vector<double> resultados;

        //para guardar as soluções que já geraram filhos
        vector<bool> usadas;

        Funcoes funcoes;

        double total = 0;
        double menor;
        double media;
        double base;
        int tamanho = solutions.size();

        menor = funcoes.get_total(this->solutions[0].solucao,solutions[0].instance.arr_Pair);

        for(int i=0; i <tamanho ;i++){

            usadas.push_back(false);

            double a;
            a = funcoes.get_total(this->solutions[i].solucao,solutions[i].instance.arr_Pair);
            resultados.push_back(a);

            if(a < menor){
                menor = a;
            }

            total+=a;
        }

        media = total/(double)tamanho;
        
        //para comparar os resultados e sortear os que vão gerar filhos
        base = menor - (media-menor) - 1;

        double a1 = resultados[0]-base; 
        chances.push_back(a1);

        for(int i = 1;i < tamanho; i++){
            double a = resultados[i]-base;
            a +=chances[i-1];
            chances.push_back(a);
        }

        //agora o vector chances tem as probabilidades para cada solução

        //selecionamos as que vão gerar filhos
        
        unsigned seed = time(0);
        srand(seed);
        int maior = chances[tamanho-1];

        vector<int> fathers;
        vector<int> mothers;

        int index1;
        int index2;
        
        for(int i = 0;i<10;i++){

            double sorteio = rand()%maior +1;

            //fazer para todos os pais e mães

            //sorteamos os pais
            for(int i2 =0;i2<tamanho-1;i2++){

                double sorteio = rand()%maior +1;

                if(resultados[i]<=sorteio && sorteio<= resultados[i+1]){
                    index1 = i;
                    break;
                }
              
            }

            sorteio = rand()%maior +1;
            
            //sorteamos as mães
            for(int i2 =0;i2<tamanho-1;i2++){
               
                if(resultados[i]<=sorteio && sorteio<= resultados[i+1]){
                    index2 = i;
                    break;
                }
              
            }

            fathers.push_back(index1);
            mothers.push_back(index2);

        }    

        int tamanho2 = fathers.size();

        //agora geramos os filhos
        for(int i=0;i<tamanho2;i++){
            Solution solution1 = this->solutions[fathers[i]];
            Solution solution2 = this->solutions[mothers[i]];

            Solution resultado = this->Gerar_filho(solution1,solution2);

            this->solutions.push_back(resultado);
        }

    }

    //faz restarem apenas 20 organismos
    void destruir(){

    }

    //reproduz organismos, mata organismos, gera mutações, salva melhor até o momento
    void faz_tudo(){

    }

};
