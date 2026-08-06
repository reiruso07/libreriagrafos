LIBRERIA DE GRAFOS (GRAFOS.HPP / GRAFOS.CPP)
=============================================

Libreria generica de grafos no dirigidos implementada con listas
enlazadas de punteros. Esta pensada como template, asi que el
tipo de dato que guarda cada vertice/arista (M o N) lo decide quien
usa la libreria.


ESTRUCTURA INTERNA
-------------------

La libreria usa una sola clase de nodo (nodo<N>) para dos cosas
distintas, igual que en el diseno original:

- Nodo-vertice: representa un vertice del grafo. Esta enlazado con los
  demas vertices a traves de sigVertice, formando la lista principal
  grafo::nodoP -> sigVertice -> sigVertice -> ... -> nullptr.

- Nodo-adyacencia: representa una arista. Cada vertice tiene su propia
  lista de adyacencia, enlazada por sigAdyacente, con un nodo por cada
  vecino al que esta conectado.

Por eso cada nodo tiene DOS punteros "siguiente" (sigVertice y
sigAdyacente) segun el rol que este cumpliendo en cada momento.

Como el grafo es no dirigido, agregarartistas(origen, destino, dato)
crea DOS nodos de adyacencia: uno en la lista de origen apuntando a
destino, y otro en la lista de destino apuntando a origen. Esto es
importante para entender eliminararista y eliminarvertice: para dejar
el grafo consistente hay que tocar las dos listas, no solo una.


BUGS QUE TENIA EL CODIGO Y SE CORRIGIERON
----------------------------------------

Antes de agregar funciones nuevas, revisamos el codigo y encontramos 3 errores al ir compilando

1) agregarartistas
   Cuando el vertice "origen" no existia todavia, el codigo lo creaba
   pero despues volvia a buscar "destino" en vez de "origen":

       agregarvertice(origen,dato);
       vOrigen=buscarvertice(destino); // debia ser buscarvertice(origen)

   Esto dejaba vOrigen apuntando al vertice equivocado y podia generar
   aristas mal armadas.

2) imprimirgrafo
   Al final del ciclo externo avanzaba con vact=vact->sigAdyacente en
   vez de vact=vact->sigVertice. Como sigAdyacente pertenece a la
   lista de ARISTAS, no a la de VERTICES, el recorrido se metia dentro
   de la lista de adyacencia del primer vertice y el resto de los
   vertices del grafo nunca se llegaban a imprimir (con 3 o mas
   vertices el bug se nota claramente: se imprime el primero y despues
   cualquier cosa, segun los ids de sus vecinos).

3) Destructor ~grafo()
   Tenia el mismo error que imprimirgrafo (vact=vact->sigAdyacente en
   vez de vact=vact->sigVertice), pero aca es mas grave: en ese punto
   la lista de adyacencia de vact ya se habia liberado en el ciclo
   interno, asi que vact->sigAdyacente apuntaba a memoria ya liberada.
   Esto provoca use-after-free, que es comportamiento indefinido, crasheaba casi de una vez al intentar borrar 
   un grafo con 3 o mas vertices

Los tres se corrigieron cambiando sigAdyacente por sigVertice en el
lugar correcto (y en el punto 1, buscando origen en vez de destino).
El comportamiento visible para quien ya usaba la libreria no cambia en
nada, salvo que ahora imprimirgrafo y el destructor funcionan bien con
cualquier cantidad de vertices.

FUNCIONES EXTRAS:


Consultas:

  bool existevertice(int id)
    Muestra si un vertice ya fue agregado. Es literalmente
    buscarvertice(id) != nullptr, para no tener que comparar contra
    nullptr en el codigo que usa la libreria.

  bool existearista(int origen, int destino)
    Recorre la lista de adyacentes de "origen" (la misma que recorre
    imprimirgrafo para imprimir las flechas ->) buscando un nodo con
    id == destino.

  int gradovertice(int id)
    Cuenta cuantos nodos hay en la lista de adyacentes de un vertice,
    es decir, con cuantos vecinos esta conectado. Devuelve -1 si el
    vertice no existe.

  int numerovertices()
    Cuenta los vertices recorriendo nodoP con sigVertice, igual que lo
    hace imprimirgrafo por fuera para el ciclo externo.

Eliminacion:

  void eliminararista(int origen, int destino)
    Como cada arista esta representada por DOS nodos de adyacencia
    (uno en cada vertice), esta funcion busca y borra el nodo destino
    dentro de la lista de origen, y el nodo origen dentro de la lista
    de destino. Si alguno de los dos vertices no existe, no hace nada.

  void eliminarvertice(int id)
    Primero recorre todos los demas vertices del grafo y les llama
    eliminararista(otroId, id), para que ningun vecino se quede con
    una arista "colgada" apuntando a un vertice que ya no va a
    existir. Despues libera lo que haya quedado en la propia lista de
    adyacencia del vertice (normalmente ya queda vacia por el paso
    anterior; es solo una red de seguridad) y por ultimo lo
    desconecta de la lista principal nodoP y libera su memoria.

Recorridos (DFS y BFS):

No se agrego ninguna libreria nueva de C++ para implementarlos (nada
de <queue>, <stack> ni <vector>), tal como se pidio. Ambos recorridos
usan el campo visitado de nodo para no procesar dos veces el mismo
vertice ni entrar en un ciclo infinito si el grafo tiene ciclos.

  void reiniciarvisitados() [privada]
    Pone visitado=false en todos los vertices. Se llama al empezar
    cada recorrido nuevo, para que las marcas de un recorrido anterior
    no interfieran con el siguiente.

  void dfsauxiliar(nodo<M>* vertice) [privada]
    Recorrido en profundidad de toda la vida, implementado con
    recursion (no hace falta ninguna estructura auxiliar propia: la
    pila de llamadas de C++ hace ese trabajo). Marca el vertice como
    visitado, lo imprime, y se llama a si misma con cada vecino no
    visitado.

  void recorridoDFS(int idInicio)
    Funcion publica que valida que idInicio exista, reinicia las
    marcas de visitado y delega el trabajo en dfsauxiliar.

  void recorridoBFS(int idInicio)
    Recorrido en anchura. Como no se puede usar <queue>, la cola se
    armo "a mano" con un arreglo dinamico (new int[totalVertices]) del
    tamano de numerovertices() -eso ya alcanza porque cada vertice
    entra a la cola una sola vez- y dos indices, frente y final, que
    avanzan como en cualquier cola FIFO. Se libera con delete[] al
    terminar.


EJEMPLO DE USO
----------------


muestra el uso de cada funcion tanto general como de consultas

    grafito->numerovertices();
    grafito->existevertice(3);
    grafito->existearista(1,2);
    grafito->gradovertice(1);

    grafito->recorridoDFS(1);
    grafito->recorridoBFS(1);

    grafito->eliminararista(1,2);
    grafito->eliminarvertice(3);

Salida real de ese ejemplo (compilado con g++ -std=c++17):

    --- Grafo completo ---
    Vertice 4: -> 1 -> 3
    Vertice 3: -> 4 -> 2
    Vertice 2: -> 3 -> 1
    Vertice 1: -> 4 -> 2
    --- Consultas ---
    Numero de vertices: 4
    Existe vertice 3: 1
    Existe arista 1-2: 1
    Grado del vertice 1: 2
    --- Recorridos ---
    Recorrido DFS desde el vertice 1: 1 4 3 2
    Recorrido BFS desde el vertice 1: 1 4 2 3
    --- Eliminaciones ---
    Vertice 4: -> 1 -> 3
    Vertice 3: -> 4 -> 2
    Vertice 2: -> 3
    Vertice 1: -> 4
    Vertice 4: -> 1
    Vertice 2:
    Vertice 1: -> 4


NOTA SOBRE COMPILACION
-------------------------

ARCHIVOS
----------

- GRAFOS.HPP / GRAFOS.CPP: la libreria
- ejemplolibreria.cpp: el ejemplo
