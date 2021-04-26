//Vasiot kod ovde

#include<iostream>
#include<cstring>
using namespace std;

class Ekipa{
protected:
    char name[15];
    int defeats;
    int wins;

public:
    Ekipa(char *name = "name", int wins = 0, int defeats = 0)
    {
        strcpy(this->name, name);
        this->defeats = defeats;
        this->wins = wins;
    }

    void pecati()
    {
        cout<<"Ime: "<<this->name<<" Pobedi: "<<this->wins<<" Porazi: "<<this->defeats;
    }


};


class FudbalskaEkipa : public Ekipa{

    int redCards;
    int yellowCards;
    int remis;

public:
    FudbalskaEkipa(char *name = "name", int wins = 0, int defeats = 0, int redCards = 0, int yellowCards = 0, int remis = 0) : Ekipa(name, wins, defeats) {
    this->redCards = redCards;
    this->yellowCards = yellowCards;
    this->remis = remis;
    }

    int calcPoints()
    {
        return 3 * this->wins + this->remis;
    }

    void pecati()
    {
        Ekipa temp(*this);
        temp.pecati();
        cout<<" Nereseni: "<<this->remis<<" Poeni: "<<calcPoints();
    }


};

int main(){
	char ime[15];
	int pob,por,ck,zk,ner;
	cin>>ime>>pob>>por>>ck>>zk>>ner;
	FudbalskaEkipa f1(ime,pob,por,ck,zk,ner);
	f1.pecati();
	return 0;
}
