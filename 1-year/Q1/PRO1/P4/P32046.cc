#include<iostream>
using namespace std;
int main(){
    int number_ini, numbers;
    cin >> number_ini;
    cout << "nombres que acaben igual que " << number_ini << ":" <<endl;
    int primer = number_ini % 10;
    number_ini = number_ini / 10;

    int segon = number_ini % 10;
    number_ini = number_ini / 10;

    int tercer = number_ini % 10;

    int contador = 0;
    while (cin >> numbers) {
        int aux = numbers;
        if (numbers % 10 == primer) {
            numbers = numbers / 10;
            if (numbers %  10 == segon) {
                numbers = numbers / 10;
                if (numbers % 10 == tercer) {
                    ++contador;
                    cout << aux << endl;
                }
            }
        }
    }
    cout << "total: " << contador << endl;
}
