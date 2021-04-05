#include <iostream>
#include <cstring>
using namespace std;


// vashiot kod ovde
class Pair
{
private:
  char *key;
  int value;

  void copy_class (const Pair & other)
  {
    this->key = new char[strlen (other.key) + 1];
      strcpy (this->key, other.key);
      this->value = other.value;
  }

public:

  //constructors
    Pair (char *key = "", int value = 0)
  {
    this->key = new char[strlen (key) + 1];
    strcpy (this->key, key);
    this->value = value;
  }


  //copy constructor
  Pair (const Pair & pair)
  {
    copy_class (pair);
  }

  //destructor
  ~Pair ()
  {
    delete[]this->key;
  }

  //operator<<
  friend ostream & operator<< (ostream & o, const Pair & pair)
  {
    o << pair.key << " -> " << pair.value<<" ";
    return o;
  }

  //done <<

  //operaor-- prefix
  Pair operator-- ()
  {
    this->value -= 1;
    return *this;
  }

  //done

  //operator-- postfix
  Pair operator-- (int)
  {
    Pair temp_pair (*this);
    this->value -= 1;
    return temp_pair;
  }
  //done

  //operator*

Pair operator*(const Pair & pair){
    Pair temp_pair;
    if(strlen(this->key) < strlen(pair.key))
        temp_pair.set_key(this->key);
    else
        temp_pair.set_key(pair.key);
    //done with the key

    //now value
    temp_pair.set_value(this->value * pair.value);
    return temp_pair;

}

    //operator=
    Pair& operator=(const Pair &pair){
        delete [] this->key;
        copy_class(pair);
        return *this;
    }

    //set methods
    void set_key(char *key){
        delete [] this->key;
        this->key = new char [strlen(key) + 1];
        strcpy(this->key, key);
    }

    void set_value(int value){
        this->value = value;
    }

    //get methods
    int get_value(){
        return this->value;
    }
};

//Everything working nice for class Pair

class Collection{
    Pair *pairs;
    int n_pairs;

    void copy(const Collection &other){
        this->n_pairs = other.n_pairs;
        this->pairs = new Pair [this->n_pairs];
        for(int i = 0; i<this->n_pairs; i++){
            this->pairs[i] = other.pairs[i];
        }
    }

    public:
    Collection(){
        pairs = new Pair [0];
        n_pairs = 0;
    }

    ~Collection(){
        delete [] this->pairs;
    }

    //copy constructor;
    Collection(const Collection &other){
        copy(other);
    }

    Collection& operator+=(const Pair &pair){
        Pair *temp_pair_array = new Pair [this->n_pairs + 1];
        for(int i = 0; i<this->n_pairs; i++){
            temp_pair_array[i] =  this->pairs[i];
        }
        temp_pair_array[this->n_pairs] = pair;
        delete[]this->pairs;
        this->n_pairs+=1;
        this->pairs = new Pair [this->n_pairs];
        for(int i = 0; i<this->n_pairs; i++)
        {
            this->pairs[i] = temp_pair_array[i];
        }
        delete[]temp_pair_array;
        return *this;
    }

    //operator<<


    friend ostream& operator<<(ostream & o, Collection &collection)
    {
        o<<collection.get_n_pairs()<<endl;
        for(int i = 0; i<collection.get_n_pairs(); i++){
            o<<collection.pairs[i]<<endl;
        }
        return o;
    }

    int get_n_pairs(){
        return this->n_pairs;
    }

    int product_values(){
        int product =1;
        for(int i= 0; i<this->n_pairs; i++){
            product *= this->pairs[i].get_value();
        }
    }
    //

    //operator<
    bool operator<(Collection &collection){
        return (this->product_values() < collection.product_values());
    }


    //methods
    int greater(int value){
        int count = 0;
        for(int i = 0; i<this->n_pairs; i++)
        {
            if(this->pairs[i].get_value() > value)
                 count++;
        }

        return count;
    }
};




void
read (char *k, float *v)
{
  cin >> k;
  cin >> *v;
}

int
main ()
{
  char key[50];
  float value;
  cout << "----- class Pair -----" << endl;
  read (key, &value);
  cout << "----- constructor -----" << endl;
  Pair p1 (key, value);
  read (key, &value);
  Pair p2 (key, value);
  Pair p3 (p1);
  cout << "----- operator << -----" << endl;
  cout << p1;
  cout << p2;
  cout << "----- operator --(int) -----" << endl;
  cout << (p1--);
  cout << p1;
  cout << "----- operator -- -----" << endl;
  cout << (--p2);
  cout << "----- operator * -----" << endl;
  Pair p = p1 * p2;
// Pair p;
// p = p1*p2;
// p = p1;
  cout << "----- operator = -----" << endl;
  p3 = p;
  cout << p3;
// cout<<p;

  cout << "----- class Collection -----" << endl;
  cout << "----- constructor -----" << endl;
  Collection k;
  cout << "----- operator += -----" << endl;
  k += p1;
  k += p2;
  k += p3;
  cout << "----- operator << -----" << endl;
  cout << k;
  cout << "----- copy constructor -----" << endl;
  Collection k2 (k);
  cout << "----- operator < -----" << endl;
  if (k < k2)
    {
      cout << "k < k2" << endl;
    }
  else
    {
      cout << "k >= k2" << endl;
    }
  k2 += p1;
  if (k < k2)
    {
      cout << "k < k2" << endl;
    }
  else
    {
      cout << "k >= k2" << endl;
    }
  cout << "----- greater -----" << endl;
  int x;
  cin >> x;
  int pp = k.greater (x);
  cout << pp;
  return 0;
}

