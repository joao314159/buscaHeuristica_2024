#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

#include "instance.hpp"
#include "pair.hpp"
#include "solution.hpp"

using namespace std;



// Imprime os resultados.
void resultados(Instance instance)
{
    Funcoes funcoes;
    Solution solution(instance);

    //vector<Grupo> grupos1 = solution.calcular_resultado();
    //vector<Grupo> grupos3 = solution.calcular_resultado2();
    //vector<Grupo> grupos2 = solution.calcular_resultado3();
    //vector<Grupo> grupos4 = solution.calcular_resultado4();
    vector<Grupo> grupos5 = solution.calcular_resultado5();

    //double resultado1 = funcoes.get_total(grupos1, instance.arr_Pair);
    //double resultado2 = funcoes.get_total(grupos2, instance.arr_Pair);
    //double resultado3 = funcoes.get_total(grupos3, instance.arr_Pair);
    //double resultado4 = funcoes.get_total(grupos4, instance.arr_Pair);
    double resultado5 = funcoes.get_total(grupos5, instance.arr_Pair);

/*
    cout<<"resultado 1: ";
    cout << std::setprecision (15) << resultado1 <<endl;
    
    cout<<"resultado 2: ";
    cout << std::setprecision (15) << resultado2 <<endl;

    cout<<"resultado 3: ";
    cout << std::setprecision (15) << resultado3 <<endl;

    cout<<"resultado 4: ";
    cout << std::setprecision (15) << resultado4 <<endl;

    cout<<"resultado 5: ";

    */

    cout<<"resultado antes da busca local: "<<endl;
    cout<< std::setprecision (15) << resultado5 <<endl;

    cout<<"trocando elementos de dois grupos: "<<endl;
    cout<<"resultado: "<<endl;

    //funcoes.trocaElementos(solution.solucao[0], solution.solucao[1],0,0);
    //resultado5 = funcoes.get_total(solution.solucao, instance.arr_Pair);
    
    solution.get_todos_vizinhos();

    //pegar o vizinho que leva ao melhor resultado entre os vizinhos
    int i = solution.maior_vizinho();
    cout<<"índice: "<<i<<endl<<endl;
    
    resultado5 = funcoes.get_total(solution.vizinhos[i].solucao,instance.arr_Pair);


    cout<< std::setprecision (15) << resultado5 <<endl;

    cout<<endl<<endl;
    cout<<endl<<endl;
    cout<<endl<<endl;
    cout<<endl<<endl;


}

int main()
{
    setlocale(LC_ALL, "Portuguese");


    vector<string> fileNames = {
    "instances/Geo/Geo_n010_ss_01.txt",
    "instances/Geo/Geo_n012_ss_01.txt" ,
    "instances/Geo/Geo_n030_ss_01.txt" ,
    "instances/Geo/Geo_n060_ss_01.txt" ,
    "instances/Geo/Geo_n120_ss_01.txt" ,
    "instances/Geo/Geo_n240_ss_01.txt" ,
    "instances/Geo/Geo_n480_ss_01.txt" ,

    /*
    "instances/Geo/Geo_n960_ss_01.txt",

    "instances/RanInt/RanInt_n010_ss_01.txt",
    "instances/RanInt/RanInt_n012_ss_01.txt", 
    "instances/RanInt/RanInt_n030_ss_01.txt",
    "instances/RanInt/RanInt_n060_ss_01.txt",
    "instances/RanInt/RanInt_n120_ss_01.txt",
    "instances/RanInt/RanInt_n240_ss_01.txt",
    "instances/RanInt/RanInt_n480_ss_01.txt",
    "instances/RanInt/RanInt_n960_ss_01.txt",

    "instances/RanReal/RanReal_n010_ss_01.txt",
    "instances/RanReal/RanReal_n012_ss_01.txt", 
    "instances/RanReal/RanReal_n030_ss_01.txt",
    "instances/RanReal/RanReal_n060_ss_01.txt",
    "instances/RanReal/RanReal_n120_ss_01.txt",
    "instances/RanReal/RanReal_n240_ss_01.txt",
    "instances/RanReal/RanReal_n480_ss_01.txt",
    "instances/RanReal/RanReal_n960_ss_01.txt", 

    "instances/Geo/Geo_n010_ds_01.txt",
    "instances/Geo/Geo_n012_ds_01.txt",
    "instances/Geo/Geo_n030_ds_01.txt", 
    "instances/Geo/Geo_n060_ds_01.txt",
    "instances/Geo/Geo_n120_ds_01.txt",
    "instances/Geo/Geo_n240_ds_01.txt",
    "instances/Geo/Geo_n480_ds_01.txt",
    "instances/Geo/Geo_n960_ds_01.txt",

    "instances/RanInt/RanInt_n010_ds_01.txt" ,
    "instances/RanInt/RanInt_n012_ds_01.txt" ,
    "instances/RanInt/RanInt_n030_ds_01.txt" ,
    "instances/RanInt/RanInt_n060_ds_01.txt" ,
    "instances/RanInt/RanInt_n120_ds_01.txt" ,
    "instances/RanInt/RanInt_n240_ds_01.txt" ,
    "instances/RanInt/RanInt_n480_ds_01.txt" ,
    "instances/RanInt/RanInt_n960_ds_01.txt",

    "instances/RanReal/RanReal_n010_ds_01.txt" ,
    "instances/RanReal/RanReal_n012_ds_01.txt" ,
    "instances/RanReal/RanReal_n030_ds_01.txt" ,
    "instances/RanReal/RanReal_n060_ds_01.txt",
    "instances/RanReal/RanReal_n120_ds_01.txt" ,
    "instances/RanReal/RanReal_n240_ds_01.txt" ,
    "instances/RanReal/RanReal_n480_ds_01.txt",
    "instances/RanReal/RanReal_n960_ds_01.txt"

    */
    };

    vector<string> resultados_artigo{
"3660.67",
"716.46",
"13776.34",
"45374.32",
"99906.5",
"185 973.83",
"não foi calculado",
"não foi calculado",
"1292.00",
"985.00",
"5324.00",
"18408.00",
"40577.00",
"129877.00",
"não foi calculado",
"não foi calculado",
"1427.85",
"956.43",
"5503.12",
"18164.17",
"42047.6",
"128619.53",
"não foi calculado",
"não foi calculado",
"3864.69",
"807.68",
"14358.40",
"48163.77"
/*
"108971.98",
"190288.26",
"não foi calculado",
"não foi calculado",
"1325.00",
"1059.00",
"5607.00",
"19080.00",
"44589.00",
"137150.00",
"não foi calculado",
"não foi calculado",
"1437.81",
"1050.35",
"5595.16",
"18967.72",
"43420.36",
"133756.40",
"não foi calculado",
"não foi calculado"*/

        /*
        Geo_n010_ss_01.txt 40 12 20 3660.67 3660.67 0 0.64 503
Geo_n012_ss_01.txt 96 16 48 716.46 716.46 0 45.27 701 993
Geo_n030_ss_01.txt 300 35 150 13 776.34 60 354.76 77 1802.55 5 291 729
Geo_n060_ss_01.txt 720 66 360 45 374.32 268 663.1 83 1800.61 661 408
Geo_nl20_ss_01.txt 2400 130 1200 99 906.5 1 044 060.53 90 1800.81 10 389
Geo_n240_ss_01.txt 5760 252 2880 185 973.83 2 280 971.91 92 1811.05 149
Geo_n480_ss_01.txt 19 200 500 9600 — — — — —
Geo_n960_ss_01.txt 46 080 984 23 040 — — — — —
RanInt_n010_ss_01.txt 40 12 20 1292.00 1292.00 0 0.03 225
RanInt_n012_ss_01.txt 96 16 48 985.00 985.00 0 25.51 398 594
RanInt_n030_ss_01.txt 300 35 150 5324.00 17 084.75 69 1802.57 551 470
RanInt_n060_ss_01.txt 720 66 360 18 408.00 83 352.74 78 1800.77 806 515
RanInt_nl20_ss_01.txt 2400 130 1200 40 577.00 355 806.92 89 1800.84 16 140
RanInt_n240_ss_01.txt 5760 252 2880 129 877.00 1 426 655.06 91 1811.47 130
RanInt_n480_ss_01.txt 19 200 500 9600 — — — —
RanInt_n960_ss_01.txt 46 080 984 23 040 — — — —
RanReal_n010_ss_01.txt 40 12 20 1427.85 1427.85 0 0.03 221
RanReal_n012_ss_01.txt 96 16 48 956.43 956.43 0 25.82 398 022
RanReal_n030_ss_01.txt 300 35 150 5503.12 16 982.96 68 1802.63 5 664 732
RanReal_n060_ss_01.txt 720 66 360 18 164.17 82 653.29 78 1800.77 813 249
RanReal_nl20_ss_01.txt 2400 130 1200 42 047.6 352 947.83 88 1800.24 16 368
RanReal_n240_ss_01.txt 5760 252 2880 128 619.53 1 424 593.19 91 1812.2 177
RanReal_n480_ss_01.txt 19 200 500 9600 — — — — —
RanReal_n960_ss_01.txt 46 080 984 23 040 
        */
    };

    // vector<Instance> instances[fileNames.size()];
    Instance instances[fileNames.size()];

    
   
    for (size_t i = 0; i < fileNames.size(); ++i) {
        instances[i].read_File(fileNames[i]);
    }

    /*

    // #pragma parallel for
    for(size_t i = 0; i < fileNames.size(); i++) {
        if(i == 0)
            cout<<"\t\t ### INSTANCIAS CURTAS: ### "<<endl;
        if(i == 5)
            cout << "\n\t\t ### INSTANCIAS PEQUENAS COM GRUPOS COM MESMO TAMANHO: ###" << endl;
        if(i == 10)
            cout<<"\n\t\t ### INSTANCIAS GRANDES: ###"<<endl;
        if(i == 15)
            cout<<"\n\t\t ### INSTANCIAS GRANDES COM GRUPOS COM MESMO TAMANHO: ###"<<endl;
        if(i == 20)
            cout<<"\n\t\t ### INSTANCIAS EXTREMAMENTES GIGANTES: ###"<<endl;
        if(i == 25)
            cout<<"\n\t\t ### INSTANCIAS MAIS CURTAS: ###"<<endl;

        cout << endl;
        resultados(instances[i]);
    }
   
*/


vector<string> fileNames2{

"RanInt_n120_ds_01",
"RanInt_n120_ds_02",
"RanInt_n120_ds_03",
"RanInt_n120_ds_04",  
"RanInt_n120_ds_05", 
"RanInt_n120_ds_06",  
"RanInt_n120_ds_07",  
"RanInt_n120_ds_08", 
"RanInt_n120_ds_09",  
"RanInt_n120_ds_10",  
"RanInt_n240_ds_01",  
"RanInt_n240_ds_02",  
"RanInt_n240_ds_03",  
"RanInt_n240_ds_04",  
"RanInt_n240_ds_05",  
"RanInt_n240_ds_06",  
"RanInt_n240_ds_07", 
"RanInt_n240_ds_08", 
"RanInt_n240_ds_09", 
"RanInt_n240_ds_10"

/*
"RanInt_n480_ds_01",  
"RanInt_n480_ds_02", 
"RanInt_n480_ds_03", 
"RanInt_n480_ds_04",
"RanInt_n480_ds_05", 
"RanInt_n480_ds_06", 
"RanInt_n480_ds_07",  
"RanInt_n480_ds_08",  
"RanInt_n480_ds_09", 
"RanInt_n480_ds_10",  
"RanInt_n960_ds_01",  
"RanInt_n960_ds_02", 
"RanInt_n960_ds_03", 
"RanInt_n960_ds_04",
"RanInt_n960_ds_05", 
"RanInt_n960_ds_06", 
"RanInt_n960_ds_07", 
"RanInt_n960_ds_08", 
"RanInt_n960_ds_09",  
"RanInt_n960_ds_10" */
};

vector<double> resultados2{

51146.00,
51372.00, 
50248.00, 
50436.00,
50008.00, 
49767.00,
50282.00, 
50385.00, 
50451.00, 
50407.00, 
160596.00,
160468.00, 
160400.00, 
162619.00, 
160841.00, 
161334.00, 
160412.00, 
158321.00,
160799.00,
  160299.00
  /*
  390718.00, 
  389327.00,
  389098.00, 
  392628.00, 
  389981.00, 
  390088.00, 
  390181.00,
  391339.00,
  389116.00, 
  394099.00, 
  1244347.00, 
  1242006.00, 
  1242461.00, 
  1243122.00, 
  1241729.00, 
  1239217.00, 
  1242811.00, 
  1239231.00, 
  1240150.00, 
  1242428.00 */
};

/*
  Geo_n010_ss_01.txt
    Geo_n012_ss_01.txt 
    Geo_n030_ss_01.txt 
    Geo_n060_ss_01.txt 
    Geo_nl20_ss_01.txt 
    Geo_n240_ss_01.txt 
    Geo_n480_ss_01.txt 
    Geo_n960_ss_01.txt

    RanInt_n010_ss_01.txt 
    RanInt_n012_ss_01.txt 
    RanInt_n030_ss_01.txt 
    RanInt_n060_ss_01.txt 
    RanInt_nl20_ss_01.txt 
    RanInt_n240_ss_01.txt 
    RanInt_n480_ss_01.txt 
    RanInt_n960_ss_01.txt 

    RanReal_n010_ss_01.txt 
    RanReal_n012_ss_01.txt 
    RanReal_n030_ss_01.txt 
    RanReal_n060_ss_01.txt 
    RanReal_nl20_ss_01.txt 
    RanReal_n240_ss_01.txt
    RanReal_n480_ss_01.txt 
    RanReal_n960_ss_01.txt 

    Geo_n010_ds_01.txt 
    Geo_n012_ds_01.txt 
    Geo_n030_ds_01.txt 
    Geo_n060_ds_01.txt 
    Geo_nl20_ds_01.txt 
    Geo_n240_ds_01.txt 
    Geo_n480_ds_01.txt 
    Geo_n960_ds_01.txt

    RanInt_n010_ds_01.txt 
    RanInt_n012_ds_01.txt 
    RanInt_n030_ds_01.txt 
    RanInt_n060_ds_01.txt 
    RanInt_nl20_ds_01.txt 
    RanInt_n240_ds_01.txt 
    RanInt_n480_ds_01.txt 
    RanInt_n960_ds_01.txt

    RanReal_n010_ds_01.txt 
    RanReal_n012_ds_01.txt 
    RanReal_n030_ds_01.txt 
    RanReal_n060_ds_01.txt
    RanReal_nl20_ds_01.txt 
    RanReal_n240_ds_01.txt 
    RanReal_n480_ds_01.txt 
    RanReal_n960_ds_01.txt

*/

   

    for(size_t i = 0; i < fileNames.size(); i++) {

        cout<<endl;
        cout<<"instância:"<<endl;
        cout<<fileNames[i]<<endl;
        cout << endl;
        cout<<"resultado encontrado pelo algoritmo: "<<endl;
        resultados(instances[i]);
        cout<<"resultado da tabela: "<<endl;
        cout<<resultados_artigo[i]<<endl;
        cout<<endl;

    }

    
   /*
     for(size_t i = 0; i < fileNames.size(); i++) {

        Instance instance;
        instance.read_File(fileNames[i]);
        Solution solucao(instance); 
        double resultado = solucao.limite_superior();

        cout<<endl;
        cout<<"instância:"<<endl;
        cout<<fileNames[i]<<endl;
        cout << endl;
        cout<<"resultado encontrado pelo algoritmo: "<<endl;
        cout<<resultado<<endl;
        cout<<"resultado da tabela: "<<endl;
        cout<<resultados_artigo[i]<<endl;
        cout<<endl;

    }

*/
    
    return 0;
}
