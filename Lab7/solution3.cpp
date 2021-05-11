#include<iostream>
#include<cstring>
using namespace std;

// your code here

class Vehicle{
    protected:
    int mass, width, height;

    public:
    //constructors and destructor
    Vehicle(int mass, int width, int height)
    {
        this->mass = mass;
        this->width = width;
        this->height = height;
    }

    ~Vehicle(){
    }

    int getMass(){
        return mass;

    }
    int getWidth(){
        return width;
    }
    int getHeight(){
        return height;
    }


    virtual int dailyPrice() = 0;
};

class Automobile : public Vehicle{
    private:
    int n_of_doors;

    public:
      Automobile(int mass, int width, int height, int n_of_doors) : Vehicle( mass,  width,  height){
        this->n_of_doors= n_of_doors;
    }

    int dailyPrice() override{
        if(n_of_doors<5)
            return 100;
        return 130;
    }
};

class Bus : public Vehicle{
    private:
    int n_of_passengers;

    public:
    Bus(int mass, int width, int height, int n_of_passengers) : Vehicle( mass,  width,  height){
        this->n_of_passengers= n_of_passengers;
    }
    int dailyPrice() override{
       return  5 * n_of_passengers;
    }
};

class Truck : public Vehicle{
    private:
    int max_weight;

    public:
      Truck(int mass, int width, int height, int max_weight) : Vehicle( mass,  width,  height){
        this->max_weight= max_weight;
    }
    int dailyPrice() override{
       return  (mass + max_weight) * 0.02;
    }

};

class Parking{
    private:
        Vehicle **vehicles;
        int n_of_vehicles;
        int automobiles;
        int busses;
        int trucks;
    public:
    //default constructor
    Parking(){
        vehicles = new Vehicle *[0];
        n_of_vehicles = 0;
        automobiles = 0;
        busses = 0;
        trucks = 0;
    }

    ~Parking(){
        delete [] vehicles;
    }

    int type(Vehicle *v){
        // char type_of_vehicle[20];
        // strcpy(type_of_vehicle, "ilir2222");
        // cout<<"t1"<<endl;
        Automobile *a = dynamic_cast<Automobile*>(v);
        Bus *b = dynamic_cast<Bus*>(v);
        Truck *t = dynamic_cast<Truck*>(v);
                // cout<<"t2"<<endl;
        // cout<<a<<" "<<b<<" "<<t<<"  the end"<<endl;
        if(a!=NULL){
            // strcpy(type_of_vehicle, "automobile");
            // cout<<"we are in with type_of_vehicle = "<<type_of_vehicle<<endl;
            // return type_of_vehicle;
            return 1;

        }
        else if(b!=NULL){
            //   strcpy(type_of_vehicle, "bus");
            // return type_of_vehicle;
            return 2;
        }
        else if(t!=NULL){
            //   strcpy(type_of_vehicle, "truck");
            // return type_of_vehicle;
            return 3;
        }
                // cout<<"t3"<<endl;

    // cout<<"we are in with type_of_vehicle = "<<type_of_vehicle<<endl;

    }

    Parking& operator+=(Vehicle *v){
        Vehicle ** temp_vehicles = new Vehicle *[n_of_vehicles + 1];
        for(int i = 0; i<n_of_vehicles; i++)
        {
            temp_vehicles[i] = vehicles[i];
        }
        temp_vehicles[n_of_vehicles] = v;

        delete [] vehicles;

        vehicles = new Vehicle * [++n_of_vehicles];
        for(int i = 0; i<n_of_vehicles; i++)
        {
            vehicles[i] = temp_vehicles[i];
        }

        delete[]temp_vehicles;

        //here in the end I want to see what vehicle i put in;
        // char type_of_v_vehicle[20];

        // problem: function type
        // type(v);
        // if(strcmp(type(v), "automobile") == 0)
        // {
        //     automobiles++;
        // }
        if(type(v) == 1)
        {
            automobiles++;
        }
        else if(type(v) ==2)
        {
            busses++;
        }
        else if(type(v) ==3)
        {
            trucks++;
        }
        // else if(strcmp(type(v), "bus") == 0)
        // {
        //     busses++;
        // }
        // else if(strcmp(type(v), "truck") == 0)
        // {
        //     trucks++;
        // }
        return *this;
    }


    float totallMass(){
        float total_mass = 0;
        for(int i = 0; i<n_of_vehicles; i++)
        {
            total_mass += vehicles[i]->getMass();
        }
        return total_mass;
    }

    int vehiclesWiderThan(int width){
        int wider = 0;
        for(int i = 0; i<n_of_vehicles; i++){
            if(vehicles[i]->getWidth() > width)
                wider++;
        }
        return wider;
    }

    void print(){
        cout<<"Automobiles: "<<automobiles<<endl<<"Busses: "<<busses<<endl<<"Trucks: "<<trucks<<endl;
    }

    int greaterMaxWeightThan(Vehicle &v){
        int trucks_heavier = 0;
        for(int i = 0; i<n_of_vehicles; i++)
        {
            // if(strcmp(type(vehicles[i]), "truck") == 0)
            if(type(vehicles[i]) == 3)
            {
                if(vehicles[i]->getMass() > v.getMass())
                {
                    trucks_heavier++;
                }
            }
        }
        return trucks_heavier;
    }

    int dailyProfit(){
        int profit = 0;

        for(int i = 0; i<n_of_vehicles; i++)
        {
            // cout<<"vehicle["<<i<<"] = type"<<type(vehicles[i])<<endl;
            // cout<<vehicles[i]->dailyPrice()<<endl;
            profit+=(vehicles[i]->dailyPrice());
        }
    return profit;

    }


};



int main() {
    Parking p;
    int n;
    cin >> n;
    int width, height, broj;
    float mass, max_weight;
    // cout<<"1"<<endl;
    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;
        // cout<<"2"<<endl;
        if (type == 1) {
            cin >> mass >> width >> height >> broj;
            Automobile *a = new Automobile(mass, width, height, broj);
            // cout<<"ilir"<<endl;
            p += a;
            // cout<<"ilir1"<<endl;
        }
        if (type == 2) {
            cin >> mass >> width >> height >> broj;
            p += new Bus(mass, width, height, broj);
        }
        if (type == 3) {
            cin >> mass >> width >> height >> max_weight;
            p += new Truck(mass, width, height, max_weight);
        }
        // cout<<"3"<<endl;
    }

    p.print();
    cout << "\nDaily profit: " << p.dailyProfit() << endl;
    cout << "Total mass: " << p.totallMass() << endl;
    cout << "Number wider then 5 is: " << p.vehiclesWiderThan(5) << endl;
    Automobile a(1200, 4, 3, 5);
    cout << "Number of trucks with max weight larger then the automobile is: " << p.greaterMaxWeightThan(a) << endl;
    return 0;
}

