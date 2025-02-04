#pragma once

#include <iostream>
#include <algorithm>
#include "solution.hpp"


class Population{

    vector<Solution> solutions;

    Solution melhor; 
             
    
    Population(){
        cout<<"TESTE"<<endl<<endl;
    }

    Solution Gerar_filho(int index1, int index2){

        Solution solution1 = this->solutions[index1];
        Solution solution2 = this->solutions[index2];

        Instance instance = solution1.instance;

        Solution solution3(instance);

        
        for(int i =0; i< instance.quant_Grup;i++){
            Grupo grupo;
            grupo.tam_minimo = solution1.solucao[i].tam_minimo;
            grupo.tam_maximo = solution1.solucao[i].tam_maximo;

            solution3.solucao.push_back(grupo);
        }

    }

    void Criar_mutacao(int index){

    }

    Solution seleciona_e_gera_filho(){


    }

};
