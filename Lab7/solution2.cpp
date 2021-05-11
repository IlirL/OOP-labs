#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;

enum Color {red, green, blue};

class Shape{
    protected:
    Color color;
    char id[5];
    char *description;

    public:
    Shape( char *id, char *description,Color color){
        this->color = color;
        strcpy(this->id, id);
        this->description = new char [strlen(description) + 1];
        strcpy(this->description, description);
    }

    ~Shape(){
        delete [] this->description;
    }

    virtual double perimeter() = 0;
    virtual double area() = 0;
    virtual void draw() = 0;


    bool operator>(Shape &s)
    {
        if(this->perimeter() > s.perimeter())
            return 1;
        return 0;
    }

    char* getColor(){
        if(color == 0)
        {
            return "RED";
        }
        else if(color == 1)
        {
            return "GREEN";

        }

        return "BLUE";
    }

    char* getID(){
        return id;
    }

    char* getDescription(){
        return description;
    }
};

class Circle : public Shape{
    private:
    double radius;

    public:
    Circle(char *id, char *description,Color color, double radius) : Shape(id, description,color){
        this->radius = radius;
    }

    double area() override{
        return 3.14 * radius * radius;
    }

    double perimeter() override{
    return 3.14 *radius *2;
    }

    void draw() override{
        cout<<id<<" "<<color<<" "<<description<<" : circle "<<perimeter()<<" "<<area();
    }
};

class Square : public Shape{
    private:
    double a;

    public:
    Square(char *id, char *description,Color color,  double a) : Shape( id, description,color){
        this->a = a;
    }

    double area() override{
        return  a*a;
    }

    double perimeter() override{
    return 4*a;
    }

    void draw() override{
        cout<<id<<" "<<color<<" "<<description<<" type: square "<<perimeter()<<" "<<area();
    }
};


class Rectangle : public Shape{
    private:
    double a, b;

    public:
    Rectangle( char *id, char *description, Color color,double a, double b) : Shape( id, description,color){
        this->a = a;
        this->b = b;
    }

    double area() override{
        return a*b;
    }

    double perimeter() override{
    return a+b + a +b;
    }

    void draw() override{
        cout<<id<<" "<<color<<" "<<description<<" type: rectangle "<<perimeter()<<" "<<area();
    }
};


double totalArea(Shape **shapes, int n)
{
    double total_area = 0;
    for(int i = 0; i<n; i++)
    {
        total_area+=shapes[i]->area();
    }

    return total_area;
}

Shape *maxPerimeter(Shape ** shapes, int n){
    Shape *max_perimeter = shapes[0];
    for(int i = 1; i<n; i++)
    {
        if(shapes[i] -> perimeter() > max_perimeter -> perimeter())
        {
            max_perimeter = shapes[i];
        }
    }

    //circle, rectangle square
    // Circle *c = dynamic_cast<Circle*>(max_perimeter);
    // if(c!=0)
    // {
    //     return c;
    // }
    // Rectangle *r = dynamic_cast<Rectangle*>(max_perimeter);
    // if(r!=0)
    //     return r;

    // Square *s = dynamic_cast<Square*>(max_perimeter);

    // return s;
    return max_perimeter;
}

void drawAllFromType(Shape **shapes, int n, char *type){
            bool printed = false;

    for(int i = 0; i<n; i++)
    {

        if(strcmp(type, "circle") == 0)
        {
            //type is circle
            //lets see if shapes[i] is a circle
            Circle *c = dynamic_cast<Circle*>(shapes[i]);
            if(c!=NULL)
            {
                printed = true;
                cout<<shapes[i]->getID()<<" "<<shapes[i]->getColor()<<" "<<shapes[i]->getDescription()
                <<" type: circle "<<shapes[i]->perimeter()<<
                " "<<shapes[i]->area()<<endl;
            }
        }
        else if(strcmp(type, "rectangle") == 0)
        {
            Rectangle *r = dynamic_cast<Rectangle*>(shapes[i]);
            if(r!=NULL){
                printed = true;
                cout<<shapes[i]->getID()<<" "<<shapes[i]->getColor()<<" "<<shapes[i]->getDescription()
                <<" type: rectangle "<<shapes[i]->perimeter()<<
                " "<<shapes[i]->area()<<endl;        }}
        else if(strcmp(type, "square") == 0)
        {
            Square *s = dynamic_cast<Square*>(shapes[i]);
            if(s!=NULL)
            {
                printed = true;
                cout<<shapes[i]->getID()<<" "<<shapes[i]->getColor()<<" "<<shapes[i]->getDescription()
                <<" type: square "<<shapes[i]->perimeter()<<
                " "<<shapes[i]->area()<<endl;            }
        }
    }
    if(printed==false){
        cout<<"There are no shapes from type "<<type<<endl;
    }
}

int main () {

	int n;
	cin>>n;
	//cout<<n;
	Shape ** shapes = new Shape * [n];

	int type;
	char id [5];
	char description[20];
	int color;
	double radius, a, b;
	for (int i=0;i<n;i++) {
		cin>>type>>id>>description>>color;
		//cout<<i;
		switch(type) {
			case 0: //circle
			cin>>radius;
			shapes[i] = new Circle (id, description, (Color) color, radius);
			break;
			case 1: //square
			cin>>a;
			shapes[i] = new Square (id, description, (Color) color, a);
			break;
			case 2: //rectangle
			cin>>a>>b;
			shapes[i] = new Rectangle (id, description, (Color) color, a, b);
			break;
			default:
			break;

		}
	}


	cout<<"Total area: "<<totalArea(shapes,n)<<endl;
	cout<<"Max perimeter of a shape is: "<<(maxPerimeter(shapes,n))->perimeter()<<endl;

	cout<<"Draw only circles"<<endl;
	drawAllFromType(shapes,n,"circle");

	cout<<"Draw only squares"<<endl;
	drawAllFromType(shapes,n,"square");

	cout<<"Draw only rectangle"<<endl;
	drawAllFromType(shapes,n,"rectangle");

	return 0;

}


