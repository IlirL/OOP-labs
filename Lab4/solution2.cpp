#include<iostream>
#include<cstring>

using namespace std;


enum Color
{ RED, GREEN, BLUE };

class Shape
{
private:
  Color color;
  char id[5];
  char *description;
  double area;

  void copyClass(const Shape &other){
      this->color = other.color;
      this->area = other.area;
      strcpy(this->id, other.id);
      delete [] this->description;
      description = new char [strlen(other.description) +  1];

      strcpy(this->description, other.description);
  }

public:
  Shape ()
  {
    this->color = RED;
    strcpy (this->id, "");
    description = new char[0];
    this->area = 0.0;
  }

  Shape (char *id, char *description, Color color,   double area)
  {
    this->color = color;
    strcpy (this->id, id);
    this->area = area;
    this->description = new char[strlen (description) + 1];
     strcpy (this->description, description);

  }



//   ~Shape ()
//   {
//     delete[]this->description;
//   }

  //Equal operator

    Shape& operator=(const Shape &other){
        copyClass(other);
        return *this;
    }

  //set methods
    void set_area(double area){
        this->area = area;
    }
  //get methods
    char* get_id(){
        return this->id;
    }

    Color get_color(){
        return this->color;
    }

    double get_area(){
        return this->area;
    }
    //print stuff
  void draw()
  {
        char colorToString[10];
        if(this->color == 0)
        {
            strcpy(colorToString, "RED");
        }
        if(this->color == 1)
        {
            strcpy(colorToString, "GREEN");
        }
        if(this->color == 2)
        {
            strcpy(colorToString, "BLUE");
        }
        cout << this->id << " " << colorToString << " " << this->area << " [" << this->description <<"]"<< endl;
  }
};

class Canvas
{
  Shape *shapes;
  int nOfshapes;

public:
  //Constructors
    Canvas ()
  {
    this->shapes = new Shape[0];
    this->nOfshapes = 0;
  }

    //copyConstructor
    Canvas (const Canvas &other){
        //Be careful
        //I am first going to create an object so that it gets the initial values
        this->nOfshapes = other.nOfshapes;
        delete[] this->shapes;

        this->shapes = new Shape [other.nOfshapes];
        for(int i = 0; i<other.nOfshapes; i++)
        {
            this->shapes[i] = other.shapes[i];
        }

        // return *this;
    }

    //operator =
    Canvas& operator=(const Canvas &other){
        this->nOfshapes = other.nOfshapes;
        delete[] this->shapes;

        this->shapes = new Shape [other.nOfshapes];
        for(int i = 0; i<other.nOfshapes; i++)
        {
            this->shapes[i] = other.shapes[i];
        }

        return *this;
    }


  //addShape function

  void addShape (const Shape & other)
  {
    Shape *tempShapes = new Shape [this->nOfshapes + 1];
    for (int i = 0; i < this->nOfshapes; i++)
      {
	tempShapes[i] = this->shapes[i];
      }
    tempShapes[this->nOfshapes] = other;
    delete [] this->shapes;
    this->shapes = new Shape [++this->nOfshapes];
    for (int i = 0; i < this->nOfshapes; i++)
      {
	this->shapes[i] = tempShapes[i];
      }

    delete [] tempShapes;
    return;
  }


  //set
    void set_area_all(double percent){
        for(int i = 0; i<this->nOfshapes; i++)
        {
            this->shapes[i].set_area(this->shapes[i].get_area() * percent);
        }
    }
  //get




  //removeShapeById function

    void removeShapeById(char *id){
        Shape *tempShapes = new Shape [this->nOfshapes];
        int currentElement = 0;
        for(int i =0; i<this->nOfshapes; i++)
        {
            if(strcmp(this->shapes[i].get_id(), id)!=0)
            {
                tempShapes[currentElement++] = this->shapes[i];
            }
        }
        delete [] this->shapes;
        this->nOfshapes = currentElement;
        this->shapes = new Shape [this->nOfshapes];

        for(int i =0; i<this->nOfshapes; i++)
        {
           this->shapes[i] = tempShapes[i];
        }
        delete [] tempShapes;
    }


    //removeShapesByColor

    void removeShapesByColor(Color color){
        Shape *tempShapes = new Shape [this->nOfshapes];
        int currentElement = 0;
        for(int i =0; i<this->nOfshapes; i++)
        {
            if(this->shapes[i].get_color() != color)
            {
                tempShapes[currentElement++] = this->shapes[i];
            }
        }
        delete [] this->shapes;
        this->nOfshapes = currentElement;
        this->shapes = new Shape [this->nOfshapes];

        for(int i =0; i<this->nOfshapes; i++)
        {
           this->shapes[i] = tempShapes[i];
        }
        delete [] tempShapes;
    }


  //drawAll function

    void drawAll(){

    //   cout<<"drawAll "<<this->nOfshapes<<endl;
        for(int i = 0; i<this->nOfshapes; i++)
        {
            this->shapes[i].draw();
        }
        return;
    }

  //drawOnly function
    void drawOnly(Color color){
        // cout<<"drawOnly "<<this->nOfshapes<<endl;
        for(int i = 0; i<this->nOfshapes; i++){
            if(this->shapes[i].get_color() == color)
                this->shapes[i].draw();
        }
    }

  //totalArea funciton
    double totalArea(){
        double total = 0.0;
        for(int i = 0; i<this->nOfshapes; i++){
            total += this->shapes[i].get_area();
        }

        return total;
    }




    //getHalfCanvas
    Canvas getHalfCanvas(){
        Canvas tempCanvas;
        // Canvas tempCanvas(*this);
        tempCanvas = *this;
        tempCanvas.set_area_all(0.5);
        return tempCanvas;
    }

    //expandAll
    Canvas & expandAll (double percent){
        this->set_area_all(1 + percent);
        return *this;
    }
};


int
main ()
{

  int n;
  cin >> n;
  cout << "ADITION OF SHAPES IN THE CANVAS" << endl;
  Canvas canvas;

  for (int i = 0; i < n; i++)
    {
      char id[5];
      int color;
      double area;
      char description[100];

      cin >> id >> description >> color >> area;
      Shape s (id, description, (Color) color, area);
      canvas.addShape (s);
    }

  cout << "TESTING = FOR CLASS CANVAS" << endl;
  Canvas c;
  c = canvas;

  cout << "TESTING DRAW ALL" << endl;

  c.drawAll ();

  cout << "TESTING DRAW RED SHAPES" << endl;

  c.drawOnly (RED);

  cout << "TESTING TOTAL AREA" << endl;

  cout << c.totalArea () << endl;

  cout << "TESTING HALF CANVAS" << endl;
  Canvas reducedCanvas = c.getHalfCanvas ();
  cout << c.totalArea () << " " << reducedCanvas.totalArea () << endl;

  if (reducedCanvas.totalArea () == c.totalArea ())
    {
      cout <<
	"DO NOT CHANGE THE AREA OF THE OBJECT IN THE CURRENT CANVAS. JUST IN THE NEW CANVAS"
	<< endl;
    }

  cout << "TESTING EXPAND ALL" << endl;
  c.expandAll (0.10);
  cout << c.totalArea () << endl;

  cout << "TESTING REMOVE BY ID" << endl;
  c.removeShapeById ("A1");
  c.removeShapeById ("Z11");

  c.drawAll ();

  cout << "TESTING REMOVE BY COLOR" << endl;
  c.removeShapesByColor (RED);

  c.drawAll ();

  return 0;
}
