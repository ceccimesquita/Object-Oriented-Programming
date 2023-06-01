#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fn.hpp>
#include <math.h>

using namespace std;
using namespace fn;

class Point2D{
public:
    double x;
    double y;
    string toString(){
        stringstream ss;
        ss << "(" << setprecision(2) << fixed << to_string(x) << ", " << to_string(y) << ")";
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
        ss << getName() << " " << center.toString() << ", " << setprecision(2) << fixed << to_string(radius);
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
        ss << getName() << " " << topLeft.toString() << ", " << bottomRight.toString();
        return ss.str();
    }

};

std::ostream& operator<<(std::ostream& os, Rectangle& p) {
    return os << p.toString();
}

std::ostream& operator<<(std::ostream& os, Circle& p) {
    return os << p.toString();
}

std::ostream& operator<<(std::ostream& os, Shape& p) {
    return os << p.toString();
}

int main() {
    vector<shared_ptr<Shape>> shapes;
    while(true) {
        auto line = fn::input();
        auto args = fn::split(line, ' ');
        fn::write("$" + line);
        
        if(args[0] ==  "end" ){
            break;
        }
        else if(args[0] == "Circle"){
            auto x = number(args[1]);
            auto y = number(args[2]);
            auto r = number(args[3]);

            shapes.push_back(make_shared<Circle>(Point2D{x, y}, r));
        }
        else if(args[0] ==  "show"){
            write(join(shapes, "\n"));
        }
        else if(args[0] == "rect"){
            auto p1 = Point2D{number(args[1]), number(args[2])};
            auto p2 = Point2D{number(args[3]), number(args[4])};
            shapes.push_back(make_shared<Rectangle>(p1, p2));
        }
        else if(args[0] == "info"){
            for(auto shape : shapes){
                cout << shape->getName() << ":" << fixed <<  " A=" << setprecision(2) << shape->getArea() << " P=" << setprecision(2) << shape->getPerimeter() << endl;
            }

        }
    }
}





