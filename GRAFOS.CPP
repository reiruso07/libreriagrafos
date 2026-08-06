#include "GRAFOS.HPP"
#include <iostream>
using namespace std;
template <typename N>
nodo<N>::nodo(int idd,N datoo){
    id=idd;
    dato=datoo;
    sigAdyacente=nullptr;
    sigVertice=nullptr;
    visitado=false;
}
template <typename M>
grafo<M>::grafo(){
    nodoP=nullptr;
}
template <typename M> // busca un vertice en el grafo por id y devuelve el puntero al nodo, si no encuentra el vertice da nullptr
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
template <typename M> // agrega un nuevo vertice al grafo, si no existe no hace nada
void grafo<M>:: agregarvertice(int id,M dato){
  if(buscarvertice(id)!=nullptr){
    return;
  }  
  nodo<M>* nuevovertice=new nodo(id,dato);
  nuevovertice->sigVertice=nodoP;
  nodoP=nuevovertice;
}
template <typename M> // agrega una arista al grafo entre 2 vertices, si uno de los vertices no existe lanza nullptr, si existe pues la agrega a la lista  de ambos vertices, creando un nuevo nodo para cada conexion.
void grafo<M>::agregarartistas(int origen,int destino,M dato){
    nodo<M>* vOrigen=buscarvertice(origen);
    nodo<M>* vDestino=buscarvertice(destino);
    if(vOrigen==nullptr){
        agregarvertice(origen,dato);
        vOrigen=buscarvertice(origen);
    }
    if(vDestino==nullptr){
        agregarvertice(destino,dato);
        vDestino=buscarvertice(destino);
    }
    nodo<M>* conexion1=new nodo(destino,dato);
    conexion1->sigAdyacente=vOrigen->sigAdyacente;
    vOrigen->sigAdyacente=conexion1;
    nodo<M>* conexion2=new nodo(origen,dato);
    conexion2->sigAdyacente=vDestino->sigAdyacente;
    vDestino->sigAdyacente=conexion2;
}
template <typename N> // imprime el grafo mostrando vertices y vertices adyacentes, si no hay vertices pues nada no imprime nada
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

template <typename M> // verifica si existe un vertice en el grafo, si existe suelta true, sino false
bool grafo<M>::existevertice(int id){
    return buscarvertice(id)!=nullptr;
}

template <typename M>
bool grafo<M>::existearista(int origen,int destino){
    nodo<M>* vOrigen=buscarvertice(origen);
    if(vOrigen==nullptr){
        return false;
    }
    nodo<M>* act=vOrigen->sigAdyacente;
    while(act!=nullptr){
        if(act->id==destino){
            return true;
        }
        act=act->sigAdyacente;
    }
    return false;
}

template <typename M> // devuelve el grado de un vertice, osea la cantidad de vertices adyecentes que tiene, si no existe el vertice lanza -1
int grafo<M>::gradovertice(int id){
    nodo<M>* vertice=buscarvertice(id);
    if(vertice==nullptr){
        return -1;
    }
    int grado=0;
    nodo<M>* act=vertice->sigAdyacente;
    while(act!=nullptr){
        grado++;
        act=act->sigAdyacente;
    }
    return grado;
}

template <typename M> // muestra el numero de vertices en el grafo, si no hay manda 0 y ya
int grafo<M>::numerovertices(){
    int contador=0;
    nodo<M>* act=nodoP;
    while(act!=nullptr){
        contador++;
        act=act->sigVertice;
    }
    return contador;
}

template <typename M> // elimina una arista , si uno de los vertices no existe no hace nada, si existe elimina la arista de la lista de ambos vertices y libera la memoria del nodo de la arista
void grafo<M>::eliminararista(int origen,int destino){
    nodo<M>* vOrigen=buscarvertice(origen);
    nodo<M>* vDestino=buscarvertice(destino);
    if(vOrigen==nullptr||vDestino==nullptr){
        return;
    }
    nodo<M>* act=vOrigen->sigAdyacente;
    nodo<M>* ant=nullptr;
    while(act!=nullptr){
        if(act->id==destino){
            if(ant==nullptr){
                vOrigen->sigAdyacente=act->sigAdyacente;
            }else{
                ant->sigAdyacente=act->sigAdyacente;
            }
            delete act;
            break;
        }
        ant=act;
        act=act->sigAdyacente;
    }
    act=vDestino->sigAdyacente;
    ant=nullptr;
    while(act!=nullptr){
        if(act->id==origen){
            if(ant==nullptr){
                vDestino->sigAdyacente=act->sigAdyacente;
            }else{
                ant->sigAdyacente=act->sigAdyacente;
            }
            delete act;
            break;
        }
        ant=act;
        act=act->sigAdyacente;
    }
}

template <typename M>
void grafo<M>::eliminarvertice(int id){ // Elimina un vertice y todas sus aristas asociadas. Primero elimina todas las aristas que apuntan a este vertice desde otros vertices, luego elimina todas las aristas que salen de este vertice y finalmente elimina el vertice en si.
    nodo<M>* vertice=buscarvertice(id);
    if(vertice==nullptr){
        return;
    }
    nodo<M>* actVertice=nodoP; // Elimina todas las aristas que apuntan a este vertice desde otros vertices
    while(actVertice!=nullptr){
        if(actVertice->id!=id){
            eliminararista(actVertice->id,id);
        }
        actVertice=actVertice->sigVertice;
    }
    nodo<M>* actAdy=vertice->sigAdyacente;
    while(actAdy!=nullptr){
        nodo<M>* temp=actAdy;
        actAdy=actAdy->sigAdyacente;
        delete temp;
    }
    nodo<M>* act=nodoP; // Elimina el vertice en si
    nodo<M>* ant=nullptr;
    while(act!=nullptr){
        if(act->id==id){
            if(ant==nullptr){
                nodoP=act->sigVertice;
            }else{
                ant->sigVertice=act->sigVertice;
            }
            delete act;
            break;
        }
        ant=act;
        act=act->sigVertice;
    }
}

template <typename M>  // reinicia el estado de visitado de los vertices del grafo y lo vuelve falso,
void grafo<M>::reiniciarvisitados(){
    nodo<M>* act=nodoP;
    while(act!=nullptr){
        act->visitado=false;
        act=act->sigVertice;
    }
}

template <typename M> // funcion auxiliar que revisa la lista de adyacencia de un vertice y llama recursivamente a si misma para cada vertice adyacente que no haya sido visitado.
void grafo<M>::dfsauxiliar(nodo<M>* vertice){
    vertice->visitado=true;
    cout<<vertice->id<<" ";
    nodo<M>* act=vertice->sigAdyacente;
    while(act!=nullptr){
        nodo<M>* verticeAdyacente=buscarvertice(act->id);
        if(verticeAdyacente!=nullptr && !verticeAdyacente->visitado){
            dfsauxiliar(verticeAdyacente);
        }
        act=act->sigAdyacente;
    }
}

template <typename M> // funcion que realiza un recorrido en profundidad (DFS) a partir de un vertice dado. Primero busca el vertice de inicio, si no existe, imprime un mensaje y retorna. Luego reinicia los visitados y llama a la funcion auxiliar dfsauxiliar para realizar el recorrido.
void grafo<M>::recorridoDFS(int idInicio){
    nodo<M>* inicio=buscarvertice(idInicio);
    if(inicio==nullptr){
        cout<<"El vertice "<<idInicio<<" no existe en el grafo."<<endl;
        return;
    }
    reiniciarvisitados();
    cout<<"Recorrido DFS desde el vertice "<<idInicio<<": ";
    dfsauxiliar(inicio);
    cout<<endl;
}


template <typename M> // funcion que realiza un recorrido en anchura (BFS) a partir de un vertice dado. Primero busca el vertice de inicio, si no existe, imprime un mensaje y retorna. Luego reinicia los visitados y utiliza una cola para almacenar los vertices a visitar. Mientras la cola no este vacia, se saca un vertice de la cola, se marca como visitado y se agregan sus vertices adyacentes no visitados a la cola.
void grafo<M>::recorridoBFS(int idInicio){
    nodo<M>* inicio=buscarvertice(idInicio);
    if(inicio==nullptr){
        cout<<"El vertice "<<idInicio<<" no existe en el grafo."<<endl;
        return;
    }
    reiniciarvisitados();
    int totalVertices=numerovertices();
    int* cola=new int[totalVertices];
    int frente=0;
    int final=0;
    inicio->visitado=true;
    cola[final]=inicio->id;
    final++;
    cout<<"Recorrido BFS desde el vertice "<<idInicio<<": ";
    while(frente<final){
        int idActual=cola[frente];
        frente++;
        cout<<idActual<<" ";
        nodo<M>* verticeActual=buscarvertice(idActual);
        nodo<M>* act=verticeActual->sigAdyacente;
        while(act!=nullptr){
            nodo<M>* verticeAdyacente=buscarvertice(act->id);
            if(verticeAdyacente!=nullptr && !verticeAdyacente->visitado){
                verticeAdyacente->visitado=true;
                cola[final]=verticeAdyacente->id;
                final++;
            }
            act=act->sigAdyacente;
        }
    }
    cout<<endl;
    delete[] cola;
}

template<typename M> // borrador de grafos, elimina todos los vertices y aristas del grafo. Primero elimina todas las aristas de cada vertice y luego elimina cada vertice.
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