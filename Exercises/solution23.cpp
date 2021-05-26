#include <iostream>
#include <cstring>
using namespace std;

// Your code here!!!


class MonthlyInvoice{
    protected:
    char username[100];
    int userNumber;
    float initial_price;
    int used_internet;

    public:
    MonthlyInvoice(char *username, int userNumber, float initial_price, int used_internet){
        strcpy(this->username, username);
        this->userNumber = userNumber;
        this->initial_price = initial_price;
        this->used_internet=  used_internet;
    }

    virtual float total_price() = 0;

    void print(){
        cout<<userNumber<<" - "<<username<<", "<<initial_price<<endl;
    }

    bool operator>(MonthlyInvoice *mi)
    {
        return this->total_price() > mi->total_price();
    }

    MonthlyInvoice& operator=(MonthlyInvoice &mi)
    {
        strcpy(this->username, mi.username);
        this->userNumber = mi.userNumber;
        this->initial_price = mi.initial_price;
        this->used_internet = mi.used_internet;
    }
};

class BusinessInvoice : public MonthlyInvoice{
  private:
  bool optic_cable;
  int free_gigabytes;

  public:

  BusinessInvoice(char *username, int userNumber, float initial_price, int used_internet, bool optic_cable, int free_gigabytes) : MonthlyInvoice(username,  userNumber,  initial_price, used_internet)
    {
        this->optic_cable = optic_cable;
        this->free_gigabytes = free_gigabytes;
    }
  float total_price(){
      int gigas_over_free_internet = (used_internet > free_gigabytes ? used_internet - free_gigabytes : 0);
      float temp = initial_price +gigas_over_free_internet*100;
      if(optic_cable){
          temp += initial_price/2;
      }
      return temp;
  }

  BusinessInvoice& operator++(int i){
      this->used_internet++;

      return *this;
  }

  friend ostream& operator<<(ostream &o, BusinessInvoice &bi){
      bi.print();
      o<<(bi.optic_cable ? "optical link, " : "cable link, ")<<(bi.free_gigabytes < bi.used_internet ? bi.used_internet-bi.free_gigabytes : 0)<<endl;

      return o;
  }

};

class PrivateInvoice : public MonthlyInvoice{
  private:
  char id[13];
  int *movies;
  int n_movies;

  public:
  PrivateInvoice(char *username, int userNumber, float initial_price, int used_internet) : MonthlyInvoice(username,  userNumber,  initial_price, used_internet)
    {
        // strcpy(this->id = id);
        this->movies = new int [0];
        this->n_movies = 0;
    }
  int gigabytes_movies(){
      int temp = 0;
      for(int i = 0; i<n_movies; i++)
      {
          temp+=movies[i];
      }
      return temp;
  }

  float total_price(){
      float temp = initial_price + used_internet * 50 + gigabytes_movies() * 10;
      return temp;
  }

  int operator[](int index){
      if(index >= n_movies)
      {
          return -1;
      }

      return movies[index];
  }

  PrivateInvoice& operator+=(int newMovie)
  {
      int *tempMovies = new int[n_movies + 1];
      for(int i = 0; i<n_movies; i++)
      {
          tempMovies[i] = movies[i];
      }
      tempMovies[n_movies] = newMovie;
      delete [] movies;
      movies = new int [++n_movies];
      for(int i = 0;i<n_movies; i++)
      {
          movies[i] = tempMovies[i];
      }
      delete[] tempMovies;

      return *this;
    }

    PrivateInvoice& operator++(int i)
    {
        this->used_internet++;
        return *this;
    }

      friend ostream& operator<<(ostream &o, PrivateInvoice &bi){
      bi.print();
      o<<bi.used_internet<<endl<<bi.n_movies<<", "<<bi.gigabytes_movies()<<endl;

      return o;
  }

  int getMoviesNo()
  {
      return n_movies;
  }
};

MonthlyInvoice& biggestInvoice(MonthlyInvoice**mi, int n)
{
    MonthlyInvoice* temp = mi[0];
    for(int i = 1; i<n; i++)
    {
        if(mi[i]->total_price() > temp->total_price())
        {
            temp = mi[i];
        }
    }

    return *temp;
}

// Testing the program!!!
int main(){
    int test_case;
    char username[101];
    int userNumber;
    float basic_price;
    int spent_gigabytes;
    bool optical;
    int free_gigabytes;
    int num_inc;

    cin>>test_case;
    if (test_case == 1){
        // Test Case Business Invoice - Constructor, operator <<
        cin>>username>>userNumber>>basic_price>>spent_gigabytes;
        cin>>optical>>free_gigabytes;
        BusinessInvoice bi(username, userNumber,basic_price, spent_gigabytes, optical, free_gigabytes);
        cout<<"BusinessInvoice Created:\n";
        cout<<bi;
    }
    else if (test_case == 2) {
        // Test Case Business Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "BusinessInvoice:\n";
        cout << bi;
        cout << "testing operator++\n";

        // Additional spent gigabytes
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i) {
            bi++;
        }
        cout << bi;
    }
    else if (test_case == 3) {
        // Test Case Business Invoice - Constructor, total_price, operators <<, ++,
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "Testing total_price()\n";
        cout << bi;
        cout<<bi.total_price()<<endl;
        bi++;
        cout << bi;
        cout<<bi.total_price()<<endl;
    }
    else if (test_case == 4){
        // Test Case Private Invoice - Constructor, operator <<
        cin>>username>>userNumber>>basic_price>>spent_gigabytes;

        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cout<<"Private Invoice Created:\n";
        cout<<pi;
    }
    else if (test_case == 5) {
        // Test Case Private Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i) {
            pi++;
        }
        cout << pi;
    }
    else if (test_case == 6) {
        // Test Case Private Invoice - Constructor, operators <<, +=
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cout << pi;
    }
    else if (test_case == 7) {
        // Test Case Private Invoice - Constructor, operators <<, +=, []
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cout << pi;
        cout << "Movie sizes: [";
        for (int i=0; i<pi.getMoviesNo(); ++i){
            cout << pi[i] << " ";
        }
        cout << "]" << endl;
    }
    else if (test_case == 8) {
        // Test Case Private Invoice - Constructor, total_price
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cout<<pi;
        cout<< pi.total_price() <<endl;
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i){
            pi++;
        }
        cout << pi;
        cout<< pi.total_price() <<endl;
    }
    else if (test_case == 9) {
        // Test Case

        int num_invoices;
        int invoice_type;

        cin >>num_invoices;
        MonthlyInvoice ** mi = new MonthlyInvoice*[num_invoices];
        for (int j=0;j<num_invoices; ++j) {

            cin >> invoice_type;
            if (invoice_type == 1){
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                cin >> optical >> free_gigabytes;
                BusinessInvoice * bip;
                bip = new BusinessInvoice(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
                cin >> num_inc;
                for (int i=0; i<num_inc; ++i) {
                    (*(bip))++;
                }
                cout << *(bip);
                cout<<bip->total_price()<<endl;

                mi[j] = bip;
            }
            if (invoice_type == 2) {
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                PrivateInvoice* pip = new PrivateInvoice(username, userNumber, basic_price, spent_gigabytes);
                cin >> num_inc;
                int film_length;
                for (int i = 0; i < num_inc; ++i) {
                    cin >> film_length;
                    (*pip) += film_length;
                }
                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*pip)++;
                }
                cout << (*pip);
                cout << pip->total_price() << endl;
                mi[j] = pip;
            }
        }

        cout << "The biggest invoice is:\n";
        MonthlyInvoice& invoice = biggestInvoice(mi, num_invoices);

        MonthlyInvoice* m = &invoice;
        BusinessInvoice* bip;
        PrivateInvoice* pip;
        if (dynamic_cast<BusinessInvoice *> (m)){
            bip = dynamic_cast<BusinessInvoice *> (m);
            cout<<*bip << bip->total_price();
        }
        if (dynamic_cast<PrivateInvoice *> (m)){
            pip = dynamic_cast<PrivateInvoice *> (m);
            cout<<*pip << pip->total_price();
        }

    }
    return 0;
}
