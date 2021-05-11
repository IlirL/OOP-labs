
#include <iostream>
#include <cstring>
using namespace std;


// YOUR CODE HERE

// DO NOT CHANGE THE MAIN FUNCTION

class AlcoholicDrink{
    protected:
    char name[100];
    char origin[100];
    float percent;
    float basePrice;
    static int discount;

    public:
    AlcoholicDrink(float percent =  0, char *name = "", char *origin = "", float basePrice = 0){
        this->basePrice = basePrice;
        this->percent = percent;
        strcpy(this->name, name);
        strcpy(this->origin, origin);
    }

   friend ostream& operator<<(ostream &o, AlcoholicDrink &a){
        o<<a.name<<" "<<a.origin<<" "<<a.computePrice();
    }

    bool operator<(AlcoholicDrink &a){
        return computePrice() < a.computePrice();
    }

    virtual float computePrice() = 0;

   static void changeDiscount(int d){
        AlcoholicDrink::discount = d;
    }
    static void total(AlcoholicDrink** ad, int n){
        float total_sum = 0;
        for(int i = 0; i<n; i++)
        {
            total_sum+=ad[i]->computePrice();
        }
        cout<<"Total price: "<<total_sum<<endl;
        cout<<"Total price with discount: "<<total_sum*(1-(discount*1.0/100))<<endl;

    }
};

int AlcoholicDrink::discount = 5;

class Beer : public AlcoholicDrink{
    private:
    bool main_ingredient; //0 for barley and 1 for wheat

    public:
    Beer(float percent =  0, char *name = "", char *origin = "", float basePrice = 0, bool main_ingredient=  0) : AlcoholicDrink(percent, name ,origin, basePrice){
        this->main_ingredient = main_ingredient;
    }

    float computePrice() override{
        float increase_origin = 0;
        float increase_wheat = 0;
        if(strcmp(origin, "Germany") == 0)
        {
            increase_origin = 0.05*basePrice;
        }
        if(main_ingredient == 0)
        {
            increase_wheat = 0.1 * basePrice;
        }

        // basePrice+=increase_wheat + increase_origin;
            return basePrice + increase_wheat + increase_origin;

    }

};

class Wine : public AlcoholicDrink{
    private:
    int year;
    char grape[20];

    public:
    Wine(float percent =  0, char *name = "", char *origin = "", float basePrice = 0, int year = 0, char * grape = "") : AlcoholicDrink(percent, name, origin, basePrice){
        this->year = year;
        strcpy(this->grape, grape);
    }

    float computePrice() override{
         float increase_origin = 0;
        float increase_year = 0;
        if(strcmp(origin, "Italy") == 0)
        {
            increase_origin = 0.05*basePrice;
        }
        if(year < 2005)
        {
            increase_year = 0.15 * basePrice;
        }

        // basePrice+=increase_year + increase_origin;

        return basePrice + increase_year + increase_origin;
    }

};

void lowestPrice(AlcoholicDrink ** ad, int n){

    AlcoholicDrink *temp_ad = ad[0];

    for(int i = 1; i<n; i++)
    {
        // if(temp_ad->computePrice() > ad[i] ->computePrice()){
        if(*ad[i] < *temp_ad ){
            temp_ad = ad[i];
        }
    }

    cout<<*temp_ad;
}


int main() {
    int testCase;
    cin >> testCase;
    float p;
    char name[100];
    char country[100];
    float price;
    bool mainI;
    int year;
    char grape [20];
    if(testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> mainI;
        Beer b(p, name, country, price, mainI);
        cout << b << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> year;
        cin >> grape;
        Wine w(p, name, country, price, year, grape);
        cout << w << endl;

    } else if(testCase == 2) {
        cout << "===== TESTING LOWEST PRICE ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
        	cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;

            if(i % 2 == 1){
                cin >> mainI;
        		ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
            	cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }

        lowestPrice(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    } else if(testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
        	cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;
            if(i % 2 == 1){
                cin >> mainI;
        		ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
            	cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }
        AlcoholicDrink::total(ad, n);
        int d;
        cin >> d;
        AlcoholicDrink::changeDiscount(d);
        AlcoholicDrink::total(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    }

}

