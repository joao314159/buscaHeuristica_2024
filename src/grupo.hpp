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

    void teste(){
        double tamanho1 = (double)this->tam_minimo;
        double tamanho2 = (double)this->tam_maximo;
        if(elementos.size() < tamanho1 || elementos.size()>tamanho2){
            cout<<endl<<endl;
            cout<<"Erro! A quantidade de elementos é "<<elementos.size()<<" e o tamanho máximo é "<<this->tam_maximo<<" e o tamanho mínimo é "<<this->tam_minimo<<endl;
            cout<<endl<<endl;
        }
    }

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

    bool operator==(const Grupo& other) const {
        
        bool resultado = true;

        if(&other == NULL){
            resultado = false;
        }

        if(this->elementos.size() != other.elementos.size()){
            resultado = false;
        }
        else{
            for(int i = 0;i<this->elementos.size(); i++){
                if(this->elementos[i] != other.elementos[i]){
                    resultado=false;
                }
            }
        }
        
        return resultado;
    }

};
