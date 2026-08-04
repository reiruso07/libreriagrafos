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
#endif