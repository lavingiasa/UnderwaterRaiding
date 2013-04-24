#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

class Shape 
{
 public:
  virtual ~Shape() { }
  virtual double getArea() = 0;
  virtual double getPerimeter() = 0;
  virtual string getType() = 0;
};

class RightTriangle : public Shape 
{
 public:
  RightTriangle(double b, double h) : _b(b), _h(h) { }
  ~RightTriangle() { }
  double getArea() { return 0.5*_b*_h; }
  double getPerimeter() { return sqrt(_b*_b + _h*_h) + _h + _b; }
  string getType() { return "Right Triangle"; }
private:
  double _b, _h;
};

class Rectangle : public Shape
{
public:
    Rectangle(double b, double h) : _b(b), _h(h) { }
    ~Rectangle() { }
    double getArea() { return _b*_h; }
    double getPerimeter() { return _b+_b + _h+_h; }
    string getType() { return "Rectangle"; }
private:
    double _b, _h;
};

class Square : public Rectangle
{
public:
    Square(double l) : Rectangle(l,l) { }
    ~Square() { }
    //double getArea() { return _b*_h; }
    //double getPerimeter() { return _b+_b + _h+_h; }
    string getType() { return "Square"; }
};

class Circle : public Shape
{
public:
    Circle(double radius) : _r(radius){ }
    ~Circle() { }
    double getArea() { return _r*_r*3.14159; }
    double getPerimeter() { return 2*_r*3.14159; }
    string getType() { return "Circle"; }
private:
    double _r;
};
