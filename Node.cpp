#include "Node.h"

Node::Node ()
{
    parent = NULL;
    l = NULL;
    r = NULL;
    key = "";
    color = "r";
}


void Node::set_nodo(string value)
{
    parent = NULL;
    l = NULL;
    r = NULL;
    key = value;
    color = "b";
}

void Node::setP(Node* x)
{
    parent = x;
}

void Node::setL(Node* x)
{
    l = x;
}

void Node::setR(Node* x)
{
    r = x;
}

void Node::setK(string value)
{
    key = value;
}

void Node::setC(string colore)
{
    color = colore;
}

string Node::getC()
{
    return color;
}

string Node::getK()
{
    return key;
}

Node *Node::getL()
{
    return l;
}

Node *Node::getP()
{
    return parent;
}

Node *Node::getR()
{
    return r;
}

