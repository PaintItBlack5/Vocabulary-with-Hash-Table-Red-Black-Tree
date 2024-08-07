#include "Node.cpp"
#include "Levenshtein.h"
#include "ClasseAstrattaVocabolario.h"



class VocabolarioRB : public Vocabolario
{
    public:

    VocabolarioRB();

    bool Inserimento(string);
	bool Cancellazione(string);
	bool Ricerca(string);
	list <string> Levenshtein (string);

    ~VocabolarioRB(){};

    private:

    Node* root;
    Node* sentinel;
    Node* successore (string);
	Node* getMin (Node*);
	Node* getMax (Node*);
	Node* searchNodo (Node*, string);
	void saveNodi (Node*);
    void insertFixup (Node*);
    void deleteFixup (Node*);
    void lRotation (Node*);
    void rRotation (Node*);

    list <string> nodi;
    list <string>::iterator p;
    list <string> Parole_simili;



};
