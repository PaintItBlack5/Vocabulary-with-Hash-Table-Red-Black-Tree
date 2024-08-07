#include <iostream>
#include <string>
#include <list>
#include "levenshtein.h"

using namespace std;

class hashVocabolario: public Vocabolario
{
	public:

	hashVocabolario (){};

	bool Inserimento (string);
	void Visualizzazione();
	bool Ricerca (string);
	bool Cancellazione (string);

	list <string> Levenshtein(string);

	~hashVocabolario (){};

	private:
	    static const int M = 1000;

	list <string> hashTable[M];
	list <string> Parole_simili;
	list <string>::iterator p;

	//hash concatenato
	int a,b,h;
	int hash(char*);
	int x;



};

int hashVocabolario::hash(char *v)
{
	a = 31415; b = 27183;

	for(h=0; *v !='\0'; v++, a= a*b % (M-1))
		h = (a*h + *v) %M;

	return (h<0) ? (h+M) : h;
}


bool hashVocabolario::Inserimento(string parola)
{
	x = this->hash((char *)parola.c_str());
	this->hashTable[x].push_back(parola);
	return true;
}

void hashVocabolario::Visualizzazione()
{
int i=0;
    for(int j=0; j<M;j++){

        if(!hashTable[j].empty()){
            for(p= hashTable[j].begin(); p!=hashTable[j].end();p++){
                cout<<"Elemento\t"<<j<<"::\t"<<i<<"\t->\t"<<*p<<endl;
                i++;}
        }
    }
i=0;
}

bool hashVocabolario::Ricerca(string parola)
{
	x = this->hash((char *)parola.c_str());
	p = this->hashTable[x].begin();
	for (p = this->hashTable[x].begin(); p != this->hashTable[x].end(); p++)
	{
		if(*p == parola)
			return true;
	}
	return false;
}

bool hashVocabolario::Cancellazione(string parola)
{
	x = this->hash((char *)parola.c_str());
	this->p = this->hashTable[x].begin();
	for (p = this->hashTable[x].begin(); p != this->hashTable[x].end(); p++)
	{
		if(*p == parola)
		{
			p = hashTable[x].erase(p);
			return true;
		}
	}
	return false;
}

list <string> hashVocabolario::Levenshtein(string parola)
{
	int distmin = 100;//utilizzo un valore relativamente alto

	for (int j=0; j<M; j++) // Scorre tabella hash
	{
	    p= this->hashTable[j].begin();
	    for (p= this->hashTable[j].begin(); p!= this->hashTable[j].end(); p++) // Scorre gli elementi con la stessa chiave
	    {

	        DISTANZA* stringhe = new DISTANZA;
	    	string s = *p;
	    	stringhe->set_string(s, parola);
	    	stringhe->crea_matrice();  //alloca memoria e inizializza prima riga e colonna
            stringhe->calcolo_distanza();

            if (stringhe->getOperazioni() < distmin)
            {
                distmin = stringhe->getOperazioni();
                Parole_simili.clear();
                Parole_simili.push_back(s);
			}
			else if (stringhe->getOperazioni()== distmin)
			    Parole_simili.push_back(s);
	    }
    }
    cout << "\nLa Distanza di Editing minore e' " << distmin << "." << endl;
	return Parole_simili;
}
