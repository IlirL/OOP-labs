

//Problem 2


#include <iostream>
using namespace std;

class Circle {
private:
float radius;
const float pi = 3.14;
public:
Circle(float _radius = 0)
{
    radius = _radius;
}
~Circle(){};

float perimeter(){
    return radius * 2 * pi;
};

float area(){
    return radius * radius * pi;
};

bool equal(){
    if(perimeter() == area())
        return 1;
    return 0;
}

};

int main() {
	float r;
	cin >> r;
	//instanciate object from class Circle
    Circle c(r);
	cout << c.perimeter() << endl;
	cout << c.area() << endl;
	cout << c.equal() <<endl;
	return 0;
}
