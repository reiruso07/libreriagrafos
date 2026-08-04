#include "GRAFOS.HPP"
using namespace std;
template <typename N>
nodo<N>::nodo(int idd,N datoo){
    id=idd;
    dato=datoo;
    sigAdyacente=nullptr;
    sigVertice=nullptr;
}
template <typename M>
grafo<M>::grafo(){
    nodoP=nullptr;
}
template <typename M>
nodo<M>* grafo<M>::buscarvertice(int id) {
    nodo* act=nodoP;
    while(act!=nullptr){
        if (act->id==id){
            return act;
        }
        act=act->sigVertice;
    }
    return nullptr;
}
template <typename M>
void grafo<M>:: agregarvertice(int id,M dato){
  if(buscarvertice(id)!=nullptr){
    return;
  }  
  nodo* nuevovertice=new nodo(id);
  nuevovertice->sigVertice=nodoP;
  nodoP=nuevovertice;
}
template <typename M>
void grafo<M>::agregarartistas(int origen,int destino){
    nodo* vOrigen=buscarvertice(origen);
    nodo* vDestino=buscarvertice(destino);
    if(vOrigen==nullptr){
        agregarvertice(origen);
        vOrigen=buscarvertice(destino);
    }
    if(vDestino==nullptr){
        agregarvertice(destino);
        vDestino=buscarvertice(destino);
    }
    nodo* conexion1=new nodo(destino);
    conexion1->sigAdyacente=vOrigen->sigAdyacente;
    vOrigen->sigAdyacente=conexion1;
    nodo* conexion2=new nodo(origen);
    conexion2->sigAdyacente=vDestino->sigAdyacente;
    vDestino->sigAdyacente=conexion2;
}
template <typename N>
void grafo<N>:: imprimirgrafo()const{
    nodo* vact=nodoP;
    while(vact!=nullptr){
        cout<<"Vertice "<<vact->id<<":";
        nodo* act=vact->sigAdyacente;
        while (act!=nullptr)
        {
            cout<<" -> "<<act->id;
            act=act->sigAdyacente;
        }
        cout<<endl;
        vact=vact->sigAdyacente;
    }
}