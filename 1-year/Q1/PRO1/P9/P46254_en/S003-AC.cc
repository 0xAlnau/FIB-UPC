#include <typeinfo>
#include <iostream>
#include <cmath>
using namespace std;

/*
struct Punt {
    double x, y;
};*/

struct Point {
            double x, y;
        };

double dist(const Point& a, const Point& b) {
    double x3 = pow((b.x - a.x), 2);
    double y3 = pow((b.y - a.y), 2);
    double d = sqrt(x3 + y3);
    return d;
}

