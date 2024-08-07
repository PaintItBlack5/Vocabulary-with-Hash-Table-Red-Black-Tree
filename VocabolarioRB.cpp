#include "VocabolarioRB.h"

VocabolarioRB::VocabolarioRB()
{
	sentinel = new Node;
	sentinel->set_nodo("");
	root = sentinel;
};


bool VocabolarioRB::Inserimento(string parola)
{
    Node *x,*y;
	Node *z = new Node;
    z->set_nodo(parola);
	y = sentinel;
    x = root;

    while (x != sentinel)
	{
        y = x;
        if (z->getK() < x->getK())
            x = x->getL();
        else
            x = x->getR();
    }

    z->setP(y);
    if (y == sentinel)
        root = z;
    else
	{
        if (z->getK() < y->getK())
            y->setL(z);
        else
            y->setR(z);
    }
    z->setL(sentinel);
    z->setR(sentinel);
    z->setC("r");
    VocabolarioRB::insertFixup(z);
    return true;
}

void VocabolarioRB::insertFixup(Node *z)
{
    Node *y;

    while (z->getP()->getC() == "r")
    {
        if (z->getP() == z->getP()->getP()->getL())
        {
            y = z->getP()->getP()->getR();
            if (y->getC()=="r")
            {
                z->getP()->setC("b");
                y->setC("b");
                z->getP()->getP()->setC("r");
                z = z->getP()->getP();
            }
            else
            {
                if(z == z->getP()->getR())
                {
                    z = z->getP();
                    VocabolarioRB::lRotation(z);
                }
                z->getP()->setC("b");
                z->getP()->getP()->setC("r");
                VocabolarioRB::rRotation(z->getP()->getP());
            }
        }
        else
        {
            y = z->getP()->getP()->getP();
            if (y->getC() == "r")
            {
                z->getP()->setC("b");
                y->setC("b");
                z->getP()->getP()->setC("r");
                z = z->getP()->getP();
            }
            else
            {
                if (z == z->getP()->getL())
                {
                    z = z->getP();
                    VocabolarioRB::rRotation(z);
                }
                z->getP()->setC("b");
                z->getP()->getP()->setC("r");
                VocabolarioRB::lRotation(z->getP()->getP());
            }
        }
    }
    root->setC("b");
}

bool VocabolarioRB::Cancellazione(string parola)
{
	if (!Ricerca(parola))
	    return false;

    Node *x,*y,*z;
	z = searchNodo(root, parola);

    if (z->getL() == sentinel || z->getR() == sentinel)
        y = z;
    else
        y = VocabolarioRB::successore(z->getK());

    if (y->getL() != sentinel)
        x = y->getL();
    else
        x = y->getR();

    x->setP(y->getP());

    if (y->getP() == sentinel)
        root = x;
    else
	{
        if (y == y->getP()->getL())
            y->getP()->setL(x);
        else
            y->getP()->setR(x);
    }

    if (y != z)
        z->setK(y->getK());

    if (y->getC() == "b")
        VocabolarioRB::deleteFixup(x);

    if (y->getK() == z->getK())
        delete y;
    else
        delete z;

    return true;
}

void VocabolarioRB::deleteFixup (Node *z)
{
    Node *y;

    while (z != root && z->getC() == "b")
    {
        if (z == z->getP()->getL())
        {
            y = z->getP()->getR();
            if (y->getC() == "r")
            {
                y->setC("b");
                y->getP()->setC("r");
                VocabolarioRB::lRotation(z->getP());
                y = z->getP()->getR();
            }
            if (y->getL()->getC() == "b" && y->getR()->getC() == "b")
            {
                y->setC("r");
                z = z->getP();
            }
            else
            {
                if (y->getC() == "b")
                {
                    y->getL()->setC("b");
                    y->setC("r");
                    VocabolarioRB::rRotation(y);
                    y = z->getP()->getR();
                }
                y->setC(z->getP()->getC());
                z->getP()->setC("b");
                y->getR()->setC("b");
                VocabolarioRB::lRotation(z->getP());
                z = root;
            }
        }
        else
            {
            y = z->getP()->getL();
            if (y->getC() == "r")
            {
                y->setC("b");
                y->getP()->setC("r");
                VocabolarioRB::rRotation(z->getP());
                y = z->getP()->getL();
            }
            if (y->getR()->getC() == "b" && y->getL()->getC() == "b")
            {
                y->setC("r");
                z = z->getP();
            }
            else
            {
                if(y->getC() == "b")
                {
                    y->getR()->setC("b");
                    y->setC("r");
                    VocabolarioRB::lRotation(y);
                    y = z->getP()->getL();
                }
                y->setC(z->getP()->getC());
                z->getP()->setC("b");
                y->getL()->setC("b");
                VocabolarioRB::rRotation(z->getP());
                z = root;
            }
        }
    }
    z->setC("b");
}

bool VocabolarioRB::Ricerca(string parola)
{
    Node *p = root;
    int trovato = 0;
    while (p != NULL && trovato == 0)
    {
        if (p->getK() == parola)
            trovato = 1;
        if (trovato == 0)
            {
                if (p->getK() < parola)
                    p = p->getR();
                else
                    p = p->getL();
            }
    }
    if (trovato == 0)
        return false;
    else
        return true;
}

Node *VocabolarioRB::searchNodo (Node *punt, string k)
{
    while (punt != sentinel && k != punt->getK())
	{
        if (k < punt->getK())
            punt = punt->getL();
        else
            punt = punt->getR();
    }

    if (punt == sentinel)
        return NULL;
    return punt;
}



list <string> VocabolarioRB::Levenshtein(string parola)
{
	int distMin = 100;// Utilizzo un valore relativamente alto.
    saveNodi(root);
	for (p= this->nodi.begin(); p!= this->nodi.end(); p++) // Scorre gli elementi con la stessa chiave.
	    {

            DISTANZA* stringhe = new DISTANZA;
	    	string s = *p;
	    	stringhe->set_string(s, parola);
	    	stringhe->crea_matrice();  //alloca memoria e inizializza prima riga e colonna
            stringhe->calcolo_distanza();

           if (stringhe->getOperazioni() < distMin)
            {
                distMin = stringhe->getOperazioni();
                Parole_simili.clear();
                Parole_simili.push_back(s);
			}
			else if (stringhe->getOperazioni()== distMin)
			    Parole_simili.push_back(s);
	    }
	    cout << "\nDistanza di Editing minore: " << distMin << "" << endl;
	    nodi.clear();
	return Parole_simili;
    }


void VocabolarioRB::saveNodi(Node *nodo)
{
	if (nodo != sentinel)
	{
		saveNodi(nodo->getL());
		nodi.push_back(nodo->getK());
		saveNodi(nodo->getR());
	}
}

Node *VocabolarioRB::getMax (Node *x)
{
    while (x->getR() != sentinel)
	{
        x = x->getR();
    }
    return x;
}

Node *VocabolarioRB::getMin (Node *x)
{
    while(x->getL() != sentinel)
	{
        x=x->getL();
    }
    return x;
}

void VocabolarioRB::lRotation (Node *z)
{
    Node *y;
    y = z->getR();
    z->setR(y->getL());

    if (y->getL() != sentinel)
        y->getL()->setP(z);

    y->setP(z->getP());

    if (y->getP() == sentinel)
        root = y;
    else
	{
        if (z == y->getP()->getL())
            z->getP()->setL(y);
        else
            z->getP()->setR(y);
    }

    y->setL(z);
    z->setP(y);
}

void VocabolarioRB::rRotation (Node *z)
{
    Node *y;
    y = z->getL();
    z->setL(y->getR());

    if (y->getR() != sentinel)
        y->getR()->setP(z);

    y->setP(z->getP());

    if (y->getP() == sentinel)
        root=y;
    else
	{
        if (z == y->getP()->getR())
            z->getP()->setR(y);
        else
            z->getP()->setL(y);
    }

    y->setR(z);
    z->setP(y);
}

Node *VocabolarioRB::successore (string k)
{
    Node *z,*y;
    z = root;
    y = sentinel;

    while (z != sentinel && z->getK() != k)
	{
        if (z->getK() < k)
            z=z->getR();
        else if (z->getK() > k)
        {
            y = z;
            z = z->getL();
        }
    }
    if (z != sentinel && z->getR() != sentinel)
        return VocabolarioRB::getMin (z->getR());
    else
        return y;
}
