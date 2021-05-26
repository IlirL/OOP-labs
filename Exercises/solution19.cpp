#include <iostream>
#include <string.h>
using namespace std;

// your code here
class Parcel{
    protected:
    int id;
    static int processing_price;

    public:

    Parcel(int id = 0){
        this->id = id;
    }

    static void setProcessingPrice(int i){
        Parcel::processing_price =i;
    }

    int getId(){
        return id;
    }
};
int Parcel::processing_price = 150;
class Envelope : public Parcel{
    private:
    int width, height;
    char receiver[50];

    public:
    Envelope(int id = 0, char *receiver = "", int width = 0, int height = 0) : Parcel(id)
    {
        this->width = width;
        this->height = height;
        strcpy(this->receiver, receiver);
    }

    int price(){
        return processing_price + height * width * 0.3;
    }


    char *getReceiver(){
        return receiver;
    }

    Envelope& operator=(Envelope &e){
        this->id = e.id;
        this->width = e.width;
        this->height = e.height;
        strcpy(this->receiver, e.receiver);

        return *this;
    }

};

class PostOffice{
    private:
    Envelope envelopes[100];
    int n;

    public:
    PostOffice(){
        this->n = 0;
    }


    int sendEnvelope(int id, char *receiver, int height, int width){
        Envelope temp(id, receiver, width, height);
        envelopes[n++] = temp;
        // envelopes[n++] = Envelope(id, receiver, width, height);
        return envelopes[n-1].price();
    }

    void printEnvelopsTo(char* receiver) {
        cout<<"For "<<receiver<<" are envelops with ids: ";
        for(int i = 0; i<n; i++)
        {
            if(strcmp(receiver, envelopes[i].getReceiver()) == 0)
            {
                cout<<envelopes[i].getId()<<" ";
            }
        }

        cout<<endl;

    }
};


int main() {

    int type;
    int n;
    int price;
    int id;
    int height, width;
    char receiver[50];

    PostOffice p;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> type;
        if (type == 1) { // send envelope
            cin >> id >> receiver >> width >> height;
            cout << "The price of sending envelope with id " << id << " is:" << p.sendEnvelope(id, receiver, width, height) << endl;
        } else if (type == 2) { // print envelops to
            cin >> receiver;
            p.printEnvelopsTo(receiver);
        } else if (type == 3) { // set processing price
            cin >> price;
            Parcel::setProcessingPrice(price);
        } else if (type == 4) { // Parcel
            cin >> id;
            Parcel p1(id);
            cout << "Parcel with id [" << p1.getId() << "] is created" << endl;
        } else {// Envelope
            cin >> id >> receiver >> width >> height;
            Envelope p2(id, receiver, width, height);
            cout << "Price of sending envelope with ID: " << p2.getId() << " To: " << p2.getReceiver() << " is: " << p2.price() << endl;
        }
    }
    return 0;
}

