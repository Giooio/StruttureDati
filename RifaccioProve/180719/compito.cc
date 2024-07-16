#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#include "grafi.h"
#include "coda.h"
#include "node.h"

const char NOMEFILE1[] = "graph";
const char NOMEFILE2[] = "node";

void leggi_riga(istream &is, char* riga){
    while(is.peek() == '\n')
        is.get();
    is.getline(riga, 81);
}

void leggi_grafo(graph& grafo){
    fstream g(NOMEFILE1);
    int src, dest;

    if(!g)
        cout<<"Apertura del file fallita!"<<endl;

    g>>grafo.dim;
    grafo = new_graph(grafo.dim);

    while(g>>src>>dest){
        add_arc(grafo, src, dest, 1);
    }
    g.close();
}

void leggi_nodi(graph &gr, node*& nod){
    fstream n(NOMEFILE2);

    int i = 0;
    while(n){
        leggi_riga(n, nod[i].cont);
        n>>nod[i].tipo;
        i++;
    }
}

void stampa(graph grafo){
    cout<<"Numero dei nodi: "<<grafo.dim<<endl;
    for(int i=1; i<= grafo.dim; ++i){
        adj_list lista_adiacenza = get_adjlist(grafo, i);
        while(lista_adiacenza != NULL){
            cout<<i<<" "<<get_adjnode(lista_adiacenza)<<endl;
            lista_adiacenza = get_nextadj(lista_adiacenza);
        }
    }
}

void stampa_con_nodi(graph grafo, node* nodo){
    for(int i=1; i<= grafo.dim; ++i){
        adj_list lista_adiacenza = get_adjlist(grafo, i);

        while(lista_adiacenza != NULL){
            int adjNextNode = get_adjnode(lista_adiacenza);
            cout<<nodo[i-1].cont;

            if(nodo[i-1].tipo == 'U' && nodo[adjNextNode-1].tipo == 'U'){
                cout<<" FOLLOW ";
            } else if(nodo[i-1].tipo == 'U' && nodo[adjNextNode-1].tipo == 'T'){
                cout<<" LIKE ";
            }  else if(nodo[i-1].tipo == 'T' && nodo[adjNextNode-1].tipo == 'U'){
                cout<<" OWNER ";
            } 

            cout<<nodo[adjNextNode-1].cont<<endl;

            lista_adiacenza = get_nextadj(lista_adiacenza);
        }
    }
}

int cerca_tweet(graph gr, node* nod, char* c){
    for(int i=1; i<= gr.dim; ++i){
        adj_list lista_adiacenza = get_adjlist(gr, i);

        while(lista_adiacenza != NULL){
            int adjNextNode = get_adjnode(lista_adiacenza);
            

            if(nod[i-1].tipo == 'T' && nod[adjNextNode-1].tipo == 'U'){
                if(strcmp(nod[i-1].cont,c) == 0){
                    return adjNextNode-1;
                }
            }

            lista_adiacenza = get_nextadj(lista_adiacenza);
        }
    }
    return -1;
}

int* totalLike(graph gr, node* nod){
    int* V = new int[gr.dim];
    int user_iterator;

    for(int i=0; i<gr.dim;i++){
        V[i]=0;
    }

    for(int i=1; i<= gr.dim; ++i){
        adj_list lista_adiacenza = get_adjlist(gr, i);

        while(lista_adiacenza != NULL){
            int adjNextNode = get_adjnode(lista_adiacenza);
            
            if(nod[i-1].tipo == 'U' && nod[adjNextNode-1].tipo == 'T'){
                user_iterator = cerca_tweet(gr,nod,nod[adjNextNode-1].cont);
                V[user_iterator]++;
            } 

            lista_adiacenza = get_nextadj(lista_adiacenza);
        }
    }
    return V;
}

void stampa_most_influential(int* V, int dim, node* n){
    int max=0;
    for(int i=0; i<dim; i++){
        if(V[i]>max){
            max = V[i];
        }
    }

    for(int i=0; i<dim; i++){
        if(V[i]==max){
            cout<<n[i].cont<<endl;
        }
    }
    
}

int main(){
    graph gg;

    leggi_grafo(gg);
    stampa(gg);
    cout<<endl;
    
    node* nn = new node[gg.dim];
    
    leggi_nodi(gg, nn);
    stampa_con_nodi(gg, nn);
    cout<<endl;

    cout<<"Most influential users: "<<endl;
    int* V = totalLike(gg, nn);
    stampa_most_influential(V, gg.dim, nn);

    return 0;
}