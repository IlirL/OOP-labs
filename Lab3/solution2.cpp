#include<iostream>
#include<cstring>
using namespace std;

class Worker{
    private:
        char firstName[30];
        char lastName[30];
        int salary;
    public:
        Worker(char *name = "name", char *surname = "surname", int salary = 0){
            strcpy(this->firstName, name);
            strcpy(this->lastName, surname);
            this->salary = salary;
        }

        int getSalary(){
            return this->salary;

        }

        void print(){
            cout<<this->firstName<<" "<<this->lastName<<" "<<this->salary<<endl;
        }
};


class Factory{

    private:
        Worker workers[100];
        int workersNumber;
    public:


        Factory(Worker w[], int size){
            this->workersNumber = size;
            for(int i = 0; i<workersNumber; i++)
            {
                this->workers[i] = w[i];
            }

        }

        void printWorkers(){
            for(int i = 0; i<workersNumber; i++)
            {
                workers[i].print();
            }
        }

        void printWithSalary(int salary){
            for(int i = 0; i<workersNumber; i++)
            {
                if(workers[i].getSalary() > salary)
                {
                    workers[i].print();
                }

            }
        }
};
int main()
{
    int n;
    cin>>n;
    cout<<"ALL WORKERS:"<<endl;

    Worker allWorkers[n];

    for(int i =0; i<n; i++)
    {
        char firstName[30],lastName[30];
        int salary;
        cin>>firstName>>lastName>>salary;
        allWorkers[i] = Worker(firstName, lastName, salary);
        // allWorkers[i].print();
        // cout<<endl;
    }

    int minSalary;
    cin>>minSalary;

    Factory f(allWorkers, n);
    f.printWorkers();
    cout<<"EMPLOYEES WITH SALARY "<<minSalary<<":"<<endl;
    f.printWithSalary(minSalary);

}
