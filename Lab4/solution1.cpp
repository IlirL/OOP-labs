
#include<iostream>
#include<cstring>
using namespace std;


class Recipe{
  private:
    int nOfIngredients;
    char name[100];
    char *contents;

    void copy(const Recipe &other){
        // cout<<"Copy function"<<endl;
        this->nOfIngredients = other.nOfIngredients;
        strcpy(this->name, other.name);
        delete [] this->contents;
        this->contents = new char [strlen(other.contents) + 1];
        strcpy(this->contents, other.contents);
    }

    public:
        Recipe(){
            this->nOfIngredients = 0;
            this->contents = new char [0];
            strcpy(this->name, "");
        }
        Recipe(int nOfIngredients, char *name, char * contents){
            this->nOfIngredients = nOfIngredients;
            strcpy(this->name, name);
            // delete [] this->contents; this line cost me 2hours
            //you cannot delete something u havent created
            this->contents = new char [strlen(contents) + 1];
            strcpy(this->contents, contents);
        }
        Recipe& operator=(const Recipe& other){
            if(this != &other){
                copy(other);
            }
            return *this;
        }


        void print(){
            cout<<this->nOfIngredients<<endl<<this->name<<endl<<this->contents<<endl;
        }

         bool Eq(Recipe &other){
             if(strcmp(this->name, other.name) == 0)
                return true;
            else return false;
        }

      void set_num_ing(int num_ing){
          this->nOfIngredients = num_ing;
      }

      void set_name(char *name){
          strcpy(this->name, name);

      }

      void set_contents(char *contents){
          delete [] this->contents;
          this->contents = new char [strlen(contents) + 1];
          strcpy(this->contents, contents);
      }

      int get_ingredients()
      {
          return this->nOfIngredients;
      }


};

class RecipesBook{
  private:
        char name[100];
        Recipe *recipes;
        int nOfRecipes;
    public:
        RecipesBook(char *name = ""){
            strcpy(this->name, name);
            this->nOfRecipes = 0;
            recipes = new Recipe [0];
        }

        RecipesBook(const RecipesBook &other){
             strcpy(this->name, other.name);
            this->nOfRecipes = other.nOfRecipes;
            delete [] this->recipes;
            this->recipes = new Recipe [this->nOfRecipes];
            for(int i = 0; i<nOfRecipes; i++)
            {
                this->recipes[i] = other.recipes[i];
            }
        }

        RecipesBook& operator=(const RecipesBook &other){
            strcpy(this->name, other.name);
            this->nOfRecipes = other.nOfRecipes;
            delete [] this->recipes;
            Recipe *temp = new Recipe [other.nOfRecipes];
            for(int i = 0; i<nOfRecipes; i++)
            {
                temp[i] = other.recipes[i];
            }
            this->recipes = new Recipe [this->nOfRecipes];
            for(int i = 0; i<nOfRecipes; i++){
                this->recipes[i] = temp[i];
            }
            delete [] temp;

            return *this;

        }

    void add(Recipe &other){
        bool exists = false;
        for(int i = 0; i<nOfRecipes; i++)
        {
            if(other.Eq(this->recipes[i]) ){
                exists = true;
                break;
            }
        }

        if(!exists){
            Recipe *temp = new Recipe [nOfRecipes + 1];
            for(int i = 0; i<this->nOfRecipes; i++)
            {
                temp[i] = recipes[i];
            }
            temp[this->nOfRecipes] = other;
            this->nOfRecipes++;
            delete [] recipes;
          this->recipes = new Recipe [this->nOfRecipes];
            for(int i = 0; i<this->nOfRecipes; i++)
            {
                this->recipes[i] = temp[i];
            }
            delete [] temp;
        }
    }

    void print(){
        cout<<this->name<<endl;
        for(int i = 0; i<nOfRecipes; i++)
        {
            recipes[i].print();
        }
    }


    RecipesBook novaBrosura(Recipe &other){
        RecipesBook temp(this->name);
        for(int i = 0; i<this->nOfRecipes; i++)
        {
            if(other.get_ingredients() > recipes[i].get_ingredients())
            {
                Recipe tempRecipe = recipes[i];
                tempRecipe.set_num_ing(other.get_ingredients());
                temp.add(tempRecipe);
            }

        }
         return temp;

    }

    void set_num_recipes(int n)
    {
        this->nOfRecipes = n;
    }

    int get_num_recipes(){
        return this->nOfRecipes;
    }


};

// your code here

int main()
{
     Recipe rec;
    int n;
    char name[100], contents[200];
    int num_ing;
	cin >> name >> n;
    RecipesBook b1(name);
    Recipe last;
    for(int i = 0; i < n; i++){
    	cin >> num_ing >> name >> contents;
        Recipe r(num_ing, name, contents);
        b1.add(r);
        last = r;
    }
    b1.print();
    cin >> num_ing >> name >> contents;
    rec.set_num_ing(num_ing);
    rec.set_name(name);
    rec.set_contents(contents);
    b1.add(rec);
    b1.print();
    RecipesBook b2 = b1.novaBrosura(rec);
    b2.print();
    // testing copy constructor
    cout << "b2 copy" << endl;
    RecipesBook rb = b2;
    last.set_name("changed-name");
    rb.add(last);
    rb.print();
    cout << "original" << endl;
    b2.print();
	return 0;
}


