#include <iostream>
#include <cstring>
using namespace std;

//Your code here

int fromDigitToNumber(int a, int b, int c, int d)
{
    return 1000*a + 100*b + 10*c + d;
}


class Tickets{
    protected:
    int id[12];
    char event[100];
    float basePrice;
    static float discount;

    public:
    Tickets(int id[], char *event, float basePrice)
    {
        for(int i = 0; i<12;i++)
        {
            this->id[i] = id[i];

        }
            strcpy(this->event, event);
            this->basePrice = basePrice;
    }

    friend ostream& operator<<(ostream &o, Tickets &t){
        for(int i = 0; i<12; i++)
        {
            o<<t.id[i];
            if(i==11){
                o<<"-";
            }
        }
        o<<t.event<<"-"<<t.presmetajCena();

        return o;
    }

    bool falsifikat(int from, int to)
    {
        if(fromDigitToNumber(id[8],id[9], id[10],id[11]) <= to && fromDigitToNumber(id[8],id[9], id[10],id[11]) >= from){
            return 0;
        }
        return 1;
    }

    virtual float presmetajCena() = 0;

   static void changeDiscount(int d) {
       Tickets::discount = d;
   }
};

float Tickets::discount = 0;

class Online : public Tickets{
    private:
    bool premium;

    public:
    Online(int id[], char *event, float basePrice, bool premium) : Tickets(id, event, basePrice){
        this->premium = premium;
    }

    float presmetajCena(){
        if(premium)
            return basePrice - basePrice*0.15 - basePrice * discount /100;

        return this->basePrice - basePrice * discount /100;
    }
};

class Offline : public Tickets{
    private:
    bool reservation;

    public:
     Offline(int id[], char *event, float basePrice, bool reservation) : Tickets(id, event, basePrice){
        this->reservation = reservation;
    }

    float presmetajCena(){
        if(reservation)
        return this->basePrice + this->basePrice * 0.1 - this->basePrice*discount/100;

        return this->basePrice - this->basePrice*discount/100;
    }
};


 void vkupenPrihod(Tickets ** t, int n, int from, int to){
     float total = 0;
     for(int i = 0; i<n; i++)
     {
         if(!t[i]->falsifikat(from, to)){
             total+=t[i]->presmetajCena();
         }
     }
     cout<<total;
 }
// DO NOT CHANGE THE MAIN FUNCTION, EXCEPT THE MARKED PART FOR HANDLING WITH THE EXCEPTION
int main() {
	int testCase;
	cin >> testCase;
	int ID[12];
	char nastan[100];
	float price;
	bool premium;
	bool rezervacija;
	int od, doo;

	if (testCase == 1) {
		cout << "===== TESTING CONSTRUCTORS ======" << endl;
		for (int i = 0; i < 12; i++)
			cin >> ID[i];
		cin >> nastan;
		cin >> price;
		cin >> premium;
		Online o1(ID, nastan, price, premium);
		cout << o1 << endl;
		for (int i = 0; i < 12; i++)
			cin >> ID[i];
		cin >> nastan;
		cin >> price;
		cin >> rezervacija;
		Offline o2(ID, nastan, price, rezervacija);
		cout << o2 << endl;

	}
	else if (testCase == 2) {
		cout << "===== TESTING METHOD vkupenPrihod()  ======" << endl;
		int n;
		cin >> n;
		Tickets** t = new Tickets*[n];
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 12; j++)
				cin >> ID[j];
			cin >> nastan;
			cin >> price;

			if (i % 2 == 0){
				cin >> premium;
				t[i] = new Online(ID, nastan, price, premium);
			}
			else {
				cin >> rezervacija;
				t[i] = new Offline(ID, nastan, price, rezervacija);
			}
		}
		cin >> od;
		cin >> doo;
		vkupenPrihod(t, n, od, doo);
		for (int i = 0; i < n; ++i) {
			delete t[i];
		}
		delete[] t;
	}
	else if (testCase == 3) {
		cout << "===== TESTING DISCOUNT STATIC ======" << endl;
		int n;
		cin >> n;
		//cout<<n<<endl;
		Tickets** t = new Tickets*[n];
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 12; ++j)
				cin >> ID[j];
			cin >> nastan;
			//cout<<nastan<<endl;
			cin >> price;
			//cout<<price<<endl;
			if (i % 2 == 0){
				cin >> premium;
				t[i] = new Online(ID, nastan, price, premium);
			}
			else {
				cin >> rezervacija;
				//cout<<rezervacija<<endl;
				t[i] = new Offline(ID, nastan, price, rezervacija);
			}
		}
		int d;
		cin >> d;
		Tickets::changeDiscount(d);
		for (int i = 0; i < n; ++i)
			cout << *t[i] << endl;

	}
}

