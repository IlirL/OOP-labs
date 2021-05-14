
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

class ExistingPodcast{
    public:
    void message(){
        cout<<"The podcast is already in the collection"<<endl;
    }
};

class Podcast{
    protected:
    char podcast_name[100];
    char podcast_url[1000];
    float podcast_price;
    int podcast_discount;


    public:
    Podcast(char *podcast_name = "", char *podcast_url = "", float podcast_price = 0, int podcast_discount = 0)
    {
        strcpy(this->podcast_name, podcast_name);
        strcpy(this->podcast_url, podcast_url);
        this->podcast_price = podcast_price;
        this->podcast_discount = podcast_discount;
        // cout<<"Podcast constructor with"<<this->podcast_name<<" "<<this->podcast_url<<" "<<this->podcast_price<<" "<<this->podcast_discount<<endl;

    }


    friend ostream & operator<<(ostream & , Podcast& );
  friend istream & operator>>(istream & , Podcast& );

    bool operator==(Podcast &p)
    {
        if(strcmp(this->podcast_url, p.podcast_url) ==0)
            return 1;
        return 0;
    }

    char* getName(){
        return podcast_name;
    }

    char* getUrl(){
        return podcast_url;
    }

    float getPrice(){
        return podcast_price;
    }

    int getDiscount(){
        return podcast_discount;
    }

       virtual void dummy_function(){
        cout<<"1";
    }

    virtual float get_price(){
    // cout<<"type 1"<<endl;
    return podcast_price * (1.0 - (this->podcast_discount/100.0));
  }
};

class StreamingPodcast : public Podcast{
    private:
    float monthly_fee;
    int month;
    int year;

    public:
    StreamingPodcast(char *podcast_name = "", char *podcast_url = "", float podcast_price = 0, int podcast_discount = 0, float monthly_fee = 0, int month = 0, int year = 0)
    : Podcast(podcast_name, podcast_url, podcast_price, podcast_discount){
        this->monthly_fee = monthly_fee;
        this->month = month;
        this->year = year;
    }

   friend ostream & operator<<(ostream & , StreamingPodcast& );
  friend istream & operator>>(istream & , StreamingPodcast& );

    int getMonth(){
        return month;
    }

    float getMonthlyFee(){
        return monthly_fee;
    }
    void dummy_function() override{
        cout<<"2";
    }

    float get_price() override{
    // cout<<"2 type"<<endl;
    float p = Podcast::get_price();

    int months=0;
    if (year<2018){
      months = (12 - this->month) + (2017 - year)*12 + 5;
    }
    else {
        months = 5 - this->month;
      }

    p += months * monthly_fee;

    return p;
  }
};

ostream & operator<<(ostream & o,  Podcast& p) {
  o<<"Podcast: "<< p.podcast_name << "\nURL: "<< p.podcast_url
  <<"\nregular price: $" << p.podcast_price;

  if (p.podcast_discount){
    o<<", bought on discount";
  }
  return o;
}

ostream & operator<<(ostream & o, StreamingPodcast& sp) {

  Podcast * tmp = dynamic_cast<Podcast*>(&sp);

  o << *tmp;

  o<<", monthly fee: $"<< sp.monthly_fee
  <<", purchased: "<< sp.month << "-" << sp.year<<std::endl;

  return o;
}

istream & operator>>(istream & is, Podcast &p){

  is.get();
  is.getline(p.podcast_name,100);
  is.getline(p.podcast_url,1000);
    //cin.get();
  is>>p.podcast_price>>p.podcast_discount;

  return is;
}

istream & operator>>(istream & is, StreamingPodcast &sp){
  is.get();
  is.getline(sp.podcast_name,100);
  is.getline(sp.podcast_url,1000);
  is>>sp.podcast_price>>sp.podcast_discount;
  is>>sp.monthly_fee >> sp.month >> sp.year;
  return is;


}

class Playlist{
    private:
    char playlist_name[100];
    Podcast **podcasts;
    int n;


    public:
    Playlist(char *playlist_name)
    {
        strcpy(this->playlist_name, playlist_name);
        this->n = 0;
        this->podcasts = new Podcast*[n];
    }

    Playlist& operator+=(Podcast &p)
    {
        //checking if this podacst was already added;
        for(int i = 0; i<n; i++)
        {
            if(strcmp(podcasts[i]->getName(), p.getName()) == 0)
                {
                    throw ExistingPodcast();
                    return *this;
                }
        }


        Podcast **temp = new Podcast *[n+1];
        for(int i = 0; i<n; i++)
        {
            temp[i] = podcasts[i];
        }
        temp[n] = &p;

        delete [] podcasts;

        podcasts = new Podcast *[++n];
        for(int i = 0; i<n; i++)
        {
            podcasts[i] = temp[i];
        }

        delete[] temp;

        return *this;
    }

    float total_spent(){

        float total = 0;

        for(int i = 0; i<n; i++)
        {
            //calculate the price being as a podcast;
            // cout<<"podcasts[i]->getPrice() = "<<podcasts[i]->getPrice()<<endl;
            total+=podcasts[i]->get_price();
        }

        return total;
    }

    friend ostream& operator<<(ostream &o, Playlist &p)
    {
        StreamingPodcast* temp;
        o<<endl<<"Playlist: "<<p.playlist_name<<endl;
        for(int i = 0; i<p.n; i++)
        {
            temp = dynamic_cast<StreamingPodcast*>(p.podcasts[i]);
            if(temp!=NULL)
                cout<<*temp;
            else
                cout<<*(p.podcasts[i]);
            // if(i<p.n-1)
            cout<<endl;
        }
        return o;
    }


};

//operator overloading for printing and reading is a little bit of a problem
//I am thinking of overloading them globally because


int main() {
  int test_case_num;

  cin>>test_case_num;

  // for Podcast
  char podcast_name[100];
  char podcast_url[1000];
  float podcast_price;
  int podcast_discount;

  // for StreamingPodcast
  float sub_podcast_monthly_fee;
  int sub_podcast_month, sub_podcast_year;

  // for Playlist
  char name[100];
  int num_podcasts_in_playlist;

  if (test_case_num == 1){
    cout<<"Testing class Podcast and operator<< for Podcast"<<std::endl;
    cin.get();
    cin.getline(podcast_name,100);
    cin.getline(podcast_url, 1000);
    //cin.get();
    cin>>podcast_price>>podcast_discount;

    Podcast p(podcast_name, podcast_url, podcast_price, podcast_discount);

    cout<<p;
  }
  else if (test_case_num == 2){
    cout<<"Testing class StreamingPodcast and operator<< for StreamingPodcast"<<std::endl;
    cin.get();
    cin.getline(podcast_name,100);
    cin.getline(podcast_url, 1000);
    //cin.get();
    cin>>podcast_price>>podcast_discount;

    cin>>sub_podcast_monthly_fee;
    cin>>sub_podcast_month>>sub_podcast_year;

    StreamingPodcast sp(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
    cout<<sp;
  }
  else if (test_case_num == 3){
    cout<<"Testing operator>> for Podcast"<<std::endl;
    Podcast p;

    cin>>p;

    cout<<p;
  }
  else if (test_case_num == 4){
    cout<<"Testing operator>> for StreamingPodcast"<<std::endl;
    StreamingPodcast sp;

    cin>>sp;

    cout<<sp;
  }
  else if (test_case_num == 5){
    cout<<"Testing class Playlist and operator+= for Playlist"<<std::endl;
    cin.get();
    cin.getline(name,100);
    Playlist u(name);

    int num_user_podcasts;
    int podcast_type;
    cin >>num_user_podcasts;

    try {

      for (int i=0; i<num_user_podcasts; ++i){

        cin >> podcast_type;

        Podcast *g;
        // 1 - Game, 2 - SubscriptionGame
        if (podcast_type == 1){
          cin.get();
          cin.getline(podcast_name, 100);
          cin.getline(podcast_url, 1000);

          cin>>podcast_price>>podcast_discount;
          g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
        }
        else if (podcast_type == 2){
          cin.get();
          cin.getline(podcast_name, 100);
          cin.getline(podcast_url, 1000);

          cin>>podcast_price>>podcast_discount;

          cin>>sub_podcast_monthly_fee;
          cin>>sub_podcast_month>>sub_podcast_year;
          g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
        }

        //cout<<(*g);


        u+=(*g);
      }
    }catch(ExistingPodcast &ex){
      ex.message();
    }

    cout<<u;

  }
  else if (test_case_num == 6){
      cout<<"Testing exception ExistingPodcast for Playlist"<<std::endl;
      cin.get();
      cin.getline(name,100);
      Playlist u(name);

      int num_podcasts_in_playlist;
      int podcast_type;
      cin >>num_podcasts_in_playlist;

      for (int i=0; i<num_podcasts_in_playlist; ++i){

          cin >> podcast_type;

          Podcast *g;
          // 1 - Game, 2 - SubscriptionGame
          if (podcast_type == 1){
            cin.get();
            cin.getline(podcast_name, 100);
            cin.getline(podcast_url, 1000);

            cin>>podcast_price>>podcast_discount;
            g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
          }
          else if (podcast_type == 2){
            cin.get();
            cin.getline(podcast_name, 100);
            cin.getline(podcast_url, 1000);

            cin>>podcast_price>>podcast_discount;

            cin>>sub_podcast_monthly_fee;
            cin>>sub_podcast_month>>sub_podcast_year;
            g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
          }

          //cout<<(*g);

          try {
            u+=(*g);
          }
          catch(ExistingPodcast &ex){
            ex.message();
          }
        }

      cout<<u;
  }
  else if (test_case_num == 7){
      cout<<"Testing total_spent method() for Playlist"<<std::endl;
      cin.get();
      cin.getline(name,100);
      Playlist u(name);

      int num_podcasts_in_playlist;
      int podcast_type;
      cin >>num_podcasts_in_playlist;

      for (int i=0; i<num_podcasts_in_playlist; ++i){

          cin >> podcast_type;

          Podcast *g;
          // 1 - Game, 2 - SubscriptionGame
          if (podcast_type == 1){
            cin.get();
            cin.getline(podcast_name, 100);
            cin.getline(podcast_url, 1000);

            cin>>podcast_price>>podcast_discount;
            g = new Podcast(podcast_name, podcast_url, podcast_price, podcast_discount);
          }
          else if (podcast_type == 2){
            cin.get();
            cin.getline(podcast_name, 100);
            cin.getline(podcast_url, 1000);

            cin>>podcast_price>>podcast_discount;

            cin>>sub_podcast_monthly_fee;
            cin>>sub_podcast_month>>sub_podcast_year;
            g = new StreamingPodcast(podcast_name, podcast_url, podcast_price, podcast_discount, sub_podcast_monthly_fee, sub_podcast_month, sub_podcast_year);
          }

          //cout<<(*g);

          try {
            u+=(*g);
          }
          catch(ExistingPodcast &ex){
            ex.message();
          }
        }

      cout<<u;

      cout<<"Total money spent: $"<<u.total_spent()<<endl;
  }
}
