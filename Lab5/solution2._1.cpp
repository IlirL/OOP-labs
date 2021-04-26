// your code here
#include<iostream>
using namespace std;

class Matrix
{
private:
  int rows;
  int columns;
  float *p;


public:
    Matrix ()
  {
    this->rows = 0;
    this->columns = 0;
    p = new float[this->rows * this->columns];
  }

  Matrix (const Matrix & other)
  {
    this->rows = other.rows;
    this->columns = other.columns;
    this->p = new float[this->rows * this->columns];
    for (int i = 0; i < this->rows; i++)
      {
	for (int j = 0; j < this->columns; j++)
	  {
	    this->p[i * this->rows + j] = other.p[i * this->rows + j];
	  }
      }
  }

  Matrix (int rows, int columns, float *p)
  {
    this->rows = rows;
    this->columns = columns;
    this->p = new float[this->rows * this->columns];
        for (int i = 0; i < this->rows; i++)
      {
    	for (int j = 0; j < this->columns; j++)
	  {
	    this->p[i * this->rows + j] = p[i * this->rows + j];
	  }
      }
  }
  //>>
  friend istream & operator>> (istream & is, Matrix & m)
  {
    delete[]m.p;
    is >> m.rows >> m.columns;
    m.p = new float[m.rows * m.columns];
    for (int i = 0; i < m.rows * m.columns; i++)
      {
	is >> m.p[i];
      }

    return is;
  }
  //<<
  friend ostream & operator<< (ostream & o, Matrix & m)
  {
    for (int i = 0; i < m.rows; i++)
      {

	for (int j = 0; j < m.columns; j++)
	  {
	    o << m.p[i * m.rows + j] << " ";
	  }
	  	o << endl;
      }

  }

  //+
  Matrix operator+ (const Matrix & m2)
  {
    float *tempArray = new float[this->rows * this->columns];
    for (int i = 0; i < this->rows; i++)
      {
	for (int j = 0; j < this->columns; j++)
	  {
	    tempArray[i * this->rows + j] =
	      this->p[i * this->rows + j] + m2.p[i * this->rows + j];
	  }
      }
     Matrix temp_matrix(this->rows, this->columns, tempArray);
     delete [] tempArray;
    //  cout<<temp_matrix;
     return temp_matrix;
  }

  Matrix operator+ (int integer)
  {
    float *tempArray = new float[this->rows * this->columns];
    for (int i = 0; i < this->rows; i++)
      {
	for (int j = 0; j < this->columns; j++)
	  {
	    tempArray[i * this->rows + j] =
	      this->p[i * this->rows + j] + integer;
	  }
      }
     Matrix temp_matrix(this->rows, this->columns, tempArray);
     delete [] tempArray;
    //  cout<<temp_matrix;
     return temp_matrix;
  }

  //*
   Matrix operator* (const Matrix & m2)
  {
    float *tempArray = new float[this->rows * this->columns];
    for (int i = 0; i < this->rows; i++)
      {
	for (int j = 0; j < this->columns; j++)
	  {
	    tempArray[i * this->rows + j] =
	      this->p[i * this->rows + j] * m2.p[i * this->rows + j];
	  }
      }
     Matrix temp_matrix(this->rows, this->columns, tempArray);
     delete [] tempArray;
    //  cout<<temp_matrix;
     return temp_matrix;
  }

  //-
    Matrix operator- (const Matrix & m2)
  {
    float *tempArray = new float[this->rows * this->columns];
    for (int i = 0; i < this->rows; i++)
      {
	for (int j = 0; j < this->columns; j++)
	  {
	    tempArray[i * this->rows + j] =
	      this->p[i * this->rows + j] - m2.p[i * this->rows + j];
	  }
      }
     Matrix temp_matrix(this->rows, this->columns, tempArray);
     delete [] tempArray;
    //  cout<<temp_matrix;
     return temp_matrix;
  }
  //=
  Matrix& operator= (const Matrix &other)
  {
      delete [] this->p;
      this->rows = other.rows;
    this->columns = other.columns;
    this->p = new float[this->rows * this->columns];
    for (int i = 0; i < this->rows; i++)
      {
	for (int j = 0; j < this->columns; j++)
	  {
	    this->p[i * this->rows + j] = other.p[i * this->rows + j];
	  }
      }

      return *this;
  }
};


int
main ()
{
  Matrix A, B, C;
  cin >> A >> B >> C;
   Matrix D = B * C;
   Matrix R = (A - D) + 2;
   cout << R;
}

