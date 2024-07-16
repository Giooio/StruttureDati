#include <iostream>
#include <fstream>
using namespace std;

#include "liste.h"
#include "parola.h"
#include "tipo.h"

const char NOMEFILE[]= "inverted";

void leggi_parola(istream &is, char* riga){
    while(is.peek()=='\n')
        is.get();
    is.getline(riga, 80);
}

parola* load(int &num_parole){
    ifstream f(NOMEFILE);

    if(!f){
        cout<<"Errore di apertura del file"<<endl;
    }
    
    int id_doc;
    f>>num_parole;
    parola* p = new parola[num_parole];
    
    for(int i=0; i<num_parole; i++){
        leggi_parola(f, p[i].p);
        f>>p[i].n_doc;
        p[i].l = NULL;
        for(int j=0; j<p[i].n_doc; j++){
            f>>id_doc;
            elem* eTemp = new_elem(id_doc);
            p[i].l = insert_elem(p[i].l, eTemp);
        }  
    }
    return p;
}

void stampa(parola* p, int n){
    cout<<"Numero di parole: "<<n<<endl;
    for(int i=0; i<n; i++){
        cout<<p[i].p<<endl;
        cout<<"Numero di elementi della lista "<<p[i].n_doc<<endl;
        cout<<"Lista: "<<endl;
        while(p[i].l != NULL){
            cout<<head(p[i].l)<<endl;
            p[i].l = tail(p[i].l);
        }
        cout<<endl;
    }
}

void update(parola *&ll, char * fileName){
    
}

int main(){
    int num_parole=0;
    parola* parol = load(num_parole);;

    if( parol != nullptr){
        stampa(parol, num_parole);
    }


    return 0;
}
