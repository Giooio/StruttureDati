#include <iostream>

using namespace std; 

#include "tipo.h"
#include "liste.h"

void pesca(lista& l){
    tipo_inf carta_pescata;

    cout<<"Inserisci il seme della nuova carta: ";
    cin>>carta_pescata.seme;
    cout<<" e anche il valore: ";
    cin>>carta_pescata.valore;

    elem* temp = new_elem(carta_pescata);
    l = ord_insert_elem(l, temp);
}

void stampa(lista l){
    elem* p = l;
    while(p != NULL){
        print(p->inf);
        p = p->pun;
    } 
    cout<<endl;
}

carta* scala(lista carte, int& lunghezza){
    int cont=1;
    carta* c;
    while (carte->pun != NULL){
        if(carte->inf.seme == (carte->pun)->inf.seme){
            if(carte->inf.valore+1 == (carte->pun)->inf.valore){
                if(cont==1){
                    c = &carte->inf;
                }
                cont++;
            }
        }else{
            if(cont >= 3){
                lunghezza = cont;
                return c;
            }
            cont = 1; 
        }
        carte = carte->pun;
    }

    if(cont >= 3){
        lunghezza = cont;
        return c;
    }

return NULL;          
}

int main(){
    lista mazzo_giocatore1 = NULL;
    lista mazzo_giocatore2 = NULL;
    int num_carte_da_pescare;

    cout<<"Inserisci il numero di carte da pescare per giocatore: ";
    cin>>num_carte_da_pescare;

    for(int i=0; i<num_carte_da_pescare; i++){
        cout<<"Carta giocatore 1: ";
        pesca(mazzo_giocatore1);
        cout<<"Carta giocatore 2: ";
        pesca(mazzo_giocatore2);
    }

    cout<<"Stampo i due mazzi "<<endl;
    cout<<"Giocatore 1: ";
    stampa(mazzo_giocatore1);
    cout<<"Giocatore 2: ";
    stampa(mazzo_giocatore2);

    int l;
    carta* carta_a_caso = scala(mazzo_giocatore1, l);
    cout<<carta_a_caso->seme<<" "<<carta_a_caso->valore<<endl;
}