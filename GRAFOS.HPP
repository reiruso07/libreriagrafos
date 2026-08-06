#ifndef GRAFOS_HPP
#define GRAFOS_HPP 
 template<typename N>
 class nodo{
    public:
    int id;
    N dato;
    nodo<N>* sigVertice;
    nodo<N>* sigAdyacente;
    bool visitado;
    nodo(int idd,N datoo);
 };
 template<typename M>
 class grafo{
    public:
        nodo<M>* nodoP;
        grafo();
        nodo<M>* buscarvertice(int id);
        void agregarvertice(int id,M dato);
        void agregarartistas(int origen,int destino,M dato);
        void imprimirgrafo()const;
        bool existevertice(int id);
        bool existearista(int origen,int destino);
        int gradovertice(int id);
        int numerovertices();
        void eliminararista(int origen,int destino);
        void eliminarvertice(int id);
        void recorridoDFS(int idInicio);
        void recorridoBFS(int idInicio);
        ~grafo();
    private:
        void reiniciarvisitados();
        void dfsauxiliar(nodo<M>* vertice);
 };
 #include "GRAFOS.CPP"
#endif