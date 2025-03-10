#pragma once

#include <iostream>
#include "solution.hpp"

using namespace std;

bool is_in_tabu_list(const Lista_tabu &lista_tabu, const Solution &solution)
{
    bool resultado = false;
    int tamanho = lista_tabu.tamanho;
    for (int i = 0; i < tamanho; i++)
    {

        if (solution.solucao == lista_tabu.tabu_list[i].solucao)
        {
            resultado = true;
            cout << "soluções iguais." << endl;
            break;
        }
    }
    return resultado;
}

// se alternarmos trocaElementos para troca Elementos2 executamos a segunda vizinhança
Solution tabu_search(Instance instance)
{

    Funcoes funcoes;
    Solution solution(instance);

    vector<Grupo> grupos = solution.calcular_resultado5();

    Solution melhor_atual_total = solution;
    double resultado_melhor_solucao_atual_total = funcoes.get_total(solution.solucao, instance.arr_Pair);
    double auxiliar = 0;

    Lista_tabu lista_tabu(20);

    // fazemos como na primeira melhora, percorrendo os vizinhos e salvando o melhor
    // porém não salvamos o melhor caso ele esteja na lista tabu
    // quando achamos o melhor atualizamos a lista tabu, substituindo a
    // solução mais antiga pela solução anterior

    for (int i = 0; i < 13; i++)
    {

        // para guardar a melhor solução até o momento
        auxiliar = funcoes.get_total(solution.solucao, instance.arr_Pair);
        if (auxiliar > resultado_melhor_solucao_atual_total)
        {
            resultado_melhor_solucao_atual_total = auxiliar;
            melhor_atual_total = solution;
        }

        /*
        get_todos_vizinhos();

        int index = tem_maior_vizinho();
        */
        int index = -1;

        Funcoes funcoes;
        Solution vizinho_atual;
        Solution vizinho_melhor;

        vector<Solution> vizinhos2;

        // o resultado inicial é -1, para que algum vizinho seja sempre escolhido
        double resultado_atual = -1;
        double resultado_melhor = resultado_atual;

        vector<Grupo> solucao_atual = solution.solucao;

        // fazer para todos os pares de grupos
        for (int i = 0; i < solucao_atual.size() - 1; i++)
        {
            for (int i2 = i + 1; i2 < solucao_atual.size(); i2++)
            {
                // cout<<i<<", "<<i2 <<endl;
                // para cada par de grupos nós trocamos o primeiro elemento
                // de um grupo com o primeiro elemento de outro
                // e adicionamos o resultado no array de vizinhos
                funcoes.trocaElementos2(solucao_atual[i], solucao_atual[i2]);

                // adicionamos o vector de grupos com os elementos trocados no vizinho
                Solution solucao1;
                solucao1.instance = instance;
                vizinhos2.push_back(solucao1);
                vizinhos2.back().solucao = solucao_atual;

                // adiciona ao vizinho um ponteiro para a solução de onde ele veio
                vizinhos2.back().vizinhos = {};
                vizinhos2.back().vizinhos.push_back(solution);

                // restauramos a solução atual
                funcoes.trocaElementos2(solucao_atual[i], solucao_atual[i2]);

                // mantemos apenas o vizinho melhor e o atual
                vizinho_atual = vizinhos2.back();

                // removemos o vizinho da lista de vizinhos para não gastar memória
                vizinhos2.pop_back();

                resultado_atual = funcoes.get_total(vizinho_atual.solucao, instance.arr_Pair);

                if (resultado_atual > resultado_melhor && (not is_in_tabu_list(lista_tabu, vizinho_atual)))
                {
                    resultado_melhor = resultado_atual;
                    vizinho_melhor = vizinho_atual;
                    index = 0;
                }
            }
        }

        solution.vizinhos.push_back(vizinho_melhor);

        // a solução atual passa a ser o melhor vizinho, mesmo que a solução atual seja melhor.
        solution = solution.vizinhos.back();
    }

    return melhor_atual_total;
}

class Lista_tabu
{

public:
    Solution *tabu_list;
    int last;
    int tamanho;

    Lista_tabu(int tamanho1)
    {
        this->tamanho = tamanho1;
        this->tabu_list = new Solution[this->tamanho];
        last = -1;
    }

    ~Lista_tabu()
    {
        delete[] this->tabu_list;
    }

    void add(Solution solution)
    {

        // primeiro elemento adicionado na lista
        if (this->last == -1)
        {
            this->last = 0;
            this->tabu_list[0] = solution;
            cout << this->tabu_list[0].solucao[0].elementos.size();
        }
        else
        {
            if (this->last == this->tamanho - 1)
            {
                this->tabu_list[0] = solution;
                this->last = 0;
            }
            else
            {
                this->tabu_list[last + 1] = solution;
                this->last++;
            }
        }
    }
};