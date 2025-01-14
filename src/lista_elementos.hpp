#pragma once

#include <iostream>
#include <vector>

using namespace std;

// Lista que ficará responsável em armazenar valores bool de um elemento.
class Lista_elementos
{
private:
    int quantidade;

public:
    vector<bool> elementos;

    Lista_elementos(int quantidade1)
    {
        for (int i = 0; i < quantidade1; i++)
        {
            this->elementos.push_back(true);
        }
        this->quantidade = quantidade1;
    }

    void remove(int i)
    {
        if (elementos[i] == true)
        {
            elementos[i] = false;
            this->quantidade -= 1;
        }
        else
        {
            cout << "ELEMENTO JÁ FOI REMOVIDO!!" << endl;
            cout << "elemento: " << i << endl;
        }
    }

    int get_tamanho()
    {
        return this->quantidade;
    }
};
