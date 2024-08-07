#include <iostream>
#include <string>
#include <list>

using namespace std;

class Vocabolario
{
	public:

	Vocabolario (){};

	virtual bool Inserimento(string) = 0;
	virtual bool Ricerca(string) = 0;
	virtual bool Cancellazione(string) = 0;


	~Vocabolario (){};


};
