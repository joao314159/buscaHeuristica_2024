#pragma once

#include <iostream>
#include <algorithm>
#include <ctime>
#include "solution.hpp"
#include "funcoes.hpp"
#include "algorithm"

class Resultado_com_indice
{

public:
    int indice;
    double resultado;

    bool operator<(const Resultado_com_indice &resultado2) const
    {

        // int sorteio =  rand()%10;

        /*
        if(sorteio != 1){
            return this->resultado < resultado2.resultado;
        }else{
            return resultado2.resultado < this->resultado;
        }
        */

        return this->resultado < resultado2.resultado;
    }
};

class Population
{

public:
    vector<Solution> solutions;

    Solution melhor;

    Instance instance;

    int tamanho_maximo;

    Population(bool inicializar, int tamanho_maximo, Instance instance)
    {

        solutions = {};

        this->tamanho_maximo = tamanho_maximo;

        this->instance = instance;

        if (inicializar)
        {
            // as primeiras soluções são aleatórias
            for (int i = 0; i < tamanho_maximo - 1; i++)
            {

                Solution solution(instance);

                solution = solution.random();

                this->solutions.push_back(solution);
            }
            // a última solução segue a heurística
            Solution solution(instance);

            solution.solucao = solution.calcular_resultado5();

            this->solutions.push_back(solution);
        }

        this->melhor = solutions[0];

        // para usar a função rand() depois
        unsigned seed = time(0) * (solutions[0].solucao[0].elementos[0] + 2 + (10 / time(0)));
        srand(seed);
    }

    int sorteador(vector<double> &lista, int tamanho)
    {

        int i2 = 0;

        double total = 0;
        for (int i = 0; i < tamanho; i++)
        {
            total += lista[i];
        }

        int total2 = (int)total + 1;

        double e = ((rand() / (double)RAND_MAX));
        double a = e * total2;

        total = 0;
        i2 = 0;
        for (int i = 0; i < tamanho; i++)
        {
            total += lista[i];
            if (total > a)
            {
                i2 = i;
                break;
            }
        }

        return i2;
    }

    Solution gerar_filho(Solution father, Solution mother)
    {

        Instance instance = father.instance;

        // filho
        Solution solution3(instance);

        // será necessário para, após adicionados os elementos do pai no filho, não repetir
        // quando adicionar os elementos da mãe
        vector<bool> usados;

        // por enquanto nenhum elemento foi colocado no filho
        for (int i = 0; i < instance.quant_Elem; i++)
        {
            usados.push_back(false);
        }

        for (int i = 0; i < instance.quant_Grup; i++)
        {
            Grupo grupo;
            grupo.tam_minimo = father.solucao[i].tam_minimo;
            grupo.tam_maximo = father.solucao[i].tam_maximo;

            solution3.solucao.push_back(grupo);
        }

        // primeiro preenchemos 50% de cada grupo com a solução do pai
        for (int i = 0; i < instance.quant_Grup; i++)
        {

            // nunca haverá valor 0
            int tamanho = father.solucao[i].elementos.size();
            tamanho = tamanho / 2 + 1;

            // passamos cada valor no grupo
            for (int i2 = 0; i2 < tamanho; i2++)
            {
                solution3.solucao[i].elementos.push_back(father.solucao[i].elementos[i2]);
                usados[father.solucao[i].elementos[i2]] = true;
            }
        }

        // solution3.imprimir();

        // para percorrer os elementos
        int i3 = 0;
        // agora passamos os elementos restantes conforme a mãe
        for (int i = 0; i < instance.quant_Grup; i++)
        {

            // primeiro garantimos que todos os grupos respeitem o tamanho mínimo
            int i2 = solution3.solucao[i].elementos.size();

            while (i2 < solution3.solucao[i].tam_minimo)
            {

                // primeiro tentamos colocar os elementos da mãe nesse grupo
                int i4 = -1;
                for (int i5 = 0; i5 < mother.solucao[i].elementos.size(); i5++)
                {
                    // se algum elemento do grupo i está presente na mãe e não foi adicionado podemos adicioná-lo
                    if (not usados[mother.solucao[i].elementos[i5]])
                    {
                        i4 = mother.solucao[i].elementos[i5];
                    }
                }

                // se há um elemento da mãe para ser adicionado
                if (i4 != -1)
                {
                    usados[i4] = true;
                    solution3.solucao[i].elementos.push_back(i4);
                    i2++;
                    continue;
                }

                if (not usados[i3])
                {

                    solution3.solucao[i].elementos.push_back(i3);
                    i2++;
                    usados[i3] = true;
                }

                i3++;
            }
        }

        i3 = 0;
        // agora que já preenchemos o tamanho mínimo, adicionamos os elementos restantes
        for (int i = 0; i < instance.quant_Grup; i++)
        {

            while (solution3.solucao[i].elementos.size() < solution3.solucao[i].tam_maximo && i3 != instance.quant_Elem)
            {
                if (not usados[i3])
                {
                    solution3.solucao[i].elementos.push_back(i3);
                    usados[i3] = true;
                }
                i3++;
            }
        }

        // solution3.imprimir();

        return solution3;
    }

    void criar_mutacao(int index, int intensidade)
    {

        Funcoes funcoes;

        for (int i = 0; i < intensidade * instance.quant_Elem / 5.0; i++)
        {
            int quantidade_grupos = this->instance.quant_Grup;
            int index1 = rand() % quantidade_grupos;
            int index2 = rand() % quantidade_grupos;

            int quantidade_elementos1 = this->solutions[index].solucao[index1].elementos.size();
            int quantidade_elementos2 = this->solutions[index].solucao[index2].elementos.size();

            int elemento1 = rand() % quantidade_elementos1;
            int elemento2 = rand() % quantidade_elementos2;

            funcoes.trocaElementos(this->solutions[index].solucao[index1], this->solutions[index].solucao[index2], elemento1, elemento2);
        }
    }

    // todas as soluções passando o tamanho máximo são as soluções
    // que foram geradas pela última execução dessa função
    void seleciona_e_gera_filhos()
    {

        // resultados para cada solução. Quanto maior, maior a chance de ser selecionada.
        vector<double> resultados;
        vector<double> chances;
        double media = 0;
        int tamanho = this->solutions.size();
        Funcoes funcoes;

        for (int i3 = 0; i3 < 10; i3++)
        {

            for (int i = 0; i < tamanho; i++)
            {
                double a;
                a = funcoes.get_total(this->solutions[i].solucao, solutions[i].instance.arr_Pair);
                resultados.push_back(a);
            }

            // gerar valores para cada solução baseado em seu resultado, para serem usados no sorteio dos pais e filhos.

            // primeiro calculamos a média dos resultados e o menor valor entre os resultados

            double menor = resultados[0];

            for (int i = 0; i < tamanho; i++)
            {
                // salvamos o menor valor
                if (resultados[i] < menor)
                {
                    menor = resultados[i];
                }

                // calculamos a media
                media += resultados[i];
            }

            media = media / tamanho;

            for (int i = 0; i < tamanho; i++)
            {
                double a;
                a = resultados[i] - menor + 100;
                // a = a*a;
                chances.push_back(a);
            }
            /*
                        //testando os resultados
                        for(int i=0;i<tamanho;i++){
                            cout<<"resultado para a solução "<<i<<endl;
                            cout<<resultados[i]<<endl;
                            cout<<"chance da solução "<<i<<" ser sorteada: "<<endl;
                            cout<<chances[i]<<endl;
                        }
                        cout<<endl<<endl;
            */

            // agora a partir das chances de cada solução, sorteamos soluções para serem pais e mães de novas soluções
            // depois teremos que DESTRUIR soluções antigas, para que restem sempre 20.
            // Mas isso será feito pela função destruir.
            int sorteado1 = this->sorteador(chances, 20);
            int sorteado2 = this->sorteador(chances, 20);

            // testando
            double maior_chance = 0;
            for (int i = 0; i < tamanho; i++)
            {

                if (chances[i] > maior_chance)
                {
                    maior_chance = chances[i];
                }
            }

            Solution pai = this->solutions[sorteado1];
            Solution mae = this->solutions[sorteado2];

            Solution filho = this->gerar_filho(pai, mae);
            this->solutions.push_back(filho);
        }

        // próximo passo: destruir 10 filhos

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

    // faz restarem apenas 20 organismos (salva o melhor também)
    void destruir()
    {

        vector<Resultado_com_indice> resultados;
        Funcoes funcoes;

        int total = this->solutions.size();
        for (int i = 0; i < total; i++)
        {
            double resultado = funcoes.get_total(solutions[i].solucao, this->instance.arr_Pair);

            Resultado_com_indice resultado1;
            resultado1.resultado = resultado;
            resultado1.indice = i;

            resultados.push_back(resultado1);
        }

        sort(resultados.begin(), resultados.end());

        // cout<<"resultados mais ou menos ordenados: "<<endl;
        // for(int i = 0;i < resultados.size();i++){
        //     cout<<resultados[i].resultado<<endl;
        // }
        // cout<<"ordenação fim"<<endl;

        // antes da destruição, salvamos o melhor até o momento
        Resultado_com_indice last = resultados.back();

        double anterior = funcoes.get_total(this->melhor.solucao, instance.arr_Pair);
        double melhor2 = funcoes.get_total(this->solutions[last.indice].solucao, instance.arr_Pair);

        if (melhor2 > anterior)
        {
            this->melhor = this->solutions[last.indice];
        }

        // agora destruímos 10 soluções
        /*

        for(int i = 0;i<10;i++){
            this->solutions[resultados[i].indice].resultado = -1;
        }

        */
        // pra ficar diversificado, não destruímos o quarto nem o quinto
        for (int i = 0; i < 4; i++)
        {
            this->solutions[resultados[i].indice].resultado = -1;
        }

        for (int i = 9; i < 15; i++)
        {
            this->solutions[resultados[i].indice].resultado = -1;
        }

        int i = 0;
        while (this->solutions.size() > 20)
        {

            if (this->solutions[i].resultado == -1)
            {
                this->solutions.erase(this->solutions.begin() + i);
            }
            else
            {
                i++;
            }
        }
    }

    // reproduz organismos, mata organismos, gera mutações, salva melhor até o momento
    void faz_tudo(int vezes)
    {

        for (int i = 0; i < vezes; i++)
        {

            this->seleciona_e_gera_filhos();
            this->destruir();

            // gerar mutação

            // para decidir se gera a mutação ou não
            int sorteio = rand() % 20;

            // caso aconteça a mutação
            if (sorteio == 1)
            {

                cout << "mutação" << endl;
                int e = rand() % 20;
                this->criar_mutacao(e, 8);
                e = rand() % 20;
                this->criar_mutacao(e, 8);
                e = rand() % 20;
                this->criar_mutacao(e, 8);
                e = rand() % 20;
            }
        }
    }

    void imprimir()
    {

        cout << "quantidade de soluções: " << endl;
        cout << this->solutions.size() << endl;

        for (int i = 0; i < this->tamanho_maximo; i++)
        {

            cout << "solução " << i << endl;

            for (int i2 = 0; i2 < this->solutions[i].solucao.size(); i2++)
            {
                cout << "grupo " << i2 << endl;
                solutions[i].solucao[i2].imprimir();
            }
            cout << endl
                 << endl;
        }
    }

    void testar()
    {
        for (int i = 0; i < this->tamanho_maximo; i++)
        {

            cout << "solução " << i << endl;

            for (int i2 = 0; i2 < this->solutions[i].solucao.size(); i2++)
            {
                cout << "grupo " << i2 << endl;
                solutions[i].solucao[i2].teste();
            }
            cout << endl
                 << endl;
        }
    }
};
