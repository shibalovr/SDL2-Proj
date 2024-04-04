#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point{
    public:
        float x;
        float y;
        // Operator overload +, -, += , -= , scale
        Point(){
            x = 0;
            y = 0;
        };
        Point(float x_, float y_) {
            x = x_;
            y = y_;
        }

        Point operator+(const Point& other) {
            return Point(x+other.x, y+other.y);
        }

        Point operator-(const Point& other) {
            return Point(x-other.x, y-other.y);
        }

        Point operator*(const float& scalar) {
            return Point(x*scalar, y*scalar);
        }

        friend Point operator+=(Point& p1, Point&p2) {
            p1.x += p2.x;
            p1.y += p2.y;
            return p1;
        }

        friend Point operator-=(Point& p1, Point&p2) {
            p1.x -= p2.x;
            p1.y -= p2.y;
            return p1;
        }

        void Log(std::string msg = "") {
            std::cout << msg << " (x y) = (" << this->x << " " << this->y << ")\n";
        }
};

#endif