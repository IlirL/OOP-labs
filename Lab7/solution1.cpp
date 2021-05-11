#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

#define my_pi 3.14

class Toy {
public:
    virtual float getVolume() = 0;
    virtual float getWeight() = 0;
};

class Shape {
protected:
    char color[100];
    int density;
public:
    // methods definition here

    //constructor
    Shape(char *color, int density){
        this->density = density;
        strcpy(this->color,color);
    }


};

class Ball : public Toy, public Shape{
    private:
    int radius;

    public:
    //constructor
    Ball(char *color, int density, int radius) : Shape(color, density){
        this->radius = radius;
    }

    float getVolume(){
        return 4 * radius* radius* radius * my_pi / 3;
    }

    float getWeight() override{
        return getVolume() * density;
    }


};

class Cube : public Toy, public Shape{
    private:
    int height, width, depth;

    public:
    Cube(char *color, int density, int height, int width, int depth) : Shape(color, density){
        this->height = height;
        this->width = width;
        this->depth = depth;
    }

    float getVolume(){
        return height * width * depth;
    }

    float getWeight() override{
        return getVolume() * density;
    }
};




int main(){
	//enter the toys informain
	int n;
	cin>>n;

	Toy **toys = new  Toy * [n];
	  char color[50];
        int density;
        int radius;
        int height, width, depth;
        int greater_volume_toy = 0;
        float total_weight = 0;
    for(int i = 0; i<n; i++)
    {
        int type;
        cin>>type;


        if(type == 1)
        {
            //insert Ball
                    cin>>color>>density>>radius;
            toys[i] = new Ball(color, density, radius);
        }
        else if(type ==2)
        {
            cin>>color>>density>>height>>width>>depth;
            toys[i] = new Cube(color, density, height, width,depth);
        }

        total_weight += toys[i] -> getWeight();
        if(toys[i]->getVolume() > toys[greater_volume_toy]->getVolume())
            greater_volume_toy = i;

    }
    //enter the Petra's cube information
    cin>>color>>density>>height>>width>>depth;
    Toy *petraCube = new Cube(color, density, height,width, depth);

	//1

    if(total_weight > petraCube -> getWeight())
        cout<<"YES"<<endl;
    else
     cout<<"NO"<<endl;
	//2
    cout<<"The difference is: "<<abs(toys[greater_volume_toy]->getVolume() - petraCube -> getVolume());

	return 0;
}
