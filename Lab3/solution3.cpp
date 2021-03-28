
// your code here
#include<iostream>
#include<cstring>
using namespace std;
class Table{
    int width;
    int height;
    public:
        Table(int width = 0, int height = 0){
            this->width = width;
            this->height = height;
        }

        void print(){
           cout<<"Table: "<<this->width<<" "<<this->height<<" ";
        }
};


class Room{
    int length;
    int width;
    Table table;

    public:
        Room(){

        }
        Room(int width, int length, Table &table){
            this->width = width;
            this->length = length;
            this->table = table;
        }

        void print(){
            cout<<"Room: "<<this->width<<" "<<this->length<<" ";
            this->table.print();
        }
};

class House{
    Room room;
    char address[50];

    public:
        House(Room &room, char *address){
            this->room = room;
            strcpy(this->address, address);
        }

        void print(){
            cout<<"Address: "<<this->address<<" ";
            this->room.print();
            cout<<endl;

        }
};

int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
    	int tableWidth, tableHeight;
        cin>>tableWidth;
        cin>>tableHeight;
    	Table t(tableWidth, tableHeight);
    	int rw, rl;
        cin>>rw;
        cin>>rl;
    	Room r(rw, rl, t);
    	char adresa[30];
        cin>>adresa;
    	House h(r,adresa);
    	h.print();

	}

    return 0;
}
