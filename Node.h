#include <iostream>
#include <string>


using namespace std;

class Node
{
    public:

    Node ();

    void set_nodo (string value);
    void setP (Node * x);
    void setL (Node * x);
    void setR(Node * x);
    void setK(string k);
    void setC (string colore);
    Node *getP ();
    Node *getL ();
    Node *getR ();
    string getK ();
    string getC ();

    ~Node (){};

    private:

	Node *parent;
    Node *l;
    Node *r;
    string key;
    string color;
};
