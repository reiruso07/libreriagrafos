#ifndef GRAFOS_HPP
#define GRAFOS_HPP
 template<typename N>
 class nodo{
    public:
    int id;
    N dato;
    nodo<N>* sigVertice;
    nodo<N>* sigAdyacente;
    nodo(int idd,N datoo)
 };
 template<typename M>
 class grafo{
    public:
        nodo<M>* nodoP;
        grafo();
        nodo<M>* buscarvertice(int id);
        void agregarvertice(int id,M dato);
        void agregarartistas(int origen,int destino);
        void imprimirgrafo()const;
        ~grafo();
 };
#endif