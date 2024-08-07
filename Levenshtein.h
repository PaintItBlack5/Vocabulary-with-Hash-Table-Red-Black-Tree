#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;


class LEVENSHTEIN
{
    private:
        string prima;
        string seconda;
        int *matrice;
    public:
        LEVENSHTEIN();

        void set_string(string s, string t);
        void crea_matrice();
        string get_prima();
        string get_seconda();
        int prima_size();
        int seconda_size();
        int get_from_tabella(int ,int);
        char car_prima(int);
        char car_seconda(int);

        ~LEVENSHTEIN();
};
// Costruttore.
LEVENSHTEIN::LEVENSHTEIN()
{
    prima=seconda="";
    matrice=NULL;
}

// Restituisce la prima stringa.
string LEVENSHTEIN::get_prima()
{
    return prima;
}

// Restituisce la seconda stringa.
string LEVENSHTEIN::get_seconda()
{
    return seconda;
}

// Restituisce la lunghezza della prima stringa.
int LEVENSHTEIN::prima_size()
{
    return prima.size();
}


// Restituisce la lunghezza della seconda stringa.
int LEVENSHTEIN::seconda_size()
{
    return seconda.size();
}

// Restituisce un elemento della tabella. L'accesso è per riga.
int LEVENSHTEIN::get_from_tabella(int i,int j)
{
    return *(matrice+i* (seconda.size()+1) +j);
}

// Restituisce un singolo carattere della prima stringa.
char LEVENSHTEIN::car_prima(int i)
{
    return prima[i];
}


// Restituisce un singolo carattere della seconda stringa.
char LEVENSHTEIN::car_seconda(int j)
{
    return seconda[j];
}


// Per inizializzare le stringhe.
void LEVENSHTEIN::set_string(string s, string t)
{
    prima=s; seconda=t;
    cout<<endl<<"Trasformazione di '"<<prima<<"' in '"<<seconda<<"':"<<endl;
}


// Allocazione dinamica della matrice.
void LEVENSHTEIN :: crea_matrice()
{
    int n = prima.size()+1;
    int m = seconda.size()+1;
    matrice = new int[(n)*(m)];
    if(matrice == NULL)
    {   cout << "Impossibile allocare memoria"<<endl;  exit(0); }

    for(int i=0;i<n;i++)
        *(matrice+i*m+0)=i;

    for(int j=0;j<m;j++)
        *(matrice+0*n+j)=j;

    for(int i=1;i<n;i++)
    {
        for(int j=1;j<m;j++)
        {
            int diff=0;
            if(prima[i-1] != seconda[j-1])
                diff=1;

            //cerca valore minimo
            vector<int> temp;
            temp.push_back(*(matrice+(i-1)*m+j)+1);           //cancellazione
            temp.push_back(*(matrice+i*m+(j-1))+1);           //inserimento
            temp.push_back(*(matrice+(i-1)*m+(j-1))+diff);    //sostituzione
            *(matrice+i*m+j)= *min_element(temp.begin(),temp.end());
            temp.clear();
        }
    }
}


// Distruttore.
LEVENSHTEIN::~LEVENSHTEIN()
{
    prima.clear();
    seconda.clear();
    delete []matrice;
}


class DISTANZA : public LEVENSHTEIN
{
    private:
        int operazioni;

    public:
        DISTANZA();

        int getOperazioni();
        void calcolo_distanza();

        ~DISTANZA() {};
};
// Costruttore di default.
DISTANZA::DISTANZA()
{
    operazioni=0;
}

int DISTANZA::getOperazioni(){
return operazioni;
}




// Partendo dalla soluzione finale(elemento in ultima riga, ultima colonna), ripercorre a
// ritroso, le celle con valore minimo, e in base al percorso intrapreso, risale all' operazione effettuata.
void DISTANZA :: calcolo_distanza()
{
    int sp=prima_size(), ss=seconda_size();
    int passo=1;
    if((operazioni=get_from_tabella(sp,ss))==0)
        cout<<"Non ci sono operazioni da effettuare!";
    else{
    cout<<"Operazioni effettuate: "<<operazioni;
    while(sp >= 0 && ss >= 0)   //ricostruzione del percorso a ritroso
    {
            //Caso 1: bordo superiore
        if(sp==0)
        {
            if( get_from_tabella(sp,ss) > get_from_tabella(sp,ss-1)) //inserimento
            {
                cout<<endl<<passo++<<") Ho inserito '"<<car_seconda(--ss)<<"'";
            }
            else
                ss--;
        }

        //Caso 2: bordo sinistro
        if(ss==0)
        {
            if(get_from_tabella(sp,ss) > get_from_tabella(sp-1,ss)) //cancellazione
            {
                cout<<endl<<passo++<<") Ho cancellato '"<<car_prima(--sp)<<"'";
            }
            else
                sp--;
        }


        //Caso 3: Resto della matrice
        if(sp!=0 && ss!=0 )
        {
            if(get_from_tabella(sp,ss)>(get_from_tabella(sp-1,ss-1)) && (get_from_tabella(sp-1,ss-1)<=get_from_tabella(sp,ss-1)) && (get_from_tabella(sp-1,ss-1)<=get_from_tabella(sp-1,ss))) //sostituzione
            {
                cout<<endl<<passo++<<") Ho sostituito '"<<car_prima(--sp)<<"' con '"<<car_seconda(--ss)<<"'";
            }
            else if(get_from_tabella(sp,ss)>get_from_tabella(sp,ss-1)) //inserimento
                {
                    cout<<endl<<passo++<<") Ho inserito '"<<car_seconda(--ss)<<"'";
                }
                else if ( get_from_tabella(sp,ss) >get_from_tabella(sp-1,ss)) //cancellazione
                    {
                        cout<<endl<<passo++<<") Ho cancellato '"<<car_prima(--sp)<<"'";
                    }
                    else
                    {
                        sp--; ss--;
                    }
                }
            }

    }
    cout<<endl;
}



