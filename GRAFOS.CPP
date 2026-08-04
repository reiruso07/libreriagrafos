#include "GRAFOS.HPP"
#include <iostream>
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
    nodo<M>* act=nodoP;
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
  nodo<M>* nuevovertice=new nodo(id,dato);
  nuevovertice->sigVertice=nodoP;
  nodoP=nuevovertice;
}
template <typename M>
void grafo<M>::agregarartistas(int origen,int destino,M dato){
    nodo<M>* vOrigen=buscarvertice(origen);
    nodo<M>* vDestino=buscarvertice(destino);
    if(vOrigen==nullptr){
        agregarvertice(origen);
        vOrigen=buscarvertice(destino);
    }
    if(vDestino==nullptr){
        agregarvertice(destino);
        vDestino=buscarvertice(destino);
    }
    nodo<M>* conexion1=new nodo(destino,dato);
    conexion1->sigAdyacente=vOrigen->sigAdyacente;
    vOrigen->sigAdyacente=conexion1;
    nodo<M>* conexion2=new nodo(origen,dato);
    conexion2->sigAdyacente=vDestino->sigAdyacente;
    vDestino->sigAdyacente=conexion2;
}
template <typename N>
void grafo<N>:: imprimirgrafo()const{
    nodo<N>* vact=nodoP;
    while(vact!=nullptr){
        cout<<"Vertice "<<vact->id<<":";
        nodo<N>* act=vact->sigAdyacente;
        while (act!=nullptr)
        {
            cout<<" -> "<<act->id;
            act=act->sigAdyacente;
        }
        cout<<endl;
        vact=vact->sigAdyacente;
    }
}
template<typename M>
grafo<M>::~grafo(){
    nodo<M>* vact=nodoP;
    while(vact!=nullptr){
        nodo<M>* act=vact->sigAdyacente;
        while (act!=nullptr){
            nodo<M>* tempArista=act;
            act=act->sigAdyacente;
            delete tempArista;
        }
        nodo<M>* tempvertice=vact;
        vact=vact->sigAdyacente;
        delete tempvertice;
        
    }
}