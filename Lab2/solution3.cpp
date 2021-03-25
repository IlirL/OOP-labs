
//Problem 3

#include <iostream>
#include <cstring>
using namespace std;

// your code here

class Film{
        private:
    char name[100];
    char director[50];
    char genre[50];
    int year;

        public:
    Film(){};
    Film(char *_name, char *_director, char *_genre, int _year){
        strcpy(name, _name);
        strcpy(director, _director);
        strcpy(genre, _genre);
        year = _year;
    }

    void printFilmInfo(){
        cout<<"Name: "<<name<<endl;
        cout<<"Director: "<<director<<endl;
        cout<<"Genre: "<<genre<<endl;
        cout<<"Year: "<<year<<endl;
    }

    int getYear(){
        return year;
    }
};

void print_by_year(Film *f, int n, int year)
{
    for(int i = 0; i<n; i++)
    {
        if(f->getYear() == year)
            f -> printFilmInfo();
        f++;
    }
}
int main() {
 	int n;
 	cin >> n;
 	//declare array of n film objects
    Film films[n];

 	for(int i = 0; i < n; ++i) {
 		char name[100];
 		char director[50];
 		char genre[50];
 		int year;
 		cin >> name;
 		cin >> director;
 		cin >> genre;
 		cin >> year;
 		//instanciate the object
        films[i] = Film(name, director, genre, year);
 	}
 	int year;
 	cin >> year;
 	// call the function print by year
    print_by_year(&films[0], n, year);

 	return 0;
 }
