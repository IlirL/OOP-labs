
#include<iostream>
#include<string.h>
using namespace std;

// Your code here

class Bill{
    private:
            char *bill_number;
            int expense;
            char date[10];
            bool status;
    public:
        //constructors
        Bill(){
            this->bill_number = new char [0];
            this->expense = 0;
            strcpy(this->date, "");
            this->status = false;
        }

        Bill(char *bill_number, int expense, char *date, bool status){
            this->bill_number = new char [strlen(bill_number) + 1];
            strcpy(this->bill_number, bill_number);
            strcpy(this->date, date);
            this->expense = expense;
            this->status = status;

        }
        //end of default constructors

        //we need copy operator
        Bill(const Bill &other){
                delete [] this->bill_number;
             this->bill_number = new char [strlen(other.bill_number) + 1];
            strcpy(this->bill_number, other.bill_number);
            strcpy(this->date, other.date);
            this->expense = other.expense;
            this->status = other.status;
        }

        Bill& operator=(const Bill &other)
        {
             delete [] this->bill_number;
             this->bill_number = new char [strlen(other.bill_number) + 1];
            strcpy(this->bill_number, other.bill_number);
            strcpy(this->date, other.date);
            this->expense = other.expense;
            this->status = other.status;

            return *this;
        }

        //operator ==
        bool operator==(const Bill &other){
            return strcmp(this->bill_number, other.bill_number) == 0;
        }

        //operator <<
       friend ostream& operator<<(ostream &o, Bill &a);


       //get methods
       char *get_bill_number(){
           return this->bill_number;
       }

       bool get_status(){
           return this->status;
       }

       char *get_date(){
           return this->date;
       }

       int get_expense(){
           return this->expense;
       }
};


ostream& operator<<(ostream &o, Bill &a) {
            o<<""<<a.bill_number<<"("<<a.date<<") - "<<a.expense<<""<<endl;
            return o;
}


class UserProfile{
  private:
    char username[30];
    Bill bills_array[30];
    int n_of_bills;
  public:
    //constructors
    UserProfile(char *name = ""){
        strcpy(this->username, name);
        this->n_of_bills = 0;
    }

    void operator+=( Bill &bill){
        bool bill_exists = false;
        for(int i = 0; i<this->n_of_bills; i++)
        {
            if(strcmp(bill.get_bill_number(), this->bills_array[i].get_bill_number()) == 0)
            {
                cout<<"The bill already exists"<<endl;
                bill_exists = true;
                break;
            }
        }
        if(!bill_exists){
            this->bills_array[this->n_of_bills] = bill;
            this->n_of_bills = this->n_of_bills+1;
        }
    }

    friend ostream& operator<<(ostream &o, const UserProfile &user_profile);

    int totalDue(int m, int y){
        int total = 0;
        // cout<<"Total due for month "<<m<<" and year "<<y<<" is:";
        for(int i = 0; i<this->n_of_bills; i++){
            string mAndy = this->bills_array[i].get_date();
            int month = stoi(mAndy.substr(0,2));
            int year = stoi(mAndy.substr(3,4));

            if(month == m && year == y){
                total += this->bills_array[i].get_expense();
                 }
        }
        //  cout<<total<<endl;
        return total;

    }

    char* get_username()
    {
        return this->username;
    }
    int get_n_bills(){
        return this->n_of_bills;
    }

    Bill & get_bill(int index){
        return this->bills_array[index];
    }
};


ostream& operator<<(ostream &o, UserProfile &user_profile){
    o<<"Unpaid bills of user "<<user_profile.get_username()<<" are:"<<endl;
    for(int i = 0; i<user_profile.get_n_bills(); i++)
    {
        if(user_profile.get_bill(i).get_status() == false){
            // o<<user_profile.bills_array[i];
            // cout<<"ilir"<<endl;
            cout<<user_profile.get_bill(i);

        }
    }
    return o;
}

int main() {
    char number[50], month[8], name[50];
    int price, n;
    bool status;


    int type;
    cin >> type;

    if (type == 1) {
        cout << "-----Test Bill & operator &lt;&lt;-----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b(number, price, month, status);
        cout<<b;
    }
     else if (type == 2) {
        cout << "-----Test Bill & operator == -----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b1(number, price, month, status);
        cin >> number >> price >> month >> status;
        Bill b2(number, price, month, status);
        if (b1 == b2) cout << "Equal" << endl;
        else cout << "Not equal" << endl;

    } else if (type == 3) {
        cout << "-----Test UserProfile & operator += &&lt;&lt; -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        cout << up;
    } else if (type == 4) {
        cout << "-----Test UserProfile & operator += & totalDue -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    } else if (type == 5) {
        cout << "-----Test all -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        cout << up;
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    }

    return 0;
}
