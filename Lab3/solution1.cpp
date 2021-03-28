#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;


int myMin(int a, int b)
{
    if(a>b)
        return a;
    return b;
}

class Potpisuvac
{
	//vasiot kod ovde
	char name[20];
	char surname[20];
	char securityN[14];

	public:
	   //default constructor and with parameters
	    Potpisuvac ( char *name = "", char *surname = "",char *securityN = ""){
	        strcpy(this->securityN, securityN);
	         strcpy(this->name, name);
	         strcpy(this->surname, surname);


	       // cout<<"Potpisuvac Constructor: "<<this->name<<" "<<this->surname<<" "<<this->securityN<<endl;
	       //cout<<"Potpisuvac constructor"<<"this->name "<<this->name<<" this->surname "<<this->surname<<" this->securityN "<<this->securityN<<endl;
	    }

	   //copy constructor
	   Potpisuvac (const Potpisuvac &other){
	       //strncpy(this->name, other.name, 19); this->name[19] = '\0';
	       //strncpy(this->surname, other.surname, 19); this->surname[19] = '\0';
	       //strncpy(this->securityN, other.securityN, 13); this->securityN[13] = '\0';

	       //cout<<"Before starting"<<this->name<<" "<<this->surname<<" "<<this->securityN<<" "<<other.name<<" "<<other.surname<<" "<<other.securityN<<endl;
	         strcpy(this->name, other.name);
	         strcpy(this->surname, other.surname);
	         strcpy(this->securityN, other.securityN);


	       //cout<<"Copy Constructor"<<this->name<<" "<<this->surname<<" "<<this->securityN<<endl;
	   }

	   ~Potpisuvac(){
	       //cout<<"Destroying Potpisuvac"<<endl;

	   }

	   char* getSecurityN(){
	       return this->securityN;
	   }
};
class Dogovor
{
    //vasiot kod ovde
    int agree_id;
    char agree_category[50];
    Potpisuvac potpisuvaci[3];

    public:
        Dogovor(const int agree_id, const char *agree_category, const Potpisuvac p[])
        {
            this->agree_id = agree_id;
            strcpy(this->agree_category, agree_category);
            this->potpisuvaci[0] = Potpisuvac(p[0]);
            this->potpisuvaci[1] = Potpisuvac(p[1]);
            this->potpisuvaci[2] = Potpisuvac(p[2]);

        // cout<<"Dogovor constructor: "<<this->agree_id<<" "<<this->agree_category<<" "<<this->potpisuvaci[0].getSecurityN()<<this->potpisuvaci[1].getSecurityN()<<this->potpisuvaci[2].getSecurityN()<<endl;
        }

        ~Dogovor(){
            //cout<<"Destroying Dogovor"<<endl;

        };

        bool proverka(){
            // cout<<"in proverka";
            // char *securityN1, *securityN2, *securityN3;
            // strcpy(securityN1, this->potpisuvaci[0].getSecurityN());
            // strcpy(securityN2, this->potpisuvaci[1].getSecurityN());
            // strcpy(securityN3, this->potpisuvaci[2].getSecurityN());

            // cout<<"in proverka: "<<securityN1<<" "<<securityN2<<" "<<securityN3<<endl;

             if(strcmp(this->potpisuvaci[0].getSecurityN(), this->potpisuvaci[1].getSecurityN()) == 0
            || strcmp(this->potpisuvaci[0].getSecurityN(),  this->potpisuvaci[2].getSecurityN()) == 0
            || strcmp(this->potpisuvaci[1].getSecurityN(),  this->potpisuvaci[2].getSecurityN()) == 0)
                return true;
            return false;

        }

};


int main()
{
    char embg[14], ime[20], prezime[20], kategorija[20];
    int broj, n;
    cin >> n;
    for(int i = 0; i < n; i++){
    	cin >> embg >> ime >> prezime;
    // cin.getline(embg, )
    	Potpisuvac p1(ime, prezime, embg);
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p2(ime, prezime, embg);
    	cin >> embg >> ime >> prezime;
    	Potpisuvac p3(ime, prezime, embg);
    	cin >> broj >> kategorija;
    	Potpisuvac p[3];
    	p[0] =p1; p[1] = p2; p[2] = p3;
    	Dogovor d(broj, kategorija, p);
        cout << "Dogovor " << broj << ":" << endl;
    	if(d.proverka() == true)
    	    cout << "Postojat potpishuvaci so ist EMBG" << endl;
    	else
    	    cout << "Ne postojat potpishuvaci so ist EMBG" << endl;
    }
    return 0;
}
