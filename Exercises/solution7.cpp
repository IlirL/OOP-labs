#include<iostream>
#include<cstring>

using namespace std;

class Exception{
    private:
    char text[50];

    public:
    Exception(char *text){
        strcpy(this->text, text);
    }

    void message(){
        cout<<text<<endl;
    }
};

class DonationAction{
    protected:
    char *name;
    char id[50];
    int collected_fund;
    int needed_fund;

    public:
    DonationAction(char *name, char *id,int needed_fund){
       try
        {
             strcpy(this->id, id);
            if(strlen(this->id) > 9)
                throw Exception("The id number has more than 9 characters");
            else if(!alldigits(this->id)){
                throw Exception("The id number has a non-digit character");
            }
        }
        catch(Exception e){
            e.message();
           this->~DonationAction();
        }
        this->collected_fund = 0;
        this->needed_fund = needed_fund;


        this->name = new char [strlen(name) + 1];
        strcpy(this->name, name);
    }
    DonationAction()
    {
        this->name = new char[0];

    }

    ~DonationAction(){
        // cout<<"destructor called"<<endl;
    }

    friend ostream& operator<<(ostream &o, DonationAction &d)
    {
        if(d.collected_fund >= d.needed_fund)
                o<<d.id<<" "<<d.name<< " collected"<<endl;
        else
        o<<d.id<<" "<<d.name<<" "<<d.needed_fund - d.collected_fund<<" more denars are needed"<<endl;
    }

    DonationAction& operator+=(int donation){
        collected_fund+=donation;
        return *this;
    }

    bool operator<(DonationAction &d)
    {
        int this_difference = 0, d_difference = 0;
        this_difference = this->needed_fund - this->collected_fund;
        d_difference = d.needed_fund - d.collected_fund;

        if(this_difference == d_difference)
        {
            if(strcmp(this->id, d.id) < 0)
                return 1;
            else
                return 0;
        }

        return this_difference < d_difference;
    }

     bool alldigits(char id[])
    {
        int i = 0;
        while(id[i] != NULL)
        {
            if(id[i] > '9' || id[i] < '0')
                return 0;
            i++;

        }
        return 1;
    }

    char *getID(){
        return id;
    }

   //copy constructor
   DonationAction& operator=(DonationAction &d)
   {
       strcpy(this->id, d.id);
        this->collected_fund = d.collected_fund;
        this->needed_fund = d.needed_fund;
         delete[]this->name;
         this->name = new char [strlen(d.name) + 1];
        strcpy(this->name, d.name);

        return *this;
   }
};


class DonationSociety{
    private:
    char name[50];
    DonationAction *donations;
    int n;

    public:
    DonationSociety(char *name){
        strcpy(this->name, name);
        donations = new DonationAction [0];
        n = 0;
    }



    bool takeDonation(char id[], int donateFund)
    {

       for(int i = 0; i<n; i++)
       {
            if(strcmp(donations[i].getID(), id) ==0)
                {
                    //update
                    donations[i]+=donateFund;
                    return 1;
                }

       }

       return 0;
    }


    bool exists_id(char id[])
    {
        for(int i=0; i<n; i++)
        {
            if(strcmp(id, donations[i].getID()) == 0)
            {
                return 1;
            }
        }

        return 0;
    }

    DonationSociety& operator+=(DonationAction &d)
    {
        if(exists_id(d.getID()))
            return *this;
        if(strlen(d.getID()) > 9 || !d.alldigits(d.getID())){
            return *this;
        }

        DonationAction *temp = new DonationAction[n+1];
        for(int i =0;i<n; i++)
        {
            temp[i] = donations[i];
        }
        temp[n] = d;

        delete[]donations;
        donations = new DonationAction [++n];
        for(int i =0;i <n; i++)
        {
            donations[i] = temp[i];
        }

        delete[]temp;

        return *this;
    }

    void sort(){
        for(int i = 1; i<n; i++)
        {
            if(i==0)
                continue;
            // if(strcmp(this->donations[i-1].getID(), this->donations[i].getID()) < 0)
            if(this->donations[i-1] < this->donations[i])
            {
                DonationAction temp;
                temp = donations[i-1];
                donations[i-1] = donations[i];
                donations[i] = temp;

                i-=2;
            }
        }
    }

    friend ostream& operator<<(ostream &o, DonationSociety& d)
    {
        d.sort();
        for(int i=0; i<d.n; i++)
        {
            o<<d.donations[i];
        }
        o<<"President:"<<d.name<<endl;

        return o;
    }

};

//your code

int main(){


	DonationSociety donacii("Velko Velkovski");
	int n;
	char naziv[50],id[50];
	int potrebnasuma,doniranasuma;
	cin>>n;

	for (int i=0;i<n;i++){
        cin.get();
		cin.getline(naziv,50);
		cin>>id>>potrebnasuma;

		DonationAction edna(naziv,id,potrebnasuma);
		donacii+=edna;

    }

	//donation
	cin>>n;
	for (int i=0;i<n;i++){

		cin>>id>>doniranasuma;

		if(!donacii.takeDonation(id,doniranasuma))
			cout<<"The donation is not taken. Wrong ID."<<endl;
	}
    cout<<"==============="<<endl;
	cout<<donacii;

}

