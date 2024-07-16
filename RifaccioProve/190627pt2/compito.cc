#include <iostream>
#include <fstream>
using namespace std;

const char NOMEFILE[]="PI.txt";

#include "liste.h"
#include "tipo.h"
#include "grafo.h"

void leggi_riga(istream &is, char* riga){
    while(is.peek() == '\n')
        is.get();
    is.getline(riga, 21);
}

/**
 * @brief Leggo e aggiungo tutti gli elementi del file PI.txt alla lista
 * 
 * @param pi 
 * @return numero di elementi della lista
 */
int carica(lista& pi){
    tipo_inf corrente;
    int cont = 0;
    ifstream f(NOMEFILE);

    if(!f){
        cout<<"Errore apertura file"<<endl;
    }

    while(f){
        f>>corrente.id;
        leggi_riga(f, corrente.nome);
        f>>corrente.tipo;

        elem* elem_lista = new_elem(corrente);
        pi = ord_insert_elem(pi, elem_lista);
        cont++;
    }

    return cont;
}

/**
 * @brief Funzione che cerca e stampa l'elemento con identificativo in ingresso
 * 
 * @param pi 
 * @param id 
 * @return tipo_inf 
 */
tipo_inf search_pi(lista &pi, int id){
    tipo_inf temp;
    temp.id = id;
    elem* elem_trovato = ord_search(pi, temp);
    cout<<"Elemento trovato: ";
    return elem_trovato->inf;
}


int main(){
    lista lista = NULL;
    int num_elementi = carica(lista);

    int num_id, id_da_cercare;
    cout<<"Inserisci quanti id stai cercando: ";
    cin>>num_id;

    for(int i = 0; i < num_id; i++){
        cout<<"Inserisci id: ";
        cin>>id_da_cercare;
        print(search_pi(lista, id_da_cercare));
    }
    cout<<endl;

    return 0;
}