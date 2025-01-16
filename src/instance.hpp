#pragma once

#include <iostream>
#include "pair.hpp"

using namespace std;

// Classe que armazenará as instancias do problema
class Instance
{
public:
    int quant_Elem;               // Quantidade de elementos
    int quant_Grup;               // Quantidade de grupos
    string descriptor;            // Descriptor: (ds)
    vector<int> arr_Tam_Min_Grup; // Tamanhos mínimos grupos
    vector<int> arr_Tam_Max_Grup; // Tamanhos máximos grupos
    vector<Pair> arr_Pair;        // Todas as distancias e entre todos os elementos
    ////////////////////////////////////////////////////////////////////

    double media;

    bool igual_Tam_Grupos; // Verifica se os grupos têm o mesmo tamanho

    Instance()
    {
        this->quant_Elem = 0;
        this->quant_Grup = 0;
        this->arr_Tam_Min_Grup = {};
        this->arr_Tam_Max_Grup = {};
        this->arr_Pair = {};
        this->igual_Tam_Grupos = false;

        // cout << "instancia criada" << endl;
    }

    void read_File(const string &fileName)
    {
        // Verifica se o arquivo foi aberto corretamente
        ifstream file(fileName);
        if (!file.is_open())
        {
            cerr << "Erro ao abrir o arquivo: " << fileName << endl;
            return;
        }

        string line;

        // Lê o arquivo e armazena as informações da linha
        getline(file, line);

        // Transforma a string em um stream
        stringstream string_stream(line);

        // Armazena as informações
        string_stream >> this->quant_Elem;
        string_stream >> this->quant_Grup;
        string_stream >> this->descriptor;

        // Armazena as informações dos grupos
        int size_Arr;

        // Armazena tam_Min e tam_Max
        for (int i = 0; i < this->quant_Grup; i++)
        {
            string_stream >> size_Arr;
            this->arr_Tam_Min_Grup.push_back(size_Arr);

            string_stream >> size_Arr;
            this->arr_Tam_Max_Grup.push_back(size_Arr);
        }

        // Armazena as informações das distâncias
        int first_Elem, second_Elem;
        double distance;
        while (getline(file, line))
        {
            stringstream string_stream(line);

            string_stream >> first_Elem;
            string_stream >> second_Elem;
            string_stream >> distance;
            this->arr_Pair.push_back(Pair(first_Elem, second_Elem, distance));
        }
        
        file.close();
        // cout << "Arquivo lido com sucesso!" << endl;

        //calcula a média
        double total = 0;
        
        for(int i =0; i < this->arr_Pair.size();i++){
            total+= this->arr_Pair[i].distance_Element;
        }

        double tamanho = (double)arr_Pair.size();
        this->media = total/tamanho;

        cout<<"média: "<<this->media<<endl<<endl;

    }

    void to_String()
    {
        cout << "Quantidade de elementos: " << quant_Elem << endl;
        cout << "Quantidade de grupos: " << quant_Grup << endl;

        cout << "Array tamanhos minimos de grupos: " << endl;
        for (int tam_Min_Grup : arr_Tam_Min_Grup)
        {
            cout << tam_Min_Grup << " ";
        }
        cout << endl;

        cout << "Array tamanhos maximos de grupos: " << endl;
        for (int tam_Max_Grup : arr_Tam_Max_Grup)
        {
            cout << tam_Max_Grup << " ";
        }
        cout << endl;

        cout << endl << "Array de objetos do tipo Pair: " << endl;
        for (Pair pair : arr_Pair) {
            pair.to_String();  // Chama o método to_String de Pair
            cout << endl;
        }

        if (igual_Tam_Grupos)
        {
            cout << "Grupos com o mesmo tamanho" << endl;
        }
        else
        {
            cout << "Grupos com tamanhos diferentes" << endl;
        }
    }
};
