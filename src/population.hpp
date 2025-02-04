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

    }

    void Criar_mutacao(int index){

    }

    Solution seleciona_e_gera_filho(){



    }





};
