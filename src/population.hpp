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
             
    
    Population(){
        cout<<"TESTE"<<endl<<endl;
    }

    Solution Gerar_filho(Solution solution1, Solution solution2){
      
        Instance instance = solution1.instance;

        Solution solution3(instance);

        
        for(int i =0; i< instance.quant_Grup;i++){
            Grupo grupo;
            grupo.tam_minimo = solution1.solucao[i].tam_minimo;
            grupo.tam_maximo = solution1.solucao[i].tam_maximo;

            solution3.solucao.push_back(grupo);
        }

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

        double sorteio = rand()%maior +1;
        
        int index;
        //fazer para todos os pais
        for(int i =0;i<tamanho-1;i++){
            if(resultados[i]<=sorteio && sorteio<= resultados[i+1]){
                index = i;
            }
        }


    }

};
