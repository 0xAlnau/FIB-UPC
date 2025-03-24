#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
using namespace std;

struct Student {
    int idn;
    string name;
    double mark;
    bool repeater;
};
//esta accion se encargara de calcular la nota
//mas alta, la mas baja y el promedio de un grupo
//de estudiantes n. Sus notas no se cuentan si
//el estudiante no se prensenta o si es repetidor
void information(const vector<Student>& es, double& min, double& max, double& avg) {
    int size = es.size();
    max = -1;
    min = 11;
    avg = 0;
    int size2 = size;
    for (int i = 0; i < size; ++i) {
        if (es[i].mark == -1) { --size2;}
        else if (es[i].repeater) { --size2;}
        else {
            if (es[i].mark > max) max = es[i].mark;
            if (es[i].mark < min) min = es[i].mark;
            avg = avg + es[i].mark;
        }
    }
    avg = avg / size2;
    if (max == -1 and min == 11) {
        max = -1;
        min = -1;
        avg = -1;
    }
    else if (size == 0) {
        max = 0;
        min = 0;
        avg = 0;
        }

}




