
#include<iostream>
#include<cstring>
using namespace std;

class Automobile{
    private:
        char* brand;
        int *reg_num;
        int max_speed;

    public:

    Automobile(){
        this->brand = new char [0];
        this->reg_num = new int [5];
        this->max_speed = 0;
    }

    Automobile( char *brand, int *reg_num,int max_speed){
        // cout<<"marka in here"<<brand;
        this->brand = new char[strlen(brand) + 1];
        strcpy(this->brand, brand);
        this->reg_num = new int [5];
        for(int i = 0; i<5; i++)
        {
            this->reg_num[i] = reg_num[i];
        }
        this->max_speed = max_speed;
    }
    //=

    Automobile& operator=(Automobile& other)
    {
        //  delete [] this->brand;
        //  delete [] this->reg_num;
         this->brand = new char[strlen(other.brand) + 1];
        strcpy(this->brand, other.brand);
        this->reg_num = new int [5];
        for(int i = 0; i<5; i++)
        {
            this->reg_num[i] = other.reg_num[i];
        }
       this->max_speed = other.max_speed;
        return *this;
    }


    //==
    bool operator==(const Automobile &other)
    {
        for(int i = 0; i<5;i++)
        {
            if(other.reg_num[i] != this->reg_num[i]);
            return false;
        }
        return true;
    }

    // <<
    friend ostream& operator<<(ostream &o,  Automobile &other)
    {
        o<<"Marka\t"<<other.get_brand()<<"\tRegistracija[ ";
        for(int i = 0; i<5; i++)
        {
            o<<((other.get_reg())[i])<<" ";
        }
        o<<']'<<endl;
        return o;
    }

    //need get for ostream
    char * get_brand(){
        return this->brand;
    }

    int * get_reg(){
        return this->reg_num;
    }

    int get_max_speed(){
        return this->max_speed;
    }
};

class RentACar{
  private:
    char name[100];
    Automobile *automobiles;
    int n_automobiles;

  public:

  RentACar(char *name = ""){
      strcpy(this->name, name);
      this->automobiles = new Automobile [0];
      this->n_automobiles = 0;
  }

//   +=
   RentACar& operator+=( Automobile &automobile){
        Automobile* temp_auots = new Automobile [this->n_automobiles + 1];
        for(int i = 0; i<this->n_automobiles; i++)
        {
            temp_auots[i] = this->automobiles[i];
        }
        temp_auots[this->n_automobiles] = automobile;
        delete [] this->automobiles;
        this->n_automobiles +=1;
        this->automobiles = new Automobile [this->n_automobiles];
        for(int i = 0; i<this->n_automobiles; i++)
        {
           this->automobiles[i] = temp_auots[i];
        }

        delete [] temp_auots;

    }

  //-=
  RentACar& operator-=(const Automobile &automobile){
      Automobile* temp_auots = new Automobile [this->n_automobiles];
        int current_index= 0;
        for(int i = 0; i<this->n_automobiles; i++)
        {
            if(this->automobiles[i] == automobile)
            {
            //   cout<<"here: "<<this->automobiles[i]<<endl<<"here: "<<automobile<<endl;
                // cout<<this->automobiles[i];
                // cout<<"herer";
                continue;
            }
            else
            {
                // cout<<"here"
                temp_auots[current_index++] = this->automobiles[i];
            }

        }
        delete [] this->automobiles;
        // cout<<"current_index = "<<current_index<<endl;
        this->n_automobiles = current_index;
        this->automobiles = new Automobile [this->n_automobiles];
        for(int i = 0; i<this->n_automobiles; i++)
        {
           this->automobiles[i] = temp_auots[i];
        }

        delete [] temp_auots;

        return *this;
  }
  void printWithSpeedOver(int max){
      cout<<this->name<<endl;
      for(int i = 0; i<this->n_automobiles; i++)
      {
          if(this->automobiles[i].get_max_speed() > 150)
            cout<<this->automobiles[i]<<endl;
      }
  }

};




int main()
{
   RentACar agencija("FINKI-Car");
   int n;
   cin>>n;

   for (int i=0;i<n;i++)
   {
    	char marka[100];
    	int regisracija[5];
    	int maximumBrzina;

       	cin>>marka;

       	for (int i=0;i<5;i++)
    		cin>>regisracija[i];

    	cin>>maximumBrzina;
    // cout<<Automobile(marka,regisracija,maximumBrzina);

       	// Automobile nov=Automobile(marka,regisracija,maximumBrzina);
       	Automobile nov(marka,regisracija,maximumBrzina);
    //   cout<<nov;
    	//dodavanje na avtomobil
       	agencija+=nov;

   }
    //se cita grehsniot avtmobil, za koj shto avtmobilot so ista registracija treba da se izbrishe
    // cout<<"ilir"<<endl;
    char marka[100];
    int regisracija[5];
    int maximumBrzina;
    cin>>marka;
    for (int i=0;i<5;i++)
    cin>>regisracija[i];
    cin>>maximumBrzina;

    Automobile greshka=Automobile(marka,regisracija,maximumBrzina);

    //brishenje na avtomobil
    agencija-=greshka;
    // agencija.printAll();
    agencija.printWithSpeedOver(150);

    return 0;
}
