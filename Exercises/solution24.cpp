#include<iostream>
#include<string.h>
using namespace std;

//your code here

class InvalidTimeException{
    public:
    InvalidTimeException(){

    }
    void message(){
        cout<<"Invalid Time"<<endl;
    }
};

class Race{
    protected:
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;

    public:

    Race(char *city = "", int year = 0, int month = 0, float bestTime = 0, float length = 0){
        strcpy(this->city, city);
        this->year=  year;
        this->month = month;
        this->bestTime = bestTime;
        this->length = length;
    }

   virtual float complexity()
    {
        return bestTime / length;
    }

    friend ostream& operator<<(ostream& o, Race &r)
    {
        o<<r.city<<" "<<r.month<<"."<<r.year<<" "<<r.complexity()<<endl;

        return o;
    }

};

class MotoGPRace : public Race{
    private:
    float *bestTimes;
    int n_besttimes;
    int n_laps;
    static float coefficient;
    public:
    MotoGPRace() : Race()
    {
        this->bestTimes=  new float [0];
    }
    MotoGPRace(char *city , int year, int month, float bestTime, float length) : Race(city, year, month, bestTime, length){
                this->bestTimes=  new float [0];
                this->n_besttimes = 0;
                this->n_laps = 0;

    }
    MotoGPRace(char *city , int year, int month, float bestTime, float length, float bestTimes[], int n_besttimes, int n_laps) : Race(city, year, month, bestTime, length)
    {
        this->bestTimes = new float[n_besttimes];
        this->n_besttimes = n_besttimes;
        for(int i = 0; i<n_besttimes; i++)
        {
            this->bestTimes[i] = bestTimes[i];
        }
        this->n_laps = n_laps;
    }
    // ~MotoGPRace(){
    //     cout<<"destructor called";
    //     delete [] bestTimes;
    // s}
    float complexity(){
        //calculate the average of the best times
        float average  = 0;
        for(int i = 0; i<n_besttimes; i++)
        {
            average+=bestTimes[i];
        }
        average /= n_besttimes;

        float complexity_variable = 0;
        complexity_variable = average * coefficient;
        complexity_variable+=Race::complexity();
        if(n_laps > 22)
        {
            complexity_variable+=complexity_variable*0.2;
        }

        return complexity_variable;


    }


    MotoGPRace operator+=(float newTime)
    {
        // InvalidTimeException ilir;
        // ilir.message();
        // float tempTimes[this->n_besttimes+1];
         try{

          if(newTime < 9.5){

            throw InvalidTimeException();
             }

        //  throw InvalidTimeException();
        float tempTimes[this->n_besttimes+1];
        // cout<<"good";
        for(int i = 0; i<this->n_besttimes; i++)
        {
            tempTimes[i] = this->bestTimes[i];
        }

        tempTimes[n_besttimes] = newTime;
        delete[] bestTimes;
        bestTimes = new float [++n_besttimes];
        for(int i = 0; i<n_besttimes; i++)
        {
            bestTimes[i] = tempTimes[i];
        }
                }

        catch(InvalidTimeException i)
        {

            i.message();
            return *this;
        }
        // cout<<"ilir";
         return *this;

    }

    MotoGPRace operator++(int i){
        MotoGPRace old;
        old = *this;
        // cout<<"good"<<endl;
        // cout<<old.getNumberLaps()<<endl;
        this->n_laps++;

        return old;
    }

    void setNumberLaps(int l)
    {
        n_laps = l;
    }

    int getNumberLaps(){
        return n_laps;
    }

    static void setK(float k)
    {
        MotoGPRace::coefficient = k;
    }
    MotoGPRace& operator=(MotoGPRace &m)
    {
        delete [] bestTimes;
        this->bestTimes = new float[m.n_besttimes];
        this->n_besttimes = m.n_besttimes;
        for(int i = 0; i<m.n_besttimes; i++)
        {
            this->bestTimes[i] = m.bestTimes[i];
        }
        this->n_laps = m.n_laps;
        strcpy(this->city, m.city);
        this->year = m.year;
        this->month = m.month;
        this->bestTime = m.bestTime;
        this->length = m.length;
    }
};

float MotoGPRace:: coefficient = 0.4;


int main(){
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int choice;
    int numberLaps;

    if (testCase == 1){
        cout << "===== Testing - classes ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        Race t(city, year, month, bestTime, length);
        cout<<t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes, n, numberLaps);
        cout << mgt;
        MotoGPRace mgt2;
    }
    if (testCase == 2){
        cout << "===== Testing - operatorot += ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        // add a new best time
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace* nn = dynamic_cast<MotoGPRace*>(rArray[i]);
            if (nn != 0){
                flag = 0;
                (*nn) += best;
                break;
            }
        }

        // print the races
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }
    if (testCase == 3){
        cout << "===== Testing - exceptions ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        MotoGPRace mgt(city, year, month, bestTime, length);

        // cout<<"good";
        mgt.setNumberLaps(numberLaps);

        float time1,time2;
        cin>>time1>>time2;
        //  cout<<"good";
        mgt+=time1;
        mgt+=time2;

        cout<<mgt;
    }
    if (testCase == 4){
        cout <<"===== Testing - operator++ ======"<<endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];

        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes,n,numberLaps);
        // cout<<"good"<<endl;
        float v,koef2;
        cout<<(mgt++).getNumberLaps()<<endl;
        // cout<<"good"<<endl;
        cout<<mgt;
        mgt++;
        cout<<mgt;
    }
    if (testCase == 5){
        cout << "===== Testing - coefficient ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        MotoGPRace::setK(0.7);
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    if (testCase == 6){
        cout << "===== Testing - full functionality ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        float newCoef;
        cin>>newCoef;
        MotoGPRace::setK(newCoef);
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        // print the races
        float newBest;
        cin>>newBest;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace * pok= dynamic_cast<MotoGPRace *>(rArray[i]);
            if(pok!=0)
            {
                (*pok)++;
                (*pok)+=newBest;
                if(flag==1)
                {
                    flag = 0;
                    *pok+=1.4;

                }
            }
        }
        cout << "\nList of the races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    return 0;
}
