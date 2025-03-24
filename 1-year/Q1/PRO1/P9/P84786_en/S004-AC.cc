#include <typeinfo>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
struct Point {
  double x, y;
};

struct Circle {
            Point center;
            double radius;
        };
//esta funcion se encarga de calcular la distancia
//entre dos puntos
//Pre: dos structs que contienen 'x' y 'y'
//Post: un double con la distancia cartesiana
double dist(const Point& a, const Point& b) {
    double x3 = pow((b.x - a.x), 2);
    double y3 = pow((b.y - a.y), 2);
    double d = sqrt(x3 + y3);
    return d;
}
//esta accion se encarga de mover un punto
//segun otro punto sumandolos
//Pre: dos structs que contienen un punto cada uno
void move(Point& p1, const Point& p2){
  p1.x = p1.x + p2.x;
  p1.y = p1.y + p2.y;
}
//esta accion mueve el radio de un circulo
//segun un valor dado
//Pre: un struct de un circulo y un double
//con el valor a multiplicar
void scale(Circle& c, double sca){
  c.radius = c.radius * sca;
}
//esta accion mueve el centro de un circulo
//segun otro punto
//Pre: un struct de un circulo y un punto
//que indica cuanto mover
void move(Circle& c, const Point& p){
  move(c.center, p);
}
//esta funcion devuelve true si un punto se encuentra
//dentro de un circulo
//Pre: un struct de un punto y de un circulo
//Post: true si esta dentro false si esta fuera
bool is_inside(const Point& p, const Circle& c) {
  double distancia = dist(p, c.center);
  if (distancia >= c.radius) {return false;}
  else {return true;}
}


