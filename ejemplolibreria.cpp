#include <iostream>
#include "GRAFOS.HPP"
using namespace std;
int main (){
    grafo<int>* grafito =new grafo<int>();
    grafito->agregarvertice(1,1);
    grafito->agregarvertice(2,2);
    grafito->agregarartistas(1,2,3);
    grafito->imprimirgrafo();

}