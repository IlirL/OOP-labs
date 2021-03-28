
#include<iostream>
#include<cstring>

using namespace std;

enum Color{RED, GREEN , BLUE};

class Shape{

    private:
    Color color;
    char id[5];
    double area;

    public:

    Shape(){

    }
    Shape(char *id, Color color, double area){
        strcpy(this->id, id);
        this->color = color;
        this->area = area;

    }

    void draw(){
        if(this->color == RED)
        {
             cout<<this->id<<" "<<"RED"<<" "<<this->area<<endl;
        }
        else if(this->color == GREEN){
            cout<<this->id<<" "<<"GREEN"<<" "<<this->area<<endl;
        }
        else{
            cout<<this->id<<" "<<"BLUE"<<" "<<this->area<<endl;
        }
    }

    Color getColor(){
        return this->color;
    }

    double getArea(){
        return this->area;
    }

    void halfArea(){
        this->area/=2;
    }

};

class Canvas{

    Shape shapes[100];
    int nOfShapes;

    public:
        Canvas(){
            this->nOfShapes = 0;
        }

        void addShape(Shape &s){
            this->shapes[this->nOfShapes++] = s;
        }

        void drawAll(){
            for(int i = 0; i<this->nOfShapes; i++)
            {
                shapes[i].draw();
            }
        }

        void drawOnly(Color color){
            for(int i = 0; i<this->nOfShapes; i++)
            {
                if(shapes[i].getColor() == color){
                    shapes[i].draw();
                }
            }
        }

        double totalArea(){
            double total = 0;
            for(int i=  0; i<nOfShapes; i++)
            {
                total+=shapes[i].getArea();
            }

            return total;
        }

       int getNofShapes(){
           return this->nOfShapes;
       }

      Canvas (Canvas *other){
          this->nOfShapes = other->getNofShapes();
          for(int i = 0; i<this->nOfShapes; i++)
          {
              this->shapes[i] = other->shapes[i];
              this->shapes[i].halfArea();
          }
      }

       Canvas getHalfCanvas(){
            // Canvas tempCanvas = this;
            Canvas tempCanvas = this;
            return tempCanvas;

        }

};


int main () {

	int n;
	cin>>n;
	cout<<"ADITION OF SHAPES IN THE CANVAS"<<endl;
	Canvas canvas;

	for (int i=0;i<n;i++) {
		char id [5];
		int color;
		double area;

		cin>>id>>color>>area;
		Shape s (id, (Color) color, area);
		canvas.addShape(s);
	}

	cout<<"TESTING DRAW ALL"<<endl;

	canvas.drawAll();

	cout<<"TESTING DRAW RED SHAPES"<<endl;

	canvas.drawOnly(RED);

	cout<<"TESTING TOTAL AREA"<<endl;

	cout<<canvas.totalArea()<<endl;

	cout<<"TESTING HALF CANVAS"<<endl;
	Canvas reducedCanvas = canvas.getHalfCanvas();
	cout<<canvas.totalArea()<<" "<<reducedCanvas.totalArea()<<endl;

	if (reducedCanvas.totalArea() == canvas.totalArea()) {
		cout<<"DO NOT CHANGE THE AREA OF THE OBJECT IN THE CURRENT CANVAS. JUST IN THE NEW CANVAS"<<endl;
	}

	return 0;
}
