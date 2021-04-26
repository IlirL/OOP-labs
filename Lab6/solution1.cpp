

//Your code here
#include<iostream>
#include<cstring>
using namespace std;

class RealEstate{
    protected:
    char *address;
    int area;
    int price_variable;

    public:
    RealEstate()
    {
        this->address = new char[0];
        this->area = 0;
        this->price_variable = 0;
    }

    RealEstate(char *address, int area, int price_variable)
    {
        this->address = new char [strlen(address) + 1];
        strcpy(this->address, address);
        this->area = area;
        this->price_variable = price_variable;
    }

    RealEstate(const RealEstate &re)
    {
        this->address = new char [strlen(re.address) + 1];
        strcpy(this->address, re.address);
        this->area = re.area;
        this->price_variable = re.price_variable;
    }

    int price()
    {
        return this->area * this->price_variable;
    }

    void print()
    {
        //cout<<this->address<<", Kvadratura: "<<this->price_variable<<", Cena po Kvadrat: "<<this->price;

        cout<<this->address;
        cout<<", Kvadratura: ";
        cout<<this->area;
        cout<<", Cena po Kvadrat: ";
        cout<<this->price_variable;
    }

    float estateTax(){
        return  float(price()) * 5 / 100;
    }

    friend istream& operator>>(istream &i, RealEstate &re)
    {
        return i>>re.address>>re.area>>re.price_variable;
    }

    char * getAddress(){
    return this->address;
    }




};


class Villa : public RealEstate{
    int tax_luxury;

    public:

    Villa(char *address, int area, int price, int tax_luxury) : RealEstate(address, area, price) {
        this->tax_luxury = tax_luxury;
    }

    Villa():RealEstate(){
        this->tax_luxury = 0;
    }


     friend istream& operator>>(istream &i, Villa &v)
    {
        //return i>>v.address>>v.area>>v.price>>v.tax_luxury;
        i>>v.address;
        i>>v.area;
        i>>v.price_variable;
        i>>v.tax_luxury;

        return i;
    }

    void print()
    {
        RealEstate temp(*this);
        temp.print();
        //cout<<temp<<"tax_luxury: "<<this->tax_luxury<<endl;
        cout<<", Danok na luksuz: "<<this->tax_luxury<<endl;
    }

        float estateTax()
        {
            RealEstate temp(*this);
            float temp_tax = temp.estateTax();
            return this->price() * this->tax_luxury / 100 + temp_tax;

        }



};

int main(){
    RealEstate re;
    Villa v;
    cin >> re;
    cin >> v;
     re.print();
     cout<<endl;
     cout << "Danok za: " << re.getAddress() << ", e: " << re.estateTax() << endl;
     v.print();
     cout << "Danok za: " << v.getAddress() << ", e: " << v.estateTax() << endl;
    return 0;
}
