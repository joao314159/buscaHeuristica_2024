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

    Instance instance;

    int tamanho_maximo;
             
    
    Population(bool inicializar, int tamanho_maximo, Instance instance){
        cout<<"TESTE"<<endl<<endl;
        solutions ={};

        this->tamanho_maximo = tamanho_maximo;

        this->instance = instance;

        

        if(inicializar){
            //as primeiras soluções são aleatórias
            for(int i = 0;i<tamanho_maximo-1;i++){
                cout<<"solução " <<i<<" adicionada"<<endl;
                Solution solution(instance);                
                
                solution = solution.random();
                
                this->solutions.push_back(solution);
                
            }
            //a última solução segue a heurística
            Solution solution(instance);

            solution.solucao = solution.calcular_resultado5();

            this->solutions.push_back(solution);
        }  
        
        //para usar a função rand() depois
        unsigned seed = time(0) * (solutions[0].solucao[0].elementos[0] + 2 + (10/time(0)));
        srand(seed);

    }

   
    int sorteador(vector<double>& lista, int tamanho){
    
                
        int i2 =0;
        
        double total = 0;
        for(int i = 0;i<tamanho; i++){
            total+=lista[i];
        }
        
        int total2 = (int)total + 1;
        cout<<"total: "<<endl;
        cout<<total2<<endl;
      
        double e = ((rand() / (double)RAND_MAX)); 
        double a = e * total2; 

        cout<<"sorteado: "<<endl;
        cout<<e<<endl;
        
        total = 0;
        i2=0;
        for(int i = 0;i<tamanho;i++){
            total+=lista[i];
            if(total>a){
                i2 = i;
                break;
            }
        }
        
        return i2;
    }

    Solution gerar_filho(Solution father, Solution mother){
      
        Instance instance = father.instance;

        //filho
        Solution solution3(instance);
        /*
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

*/

        return solution3;

    }

    void criar_mutacao(int index, int intensidade){

    }

    //todas as soluções passando o tamanho máximo são as soluções 
    //que foram geradas pela última execução dessa função
    void seleciona_e_gera_filhos(){

        //resultados para cada solução. Quanto maior, maior a chance de ser selecionada.
        vector<double> resultados;
        vector<double> chances;
        double media = 0;
        int tamanho = this->solutions.size();
        Funcoes funcoes;



        for(int i3=0;i3<10;i3++){

            cout<<endl;

            cout<<"gerando filho "<<i3<<endl<<endl;


            for(int i = 0;i< tamanho; i++){
                double a;
                a = funcoes.get_total(this->solutions[i].solucao,solutions[i].instance.arr_Pair);
                resultados.push_back(a);
            }

            //gerar valores para cada solução baseado em seu resultado, para serem usados no sorteio dos pais e filhos.
            //quando sortear um pai. descartá-lo antes de sortear a mãe. Uma solução não pode ser pai e mãe.
            
            //primeiro calculamos a média dos resultados e o menor valor entre os resultados
            
            double menor = resultados[0];

            for(int i = 0;i< tamanho; i++)
            {
                //salvamos o menor valor
                if(resultados[i]< menor){
                    menor = resultados[i];
                }

                //calculamos a media
                media+=resultados[i];
            }

            media = media/tamanho;

            for(int i =0;i<tamanho;i++){
                double a;
                a = resultados[i] - menor +100;
                a = a*a;
                chances.push_back(a);
            }

            //testando os resultados
            for(int i=0;i<tamanho;i++){
                cout<<"resultado para a solução "<<i<<endl;
                cout<<resultados[i]<<endl;
                cout<<"chance da solução "<<i<<" ser sorteada: "<<endl;
                cout<<chances[i]<<endl;
            }
            cout<<endl<<endl;

            //agora a partir das chances de cada solução, sorteamos soluções para serem pais e mães de novas soluções
            //depois teremos que DESTRUIR soluções antigas, para que restem sempre 20.
            //Mas isso será feito pela função destruir.
            int sorteado1 = this->sorteador(chances,20);
            int sorteado2 = this->sorteador(chances,20);

            //testando
            double maior_chance = 0;
            for(int i = 0;i<tamanho;i++){

                cout<<"chances "<<i<<endl;
                cout<<chances[i]<<endl;

                if(chances[i]>maior_chance){
                    maior_chance = chances[i];
                }
            }

            cout<<"sorteado: "<<endl;
            cout<<chances[sorteado1]<<endl;
            cout<<"maior chance: "<<endl;
            cout<<maior_chance<<endl;
            cout<<endl<<endl;

            Solution pai = this->solutions[sorteado1];
            Solution mae = this->solutions[sorteado2];
            
            Solution filho = this->gerar_filho(pai,mae);
            this->solutions.push_back(filho);

        }
            
        /*
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
        
        /*
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

        int quantidade = 0;

        //agora geramos os filhos
        for(int i=0;i<tamanho2;i++){
            Solution solution1 = this->solutions[fathers[i]];
            Solution solution2 = this->solutions[mothers[i]];

            quantidade+=2; 

            cout<<"pai: "<<endl;
            solution1.imprimir();

            cout<<"mãe: "<<endl;
            solution2.imprimir();

            cout<<"quantidade: "<<endl;
            cout<<quantidade<<endl;

            cout<<endl<<endl;

            //Solution resultado = this->Gerar_filho(solution1,solution2);

            //this->solutions.push_back(resultado);
        }
            */

    }

    //faz restarem apenas 20 organismos
    void destruir(){

    }

    //reproduz organismos, mata organismos, gera mutações, salva melhor até o momento
    void faz_tudo(){

    }

    void imprimir(){
        for(int i = 0; i< this->tamanho_maximo; i++){

            cout<<"solução "<<i<<endl;

            for(int i2=0;i2 <this->solutions[i].solucao.size(); i2++){
                cout<<"grupo "<<i2<<endl;
                solutions[i].solucao[i2].imprimir();                
            }
            cout<<endl<<endl;
        }
    }

    void testar(){
        for(int i = 0; i< this->tamanho_maximo; i++){

            cout<<"solução "<<i<<endl;

            for(int i2=0;i2 <this->solutions[i].solucao.size(); i2++){
                cout<<"grupo "<<i2<<endl;
                solutions[i].solucao[i2].teste();          
            }
            cout<<endl<<endl;
        }

    }

};
