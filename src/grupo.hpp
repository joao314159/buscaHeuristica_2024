#pragma once

#include <iostream>
#include <vector>

using namespace std;

// Classe que armazenará os grupos das instâncias do problema.
class Grupo
{
public:
    int i;

    double tam_minimo;
    double tam_maximo;

    vector<int> elementos = {};

    vector<int> pontos = {};

    void imprimir()
    {

        cout << "tamanho mínimo: " << tam_minimo << endl;
        cout << "tamanho máximo: " << tam_maximo << endl;

        for (int i = 0; i < elementos.size(); i++)
        {
            cout << "elemento " << i << " :" << elementos[i] << endl;
        }
        cout << endl;
    }

    int get_quantidade_elementos()
    {
        return this->elementos.size();
    }
};
