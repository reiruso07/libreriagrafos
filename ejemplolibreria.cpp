#include <iostream>
#include "GRAFOS.HPP"
using namespace std;

int main (){
    grafo<int>* grafito = new grafo<int>();

    grafito->agregarvertice(1,1);
    grafito->agregarvertice(2,2);
    grafito->agregarvertice(3,3);
    grafito->agregarvertice(4,4);

    grafito->agregarartistas(1,2,10);
    grafito->agregarartistas(2,3,20);
    grafito->agregarartistas(3,4,30);
    grafito->agregarartistas(1,4,40);

    cout<<"--- Grafo completo ---"<<endl;
    grafito->imprimirgrafo();

    cout<<"--- Consultas ---"<<endl;
    cout<<"Numero de vertices: "<<grafito->numerovertices()<<endl;
    cout<<"Existe vertice 3: "<<grafito->existevertice(3)<<endl;
    cout<<"Existe arista 1-2: "<<grafito->existearista(1,2)<<endl;
    cout<<"Grado del vertice 1: "<<grafito->gradovertice(1)<<endl;

    cout<<"--- Recorridos ---"<<endl;
    grafito->recorridoDFS(1);
    grafito->recorridoBFS(1);

    cout<<"--- Eliminaciones ---"<<endl;
    grafito->eliminararista(1,2);
    grafito->imprimirgrafo();

    grafito->eliminarvertice(3);
    grafito->imprimirgrafo();

    delete grafito;
    return 0;
}
