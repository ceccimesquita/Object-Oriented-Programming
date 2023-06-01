#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fn.hpp>
#include <math.h>

#include <limits>
#include <numbers>

using namespace std;
using namespace fn;

class Point2D{
public:
    double x;
    double y;
    string toString(){
        stringstream ss;
        ss << "(" << setprecision(2) << fixed << x  << ", " << y << ")";
        return ss.str();
    }
};

class Cals{
public:
    static double distance(Point2D p1, Point2D p2){
        return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    }
};

class Shape{
public:
    string name;

    Shape(string name){
        this->name = name;
    }

    string getName(){
        return name;
    }

    virtual bool inside(Point2D p) =0;

    virtual double getArea() =0;

    virtual double getPerimeter() =0 ;

    virtual string toString()=0;
};

class Circle : public Shape {
    Point2D center;
    double radius;

public:
    Circle(Point2D center, double radius) : Shape("Circ"){
        this->center = center;
        this->radius = radius;
    }

    string getName(){
        return this->name;
    }

    bool inside(Point2D p){
        return Cals::distance(center, p) <= radius;
    }

    double getArea(){
        return M_PI * radius * radius;
    }

    double getPerimeter(){
        return 2 * M_PI * radius;
    }

    string toString(){
        stringstream ss;
        ss << getName() << ": C=" << center.toString() << fixed << setprecision(2) << ", R=" << radius << fixed << setprecision(2) ;
        return ss.str();
    }
};


class Rectangle : public Shape {
    Point2D topLeft;
    Point2D bottomRight;
public:
    Rectangle(Point2D topLeft, Point2D bottomRight) : Shape("Rect"){
        this->topLeft = topLeft;
        this->bottomRight = bottomRight;
    }
    
    string getName(){
        return this->name;
    }
    bool inside (Point2D p){
        return p.x >= topLeft.x && p.x <= bottomRight.x && p.y <= topLeft.y && p.y >= bottomRight.y;
    }

    double getArea(){
        return (topLeft.x - bottomRight.x) * (topLeft.y - bottomRight.y);
    }

    double getPerimeter(){
        return 2 * ((topLeft.x - bottomRight.x) + (topLeft.y - bottomRight.y));
    }

    string toString(){
        stringstream ss;
        ss << getName() << ": P1=" << topLeft.toString() << " P2=" << bottomRight.toString();
        return ss.str();
    }

};

// std::ostream& operator<<(std::ostream& os, Rectangle& p) {
//     return os << p.toString();
// }

// std::ostream& operator<<(std::ostream& os, Circle& p) {
//     return os << p.toString();
// }

std::ostream& operator<<(std::ostream& os, Shape& p) {
    return os << p.toString();
}

int main() {
    std::vector<std::shared_ptr<Shape>> shapes;

    while (true) {
        auto line = fn::input();
        auto args =  fn::split(line, ' ');
        fn::write("$" + line);

        if      (args[0] == "end")  { 
            break;                                  
        }
        else if (args[0] == "show") { 
            for (auto shape : shapes) {
                fn::write(shape->toString());
            }
        }
        else if (args[0] == "circle") { 
            auto x = +args[1];
            auto y = +args[2]; 
            auto r = +args[3];
            shapes.push_back(std::make_shared<Circle>(Point2D{x, y}, r));
        }
        else if (args[0] == "rect") { 
            auto p1 = Point2D{+args[1], +args[2]};
            auto p2 = Point2D{+args[3], +args[4]};
            shapes.push_back(std::make_shared<Rectangle>(p1, p2));
        }
        else if (args[0] == "info") {
            for (auto shape : shapes) {
                printf(("%s : A=%.2f P=%.2f\n"), 
                shape->getName(), shape->getArea(), shape->getPerimeter());
            }
        }
        else {
            fn::write("fail: invalid command");
        }
    }
}

