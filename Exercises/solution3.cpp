#include <iostream>
#include <cstring>
using namespace std;



// your code here
class Character{
    private:
        char c;
    public:
        Character(char c = 'a'){
            this->c = c;
        }


        Character& operator = (char c){
            this->c = c;
            return *this;
        }

        friend ostream& operator<<(ostream &o, const Character &other){
            o<<other.c;
            return o;
        }
        //get

        char get_c(){
            return this->c;
        }


        //set
        void set_c(char c){
            this->c = c;
        }
};





class CharSequence{
  private:
    Character * characters;
    int n_chars;
public:
    CharSequence(){
        this->characters = new Character [0];
        this->n_chars = 0;
    }
    CharSequence(char *str){
        this->n_chars = strlen(str);
        this->characters = new Character [this->n_chars];
        // strcpy(this->characters, str);
        for(int i = 0; i<this->n_chars; i++){
            this->characters[i].set_c(str[i]);
        }
    }

    //done with constructors

    //CharSequenc& operator[](int i) for accessing the i-th element of the sequence. (5 points)
    Character& operator[](int i){
        return this->characters[i];
    }
    //copy constructors
    CharSequence(const CharSequence &other){
         this->n_chars = other.n_chars;
        this->characters = new Character [this->n_chars];
        for(int i = 0; i<other.n_chars; i++)
        {
            this->characters[i] = other.characters[i];
        }
    }


    //operator =
    CharSequence& operator = (const CharSequence &other){
        delete [] this->characters;
        this->n_chars = other.n_chars;
        this->characters = new Character [this->n_chars];
        for(int i = 0; i<other.n_chars; i++)
        {
            this->characters[i] = other.characters[i];
        }

        return *this;
    }

    //CharSequence& operator +=(const Character &c) for adding new Character object. To add the new object, expand the dynamically allocated array for +1. (10 points)

    CharSequence& operator +=(const Character &c){
        Character * temp_characters = new Character [this->n_chars + 1];
        for(int i = 0; i<this->n_chars; i++)
        {
            temp_characters[i] = this->characters[i];
        }

        temp_characters[this->n_chars] = c;
        delete [] this->characters;
        this->n_chars+=1;
        this->characters = new Character [this->n_chars];
        for(int i = 0; i<this->n_chars; i++)
        {
            this->characters[i] = temp_characters[i];
        }
        delete [] temp_characters;
        return *this;
    }


    //bool operator==(const CharSequence &cs) that will compare two CharSequence objects.
    //Two objects are equal if they have equal arrays of Character objects, and two Character objects are equal if they hold equal character. (5 points)
    bool operator==(const CharSequence &cs){
        if(this->n_chars != cs.n_chars)
            return false;
        for(int i = 0; i<this->n_chars; i++)
        {
            if(this->characters[i].get_c() != cs.characters[i].get_c())
                return false;
        }

        return true;
    }

    //int operator[](char c) that will return how many times the character c apears in the CharSequence object. (5 points)

    int operator[](char c){
        int total_appearance = 0;
        for(int i = 0; i<this->n_chars; i++)
        {
            if(this->characters[i].get_c() == c)
                total_appearance++;
        }
        return total_appearance;
    }

    //CharSequence toUpperCase() that will return a new CharSequence object, where all characters will be in uppercase. (10 points)

    CharSequence& toUpperCase(){
        //uppercase

        CharSequence return_sequence;
        return_sequence = *this;

        for(int i = 0; i<this->n_chars; i++)
        {
            // char currentChar = (this->characters[i])).get_c();
            // char currentChar = return_sequence[i].get_c();
            // if(islower(currentChar)){
            //   currentChar = toupper(currentChar);
            //   return_sequence[i].set_c(currentChar);
            // }

            char currentChar = this->characters[i].get_c();
            if(islower(currentChar)){
              currentChar = toupper(currentChar);
              this->characters[i].set_c(currentChar);
            }
        }
        // return return_sequence;
        // cout<<return_sequence<<endl;
        return *this;
    }

    friend ostream& operator<<(ostream &o, CharSequence &other){
        for(int i = 0; i<other.get_chars(); i++)
        {
            o<<other[i];
            // o<<"ilir"<<endl;
        }

        return o;
    }

    int get_chars(){
        return this->n_chars;
    }
};


int main() {
    int n;
    cin >> n;

    if(n == 1) {
        cout << "Testing Character class" << endl;
        cout << "Character constructor" << endl;
        char c;
        cin >> c;
        Character cc(c);
        cout << "OK" << endl;
        cout << "Character operator &lt;&lt;" << endl;
        cout << cc << endl;
    } else if(n == 2) {
        cout << "Testing CharSequence constructors" << endl;
        char word[100];
        cin >> word;
        CharSequence cs1(word);
        cout << cs1 << endl;
    } else if(n == 3) {
        cout << "Testing CharSequence copy constructor and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy(cs);
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if(n == 4) {
        cout << "Testing CharSequence =operator and operator[int]" << endl;
        CharSequence cs("Some sequence");
        CharSequence copy;
        copy = cs;
        cs[0] = 'X';
        cout << "Original: " << cs << endl;
        cout << "Copy: " << copy << endl;
    } else if(n == 5) {
        cout << "Testing CharSequence operator+=" << endl;
        CharSequence cs;
        char word[100];
        cin >> word;
        int len = strlen(word);
        for(int i = 0; i < len; ++i) {
            cs += Character(word[i]);
        }
        cout << cs << endl;
    } else if(n == 6) {
        cout << "Testing CharSequence operator[char]" << endl;
        CharSequence cs("If you don't read the newspaper, you're uninformed. If you read the newspaper, you're mis-informed.");
        cout << cs['e'] << endl;
    } else if(n == 7) {
        cout << "Testing CharSequence toUpperCase" << endl;
        CharSequence cs("If you tell the truth, you don't have to remember anything");
        // cs.toUpperCase();
        cout << cs.toUpperCase()<<endl;
        // CharSequence temp = cs.toUpperCase();
        // cout<<temp;
        // cout << cs << endl;
    } else if(n == 8) {
        cout << "Testing CharSequence operator ==" << endl;
        CharSequence cs1("abc");
        CharSequence cs2("abc");
        CharSequence cs3("abcd");
        CharSequence cs4("xyz");
        cout << (cs1 == cs2) << endl;
        cout << (cs1 == cs3) << endl;
        cout << (cs2 == cs4) << endl;
    }

    return 0;
}

