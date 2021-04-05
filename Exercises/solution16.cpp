#include <iostream>
#include <cstring>
using namespace std;


// Your code here

class Pair{
    private:
        char *key;
        float value;

    void copy_pair(const Pair &pair){
        this->key = new char [strlen(pair.key) + 1];
        strcpy(this->key, pair.key);
        this->value = pair.value;
    }

    public:
    //constructor
    Pair(){
        this->key = new char [0];
        this->value = 0;
    }

    Pair(char *key, float value){
        this->key = new char [strlen(key) + 1];
        strcpy(this->key, key);
        this->value = value;
    }
    Pair(const Pair &pair){
        copy_pair(pair);

    }
    ~Pair(){
        delete [] this->key;
    }

    //done with constructors and destructors
    //everything fine

    //operator<<
    friend ostream& operator<<(ostream &o, Pair pair){
        o<<pair.get_key()<<", "<<pair.get_value()<<endl;
        return o;
    }

    //need getters for <<
    //get
    char *get_key(){
        return this->key;
    }
    float get_value(){
        return this->value;
    }


    Pair& operator++(){
        this->value += 1;
        return *this;
    }

    Pair operator++(int){

        Pair temp;
        temp = *this;

        this->value += 1;
        // cout<<"temp = "<<temp;
        return temp;
    }

    //operator=
    Pair& operator=(const Pair &pair){
        delete [] this->key;
        copy_pair(pair);
        return *this;
    }
    Pair operator+(const Pair &pair){
        char *temp_key;
        if(strcmp(this->key, pair.key) == -1)
            {
                temp_key = new char[strlen(pair.key) + 1];
                strcpy(temp_key, pair.key);
            }
        else
        {
            temp_key = new char[strlen(this->key) + 1];
                strcpy(temp_key, this->key);
        }
        int temp_value = this->value + pair.value;
        Pair temp_pair(temp_key, temp_value);
        delete [] temp_key;
        return temp_pair;
    }
};


class Collection{
    private:
        Pair *pairs;
        int length;

    public:
    Collection(){
        this->pairs = new Pair [0];
        this->length = 0;
    }

    Collection(const Collection &collection)
    {
        // delete [] this->pairs;
        this->pairs = new Pair [collection.length];
        this->length = collection.length;
        for(int i  = 0;i<this->length; i++)
        {
            this->pairs[i] = collection.pairs[i];
        }
    }

    ~Collection(){
        delete [] this->pairs;
    }

    //operator +=
    Collection& operator+=(const Pair &pair){
        Pair *temp = new Pair [this->length + 1];
        for(int i =  0; i<this->length; i++)
        {
            temp[i] = this->pairs[i];
        }
        temp[this->length] = pair;
        delete [] this->pairs;
        this->length += 1;
        this->pairs = new Pair [this->length];
        for(int i=  0; i<this->length; i++)
        {
            this->pairs[i] = temp[i];
        }
        delete [] temp;
        return *this;
    }

    //operator<<
    friend ostream& operator<<(ostream &o, Collection collection){
        o<<collection.get_length()<<endl;
        for(int i = 0; i<collection.get_length(); i++)
        {
            o<<collection.get_pair(i);
        }

        return o;
    }

    //get for <<
    int get_length(){
        return this->length;
    }
    Pair& get_pair(int index){
        return this->pairs[index];
    }

    //operator ==
    bool operator==(const Collection &collection)
    {
        if(this->length != collection.length)
        return false;

        for(int i = 0; i<this->length; i++)
        {
            //compare values
            if(this->pairs[i].get_value() != collection.pairs[i].get_value())
                return false;
            //compare keys
            if(strcmp(this->pairs[i].get_key(), collection.pairs[i].get_key()) != 0)
                return false;
        }
        return true;
    }

     Pair* find(const char* key){
         for(int i = 0; i<length; i++)
         {
             if(strcmp(this->pairs[i].get_key(), key) == 0)
                return &this->pairs[i];
         }
         return NULL;
     }
};

void read(char *k, float *v) {
    cin >> k;
    cin >> *v;
}
int main() {
    char key[50];
    float value;
    cout << "----- class Pair -----" << endl;
    read(key, &value);
    cout << "----- constructor -----" << endl;
    Pair p1(key, value);
    read(key, &value);
    Pair p2(key, value);
    Pair p3(p1);
    cout << "----- operator << -----" << endl;
    cout << p1;
    cout << p2;
    cout << "----- operator ++(int) -----" << endl;
    cout << (p1++);
    cout << p1;
    cout << "----- operator ++ -----" << endl;
    cout << ++p2;
    cout << "----- operator + -----" << endl;
    Pair p = p1 + p2;
    cout << "----- operator = -----" << endl;
    p3 = p;
    cout << p3;

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
    Collection k2(k);
    cout << "----- operator == -----" << endl;
    if(k == k2) {
        cout << "k == k2" << endl;
    }
    k2 += p1;
    if(k == k2) {
        // not equal
        cout << "k == k2" << endl;
    }
    cout << "----- find -----" << endl;
    Pair* f = k.find(key);
    cout << *f;
    strcat(key, "other");
    f = k.find(key);
    if(f == NULL) {
        cout << key << " not found" << endl;
    }
    return 0;
}

